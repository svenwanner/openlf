cmake_minimum_required(VERSION 2.8.11)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
SET(Boost_USE_STATIC_LIBS ON)

#Defines Project name which also becomes the executable name
project(DSPatch_Example)

find_package(Boost REQUIRED COMPONENTS filesystem system thread REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Vigra REQUIRED)
find_package(OpenCV REQUIRED)

#Find all files of the procject in the related directory / subdirectories (necessary for linking in the executable)
file(GLOB srcs *.cpp src/*.cpp components/*.cpp gui/src/*.cpp)
file(GLOB hdrs *.h includes/*.h components/*.h circuits/*.h gui/includes/*.h)
file(GLOB Resources gui/data/*.qrc)

QT5_ADD_RESOURCES(ResourceSources ${Resources})

#Add all directories and subdirectories of your project
include_directories(
    ${CMAKE_SOURCE_DIR}/includes
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/circuits
	${CMAKE_SOURCE_DIR}/components
    ${CMAKE_SOURCE_DIR}/gui/includes
	${CMAKE_SOURCE_DIR}/gui/src
	${CMAKE_SOURCE_DIR}/gui/forms
    ${CMAKE_CURRENT_SOURCE_DIR}
	${Qt5Widgets_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	)

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})	

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

################################################################################
######################## WINDOWS ###############################################
################################################################################
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")# the short system name, e.g. "Linux", "FreeBSD" or "Windows"
	MESSAGE( "INFO: WINDOWS BUILD" )
#Set default include directory for all dependent library headers
	set(LIBS_INCLUDE_DIR "D:/libs/include" CACHE PATH "Include path for external libraries")
	include_directories(${LIBS_INCLUDE_DIR})
#Set default include directory for all dependent libraries
	set(LIBS_LIB_DIR "D:/libs/lib" CACHE PATH "Lib path for external libraries")
	link_directories(${LIBS_LIB_DIR})
#Define output target and link dependencies
	add_executable( ${PROJECT_NAME} ${srcs} ${hdrs} ${ResourceSources} ${calculator_CONFIG} )
	target_link_libraries(${PROJECT_NAME} DSPatch vigraimpex Qt5::Widgets Qt5::Gui Qt5::Core ${OpenCV_LIBS})

endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

################################################################################
######################## Linux #################################################
################################################################################
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message( "INFO: LINUX BUILD" )
#Set default include directory for all dependent library headers	
	set(LIBS_INCLUDE_DIR "/usr/local/include" CACHE PATH "Include path for external libraries")
	include_directories(${LIBS_INCLUDE_DIR})
#Set default include directory for all dependent libraries
	set(LIBS_LIB_DIR "/usr/local/lib" CACHE PATH "Lib path for external libraries")
	link_directories(${LIBS_LIB_DIR})
#Define output target and link dependencies
	add_executable( ${PROJECT_NAME} ${srcs} ${hdrs} ${ResourceSources})
	target_link_libraries(${PROJECT_NAME} ${Vigra_LIBS} DSPatch vigraimpex Qt5::Widgets Qt5::Gui Qt5::Core)
	
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

################################################################################
################################################################################
################################################################################
