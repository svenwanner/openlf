cmake_minimum_required(VERSION 2.8.11)

project(qnodeseditor)

find_package(Qt5Widgets REQUIRED)

#Find all files of the procject in the related directory / subdirectories (necessary for linking in the executable)
file(GLOB srcs *.cpp src/*.cpp)
file(GLOB hdrs include/*.h)

add_library (${PROJECT_NAME} ${srcs} ${hdrs})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)
install(
    FILES ${hdrs}
    DESTINATION include
)