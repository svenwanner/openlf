
add_library(openlf_operators SHARED op_gauss.cpp)
target_link_libraries(openlf_operators clif cliini clif_vigra DSPatch ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})