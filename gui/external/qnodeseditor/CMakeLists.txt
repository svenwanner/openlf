cmake_minimum_required(VERSION 2.8.11)

project(qnodeseditor)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

#Find all files of the procject in the related directory / subdirectories (necessary for linking in the executable)
file(GLOB srcs *.cpp src/*.cpp)
file(GLOB hdrs include/*.h)
file(GLOB Resources resources/*.qrc)

add_library (${PROJECT_NAME} ${OPENLF_BUILD_TYPE} ${srcs} ${hdrs})
target_include_directories(${PROJECT_NAME} PUBLIC ${Qt5Network_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} ${OPENLF_LIBRARIES})

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)
install(
    FILES ${hdrs}
    DESTINATION include
)
