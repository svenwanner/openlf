add_library(openlf_components comp_lfread.cpp comp_lfwrite.cpp comp_epi.cpp comp_dispwrite.cpp)
target_link_libraries(openlf_components ${OPENLF_LIBRARIES})
set(OPENLF_LIBRARIES ${OPENLF_LIBRARIES} openlf_components PARENT_SCOPE)

add_library(lfread MODULE comp_lfread.cpp)
target_link_libraries(lfread ${OPENLF_LIBRARIES} dl)

