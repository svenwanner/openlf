cmake_minimum_required (VERSION 2.8)
project(OpenLF)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  # using Clang
  message("use clang")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  # using GCC
  message("use gcc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -g -O0 -fopenmp")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3 -fPIC")
  set(OPENLF_LIBRARIES dl)
  set(OPENLF_BUILD_TYPE "SHARED")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  message("use msvc")
  set(OPENLF_COMPILER_MSVC true)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Ox /openmp /D NOMINMAX")
  #set(CLIF_INCLUDE_DIR "D:/libs/include" CACHE PATH "Include path for external libraries")
  include_directories(${LIBS_INCLUDE_DIR})
  #set (EXTRA_LIBS ${EXTRA_LIBS} "D:/libs/include")  #see parameter list here https://cmake.org/pipermail/cmake/2006-July/010189.html
  add_definitions(-DOPENLF_COMPILER_MSVC)  
  include_directories(external/dirent)
  set(OPENLF_BUILD_TYPE)
endif()

find_package(HDF5 REQUIRED CXX)
find_package(Vigra REQUIRED )
find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS filesystem system REQUIRED)


include(ExternalProject)


# 
######################################################
## force build add configure phase                ####
######################################################
function(build_external_project target prefix url) #FOLLOWING ARGUMENTS are the CMAKE_ARGS of ExternalProject_Add

    set(trigger_build_dir ${CMAKE_BINARY_DIR}/force_${target})

    #mktemp dir in build tree
    file(MAKE_DIRECTORY ${trigger_build_dir} ${trigger_build_dir}/build)

    #generate false dependency project
    set(CMAKE_LIST_CONTENT "
    cmake_minimum_required(VERSION 2.8)

    include(ExternalProject)
    ExternalProject_add(${target}
            PREFIX ${prefix}/${target}
            GIT_REPOSITORY ${url}
            CMAKE_ARGS ${ARGN}
            INSTALL_COMMAND \"\"
            )

            add_custom_target(trigger_${target})
            add_dependencies(trigger_${target} ${target})")

    file(WRITE ${trigger_build_dir}/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

    execute_process(COMMAND ${CMAKE_COMMAND} ..
        WORKING_DIRECTORY ${trigger_build_dir}/build
        )
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${trigger_build_dir}/build
        )

endfunction()

######################################################
## clif                                             ##
######################################################
find_package(clif QUIET)
if (NOT clif_FOUND)
  option(OPENLF_INTERNAL_CLIF "internal clif download and build" ON)
else()
  option(OPENLF_INTERNAL_CLIF "internal clif download and build" OFF)
endif()

if (OPENLF_INTERNAL_CLIF)
  build_external_project(clif
                      external/clif
                      https://github.com/hendriksiedelmann/clif.git
                      )
list(APPEND CMAKE_PREFIX_PATH force_clif/build/external/clif/clif/src/clif-buil)
endif()
find_package(clif REQUIRED)
message("clif libraries: ${CLIF_LIBRARIES}")
message("clif lib dirs: ${CLIF_LIBRARY_DIRS}")

######################################################
## add clifview as external project (if required?)  ##
######################################################
#ExternalProject_Add(clifview
#                    PREFIX ${clifview}
#                    GIT_REPOSITORY https://github.com/hendriksiedelmann/clifview.git
#                    INSTALL_DIR ${CMAKE_INSTALL_PREFIX})


add_definitions(${HDF5_CPPFLAGS})

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${HDF5_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${Vigra_INCLUDE_DIRS})
include_directories(${CLIF_INCLUDE_DIRS})
message(${CLIF_INCLUDE_DIRS})
link_directories(${CLIF_LIBRARY_DIRS})
#FIXME needed for boost under windows - whats the proper way? Boost_LIBRARY_DIR?
link_directories($ENV{Path})

list(APPEND OPENLF_LIBRARIES ${CLIF_LIBRARIES})

add_subdirectory(external/gml_parser)
include_directories(external/gml_parser)

add_subdirectory(external/dspatch)
list(APPEND OPENLF_LIBRARIES DSPatch)

include_directories(external/dspatch/include)
include_directories(external/dspatch/include/dspatch)

include_directories(include)
include_directories(include/openlf)
#include_directories(include/openlf/components)
#include_directories(include/openlf/workflows)
#include_directories(include/openlf/operators)

#add_subdirectory(src/lib/operators)
#add_subdirectory(src/lib/workflows)
#add_subdirectory(src/lib/components)

add_subdirectory(src/lib)

add_subdirectory(components)

add_subdirectory(gui)


add_executable(openlf-bin src/bin/openlf.cpp)
set_target_properties(openlf-bin PROPERTIES OUTPUT_NAME openlf)
target_link_libraries(openlf-bin ${OPENLF_LIBRARIES})

#add_executable(teststuff src/bin/test.cpp)
#add_executable(teststuff2 src/bin/test2.cpp)
#add_executable(teststuff3 src/bin/test3.cpp)

#target_link_libraries(teststuff  ${OPENLF_LIBRARIES})
#target_link_libraries(teststuff2 ${OPENLF_LIBRARIES})
#target_link_libraries(teststuff3 ${OPENLF_LIBRARIES})
