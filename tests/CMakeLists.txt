	#TEST: test_image 
	    add_executable(OpenLF_test_image
		./test_image_run.cpp
		./test_image.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_image libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY} )

	add_dependencies(OpenLF_test_image Configure)

	#TEST: test_imgproc 
	add_executable(OpenLF_test_imgproc
		./test_imgproc_run.cpp
		./test_imgproc.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_imgproc libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY})

	add_dependencies(OpenLF_test_imgproc Configure)

	#TEST: test_lightfield_IO 
	add_executable(OpenLF_test_lightfield_IO 
		./test_lightfield_IO_run.cpp
		./test_lightfield_IO.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_lightfield_IO libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY})

	add_dependencies(OpenLF_test_lightfield_IO Configure)

	#TEST: test_lightfield 
	add_executable(OpenLF_test_lightfield 
		./test_lightfield_run.cpp
		./test_lightfield.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_lightfield libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY})

	add_dependencies(OpenLF_test_lightfield Configure)

	#TEST: test_channel
	add_executable(OpenLF_test_channel 
		./test_channel_run.cpp
		./test_channel.cpp 
		${SRCS} ${HDRS})
	    target_link_libraries(OpenLF_test_channel libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY} ${CPPUNIT_LIBRARY}) 

	add_dependencies(OpenLF_test_channel Configure)



	enable_testing()
	add_test(OpenLF_test_image ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_image)
	add_test(OpenLF_test_channel ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_channel)
	add_test(OpenLF_test_imgproc ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_imgproc)
	add_test(OpenLF_test_lightfield_IO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_lightfield_IO)
	add_test(OpenLF_test_lightfield ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenLF_test_lightfield)