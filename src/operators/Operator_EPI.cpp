/* 
 * File:   Operator_EPI.cpp
 * Author: swanner
 * 
 * Created on May 15, 2014, 2:03 PM
 */

#include "OpenLF/operators/Operator_EPI.hpp"

OpenLF::operators::Operator_EPI::~Operator_EPI() {
    
}

/*!
 * This function initializes the internal lf variable with the address of the
 * lf instance passed. If in advance an additional Properties instance was set
 * the lf properties are updated with the additional properties passed.
 * If both property instances share the same fields the lf internal are overwritten 
 * with the values of the additional properties instance. This enables to update 
 * computation parameter during runtime.   
 */
void OpenLF::operators::Operator_EPI::set(OpenLF::lightfield::Lightfield *lf) 
{
    this->lf = lf;
    
    if(this->properties != NULL) {
        this->lf->appendProperties(*properties);
    }
}


void OpenLF::operators::Operator_EPI::load_epi_containers(std::string channel) {

    m_horizontal_epis.clear();
    m_vertical_epis.clear();

    //horizontal
    if (lf->type() == LF_4D || LF_3DH || LF_CROSS) {
        if (lf->hasChannel(channel)){
            shape epi_shape = shape(lf->imgWidth(),lf->cams_h());
            for (int i=0; i<lf->height(); i++) {
                view_1D row = lf->data()->find(channel)->second.viewToRow(i); 
                this->m_horizontal_epis.push_back (view_2D(epi_shape,row.data()));
            }
        }
        else throw OpenLF_Exception("Operator_EPI::loadEpiContainers -> no channel with that name available!");
    }

    //vertical
    if (lf->type() == LF_4D || LF_3DV || LF_CROSS) {
        shape epi_shape = shape(lf->imgHeight(),lf->cams_v());
        for (int i=0; i<lf->width(); i++) {
            view_1D column = lf->data()->find(channel)->second.viewToColumn(i); 
            this->m_vertical_epis.push_back (view_2D(epi_shape,column.data()));
        }
    } 
}

view_2D OpenLF::operators::Operator_EPI::refocus(int focus, view_2D epi) {

    int offset = (epi.height()-1)*focus;
    shape epi_shape = shape(epi.width()-(epi.height()-1)*focus,epi.height());
    strideTag stride = strideTag(1, epi.width() - focus);
    return view_2D(epi_shape, stride, epi.data() + offset);
}

epi_vector OpenLF::operators::Operator_EPI::refocus(int focus) {

    epi_vector refocused;
    for(auto it = horizontal_epis_ptr()->begin(); it<horizontal_epis_ptr()->end(); it++) {
        refocused.push_back(refocus(focus, *it));
    }   
    return refocused; 
}

epi_vector * OpenLF::operators::Operator_EPI::vertical_epis_ptr() {
    return &this->m_vertical_epis;
}

epi_vector * OpenLF::operators::Operator_EPI::horizontal_epis_ptr() {
    return &this->m_horizontal_epis;
}
view_2D OpenLF::operators::Operator_EPI::get_vertical_epi(int where) {
    return this->m_vertical_epis.at(where);
}

view_2D OpenLF::operators::Operator_EPI::get_horizontal_epi(int where) {
    return this->m_horizontal_epis.at(where);
}
