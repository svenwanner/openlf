

add_library(openlf_components SHARED comp_epi.cpp comp_gauss.cpp)
target_link_libraries(openlf_components clif cliini clif_vigra DSPatch ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})