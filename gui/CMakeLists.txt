cmake_minimum_required(VERSION 2.8.11)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#SET(Boost_USE_STATIC_LIBS ON)

#Defines Project name which also becomes the executable name
project(LF_Toolbox)

#find_package(Boost REQUIRED COMPONENTS system filesystem serialization program_options regex thread date_time REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Vigra REQUIRED)
find_package(OpenCV REQUIRED)

#Find all files of the procject in the related directory / subdirectories (necessary for linking in the executable)
file(GLOB srcs src/*.cpp)
file(GLOB hdrs include/*.h)
file(GLOB Resources resources/*.qrc)

QT5_ADD_RESOURCES(ResourceSources ${Resources})

#Add all directories and subdirectories of your project
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${Qt5Widgets_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
	)

link_directories(${Boost_LIBRARY_DIRS})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_subdirectory (external/qnodeseditor)
add_subdirectory (external/LFCamconfigurator)

include_directories(external)

qt5_wrap_ui(hdrs src/toolbox_ui.ui)

################################################################################
######################## WINDOWS ###############################################
################################################################################
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")# the short system name, e.g. "Linux", "FreeBSD" or "Windows"
	MESSAGE(STATUS "INFO: WINDOWS BUILD" )

#Define output target and link dependencies
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc /EHsc")
	add_executable( ${PROJECT_NAME} ${srcs} ${hdrs} ${ResourceSources} )
	message("openlf libs: ${OPENLF_LIBRARIES}")
	target_link_libraries(${PROJECT_NAME} ${OPENLF_LIBRARIES} Qt5::Widgets Qt5::Gui Qt5::Core Qt5::Network qnodeseditor LFCamconfigurator)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

################################################################################
######################## Linux #################################################
################################################################################
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message(STATUS "INFO: LINUX BUILD" )
#Set default include directory for all dependent library headers	
	set(LIBS_INCLUDE_DIR "/usr/local/include" CACHE PATH "Include path for external libraries")
	include_directories(${LIBS_INCLUDE_DIR})
#Set default include directory for all dependent libraries
	set(LIBS_LIB_DIR "/usr/local/lib" CACHE PATH "Lib path for external libraries")
	link_directories(${LIBS_LIB_DIR})
#Define output target and link dependencies
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	add_executable( ${PROJECT_NAME} ${srcs} ${hdrs} ${ResourceSources})
	target_link_libraries(${PROJECT_NAME} ${OPENLF_LIBRARIES} Qt5::Widgets Qt5::Gui Qt5::Core Qt5::Network qnodeseditor LFCamconfigurator)
	
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

################################################################################
################################################################################
################################################################################
