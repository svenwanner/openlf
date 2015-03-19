/*
* Copyright (c) 2014 Sven Wanner
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of 
* this software and associated documentation files (the "Software"), to deal in 
* the Software without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
* Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all 
* copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "OpenLF/lightfield/Lightfield_CROSS.hpp"

OpenLF::lightfield::Lightfield_CROSS::Lightfield_CROSS() : OpenLF::lightfield::Lightfield() 
{
    print(1,"lightfield::Lightfield_CROSS() called...");
    
}

OpenLF::lightfield::Lightfield_CROSS::Lightfield_CROSS(const std::string filename) : OpenLF::lightfield::Lightfield(filename)
{
    print(1,"lightfield::Lightfield_CROSS(filename) called...");
}

OpenLF::lightfield::Lightfield_CROSS::~Lightfield_CROSS() 
{
    print(1,"lightfield::~Lightfield_CROSS() called...");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield_CROSS::getImage(int h, int v, const std::string channel_name, vigra::MultiArrayView<2,float> &img)
{
    // check if channel exists
    if (m_channels.find(channel_name) == m_channels.end())
        throw OpenLF_Exception("Lightfield::getImage -> channels doesn't exist!");
    
    // check if requested image is in range
    if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        throw OpenLF_Exception("Lightfield::getImage -> out of light field bounds!");
    
    
    if(type()==LF_CROSS) {
        if(v==0) img = m_channels[channel_name].viewToROI(h*imgWidth(),0,imgWidth(),imgHeight());
        else if(h==0) img = m_channels[channel_name].viewToROI(v*imgHeight(),imgHeight(),imgHeight(),imgWidth());
    }
    
    else throw OpenLF_Exception("Lightfield::getImage -> unknown LF_TYPE!");
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
float OpenLF::lightfield::Lightfield_CROSS::getLoxel(int h, int v, int x, int y, const std::string channel_name)
{   
    //I added some additional checks that are set in comments at the moment
    // as I am not sure wether they take to much time.
    float val = 0;
    
    // check if channel exists
    //if (m_channels.find(channel_name) == m_channels.end())
    //    throw OpenLF_Exception("Lightfield::getImage -> channels doesn't exist!");
    
    
    if(type()==LF_CROSS) {
        // check if requested image is in range
        //if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        //    throw OpenLF_Exception("Lightfield::getImage -> out of light field bounds!");
        try {
            val = m_channels[channel_name](h*imgWidth()+x,v*imgHeight()+y);
        }
        catch(std::exception &e)
        {
            e = OpenLF_Exception("Lightfield::getLoxel -> channel access exception!");
            std::cout << e.what() << std::endl;
        }
        return val;
    }
    
    else throw OpenLF_Exception("Lightfield::getLoxel -> unknown LF_TYPE!");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield_CROSS::getVerticalEpiChannel(std::string channel_name, int x, int h, int focus) 
{
    vigra::MultiArrayView<2,float> tmp;
    
    if (h!=0) {
        throw OpenLF_Exception("Lightfield::loxel -> for the lightfield type CROSS h must be 0!");
    }

    if(type()==LF_CROSS) {
        if(x>=0 && x<imgWidth())
            tmp = _getVerticalEpiChannel_CROSS(channel_name, x, focus);
        else
            throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> out of bounce!");
    }
    return tmp;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
vigra::MultiArrayView<2,float> OpenLF::lightfield::Lightfield_CROSS::_getVerticalEpiChannel_CROSS(std::string channel_name, int x, int focus) 
{
    // if channel exist
    if (hasChannel(channel_name)) {
        
//        int offset = (cams_v()-1)*focus;
//        //vigra::MultiArrayView<2, float> row = channels[channel_name].viewToROI(0, imgHeight()+x, cams_v()*imgHeight());
//        vigra::MultiArrayView<1, float> row = channels[channel_name].viewToRow(imgHeight()+x);
//        shape epi_shape = shape(imgHeight()-(cams_v()-1)*focus,cams_v());
//        strideTag stride = strideTag(1, imgHeight() - focus);
//        return view_2D(epi_shape, stride, row.data() + offset);
        
        int offset = (cams_v()-1)*focus;
        vigra::MultiArrayView<1, float> row = m_channels[channel_name].viewToRow(imgHeight() + x);
        shape epi_shape = shape(imgHeight()-(cams_v()-1)*focus,cams_v());
        strideTag stride = strideTag(1, imgHeight() - focus);
        return view_2D(epi_shape, stride, row.data() + offset);
        
    } else
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_3DV -> channel not available!");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
vigra::MultiArrayView<2,float> OpenLF::lightfield::Lightfield_CROSS::getHorizontalEpiChannel(std::string channel_name, int y, int v, int focus)
{
    if (v!=0) {
        throw OpenLF_Exception("Lightfield::loxel -> for the lightfield type CROSS v must be 0!");
    }

    return getHorizontalEpiChannel_parent(channel_name, y, 0, focus);
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::EpiIterator_CROSS::EpiIterator_CROSS(Lightfield *lf, DIRECTION direction)
{
    this->m_lf = lf;
    this->m_direction = direction;
    m_finished = false;
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::EpiIterator_CROSS::~EpiIterator_CROSS()
{

}


/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::EpiIterator_CROSS::first()
{
    m_camera_index = 0;
    m_epi_index = 0;
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::EpiIterator_CROSS::next()
{
    m_epi_index++;
    
    if(m_lf->type() == LF_CROSS)
    {
        if(m_direction == VERTICAL)
        {
            if(m_epi_index >= m_lf->imgWidth())
            {
                m_finished = true;
            }
        }
        else if(m_direction == HORIZONTAL)
        {
            if(m_epi_index >= m_lf->imgHeight())
            {
                m_finished = true;
            }
        }
    }
}


/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::EpiIterator_CROSS::end()
{
    return m_finished;
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::EpiIterator_CROSS::get(std::string channel_name, int focus)
{
    if(!this->m_lf->hasChannel(channel_name))
        throw OpenLF_Exception("EpiIterator::get -> channel not available!");
    
    if(m_direction == VERTICAL)
        return m_lf->getVerticalEpiChannel(channel_name, m_epi_index, m_camera_index, focus);
    else if(m_direction == HORIZONTAL)
        return m_lf->getHorizontalEpiChannel(channel_name, m_epi_index, m_camera_index, focus);
    else
        throw OpenLF_Exception("EpiIterator::get -> unknown direction!");
}
