cmake_minimum_required (VERSION 2.8)
project(OpenLF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -g -O3 -fno-omit-frame-pointer")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3 -fPIC")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  # using Clang
  message(STATUS "compile with clang")  
  set(OPENLF_LIBRARIES dl)
  set(OPENLF_BUILD_TYPE "SHARED")
  set(CMAKE_MACOSX_RPATH 1)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  # using GCC
  message(STATUS "compile with gcc")
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

# Check for OpenMP and use if available
option(OPENLF_WITH_OPENMP "Use OpenMP" ON)
if(OPENLF_WITH_OPENMP)
  find_package(OpenMP QUIET)
  if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    add_definitions(-DOPENLF_WITH_OPENMP)
  else()
	option(OPENLF_WITH_OPENMP "Use OpenMP" OFF)
	set(OPENLF_WITH_OPENMP OFF)
  endif()
endif()


SET(CompileAs "Release" CACHE STRING "library selected at CMake configure time")
SET_PROPERTY(CACHE CompileAs PROPERTY STRINGS RelWithDebInfo Release Debug) 

include(ExternalProject)

###########################################################################################
# Below is a CMake command to locate or download and build Boost 
##########################################################################################
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	message(STATUS "Search Boost")
	SET(Boost_USE_STATIC_LIBS ON)
	find_package(Boost QUIET COMPONENTS system filesystem serialization program_options regex thread date_time QUIET)
	option(REBUILD_Boost "internal HDF5 download and build" ON)
	if (Boost_FOUND)
	  set(Boost_INTERNAL OFF)
	  message(STATUS "Boost found")
	else()
	  set(Boost_INTERNAL ON)
	  message(STATUS "Boost NOT found")
	endif()

	if (Boost_INTERNAL OR REBUILD_Boost)
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
							BUILD_COMMAND bjam --with-python --with-system --with-chrono --with-filesystem --with-regex --with-atomic --with-thread --with-date_time --with-program_options --with-serialization address-model=64 toolset=msvc-12.0 variant=release debug link=static link=shared runtime-link=shared
							BUILD_IN_SOURCE 1
							INSTALL_COMMAND \"\"
			)
		")
			
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_boost/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

		execute_process(COMMAND ${CMAKE_COMMAND} . -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_boost)
		execute_process(COMMAND ${CMAKE_COMMAND} --build .
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_boost)	

		set(BOOST_ROOT ${CMAKE_CURRENT_BINARY_DIR}/force_boost/src/Boost/ CACHE TYPE STRING)
		set(REBUILD_Boost "internal HDF5 download and build" OFF)
	endif()
endif()

SET(REBUILD_Boost OFF CACHE BOOL "internal HDF5 download and build" FORCE)
find_package(Boost REQUIRED COMPONENTS system filesystem serialization program_options regex thread date_time)
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost lib dirs: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost libs: ${Boost_LIBRARIES}")
message(STATUS "Boost root: ${BOOST_ROOT}")


###########################################################################################
# Below is a CMake command to locate or download and build VIGRA 
###########################################################################################
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	message(STATUS "Search Vigra")
	find_package(Vigra QUIET)
	option(REBUILD_Vigra "internal HDF5 download and build" ON)
	if (Vigra_FOUND)
	  set(Vigra_INTERNAL OFF)
	  message(STATUS "Vigra found")
	else()
	  set(Vigra_INTERNAL ON)
	  message(STATUS "Vigra NOT found")
	endif()
	message(STATUS "Vigra CHECK_INCLUDE_FILE(Boost_PYTHON_LIBRARY)")
	if (Vigra_INTERNAL OR REBUILD_Vigra)
		message( STATUS "VIGRA Version: latest will be downloaded and installed")
		#generate auxiliary dependency project
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_vigra)
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/build)
		if(EXISTS ${Boost_PYTHON_LIBRARY})
			set(vigranumpyflag 1)
		else()
			set(vigranumpyflag 0)
		endif()
		message(${vigranumpyflag})
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
				CMAKE_ARGS -DBoost_INCLUDE_DIR=${Boost_INCLUDE_DIRS} -DBoost_PYTHON_LIBRARY=${Boost_PYTHON_LIBRARY}
				CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/force_vigra/install
				CMAKE_ARGS -DOPENEXR_HALF_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/Half.lib
				CMAKE_ARGS -DOPENEXR_IEX_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/Iex-2_2.lib
				CMAKE_ARGS -DOPENEXR_ILMIMF_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/IlmImf.lib
				CMAKE_ARGS -DOPENEXR_ILMTHREAD_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/IlmThread-2_2.lib
				CMAKE_ARGS -DOPENEXR_IMATH_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/Imath-2_2.lib
				CMAKE_ARGS -DOPENEXR_INCLUDE_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/include
				CMAKE_ARGS -DWITH_OPENEXR=1 -DWITH_VIGRANUMPY=${vigranumpyflag} -DWITH_HDF5=0
				CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CompileAs}
				INSTALL_COMMAND ;
			)
		")
				
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

		execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/build)
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CompileAs}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/build)
				
		list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/install/lib/vigra)
		set(Vigra_LIBRARY_DIRS ${CMAKE_CURRENT_BINARY_DIR}/force_vigra/install/lib CACHE TYPE STRING)				
		set(Vigra_INTERNAL OFF)
	endif()
endif()

SET(REBUILD_Vigra OFF CACHE BOOL "internal HDF5 download and build" FORCE)
find_package(Vigra REQUIRED)
message(STATUS "Vigra include dir: ${Vigra_INCLUDE_DIRS}")
message(STATUS "Vigra lib dirs: ${Vigra_LIBRARY_DIRS}")



###########################################################################################
# Below is a CMake command to locate or download and build HDF5 
###########################################################################################
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	message(STATUS "Search HDF5")
	find_package(HDF5 QUIET)
	option(REBUILD_HDF5 "internal HDF5 download and build" ON)
	if (HDF5_FOUND)
	  set(HDF5_INTERNAL OFF)
	  message(STATUS "HDF5 found")
	else()
	  set(HDF5_INTERNAL ON)
	  message(STATUS "HDF5 NOT found")
	endif()

	if (HDF5_INTERNAL OR REBUILD_HDF5)
		message( STATUS "HDF5 Version: 1.8.15-patch1 will be downloaded and installed")

		#generate auxiliary dependency project
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5)
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/build)
		set(CMAKE_LIST_CONTENT "
			cmake_minimum_required(VERSION 2.8)

			include(ExternalProject)
			ExternalProject_Add(
			hdf5
				PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5
				URL https://www.hdfgroup.org/ftp/HDF5/releases/hdf5-1.8.15-patch1/src/hdf5-1.8.15-patch1.tar.gz
				CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install
				CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CompileAs}
				CMAKE_ARGS -DBUILD_SHARED_LIBS=1
				INSTALL_COMMAND ;
			)
		")
		
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/CMakeLists.txt "${CMAKE_LIST_CONTENT}")
		
		execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/build)
		execute_process(COMMAND ${CMAKE_COMMAND} ../hdf5 -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/src/hdf5-build)	
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CompileAs}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/build)
		
		set(HDF5_C_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/include CACHE TYPE STRING FORCE)
		set(HDF5_CXX_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/include CACHE TYPE STRING FORCE)
		set(HDF5_hdf5_LIBRARY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/lib/hdf5.lib CACHE TYPE STRING FORCE)
		set(HDF5_hdf5_cxx_LIBRARY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/lib/hdf5_cpp.lib CACHE TYPE STRING FORCE)
		set(HDF5_hdf5_LIBRARY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/lib/hdf5_D.lib CACHE TYPE STRING FORCE)
		set(HDF5_hdf5_cxx_LIBRARY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/lib/hdf5_cpp_D.lib CACHE TYPE STRING FORCE)
		set(HDF5_C_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/lib/hdf5.lib CACHE TYPE STRING FORCE)
		set(HDF5_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/cmake CACHE TYPE STRING FORCE)
		set(HDF5_DIFF_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/bin/h5diff.exe CACHE TYPE STRING FORCE)
		list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_hdf5/install/cmake FORCE)
	endif()
endif()

SET(REBUILD_HDF5 OFF CACHE BOOL "internal HDF5 download and build" FORCE)

find_package(HDF5 REQUIRED)
message(STATUS "HDF5 include dir: ${HDF5_INCLUDE_DIRS}")
message(STATUS "HDF5 lib dirs: ${HDF5_LIBRARIES} ${HDF5_hdf5_cxx_LIBRARY_RELEASE} ${HDF5_hdf5_LIBRARY_DEBUG} ${HDF5_hdf5_cxx_LIBRARY_DEBUG}")



###########################################################################################
# Below is a CMake command to locate or download and build openCV 3.0
###########################################################################################
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	message(STATUS "Search OpenCV")
	find_package(OpenCV QUIET)
	option(REBUILD_OpenCV "internal HDF5 download and build" ON)
	if (OpenCV_FOUND)
	  set(OpenCV_INTERNAL OFF)
	  message(STATUS "OpenCV found")
	else()
	  set(OpenCV_INTERNAL ON)
	  message(STATUS "OpenCV not found")
	endif()

	if (OpenCV_INTERNAL OR REBUILD_OpenCV)

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
							CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CompileAs}
							CMAKE_ARGS -DWITH_QT=1
							CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/force_opencv/install
							INSTALL_COMMAND ;
			)
		")
		
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_opencv/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

		execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_opencv/build)
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CompileAs}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_opencv/build)

		list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_opencv/install)
	endif()
endif()
	
SET(REBUILD_OpenCV OFF CACHE BOOL "internal HDF5 download and build" FORCE)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV include dir: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV lib dir: ${OpenCV_LIBS}")



###########################################################################################
# Below is a CMake command to download, build and install EIGEN 
###########################################################################################
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	option(REBUILD_Eigen "internal HDF5 download and build" ON)
	if(EIGEN3_INCLUDE_DIR)
	  set(EIGEN_INTERNAL OFF)
	  message(STATUS "EIGEN found")
	else()
	  set(EIGEN_INTERNAL ON)
	  message(STATUS "EIGEN NOT found")
	endif()

	if (EIGEN_INTERNAL OR REBUILD_Eigen)
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
							CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CompileAs}
							INSTALL_COMMAND ;
			)
		")
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_eigen/CMakeLists.txt "${CMAKE_LIST_CONTENT}")
		
		execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_eigen/build)
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CompileAs}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_eigen/build)

		set(EIGEN3_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_eigen/install/include/eigen3 CACHE TYPE STRING)
	endif()
endif()

SET(REBUILD_Eigen OFF CACHE BOOL "internal HDF5 download and build" FORCE)
message(STATUS "EIGEN include dir: ${EIGEN3_INCLUDE_DIR}")

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	message(STATUS "Search glfw3")
	find_package(glfw3 QUIET)
	option(REBUILD_glfw3 "internal glfw3 download and build" OFF)
	if (glfw3_FOUND)
	  set(glfw3_INTERNAL OFF)
	  message(STATUS "glfw3 not found")
	else()
	  set(glfw3_INTERNAL ON)
	  message(STATUS "glfw3 found")
	endif()

	if (REBUILD_glfw3)

		message( STATUS "glfw3 will be downloaded and installed")
		
		#generate auxiliary dependency project
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_glfw3)
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_glfw3/build)
		set(CMAKE_LIST_CONTENT "
			cmake_minimum_required(VERSION 2.8)

			include(ExternalProject)
			ExternalProject_Add(
							glfw3
							PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_glfw3
							GIT_REPOSITORY https://github.com/glfw/glfw.git
							GIT_TAG 3.1.2
							CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CompileAs}
							CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/force_glfw3/install
							INSTALL_COMMAND ;
			)
		")
		
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_glfw3/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

		execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_glfw3/build)
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CompileAs}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_glfw3/build)

		file(COPY ${CMAKE_CURRENT_BINARY_DIR}/force_glfw3/install/lib/cmake/glfw/glfw3Config.cmake DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/force_glfw3/install/)
		set(glfw3_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_glfw3/install CACHE TYPE STRING FORCE)
	endif()
endif()

SET(REBUILD_glfw3 OFF CACHE BOOL "rebuild glfw3" FORCE)
message("glfw3: ${glfw3_DIR}")
#find_package(glfw3 REQUIRED)
message(STATUS "glfw3 include dir: ${GLFW3_INCLUDE_DIR}")
message(STATUS "glfw3 lib dir: ${GLFW3_LIBRARY}")

#from basic libs
#set(GLEW_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/basic_libs/include")
#set(GLEW_LIB "${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/glew32.lib")
#find_package(GLEW REQUIRED)

# if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	# message(STATUS "Search GLEW")
	# find_package(GLEW QUIET)
	# option(REBUILD_GLEW "internal GLEW download and build" OFF)
	# if (GLEW_FOUND)
	  # set(GLEW_INTERNAL OFF)
	  # message(STATUS "GLEW not found")
	# else()
	  # set(GLEW_INTERNAL ON)
	  # message(STATUS "GLEW found")
	# endif()

	# if (GLEW_INTERNAL OR REBUILD_GLEW)

		# message( STATUS "GLEW will be downloaded and installed")
		
		# #generate auxiliary dependency project
		# file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_glew)
		# file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_glew/src)
		
		
		
		# file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/force_glew/src/glew) 

		# find_package(Git REQUIRED)
		# execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/nigels-com/glew.git ${CMAKE_CURRENT_BINARY_DIR}/force_glew/src/glew WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
		
		# execute_process(COMMAND ${CMAKE_COMMAND} ../build/cmake -G "Visual Studio 12 2013 Win64"
			# WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_glew/src/glew-build)
		# execute_process(COMMAND ${CMAKE_COMMAND} --build cmake/ --config ${CompileAs}
			# WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_glew/src/glew-build)
	# endif()
# endif()

# SET(REBUILD_GLEW OFF CACHE BOOL "rebuild GLEW" FORCE)
# message("GLEW: ${GLEW_DIR}")
# find_package(GLEW REQUIRED)
# message(STATUS "GLEW include dir: ${GLEW_INCLUDE_DIR}")
# message(STATUS "GLEW lib dir: ${GLEW_LIBRARY}")

option(WITH_PCL "compile PCL" OFF)
if (WITH_PCL)	
	
	###########################################################################################
	# Below is a CMake command to download, build and install FLANN 
	###########################################################################################
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		option(REBUILD_Flann "internal HDF5 download and build" ON)
		if (FLANN_S_LIBRARY)
		  set(FLANN_INTERNAL OFF)
		  message(STATUS "FLANN found")
		else()
		  set(FLANN_INTERNAL ON)
		  message(STATUS "FLANN not found")
		endif()
	
		if (FLANN_INTERNAL OR REBUILD_Flann)
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
								CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CompileAs}
								INSTALL_COMMAND ;
				)
			")
			file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_flann/CMakeLists.txt "${CMAKE_LIST_CONTENT}")
			
			execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_flann/build)
			execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CompileAs}
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_flann/build)

			set(FLANN_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/force_flann/install/lib/flann.lib CACHE TYPE STRING)
			set(FLANN_S_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/force_flann/install/lib/flann_s.lib CACHE TYPE STRING)
			set(FLANN_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/force_flann/install/include CACHE TYPE STRING)
			#set(FLANN_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/force_flann/install/include CACHE TYPE STRING)
		endif()
	endif()
	
	SET(REBUILD_Flann OFF CACHE BOOL "internal HDF5 download and build" FORCE)
	message(STATUS "FLANN lib: ${FLANN_LIBRARY}")	
	message(STATUS "FLANN static lib: ${FLANN_S_LIBRARY}")	
	message(STATUS "FLANN include dir: ${FLANN_INCLUDE_DIR}")	
	
	


	###########################################################################################
	# Below is a CMake command to download, build and install VTK
	###########################################################################################
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		find_package(VTK QUIET)
		option(REBUILD_VTK "internal HDF5 download and build" ON)
		if (VTK_FOUND)
		  set(VTK_INTERNAL OFF)
		  message(STATUS "VTK found")
		else()
		  set(VTK_INTERNAL ON)
		  message(STATUS "VTK not found")
		endif()
		if (VTK_INTERNAL OR REBUILD_VTK)
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
								CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CompileAs}
								INSTALL_COMMAND ;
				)
			")
			file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_VTK/CMakeLists.txt "${CMAKE_LIST_CONTENT}")
			
			execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_VTK/build)
			execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CompileAs}
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_VTK/build)

			list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_VTK/install/lib/cmake/vtk-7.0)
		endif()
	endif()
	
	SET(REBUILD_VTK OFF CACHE BOOL "internal HDF5 download and build" FORCE)
	find_package(VTK REQUIRED)	
	message(STATUS "VTK include dir: ${VTK_INCLUDE_DIRS}")	
	message(STATUS "VTK lib: ${VTK_LIBRARIES}")
	
	
	

	###########################################################################################
	# Below is a CMake command to download, build and install PCL 
	###########################################################################################
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		find_package(PCL QUIET)
		option(REBUILD_PCL "internal HDF5 download and build" ON)
		if (PCL_FOUND)
		  set(PCL_INTERNAL OFF)
		  message(STATUS "PCL found")
		else()
		  set(PCL_INTERNAL ON)
		  message(STATUS "PCL NOT found")
		endif()
		if (PCL_INTERNAL OR REBUILD_PCL)
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
								CMAKE_ARGS -DEIGEN_INCLUDE_DIR=${EIGEN3_INCLUDE_DIR}
								CMAKE_ARGS -DFLANN_LIBRARY=${FLANN_S_LIBRARY}
								CMAKE_ARGS -DFLANN_INCLUDE_DIR=${FLANN_INCLUDE_DIR}	
								CMAKE_ARGS -DVTK_DIR=${CMAKE_CURRENT_BINARY_DIR}/force_VTK/src/VTK-build
								CMAKE_ARGS -DZLIB_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}basic_libs/include -DZLIB_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/zlib.lib
								CMAKE_ARGS -DPNG_PNG_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/include -DPNG_LIBRARY=${CMAKE_CURRENT_BINARY_DIR}/basic_libs/lib/libpng.lib
								CMAKE_ARGS -DBOOST_ROOT=${CMAKE_CURRENT_BINARY_DIR}/force_boost/src/Boost
								CMAKE_ARGS -DWITH_PCAP=OFF
								CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CompileAs}
								INSTALL_COMMAND \"\"
				)
			")
			file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_PCL/CMakeLists.txt "${CMAKE_LIST_CONTENT}")
			
			execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_PCL/build)
			execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CompileAs}
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_PCL/build)	
			
			list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_PCL/src/PCL-build)
		endif()	
	endif()
		
	SET(REBUILD_PCL OFF CACHE BOOL "internal HDF5 download and build" FORCE)
	find_package(PCL REQUIRED)
	message(STATUS "PCL include dir: ${PCL_INCLUDE_DIRS}")	
	message(STATUS "PCL lib: ${PCL_LIBRARIES}")
	message(STATUS "PCL lib: ${PCL_INCLUDE_DIRS}")
	
endif()

###########################################################################################
## Below is a CMake command to locate or download and build clif                                             
###########################################################################################

message(STATUS "Search clif")
find_package(clif QUIET)
option(REBUILD_CLIF "internal HDF5 download and build" ON)
if (clif_FOUND)
  set(CLIF_INTERNAL OFF)
  message(STATUS "clif found")
else()
  set(CLIF_INTERNAL ON)
  message(STATUS "clif NOT found")
endif()

find_package(Qt5Widgets REQUIRED)
if (Qt5Widgets_FOUND)
  list(APPEND OPENLF_LIBRARIES ${Qt5Widgets_LIBRARIES})
  list(APPEND OPENLF_INCLUDE_DIRS ${Qt5Widgets_INCLUDE_DIRS})
  list(APPEND OPENLF_LIBRARY_DIRS ${Qt5Widgets_LIBRARY_DIRS})
endif()

find_package(Qt5Network REQUIRED)
if (Qt5Network_FOUND)
  list(APPEND OPENLF_LIBRARIES ${Qt5Network_LIBRARIES})
  list(APPEND OPENLF_INCLUDE_DIRS ${Qt5Network_INCLUDE_DIRS})
  list(APPEND OPENLF_LIBRARY_DIRS ${Qt5Network_LIBRARY_DIRS})
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	
	if (CLIF_INTERNAL OR REBUILD_CLIF)

		message( STATUS "Clif Version: latest will be downloaded and installed")
		
		#generate auxiliary dependency project
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_clif)
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_clif/build)
		
		if (CompileAs MATCHES Debug)
			set(HDF5_CXX_LIBRARIES ${HDF5_hdf5_cxx_LIBRARY_DEBUG})
			set(HDF5_LIBRARIES ${HDF5_hdf5_LIBRARY_DEBUG})
		else()
			set(HDF5_CXX_LIBRARIES ${HDF5_hdf5_cxx_LIBRARY_RELEASE})
			set(HDF5_LIBRARIES ${HDF5_hdf5_LIBRARY_RELEASE})
		endif()
		list(REMOVE_DUPLICATES HDF5_CXX_LIBRARIES)
		list(REMOVE_DUPLICATES HDF5_LIBRARIES)
		message("openlf:")
        message(STATUS ${HDF5_LIBRARIES} ${HDF5_CXX_LIBRARIES})
		#generate false dependency project
		set(CMAKE_LIST_CONTENT "
			cmake_minimum_required(VERSION 2.8)

			include(ExternalProject)
			ExternalProject_add(
			clif
				PREFIX ${CMAKE_CURRENT_BINARY_DIR}/force_clif
				GIT_REPOSITORY https://github.com/hendriksiedelmann/clif.git
				CMAKE_ARGS -DVigra_DIR=${Vigra_DIR}
				CMAKE_ARGS -DOpenCV_DIR=${OpenCV_DIR}
				CMAKE_ARGS -DBOOST_ROOT=${BOOST_ROOT}
				CMAKE_ARGS -DBoost_LIBRARIES=${Boost_LIBRARIES}
				CMAKE_ARGS -DBoost_LIBRARY_DIRS=${Boost_LIBRARY_DIRS}
				CMAKE_ARGS -DBoost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}
				CMAKE_ARGS -DQt5Widgets_LIBRARIES=${Qt5Widgets_LIBRARIES}
				CMAKE_ARGS -DCOMPILE_EXTERNAL=1
				CMAKE_ARGS -DHDF5_LIBRARIES=${HDF5_LIBRARIES}
				CMAKE_ARGS -DHDF5_CXX_LIBRARIES=${HDF5_CXX_LIBRARIES}
				CMAKE_ARGS -DQt5Widgets_INCLUDE_DIRS=${Qt5Widgets_INCLUDE_DIRS}
				CMAKE_ARGS -DHDF5_INCLUDE_DIR=${HDF5_INCLUDE_DIRS}
				CMAKE_ARGS -DHDF5_DIFF_EXECUTABLE=${HDF5_DIFF_EXECUTABLE}
				#CMAKE_ARGS -DHDF5_CXX_INCLUDE_DIR=${HDF5_CXX_INCLUDE_DIR}
				#CMAKE_ARGS -DHDF5_C_INCLUDE_DIR=${HDF5_C_INCLUDE_DIR}
				CMAKE_ARGS -DEIGEN3_INCLUDE_DIR=${EIGEN3_INCLUDE_DIR}
				CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CompileAs}
				CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/force_clif/install
				CMAKE_ARGS -Dglfw3_DIR=${glfw3_DIR}
				CMAKE_ARGS -DGLEW_INCLUDE_DIR=${GLEW_INCLUDE_DIR}
				CMAKE_ARGS -DGLEW_LIB=${GLEW_LIB}
				CMAKE_ARGS -DGLEW_LIBRARY=${GLEW_LIB}
				BUILD_ALWAYS 1
				INSTALL_COMMAND ;
				)
			")
				
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/force_clif/CMakeLists.txt "${CMAKE_LIST_CONTENT}")

		execute_process(COMMAND ${CMAKE_COMMAND} .. -G "Visual Studio 12 2013 Win64"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_clif/build)
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CompileAs}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/force_clif/build)

		list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/force_clif/src/clif-build)
	endif()
endif()

SET(REBUILD_CLIF OFF CACHE BOOL "internal HDF5 download and build" FORCE)
find_package(clif REQUIRED)
message(STATUS "clif libraries: ${CLIF_LIBRARIES}")
message(STATUS "clif lib dirs: ${CLIF_LIBRARY_DIRS}")

find_package(cliini QUIET)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${HDF5_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Vigra_INCLUDE_DIRS})
include_directories(${CLIF_INCLUDE_DIRS})
include_directories(${CLIINI_INCLUDE_DIRS})

link_directories(${CLIF_LIBRARY_DIRS})
link_directories(${CLIINI_LIBRARY_DIRS})

list(APPEND OPENLF_LIBRARIES ${CLIF_LIBRARIES} ${CLIINI_LIBRARIES} ${Boost_LIBRARIES})

message("${CLIF_LIBRARIES}")
message("${CLIINI_LIBRARIES}")
message("boost: ${Boost_LIBRARIES}")

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


message("")
message("build info:")
message("  optional components:")

if(OPENLF_WITH_OPENMP)
  message("    OpenMP         -   yes")
else()
  message("    OpenMP         -   no")
endif()

message("")
