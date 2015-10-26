add_library(openlf openlf.cpp)
target_link_libraries(openlf ${OPENLF_LIBRARIES})

set(OPENLF_LIBRARIES ${OPENLF_LIBRARIES} openlf PARENT_SCOPE)