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
// TODO
/*
void OpenLF::operators::Operator_EPI::load_epi_containers() {

    m_horizontal_epis.clear();
    m_vertical_epis.clear();

    std::vector <std::string> channels = lf->getListOfChannelNames();

    if (lf->type() == LF_4D || LF_3DH || LF_CROSS) {
        
	shape epi_shape = shape(lf->imgWidth(),lf->cams_h());
        for(auto it = channels.begin(); it != channels.end(); it++)
	    for (int i=0; i<lf->height(); i++) {
		view_1D row = lf->data()->find(channel)->second.viewToRow(i); 
		this->m_horizontal_epis[it->first()].push_back (view_2D(epi_shape,row.data()));
	    }
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
*/
/* gets the focus of the members m_horizontal_refocused and m_vertical_refocused */

double OpenLF::operators::Operator_EPI::get_focus(std::string channel) {
    return m_focuses[channel]; //horizontal only!
}

// CHANGE
void OpenLF::operators::Operator_EPI::load_epi_containers(std::string channel) {

    m_horizontal_epis[channel].clear();
    m_vertical_epis[channel].clear();
    m_focuses[channel] = 0.0; //horizontal only!

    //horizontal
    if (lf->type() == LF_4D || LF_3DH || LF_CROSS) {
        if (lf->hasChannel(channel)){
            shape epi_shape = shape(lf->imgWidth(),lf->cams_h());
            for (int i=0; i<lf->height(); i++) {
                view_1D row = lf->data()->find(channel)->second.viewToRow(i); 
                m_horizontal_epis[channel].push_back(array_2D(epi_shape,row.data()));
            }
        }
        else throw OpenLF_Exception("Operator_EPI::loadEpiContainers -> no channel with that name available!");
    }
    
    //vertical
    if (lf->type() == LF_4D || LF_3DV || LF_CROSS) {
        if (lf->hasChannel(channel)){
            shape epi_shape = shape(lf->imgHeight(),lf->cams_v());
            for (int i=0; i<lf->width(); i++) {
                vigra::MultiArray<2,float> image = *(lf->data()->find(channel)->second.image());
                vigra::MultiArray<1,float> column(image.bind<0>(i));
                m_vertical_epis[channel].push_back(array_2D(epi_shape,column.data())); 
            }
        }
    }
    
}

/* this function refocuses a given epi, leaving shape the same */
view_2D OpenLF::operators::Operator_EPI::refocus(int focus, view_2D epi) {
    int offset = (epi.height()-1)*focus;
    shape epi_shape = shape(epi.width()-(epi.height()-1)*focus,epi.height());
    strideTag stride = strideTag(1, epi.width() - focus);
    return view_2D(epi_shape, stride, epi.data() + offset);
}

/* this function refocuses a given epi, leaving shape the same */
/*
epi_borders OpenLF::operators::Operator_EPI::refocus_borders(int focus, view_2D epi) {
    int offset = (epi.height()-1)*focus;
    shape epi_shape = shape(epi.width()-(epi.height()-1)*focus,epi.height());
    strideTag stride = strideTag(1, epi.width() - focus);
    epi_borders_view epi_data(epi_shape, stride, epi.data() + offset);
    epi_borders epi_final(epi.shape());
    for (int i=0;i<epi.width();i++) {
        for (int j=0;j<epi.height;j++) {
            if (i < offset || i >= epi_data.width+offset) {
                epi_final(i,j) = 0.0;
            }
            else {
                epi_final(i,j) = epi_data(i-offset,j);
            }
        }
    }
}
*/

OpenLF::operators::epi OpenLF::operators::Operator_EPI::refocus_uncut(int focus, epi epi) {
    if (epi.focus == -pow(10,6)) {
        throw OpenLF_Exception("OpenLF::operators::Operator_EPI::refocus_uncut -> no focus initialized!");
    }

    OpenLF::operators::epi epi_tmp = OpenLF::operators::Operator_EPI::backfocus(epi);
    OpenLF::operators::epi epi_new;
    epi_new.EPI = refocus_uncut(focus, epi_tmp.EPI);
    epi_new.focus = focus;

    return epi_new;
}

OpenLF::operators::epi OpenLF::operators::Operator_EPI::refocus_uncut(int focus, epi_view epi) {
    if (epi.focus == -pow(10,6)) {
        throw OpenLF_Exception("OpenLF::operators::Operator_EPI::refocus_uncut -> no focus initialized!");
    }
    OpenLF::operators::epi epi_tmp;
    epi_tmp.focus = epi.focus;
    epi_tmp.EPI = epi.EPI;
    epi_tmp = OpenLF::operators::Operator_EPI::backfocus(epi_tmp);
    OpenLF::operators::epi epi_new;
    epi_new.EPI = refocus_uncut(focus, epi_tmp.EPI);
    epi_new.focus = focus;

    return epi_new;
}

// only for internal use with original (not previously refocused) epis with focus 0
array_2D OpenLF::operators::Operator_EPI::refocus_uncut(int focus, view_2D epi) {

    int width_offset = epi.height()*abs(focus);
    vigra::Shape2 epi_shape = vigra::Shape2(epi.width()+width_offset,epi.height());
    array_2D epi_new(epi_shape, 0.0);

    if (focus > 0) {
        for (int j=0;j<epi.height();j++) {
            for (int i=0;i<epi.width();i++) {
                epi_new(i+focus*j,j) = epi(i,j);
            }
        }
    } 
    if (focus < 0) {
        for (int j=0;j<epi.height();j++) {
            for (int i=0;i<epi.width();i++) {
                epi_new(i+width_offset-abs(focus)*j,j) = epi(i,j);
            }
        }
    }
    if (focus==0) {
        epi_new = epi;
    }

    return epi_new;
}


// back to focus 0
OpenLF::operators::epi OpenLF::operators::Operator_EPI::backfocus(epi epi) {
    if (epi.focus == -pow(10,6)) {
        throw OpenLF_Exception("OpenLF::operators::Operator_EPI::refocus_uncut -> no focus initialized!");
    }
    OpenLF::operators::epi epi_new;
    int width = epi.EPI.width()-abs(epi.focus)*epi.EPI.height();
    epi_new.EPI = array_2D(vigra::Shape2(width, epi.EPI.height()), 0.0);
    epi_new.focus = 0;

    if (epi.focus > 0) {
        for (int j=0;j<epi_new.EPI.height();j++) {
            for (int i=0;i<epi_new.EPI.width();i++) {
                epi_new.EPI(i,j) = epi.EPI(i+epi.focus*j,j);
            }
        }
    } 
    if (epi.focus < 0) {
        for (int j=0;j<epi_new.EPI.height();j++) {
            for (int i=0;i<epi_new.EPI.width();i++) {
                epi_new.EPI(i,j) = epi.EPI(i+epi.EPI.height()*abs(epi.focus)-abs(epi.focus)*j,j);
            }
        }
    }
    if (epi.focus == 0) {
        epi_new.EPI = epi.EPI;
    }
    return epi_new;
}

// back to focus 0
/*
OpenLF::operators::epi OpenLF::operators::Operator_EPI::backfocus(epi_view epi) {
    if (epi.focus == -pow(10,6)) {
        throw OpenLF_Exception("OpenLF::operators::Operator_EPI::refocus_uncut -> no focus initialized!");
    }
    OpenLF::operators::epi epi_new;
    epi_new.EPI = array_2D(vigra::Shape2(epi.EPI.width()-epi.focus*epi.EPI.height(), epi.EPI.height()), 0.0);
    epi_new.focus = 0;

    if (epi.focus > 0) {
        for (int j=0;j<epi.EPI.height();j++) {
            for (int i=0;i<epi.EPI.width();i++) {
                epi_new.EPI(i,j) = epi.EPI(i+epi.focus*j,j);
            }
        }
    } 
    if (epi.focus < 0) {
        for (int j=0;j<epi.EPI.height();j++) {
            for (int i=0;i<epi.EPI.width();i++) {
                epi_new.EPI(i,j) = epi.EPI(i+epi.EPI.width()*epi.focus-epi.focus*j,j);
            }
        }
    }
    if (epi.focus == 0) {
        epi_new.EPI = epi.EPI;
    }
    return epi_new;
}
*/
/*
epi_vector OpenLF::operators::Operator_EPI::refocus(int focus) {

    epi_vector refocused;
    for(auto it = horizontal_epis_ptr()->begin(); it<horizontal_epis_ptr()->end(); it++) {
        refocused.push_back(refocus(focus, *it));
    }   
    return refocused; 
}
*/

/* this function refocuses the member maps m_horizontal_refocused and m_vertical_refocused */
void OpenLF::operators::Operator_EPI::refocus(int focus, std::string channel) {

    m_focuses[channel] = focus;
    //int height = lf->cams_v()*lf->imgHeight();
    //int width = lf->cams_h()*lf->imgWidth();
    m_horizontal_refocused[channel].clear();
    m_vertical_refocused[channel].clear();
    //m_horizontal_refocused[channel] = epi_vector(height,array_2D());
    //m_vertical_refocused[channel] = epi_vector(width,array_2D());

    for(auto it = m_horizontal_epis[channel].begin(); it != m_horizontal_epis[channel].end(); it++) {
        //m_horizontal_refocused[channel].push_back(refocus_uncut(focus, *it));
         m_horizontal_refocused[channel].push_back(*it);
    }   
    for(auto it = m_vertical_epis[channel].begin(); it != m_vertical_epis[channel].end(); it++) {
        //m_vertical_refocused[channel].push_back(refocus_uncut(focus, *it));
        m_vertical_refocused[channel].push_back(*it);
    }   
}

//OpenLF::operators::epi_vector * vertical_epis_ptr(std::string channel);


OpenLF::operators::epi_vector * OpenLF::operators::Operator_EPI::vertical_epis_ptr(std::string channel) {
    return &this->m_vertical_epis[channel];
}

OpenLF::operators::epi_vector * OpenLF::operators::Operator_EPI::horizontal_epis_ptr(std::string channel) {
    return &this->m_horizontal_epis[channel];
}
array_2D OpenLF::operators::Operator_EPI::get_vertical_epi(std::string channel, int where) {
    return this->m_vertical_epis[channel].at(where);
}

array_2D OpenLF::operators::Operator_EPI::get_horizontal_epi(std::string channel,int where) {
    return this->m_horizontal_epis[channel].at(where);
}

//TODO
/*
int OpenLF::operators::Operator_EPI::nr_epis(std::string channel, DIRECTION direction) {
    if (direction == HORIZONTAL) {
        return m_horizontal_epis[channel].size();
    }
    if (direction == VERTICAL) {
        return m_vertical_epis[channel].size();
    }
}
*/
