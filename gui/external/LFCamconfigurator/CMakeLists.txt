cmake_minimum_required(VERSION 2.8.11)

project(LFCamconfigurator)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)

add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(-DCLIF_BUILD_QT)

#Find all files of the procject in the related directory / subdirectories (necessary for linking in the executable)
file(GLOB srcs *.cpp src/*.cpp)
file(GLOB hdrs include/*.h)
file(GLOB Resources img/*.qrc)

#QT5_ADD_RESOURCES(ResourceSources ${Resources})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc /EHsc")
	qt5_wrap_ui(hdrs src/lfcamconfigurator_windows.ui)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
   qt5_wrap_ui(hdrs src/lfcamconfigurator_linux.ui)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")   
   qt5_wrap_ui(hdrs src/lfcamconfigurator_linux.ui)
   set(CMAKE_MACOSX_RPATH 1)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")



#  list(APPEND LINK_LIBRARIES ${Qt5Widgets_LIBRARIES})
#  list(APPEND INCLUDE_DIRS ${Qt5Widgets_INCLUDE_DIRS})
#  list(APPEND LIBRARY_DIRS ${Qt5Widgets_LIBRARY_DIRS})


#set(Boost_USE_STATIC_LIBS        ON)

add_library (${PROJECT_NAME} ${OPENLF_BUILD_TYPE} ${srcs} ${hdrs})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES} ${Boost_LIBRARIES})

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)
install(
    FILES ${hdrs}
    DESTINATION include
)
