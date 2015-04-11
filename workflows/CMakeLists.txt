#WORKFLOW: demo 
add_executable(OpenLF_demo_4DOp
	./demo_4DOperator/demo_4DOp.cpp
	#./demo_4DOperator/My4DOperator.cpp
	${SRCS} ${HDRS})
target_link_libraries(OpenLF_demo_4DOp libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY})

#add_executable(OpenLF_Operator_Gaussian
	#./demo_4DOperator/Operator_Gaussian.cpp
	#./demo_4DOperator/Operator_Gaussian.cpp
	#${SRCS} ${HDRS})
#target_link_libraries(OpenLF_Operator_Gaussian libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY})

#add_dependencies(OpenLF_Operator_Gaussian Configure)


if(WITH_OPENGM)
  add_executable(OpenLF_demo_opengm
    ./demo_opengm/demo_opengm.cxx
    ${SRCS} ${HDRS})
  target_link_libraries(OpenLF_demo_opengm libopenlf ${Boost_LIBRARIES} ${HDF5_LIBRARIES} ${HDF5_CPP_LIBRARY} ${VIGRA_IMPEX_LIBRARY})

  add_dependencies(OpenLF_demo_opengm Configure)
endif(WITH_OPENGM)
