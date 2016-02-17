cmake_minimum_required (VERSION 2.8)
project(OpenLF)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  # using Clang
  message(STATUS "compile with clang")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  # using GCC
  message(STATUS "compile with gcc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -g -O3 -fno-omit-frame-pointer -fopenmp")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3 -fPIC")
  set(OPENLF_LIBRARIES dl)
  set(OPENLF_BUILD_TYPE "SHARED")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  message(STATUS "Compile with msvc")
  #execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_SOURCE_DIR}/dependencies/HDF5_include.tar WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external/hdf5/src/HDF5-build)
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_SOURCE_DIR}/dependencies/basic_libs.tar 
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  include_directories(${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/)
  include_directories(${CMAKE_CURRENT_BINARY_DIR}/basic_libs/include)
  set(OPENLF_COMPILER_MSVC true)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Ox /openmp /D NOMINMAX")
  #set(CLIF_INCLUDE_DIR "D:/libs/include" CACHE PATH "Include path for external libraries")
  #include_directories(${LIBS_INCLUDE_DIR})
  #set (EXTRA_LIBS ${EXTRA_LIBS} "D:/libs/include")  #see parameter list here https://cmake.org/pipermail/cmake/2006-July/010189.html
  add_definitions(-DOPENLF_COMPILER_MSVC)  
  include_directories(external/dirent)
  set(OPENLF_BUILD_TYPE)
endif()

include(ExternalProject)

###########################################################################################
# Below is a CMake command to locate or download and build Boost 
##########################################################################################
message(STATUS "Search Boost")
SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost QUIET COMPONENTS system filesystem serialization program_options regex thread date_time QUIET)
if (NOT Boost_FOUND)
  option(Boost_INTERNAL "internal Boost download and build" ON)
else()
  option(Boost_INTERNAL "internal Boost download and build" OFF)
endif()

if (Boost_INTERNAL)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_boost)
	set( Boost_Version 1.58.0 )
	string( REPLACE "." "_" Boost_Version_Underscore ${Boost_Version} )
	#generate auxiliary dependency project
	message( STATUS "Boost_Version: " ${Boost_Version} " will be downloaded and installed")
	set(CMAKE_LIST_CONTENT "
		cmake_minimum_required(VERSION 2.8)
		include(ExternalProject)
		ExternalProject_Add(
		Boost
						PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_boost
						URL http://downloads.sourceforge.net/project/boost/boost/${Boost_Version}/boost_${Boost_Version_Underscore}.zip
						UPDATE_COMMAND \"bootstrap.bat\"
						CONFIGURE_COMMAND \"\"
						BUILD_COMMAND bjam address-model=64 toolset=msvc-12.0 variant=release link=static link=shared runtime-link=shared
						BUILD_IN_SOURCE 1
						INSTALL_COMMAND \"\"
		)
	")
		
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_boost/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

	execute_process(COMMAND ${CMAKE_COMMAND} . -G "Visual Studio 12 2013 Win64"
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_boost)
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_boost)	

	set(BOOST_ROOT ${CMAKE_CURRENT_BINARY_DIR}/force_boost/src/Boost/)
	set(BOOST_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_boost/src/Boost/)
	set(BOOST_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_boost/src/Boost/stage/lib)
	include_directories(${CMAKE_CURRENT_BINARY_DIR}/force_boost/src/Boost/stage/lib)
	link_directories (${CMAKE_CURRENT_BINARY_DIR}/force_boost/src/Boost/stage/lib)
	
endif()

message(STATUS "Boost include dir: ${BOOST_INCLUDE_DIR}")
message(STATUS "Boost lib dirs: ${BOOST_LIBRARY_DIR}")
find_package(Boost REQUIRED)

###########################################################################################
# Below is a CMake command to locate or download and build VIGRA 
###########################################################################################
message(STATUS "Search Vigra")
find_package(Vigra QUIET)
if (NOT Vigra_FOUND)
  option(Vigra_INTERNAL "internal vigra download and build" ON)
else()
  option(Vigra_INTERNAL "internal vigra download and build" OFF)
endif()

if (Vigra_INTERNAL)
	message( STATUS "VIGRA Version: latest will be downloaded and installed")
	#generate auxiliary dependency project
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_vigra)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/build)
    set(CMAKE_LIST_CONTENT "
		cmake_minimum_required(VERSION 2.8)

		include(ExternalProject)
		ExternalProject_Add(
		vigra
			PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_vigra
			GIT_REPOSITORY https://github.com/ukoethe/vigra.git
			CMAKE_ARGS -DTIFF_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/include -DTIFF_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/libtiff.lib
			CMAKE_ARGS -DJPEG_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/include -DJPEG_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/libjpeg.lib
			CMAKE_ARGS -DPNG_PNG_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/include -DPNG_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/libpng.lib
			CMAKE_ARGS -DZLIB_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/include -DZLIB_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/zlib.lib
			CMAKE_ARGS -DBoost_INCLUDE_DIR=${BOOST_INCLUDE_DIR} -DBoost_PYTHON_LIBRARY=${BOOST_LIBRARY_DIR}/boost_python-vc120-mt-1_58.lib
			CMAKE_ARGS -DWITH_OPENEXR=0 -DCMAKE_BUILD_TYPE=Release
			INSTALL_COMMAND \"\"
		)
	")
			
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

	execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/build)
	execute_process(COMMAND ${CMAKE_COMMAND} --build . --config Release
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/build)
			
	list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/src/vigra-build)
endif()

find_package(Vigra REQUIRED)


###########################################################################################
# Below is a CMake command to locate or download and build HDF5 
###########################################################################################
message(STATUS "Search HDF5")
find_package(HDF5 QUIET)
if (NOT HDF5_FOUND)
  option(HDF5_INTERNAL "internal HDF5 download and build" ON)
else()
  option(HDF5_INTERNAL "internal HDF5 download and build" OFF)
endif()

if (HDF5_INTERNAL)
	message( STATUS "HDF5 Version: 1.8.15-patch1 will be downloaded and installed")

	#generate auxiliary dependency project
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/build)
	set(CMAKE_LIST_CONTENT "
		cmake_minimum_required(VERSION 2.8)

		include(ExternalProject)
		ExternalProject_Add(
		HDF5
			PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5
			URL https://www.hdfgroup.org/ftp/HDF5/releases/hdf5-1.8.15-patch1/src/hdf5-1.8.15-patch1.tar.gz
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install
			CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
			INSTALL_COMMAND ;
		)
	")
	
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

	execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/build)
	execute_process(COMMAND ${CMAKE_COMMAND} --build . --config Release
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/build)
	
	#execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_SOURCE_DIR}/dependencies/HDF5_include.tar 
	#	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/src/HDF5-build)
	set(HDF5_C_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/include)
	set(HDF5_CXX_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/include)
	set(HDF5_hdf5_LIBRARY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/src/HDF5-build/bin/Release/libhdf5.lib)
	set(HDF5_hdf5_cxx_LIBRARY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/src/HDF5-build/bin/Release/libhdf5_cxx.lib)
	list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/cmake)
	endif()
#
find_package(HDF5 REQUIRED)

###########################################################################################
# Below is a CMake command to locate or download and build openCV 3.0
###########################################################################################
message(STATUS "Search OpenCV")
find_package(OpenCV QUIET)
if (NOT OpenCV_FOUND)
  option(OpenCV_INTERNAL "internal OpenCV download and build" ON)
else()
  option(OpenCV_INTERNAL "internal OpenCV download and build" OFF)
endif()

if (OpenCV_INTERNAL)

	message( STATUS "OpenCV Version: 3.0.0 will be downloaded and installed")
	
	#generate auxiliary dependency project
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_opencv)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_opencv/build)
	set(CMAKE_LIST_CONTENT "
		cmake_minimum_required(VERSION 2.8)

		include(ExternalProject)
		ExternalProject_Add(
		opencv
						PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_opencv
						GIT_REPOSITORY https://github.com/Itseez/opencv.git
						GIT_TAG 3.0.0
						INSTALL_COMMAND \"\"
		)
	")
	
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_opencv/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

	execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_opencv/build)
	execute_process(COMMAND ${CMAKE_COMMAND} --build . --config Release
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_opencv/build)

	list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_opencv/src/opencv-build)
endif()
#
#message(STATUS "OpenCV include dir: ${OPENCV_INCLUDE_DIR}")
#message(STATUS "OpenCV lib dir: ${OPNECV_LIBRARY_DIR}")
find_package(OpenCV REQUIRED)


option(WITH_PCL "compile PCL" OFF)

if (WITH_PCL)
	message(STATUS "Compile PCL")
	###########################################################################################
	# Below is a CMake command to download, build and install EIGEN 
	###########################################################################################
	find_package(EIGEN QUIET)
	if (NOT EIGEN_FOUND)
	  option(EIGEN_INTERNAL "internal EIGEN download and build" ON)
	else()
	  option(EIGEN_INTERNAL "internal EIGEN download and build" OFF)
	endif()

	if (EIGEN_INTERNAL)
	message( STATUS "EIGEN Version: latest will be downloaded and installed")
		#generate auxiliary dependency project
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_eigen)
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_eigen/build)

		#generate false dependency project
		set(CMAKE_LIST_CONTENT "
			cmake_minimum_required(VERSION 2.8)

			include(ExternalProject)
			ExternalProject_Add(
			eigen
							PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_eigen
							URL http://bitbucket.org/eigen/eigen/get/3.2.8.tar.bz2
							CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/force_eigen/install
							INSTALL_COMMAND ;
			)
		")
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_eigen/CMakeLists.txt "${CMAKE_LIST_CONTENT}")
		
		execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_eigen/build)
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config Release
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_eigen/build)

		set(EIGEN_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_eigen/install/include/eigen3)
	endif()


	###########################################################################################
	# Below is a CMake command to download, build and install FLANN 
	###########################################################################################
	find_package(FLANN QUIET)
	if (NOT FLANN_FOUND)
	  option(FLANN_INTERNAL "internal FLANN download and build" ON)
	else()
	  option(FLANN_INTERNAL "internal FLANN download and build" OFF)
	endif()

	if (FLANN_INTERNAL)
	message( STATUS "FLANN Version: latest will be downloaded and installed")
		#generate auxiliary dependency project
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_flann)
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_flann/build)

		#generate false dependency project
		set(CMAKE_LIST_CONTENT "
			cmake_minimum_required(VERSION 2.8)

			include(ExternalProject)
			ExternalProject_Add(
			flann
							PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_flann
							GIT_REPOSITORY https://github.com/mariusmuja/flann.git
							CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/force_flann/install
							INSTALL_COMMAND ;
			)
		")
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_flann/CMakeLists.txt "${CMAKE_LIST_CONTENT}")
		
		execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_flann/build)
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config Release
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_flann/build)

		set(FLANN_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/force_flann/install/lib/flann.lib)
		set(FLANN_S_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/force_flann/install/lib/flann_s.lib)
		set(FLANN_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_flann/install/include)
		set(FLANN_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/force_flann/sinstall/include)
	endif()
	

	###########################################################################################
	# Below is a CMake command to download, build and install VTK
	###########################################################################################
	find_package(VTK QUIET)
	if (NOT VTK)
	  option(VTK_INTERNAL "internal FLANN download and build" ON)
	else()
	  option(VTK_INTERNAL "internal FLANN download and build" OFF)
	endif()

	if (VTK_INTERNAL)
	message( STATUS "VTK Version: latest will be downloaded and installed")
		#generate auxiliary dependency project
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_VTK)
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_VTK/build)

		#generate false dependency project
		set(CMAKE_LIST_CONTENT "
			cmake_minimum_required(VERSION 2.8)

			include(ExternalProject)
			ExternalProject_Add(
			VTK
							PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_VTK
							URL http://www.vtk.org/files/release/7.0/VTK-7.0.0.zip
							CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/force_VTK/install
							INSTALL_COMMAND ;
			)
		")
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_VTK/CMakeLists.txt "${CMAKE_LIST_CONTENT}")
		
		execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_VTK/build)
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config Release
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_VTK/build)

		list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_VTK/install/lib/cmake/vtk-7.0)
	endif()
	find_package(VTK REQUIRED)


	###########################################################################################
	# Below is a CMake command to download, build and install PCL 
	###########################################################################################
	find_package(PCL QUIET)
	if (NOT PCL)
	  option(PCL_INTERNAL "internal FLANN download and build" ON)
	else()
	  option(PCL_INTERNAL "internal FLANN download and build" OFF)
	endif()

	if (PCL_INTERNAL)
	message( STATUS "PLC Version: latest will be downloaded and installed")
		#generate auxiliary dependency project
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_PCL)
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_PCL/build)

		#generate false dependency project
		set(CMAKE_LIST_CONTENT "
			cmake_minimum_required(VERSION 2.8)

			include(ExternalProject)
			ExternalProject_Add(
			PCL
							PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_PCL
							GIT_REPOSITORY https://github.com/PointCloudLibrary/pcl.git
							CMAKE_ARGS -DEIGEN_INCLUDE_DIR=${EIGEN_INCLUDE_DIR}
							CMAKE_ARGS -DFLANN_LIBRARY=${FLANN_S_LIBRARY}
							CMAKE_ARGS -DFLANN_INCLUDE_DIR=${FLANN_INCLUDE_DIR}	
							CMAKE_ARGS -DVTK_DIR=${CMAKE_CURRENT_BINARY_DIR}/force_VTK/src/VTK-build
							CMAKE_ARGS -DZLIB_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}basic_libs/include -DZLIB_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/zlib.lib
							CMAKE_ARGS -DPNG_PNG_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/include -DPNG_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/libpng.lib
							CMAKE_ARGS -DBOOST_ROOT=${CMAKE_CURRENT_BINARY_DIR}/force_boost/src/Boost
							CMAKE_ARGS -DWITH_PCAP=OFF
							INSTALL_COMMAND \"\"
			)
		")
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_PCL/CMakeLists.txt "${CMAKE_LIST_CONTENT}")
		
		execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_PCL/build)
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config Release
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_PCL/build)	
		
		list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_PCL/src/PCL-build)
	endif()	
	
	find_package(PCL REQUIRED)
	
endif()
	
###########################################################################################
## Below is a CMake command to locate or download and build clif                                             
###########################################################################################
message(STATUS "Search clif")
find_package(clif QUIET)
if (NOT clif_FOUND)
  option(OPENLF_INTERNAL_CLIF "internal clif download and build" ON)
else()
  option(OPENLF_INTERNAL_CLIF "internal clif download and build" OFF)
endif()

if (OPENLF_INTERNAL_CLIF)

	message( STATUS "Clif Version: latest will be downloaded and installed")
	
	#generate auxiliary dependency project
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_clif)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_clif/build)

    #generate false dependency project
    set(CMAKE_LIST_CONTENT "
		cmake_minimum_required(VERSION 2.8)

		include(ExternalProject)
		ExternalProject_add(
		clif
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_clif
            GIT_REPOSITORY https://github.com/hendriksiedelmann/clif.git
            CMAKE_ARGS -DVigra_DIR=${CMAKE_CURRENT_BINARY_DIR}/force_vigra/src/vigra-build
			CMAKE_ARGS -DOpenCV_DIR=${CMAKE_CURRENT_BINARY_DIR}/force_opencv/src/opencv-build
			CMAKE_ARGS -DHDF5_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/src/HDF5-build/include
			CMAKE_ARGS -DHDF5_CXX_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/src/HDF5-build/include
			CMAKE_ARGS -DHDF5_C_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/src/HDF5-build/include
			CMAKE_ARGS -DHDF5_hdf5_LIBRARY_RELEASE=${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/src/HDF5-build/bin/Release/libhdf5.lib
			CMAKE_ARGS -DHDF5_hdf5_cpp_LIBRARY_RELEASE=${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/src/HDF5-build/bin/Release/libhdf5_cpp.lib
			CMAKE_ARGS -DBoost_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/force_boost/src/Boost
			CMAKE_ARGS -DEIGEN_INCLUDE_DIR=${EIGEN_INCLUDE_DIR}
            INSTALL_COMMAND \"\"
            )
		")
			
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_clif/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

    execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_clif/build)
    execute_process(COMMAND ${CMAKE_COMMAND} --build . --config Release
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_clif/build)

	list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_clif/src/clif-build)
endif()
#
message(STATUS "clif libraries: ${CLIF_LIBRARIES}")
message(STATUS "clif lib dirs: ${CLIF_LIBRARY_DIRS}")
find_package(clif REQUIRED)




include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${HDF5_C_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${Vigra_INCLUDE_DIRS})
include_directories(${CLIF_INCLUDE_DIRS})

link_directories(${CLIF_LIBRARY_DIRS})

list(APPEND OPENLF_LIBRARIES ${CLIF_LIBRARIES} ${Boost_LIBRARIES})

add_subdirectory(external/gml_parser)
include_directories(external/gml_parser)

add_subdirectory(external/dspatch)
list(APPEND OPENLF_LIBRARIES DSPatch)

include_directories(external/dspatch/include)
include_directories(external/dspatch/include/dspatch)

include_directories(include)
include_directories(include/openlf)

##include_directories(include/openlf/components)
##include_directories(include/openlf/workflows)
##include_directories(include/openlf/operators)

##add_subdirectory(src/lib/operators)
##add_subdirectory(src/lib/workflows)
##add_subdirectory(src/lib/components)

add_subdirectory(src/lib)

add_subdirectory(components)

add_subdirectory(gui)

add_executable(openlf-bin src/bin/openlf.cpp)
set_target_properties(openlf-bin PROPERTIES OUTPUT_NAME openlf)
target_link_libraries(openlf-bin ${OPENLF_LIBRARIES})


##add_executable(teststuff src/bin/test.cpp)
##add_executable(teststuff2 src/bin/test2.cpp)
##add_executable(teststuff3 src/bin/test3.cpp)

##target_link_libraries(teststuff  ${OPENLF_LIBRARIES})
##target_link_libraries(teststuff2 ${OPENLF_LIBRARIES})
##target_link_libraries(teststuff3 ${OPENLF_LIBRARIES})
