cmake_minimum_required (VERSION 2.6)
project(fuckthis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(HDF5 REQUIRED CXX)
find_package(Vigra REQUIRED )
find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS filesystem system REQUIRED)

include_directories(${OPENCV_INCLUDE_DIR})
include_directories(${HDF5_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${VIGRA_INCLUDE_DIR})
add_definitions(${HDF5_CPPFLAGS})

include_directories(include)
include_directories(include/openlf)
include_directories(include/openlf/components)
include_directories(include/openlf/workflows)
include_directories(include/openlf/operators)

add_subdirectory(src/lib/components)
add_subdirectory(src/lib/workflows)
add_subdirectory(src/lib/operators)

add_executable(teststuff src/bin/test.cpp)
add_executable(teststuff2 src/bin/test2.cpp)

target_link_libraries(teststuff vigraimpex openlf_workflows  openlf_components  openlf_operators DSPatch clif cliini  clif_vigra ${Boost_LIBRARIES} ${HDF5_CPP_LIBRARY} ${HDF5_LIBRARIES} ${OpenCV_LIBRARIES} ${VIGRA_IMPEX_LIBRARY})
target_link_libraries(teststuff2 vigraimpex openlf_operators openlf_workflows openlf_components clif cliini DSPatch clif_vigra ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${OpenCV_LIBRARIES} ${VIGRA_IMPEX_LIBRARY})

