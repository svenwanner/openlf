cmake_minimum_required (VERSION 2.6)
project(fuckthis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#find_package(HDF5 REQUIRED)

find_package(HDF5 REQUIRED CXX)
find_package(Boost COMPONENTS filesystem system REQUIRED)

add_executable(testthings fuckthis/test.cpp)
target_link_libraries(testthings clif cliini DSPatch clif_vigra ${HDF5_CPP_LIBRARY} ${HDF5_LIBRARIES} ${Boost_LIBRARIES})

find_package(HDF5 REQUIRED )
find_package(Vigra REQUIRED )
find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS filesystem system REQUIRED)



INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIR})
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${VIGRA_INCLUDE_DIR} )
ADD_DEFINITIONS(${HDF5_CPPFLAGS})

add_executable(testthings2 fuckthis/test.cpp)
target_link_libraries(testthings2 clif cliini DSPatch clif_vigra ${HDF5_CPP_LIBRARY} ${HDF5_LIBRARIES} ${Boost_LIBRARIES})

include_directories(include)
include_directories(include/openlf)
include_directories(include/openlf/components)
include_directories(include/openlf/workflows)
include_directories(include/openlf/operators)

add_subdirectory(src/lib/components)
add_subdirectory(src/lib/workflows)
add_subdirectory(src/lib/operators)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -O0")

add_executable(testthings4 fuckthis/test.cpp)
target_link_libraries(testthings4 clif cliini DSPatch clif_vigra ${HDF5_CPP_LIBRARY} ${HDF5_LIBRARIES} ${Boost_LIBRARIES})


add_executable(teststuff src/bin/test.cpp)
add_executable(teststuff2 src/bin/test2.cpp)

add_executable(testthings3 fuckthis/test.cpp)
target_link_libraries(testthings3 clif cliini DSPatch clif_vigra ${HDF5_CPP_LIBRARY} ${HDF5_LIBRARIES} ${Boost_LIBRARIES})

target_link_libraries(teststuff DSPatch clif cliini  clif_vigra ${Boost_LIBRARIES} ${HDF5_CPP_LIBRARY} ${HDF5_LIBRARIES} ${OpenCV_LIBRARIES} ${VIGRA_IMPEX_LIBRARY})
#target_link_libraries(teststuff DSPatch cliini clif clif_vigra ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${OpenCV_LIBRARIES} ${VIGRA_IMPEX_LIBRARY})
target_link_libraries(teststuff2 openlf_operators openlf_workflows openlf_components clif cliini DSPatch clif_vigra ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${OpenCV_LIBRARIES} ${VIGRA_IMPEX_LIBRARY})

