add_library(openlf_workflows wkf_structuretensor.cpp)
target_link_libraries(openlf_workflows ${OPENLF_LIBRARIES})

set(OPENLF_LIBRARIES ${OPENLF_LIBRARIES} openlf_workflows PARENT_SCOPE)