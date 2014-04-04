cmake_minimum_required (VERSION 2.6)
project (OpenLF)

# The version number.
set (OpenLF_VERSION_MAJOR 1)
set (OpenLF_VERSION_MINOR 0)

include_directories(./src/)
include_directories(./includes/)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/test_release)

# configure a header file to pass some of the CMake settings
# to the source code
find_package(OpenGL)
find_package(HDF5)
find_package(Vigra)
find_package(OpenCV REQUIRED )
find_package(Boost REQUIRED )

find_library( CPPUNIT_LIBRARY NAMES cppunit cppunit_dll
            PATHS   ${FOO_PREFIX}/lib
                    /usr/lib
                    /usr/lib64
                    /usr/local/lib
                    /usr/local/lib64
            PATH_SUFFIXES release )

MESSAGE(STATUS " libraries : ${CPPUNIT_LIBRARY}")

MESSAGE(STATUS " boost libraries : ${Boost_LIBRARIES}")

file(GLOB_RECURSE SRCS ./src/*.cpp)
file(GLOB_RECURSE HDRS ./includes/*.hpp)

INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIR})
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
ADD_DEFINITIONS(${HDF5_CPPFLAGS})

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_SOURCE_DIR}")

# uncomment this for develop building
set(CMAKE_CXX_FLAGS "-g -O -Wall -Wshadow -Wextra -fopenmp -std=c++0x -march=native")

# uncomment this for release build to get best code optimization
#set(CMAKE_CXX_FLAGS "-g -O -Wall -Wshadow -Wextra -fopenmp -std=c++0x -O3 -#march=native")

# add the executable

    message( "INFO: RELEASE BUILD" )

#WORKFLOW: sandbox 
    add_executable(OpenLF_sandbox
	./workflows/sandbox.cpp
	${SRCS} ${HDRS})
    target_link_libraries(OpenLF_sandbox hdf5_cpp hdf5 vigraimpex boost_system boost_filesystem boost_regex 
	${OpenCV_LIBS} ${HDF5_LIBRARIES} ${CPPUNIT_LIBRARY})


#TEST: test_image 
    add_executable(OpenLF_test_image
	./tests/test_image_run.cpp
	./tests/test_image.cpp 
	${SRCS} ${HDRS})
    target_link_libraries(OpenLF_test_image hdf5_cpp hdf5 vigraimpex boost_system boost_filesystem boost_regex 
	${OpenCV_LIBS} ${HDF5_LIBRARIES} ${CPPUNIT_LIBRARY})


#TEST: test_imgproc 
add_executable(OpenLF_test_imgproc
	./tests/test_imgproc_run.cpp
	./tests/test_imgproc.cpp 
	${SRCS} ${HDRS})
    target_link_libraries(OpenLF_test_imgproc hdf5_cpp hdf5 vigraimpex boost_system boost_filesystem boost_regex 
	${OpenCV_LIBS} ${HDF5_LIBRARIES} ${CPPUNIT_LIBRARY})

#TEST: test_lightfield_IO 
add_executable(OpenLF_test_lightfield_IO 
	./tests/test_lightfield_IO_run.cpp
	./tests/test_lightfield_IO.cpp 
	${SRCS} ${HDRS})
    target_link_libraries(OpenLF_test_lightfield_IO  hdf5_cpp hdf5 vigraimpex boost_system boost_filesystem boost_regex
	${OpenCV_LIBS} ${HDF5_LIBRARIES} ${CPPUNIT_LIBRARY})

#TEST: test_lightfield 
add_executable(OpenLF_test_lightfield 
	./tests/test_lightfield_run.cpp
	./tests/test_lightfield.cpp 
	${SRCS} ${HDRS})
    target_link_libraries(OpenLF_test_lightfield  hdf5_cpp hdf5 vigraimpex boost_system boost_filesystem boost_regex
	${OpenCV_LIBS} ${HDF5_LIBRARIES} ${CPPUNIT_LIBRARY})


#TEST: test_channel
add_executable(OpenLF_test_channel 
	./tests/test_channel_run.cpp
	./tests/test_channel.cpp 
	${SRCS} ${HDRS})
    target_link_libraries(OpenLF_test_channel  hdf5_cpp hdf5 vigraimpex boost_system boost_filesystem boost_regex
	${OpenCV_LIBS} ${HDF5_LIBRARIES} ${CPPUNIT_LIBRARY})


enable_testing()
add_test(OpenLF_test_image ./test_release/OpenLF_test_image)
add_test(OpenLF_test_imgproc ./test_release/OpenLF_test_imgproc)
add_test(OpenLF_test_lightfield_IO ./test_release/OpenLF_test_lightfield_IO)
add_test(OpenLF_test_lightfield ./test_release/OpenLF_test_lightfield)
add_test(OpenLF_test_channel ./test_release/OpenLF_test_channel)

