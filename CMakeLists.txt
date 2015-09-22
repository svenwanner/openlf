
cmake_minimum_required (VERSION 2.6)
project (OpenLF)

find_package(HDF5 REQUIRED )
find_package(Vigra REQUIRED )
find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS filesystem system REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIR})
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${VIGRA_INCLUDE_DIR} )
ADD_DEFINITIONS(${HDF5_CPPFLAGS})


include_directories(include)
include_directories(include/openlf)
include_directories(include/openlf/components)
include_directories(include/openlf/workflows)
include_directories(include/openlf/operators)

add_subdirectory(src/lib/components)
add_subdirectory(src/lib/workflows)
add_subdirectory(src/lib/operators)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -O0")
add_executable(teststuff src/bin/test.cpp)
add_executable(teststuff2 src/bin/test2.cpp)
target_link_libraries(teststuff openlf_operators openlf_workflows openlf_components DSPatch clif_vigra ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${OpenCV_LIBRARIES} ${VIGRA_IMPEX_LIBRARY})
target_link_libraries(teststuff2 openlf_operators openlf_workflows openlf_components clif cliini DSPatch clif_vigra ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${OpenCV_LIBRARIES} ${VIGRA_IMPEX_LIBRARY})


