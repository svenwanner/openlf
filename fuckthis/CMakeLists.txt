cmake_minimum_required (VERSION 2.6)
project(fuckthis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#find_package(HDF5 REQUIRED)

find_package(HDF5 REQUIRED CXX)
find_package(Boost COMPONENTS filesystem system REQUIRED)

add_executable(testthings test.cpp)

target_link_libraries(testthings  clif cliini DSPatch clif_vigra ${HDF5_CPP_LIBRARY} ${HDF5_LIBRARIES} ${Boost_LIBRARIES})
