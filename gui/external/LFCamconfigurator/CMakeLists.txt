cmake_minimum_required(VERSION 2.8.11)

project(LFCamconfigurator)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)

add_definitions(${Qt5Widgets_DEFINITIONS})

#Find all files of the procject in the related directory / subdirectories (necessary for linking in the executable)
file(GLOB srcs *.cpp src/*.cpp)
file(GLOB hdrs include/*.h)
file(GLOB Resources img/*.qrc)

#QT5_ADD_RESOURCES(ResourceSources ${Resources})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc /EHsc")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

add_library (${PROJECT_NAME} ${OPENLF_BUILD_TYPE} ${srcs} ${hdrs})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)
install(
    FILES ${hdrs}
    DESTINATION include
)
