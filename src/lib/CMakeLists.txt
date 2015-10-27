add_library(openlf ${OPENLF_BUILD_TYPE} openlf.cpp)
target_link_libraries(openlf ${OPENLF_LIBRARIES})

set(OPENLF_LIBRARIES ${OPENLF_LIBRARIES} openlf PARENT_SCOPE)
