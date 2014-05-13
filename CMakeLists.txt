#--------------------------------------------------------------
# default build-type (release)
# (the next lines must be called bevore project(opengm2))
#--------------------------------------------------------------
IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ELSE()
   SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ENDIF()

#-------------------------------------------------------------

cmake_minimum_required (VERSION 2.8.3)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
project (OpenLF)

# The version number.
set (OpenLF_VERSION_MAJOR 1)
set (OpenLF_VERSION_MINOR 0)



#--------------------------------------------------------------
# options
#--------------------------------------------------------------
OPTION(BUILD_WORKFLOWS "Build workflows" ON)
OPTION(BUILD_TEST "Build tests" ON)
OPTION(WITH_OPENMP "Include OpenMP" OFF)
OPTION(WITH_OPENGM "Include OpenGM" OFF)

file(GLOB_RECURSE SOURCES src/*.cpp)
include_directories(./src/)
file(GLOB_RECURSE headers ./include/*.hpp)
include_directories(./includes/)

#--------------------------------------------------------------
# warning level
#-------------------------------------------------------------- 
SET(WARNINGLEVEL "3" CACHE STRING "selected level for compiler warning from  0 (sloppy) to 4 (sadistic)") 
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
   # no warnings
   if(WARNINGLEVEL STREQUAL "0" )
     message(STATUS "--------------------------------------------------------------------------")
     message(STATUS "WARNING: Compiler warnings are very sloppy -> increase CMake-WARNINGLEVEL")
     message(STATUS "--------------------------------------------------------------------------")
   endif()
   # with warning
   if(WARNINGLEVEL STREQUAL "1" )
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
   endif()
   # PEDANTIC -> a lot of warnings
   if(WARNINGLEVEL STREQUAL "2" )
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic -Wno-long-long ")
   endif() 
   # VERY PEDANTIC -> very lot of warnings
   if(WARNINGLEVEL STREQUAL "3" )
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic -Wno-long-long -Wextra")
   endif()
   # SADISTIC -> all warnings become errors
   if(WARNINGLEVEL STREQUAL "4" )
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic -Wno-long-long -Wextra -Werror")
   endif()
elseif(MSVC)
   add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif()




set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

Message(CMAKE_RUNTIME_OUTPUT_DIRECTORY " : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
Message(CMAKE_LIBRARY_OUTPUT_DIRECTORY " : ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# configure a header file to pass some of the CMake settings
# to the source code
#find_package(OpenGL)
find_package(HDF5 REQUIRED )
find_package(VIGRA REQUIRED )
#find_package(OpenCV)
#find_package(Boost REQUIRED ) 
find_package(Boost
             #1.55.0
             COMPONENTS filesystem
                        system
                        #log
                        #log_setup
                        #program_options
						#thread
             REQUIRED)
			 
add_definitions(${HDF5_CPPFLAGS})

find_library( CPPUNIT_LIBRARY NAMES cppunit cppunit_dll
  PATHS   ${FOO_PREFIX}/lib
  /usr/lib
  /usr/lib64
  /usr/local/lib
  /usr/local/lib64
  PATH_SUFFIXES release )

MESSAGE(STATUS " libraries : ${CPPUNIT_LIBRARY}")
MESSAGE(STATUS " boost libraries : ${Boost_LIBRARIES_DIR} ${Boost_INCLUDE_DIR}")
Message(STATUS " vigra : ${VIGRA_IMPEX_LIBRARY}")
Message(STATUS " hdf5 : ${HDF5_LIBRARIES}")
#Message(STATUS " SOURCES : ${SOURCES}")

INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIR})
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${VIGRA_INCLUDE_DIR} )
ADD_DEFINITIONS(${HDF5_CPPFLAGS})

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_SOURCE_DIR}")

ADD_LIBRARY(libopenlf SHARED ${SOURCES} )
 

#-------------------------------------------------------------
# OpenMP
#-------------------------------------------------------------
if(WITH_OPENMP)
  FIND_PACKAGE(OpenMP REQUIRED)
  message(STATUS "build with OpenMP") 
  #SET(OPENMP_INCLUDE_DIR "" CACHE STRING "OpenMP include dir")
  #include_directories(${OPENMP_INCLUDE_DIR})
  add_definitions(-DWITH_OPENMP)
  # conditional include openmp
  if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  endif()
  
else()
  message(STATUS "build without openMP -> multithreaded options disabled")
endif(WITH_OPENMP)


#-----------------------------------------------------
# OpenGM
#-----------------------------------------------------
if(WITH_OPENGM)
  FIND_PACKAGE(OPENGM)
  if(OPENMP_FOUND)
    message("OPENMP FOUND")
    INCLUDE_DIRECTORIES( ${OPENGM_INCLUDE_DIR} )
  else()
    message("OPENMP NOT FOUND")
  endif()
else()
   message(STATUS "build without OpenGM")
endif(WITH_OPENGM)

execute_process(COMMAND ${CMAKE_CURRENT_LIST_DIR}/configure)

#---------------------------------------------------------------
# OpenLF Lib
#--------------------------------------------------------------

add_custom_target(
  Configure
  COMMAND ${CMAKE_CURRENT_LIST_DIR}/configure ${CMAKE_CURRENT_LIST_FILE}
  )
target_link_libraries(libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY})

#--------------------------------------------------------------
# WORKFLOWS 
#-------------------------------------------------------------- 
if(BUILD_WORKFLOWS)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin/workflows)
  add_subdirectory(workflows)
endif()

#--------------------------------------------------------------
# TESTS 
#-------------------------------------------------------------- 
if(BUILD_TEST)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin/tests)
  add_subdirectory(tests)
  enable_testing()
endif()

