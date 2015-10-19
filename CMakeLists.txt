cmake_minimum_required (VERSION 2.8)
project(OpenLF)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  # using Clang
  message("use clang")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  # using GCC
  message("use gcc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O3 -fopenmp")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  message("use msvc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Ox /openmp")
  #set(CLIF_INCLUDE_DIR "D:/libs/include" CACHE PATH "Include path for external libraries")
  include_directories(${LIBS_INCLUDE_DIR})
  #set (EXTRA_LIBS ${EXTRA_LIBS} "D:/libs/include")  #see parameter list here https://cmake.org/pipermail/cmake/2006-July/010189.html
  add_definitions(-DOPENLF_COMPILER_MSVC)
endif()

find_package(HDF5 REQUIRED CXX)
find_package(Vigra REQUIRED )
find_package(OpenCV REQUIRED)
find_package(clif REQUIRED)
find_package(Boost COMPONENTS filesystem system REQUIRED)

add_definitions(${HDF5_CPPFLAGS})

include_directories(${OPENCV_INCLUDE_DIR})
include_directories(${HDF5_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${VIGRA_INCLUDE_DIR})
include_directories(${CLIF_INCLUDE_DIRS})

link_directories(${CLIF_LIBRARY_DIRS})
#FIXME needed for boost under windows - whats the proper way? Boost_LIBRARY_DIR?
link_directories($ENV{Path})

add_subdirectory(external/gml_parser)
include_directories(external/gml_parser)

add_subdirectory(external/dspatch)
include_directories(external/dspatch/include)
include_directories(external/dspatch/include/dspatch)

include_directories(include)
include_directories(include/openlf)
include_directories(include/openlf/components)
include_directories(include/openlf/workflows)
include_directories(include/openlf/operators)

add_subdirectory(src/lib/components)
add_subdirectory(src/lib/workflows)
add_subdirectory(src/lib/operators)

add_subdirectory(gui)

add_executable(teststuff src/bin/test.cpp)
add_executable(teststuff2 src/bin/test2.cpp)
add_executable(teststuff3 src/bin/test3.cpp)

target_link_libraries(teststuff  vigraimpex DSPatch ${CLIF_LIBRARIES} ${Boost_LIBRARIES} ${HDF5_CPP_LIBRARY} ${HDF5_LIBRARIES} ${OpenCV_LIBRARIES} ${VIGRA_IMPEX_LIBRARY} openlf_workflows  openlf_components  openlf_operators)
target_link_libraries(teststuff2 vigraimpex DSPatch ${CLIF_LIBRARIES} ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${OpenCV_LIBRARIES} ${VIGRA_IMPEX_LIBRARY} openlf_workflows  openlf_components  openlf_operators)
target_link_libraries(teststuff3 vigraimpex DSPatch ${CLIF_LIBRARIES} ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${OpenCV_LIBRARIES} ${VIGRA_IMPEX_LIBRARY} openlf_operators openlf_workflows openlf_components)
