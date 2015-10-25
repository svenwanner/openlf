add_library(openlf_operators op_test.cpp  op_vigragauss.cpp op_vigragradientmagnitude.cpp op_scharr_x.cpp op_scharr_y.cpp op_tensor2x2.cpp op_scharr.cpp op_tensor2orientation.cpp op_saveimage.cpp op_normalize.cpp op_averagechannels.cpp op_mergedispbycoherence.cpp op_discdilation.cpp op_discerosion.cpp op_discmedian.cpp op_gaussiansharpening.cpp)

target_link_libraries(openlf_operators ${OPENLF_LIBRARIES})

set(OPENLF_LIBRARIES ${OPENLF_LIBRARIES} openlf_operators PARENT_SCOPE)