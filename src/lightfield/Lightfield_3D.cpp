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

#include "OpenLF/lightfield/Lightfield_3D.hpp"

OpenLF::lightfield::Lightfield_3D::Lightfield_3D() : OpenLF::lightfield::Lightfield() 
{
    print(1,"lightfield::Lightfield_3D() called...");
    
}

OpenLF::lightfield::Lightfield_3D::Lightfield_3D(const std::string filename) : OpenLF::lightfield::Lightfield(filename)
{
    print(1,"lightfield::Lightfield_3D(filename) called...");
}

OpenLF::lightfield::Lightfield_3D::~Lightfield_3D() 
{
    print(1,"lightfield::~Lightfield_3D() called...");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield_3D::getImage(int h, int v, const std::string channel_name, vigra::MultiArrayView<2,float> &img)
{
    // check if channel exists
    if (m_channels.find(channel_name) == m_channels.end())
        throw OpenLF_Exception("Lightfield_3D::getImage -> channels doesn't exist!");
    
    // check if requested image is in range
    if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        throw OpenLF_Exception("Lightfield::getImage -> out of light field bounds!");
    
    
    if(type()==LF_3DV) img = m_channels[channel_name].viewToROI(v*imgHeight(),0,imgHeight(),imgWidth());
    
    else if(type()==LF_3DH) img = m_channels[channel_name].viewToROI(h*imgWidth(),0,imgWidth(),imgHeight());
    
    else throw OpenLF_Exception("Lightfield::getImage -> unknown LF_TYPE!");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
float OpenLF::lightfield::Lightfield_3D::getLoxel(int h, int v, int x, int y, const std::string channel_name)
{
    float val = 0;
    
    if(type()==LF_3DV) {
        return val;
    }
    
    else if(type()==LF_3DH) {
        
        try {
            val = m_channels[channel_name](h*imgWidth()+x,y);
        }
        catch(std::exception &e)
        {
            e = OpenLF_Exception("Lightfield::loxel -> channel access exception!");
            std::cout << e.what() << std::endl;
        }
        return val;
    }
    
    else throw OpenLF_Exception("Lightfield::loxel -> unknown LF_TYPE!");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield_3D::getVerticalEpiChannel(std::string channel_name, int x, int h, int focus) 
{
    vigra::MultiArrayView<2,float> tmp;
    tmp = _getVerticalEpiChannel_3D(channel_name, x, focus);
    return tmp;
}

view_2D OpenLF::lightfield::Lightfield_3D::getHorizontalEpiChannel(std::string channel_name, int y, int v, int focus) 
{
    vigra::MultiArrayView<2,float> tmp;
    
    if(type()==LF_3DH) {
        if(y>=0 && y<imgHeight())
            tmp = getHorizontalEpiChannel_parent(channel_name,y,0,focus);
        else
            throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> out of bounce!");
    }
    else if(type()==LF_3DV) {
        throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> no epis available for this LF_TYPE!");
    }
    return tmp;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield_3D::_getVerticalEpiChannel_3D(std::string channel_name, int x, int focus) 
{
    vigra::MultiArrayView<2,float> tmp;
    if(type()==LF_3DH) {
        throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> no epis available for this LF_TYPE!");
    }
    
    else if(type()==LF_3DV) {
        if(x>=0 && x<imgWidth())
            
            // if channel exist
            if (hasChannel(channel_name)) {   
                int offset = (cams_v()-1)*focus;
                vigra::MultiArrayView<1, float> row = m_channels[channel_name].viewToRow(x);
                shape epi_shape = shape(imgHeight()-(cams_v()-1)*focus,cams_v());
                strideTag stride = strideTag(1, imgHeight() - focus);
                tmp = view_2D(epi_shape, stride, row.data() + offset);   
            } else
                throw OpenLF_Exception("Lightfield::_getHorizontalEpi_3DV -> channel not available!");
        else
            throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> out of bounce!");
    }
    return tmp;  
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::EpiIterator_3D::EpiIterator_3D(Lightfield *lf, DIRECTION direction)
{
    this->m_lf = lf;
    this->m_direction = direction;
    m_finished = false;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::EpiIterator_3D::~EpiIterator_3D()
{

}


/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::EpiIterator_3D::first()
{
    m_camera_index = 0;
    m_epi_index = 0;
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::EpiIterator_3D::next()
{
    m_epi_index++;
    
    if(m_lf->type() == LF_3DH)
    {
        if(m_direction == VERTICAL)
        {
            throw OpenLF_Exception("EpiIterator::get -> unknown direction!");
        }
        else if(m_direction == HORIZONTAL)
        {
            if(m_epi_index >= m_lf->imgHeight())
            {
                m_finished = true;
            }
                
        }
    }
    if(m_lf->type() == LF_3DV)
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
            throw OpenLF_Exception("EpiIterator::get -> unknown direction!");
        }
    }
}


/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::EpiIterator_3D::end()
{
    return m_finished;
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::EpiIterator_3D::get(std::string channel_name, int focus)
{
    if(!this->m_lf->hasChannel(channel_name))
        throw OpenLF_Exception("EpiIterator::get -> channel not available!");
    
    if(m_direction == VERTICAL)
        //return m_lf->getVerticalEpiChannel_3D(channel_name, m_epi_index, focus);
        return m_lf->getVerticalEpiChannel(channel_name, m_epi_index, m_camera_index, focus);
    else if(m_direction == HORIZONTAL)
        return m_lf->getHorizontalEpiChannel(channel_name, m_epi_index, m_camera_index, focus);
    else
        throw OpenLF_Exception("EpiIterator::get -> unknown direction!");
}