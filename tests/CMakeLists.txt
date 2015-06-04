OPTION(BUILD_TEST_IMAGE "Build test_image" ON)
OPTION(BUILD_TEST_IMGPROC "Build test_imgproc" ON)
OPTION(BUILD_TEST_CHANNEL "Build test_channel" ON)
OPTION(BUILD_TEST_CHANNEL_VIEW "Build test_Channel_view" ON)
OPTION(BUILD_TEST_LIGHTFIELD_IO "Build test_lightfield_io" ON)
OPTION(BUILD_TEST_LIGHTFIELD "Build test_lightfield" ON)
OPTION(BUILD_TEST_OPERATOR "Build test_operator" ON)
OPTION(BUILD_TEST_HDF5MEMORY "Build test_hdf5memory" ON)


enable_testing()

if(BUILD_TEST_IMAGE)
	#TEST: test_image 
	    add_executable(OpenLF_test_image
		./test_image_run.cpp
		./test_image.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_image libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY} )

	add_dependencies(OpenLF_test_image Configure)
	add_test(OpenLF_test_image ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_image)
endif()

if(BUILD_TEST_IMGPROC)
	#TEST: test_imgproc 
	add_executable(OpenLF_test_imgproc
		./test_imgproc_run.cpp
		./test_imgproc.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_imgproc libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY})

	add_dependencies(OpenLF_test_imgproc Configure)
	add_test(OpenLF_test_imgproc ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_imgproc)
endif()

if(BUILD_TEST_LIGHTFIELD_IO)
	#TEST: test_lightfield_IO 
	add_executable(OpenLF_test_lightfield_IO 
		./test_lightfield_IO_run.cpp
		./test_lightfield_IO.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_lightfield_IO libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY})

	add_dependencies(OpenLF_test_lightfield_IO Configure)
	add_test(OpenLF_test_lightfield_IO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_lightfield_IO)
endif()

if(BUILD_TEST_LIGHTFIELD)
	#TEST: test_lightfield 
	add_executable(OpenLF_test_lightfield 
		./test_lightfield_run.cpp
		./test_lightfield.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_lightfield libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY})

	add_dependencies(OpenLF_test_lightfield Configure)
	add_test(OpenLF_test_lightfield ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_lightfield)
endif()

if(BUILD_TEST_CHANNEL)
	#TEST: test_channel
	add_executable(OpenLF_test_channel 
		./test_channel_run.cpp
		./test_channel.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_channel libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY}) 

	add_dependencies(OpenLF_test_channel Configure)
	add_test(OpenLF_test_channel ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_channel)
endif()

if(BUILD_TEST_CHANNEL_VIEW)
	#TEST: test_Channel_view 
	    add_executable(OpenLF_test_Channel_view
		./test_Channel_view_run.cpp
		./test_Channel_view.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_Channel_view libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY} )

	add_dependencies(OpenLF_test_Channel_view Configure)
	add_test(OpenLF_test_Channel_view ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_Channel_view)
endif()

if(BUILD_TEST_OPERATOR)
	#TEST: test_operator 
	    add_executable(OpenLF_test_operator
		./test_operator_run.cpp
		./test_operator.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_operator libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY} )

	add_dependencies(OpenLF_test_operator Configure)
	add_test(OpenLF_test_operator ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_operator)
endif()

if(BUILD_TEST_HDF5MEMORY)
	#TEST: test_hdf5memory
	    add_executable(OpenLF_test_hdf5memory
		./test_hdf5memory_run.cpp
		./test_hdf5memory.cpp
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_hdf5memory libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY} )

	add_dependencies(OpenLF_test_hdf5memory Configure)
	add_test(OpenLF_test_hdf5memory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_hdf5memory)
endif()


	
