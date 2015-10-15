add_library(openlf_workflows wkf_structuretensor.cpp)
target_link_libraries(openlf_workflows clif cliini clif_vigra DSPatch ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})