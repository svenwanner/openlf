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

#include "OpenLF/lightfield/Lightfield_4D.hpp"

OpenLF::lightfield::Lightfield_4D::Lightfield_4D() : OpenLF::lightfield::Lightfield() 
{
    print(1,"lightfield::Lightfield_4D() called...");
    
}

OpenLF::lightfield::Lightfield_4D::Lightfield_4D(const std::string filename) : OpenLF::lightfield::Lightfield(filename)
{
    print(1,"lightfield::Lightfield_4D(filename) called...");
}

OpenLF::lightfield::Lightfield_4D::~Lightfield_4D() 
{
    print(1,"lightfield::~Lightfield_4D() called...");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield_4D::getImage(int h, int v, const std::string channel_name, vigra::MultiArrayView<2,float> &img)
{
   // check if channel exists
    if (m_channels.find(channel_name) == m_channels.end())
        throw OpenLF_Exception("Lightfield::getImage -> channels doesn't exist!");
    
    // check if requested image is in range
    if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        throw OpenLF_Exception("Lightfield::getImage -> out of light field bounds!");
    
    if(type()==LF_4D) img = m_channels[channel_name].viewToROI(h*imgWidth(),v*imgHeight(),imgWidth(),imgHeight());
    
    else throw OpenLF_Exception("Lightfield::getImage -> unknown LF_TYPE!");  
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
float OpenLF::lightfield::Lightfield_4D::getLoxel(int h, int v, int x, int y, const std::string channel_name)
{
    //I added some additional checks that are set in comments at the moment
    // as I am not sure, wether they take to much time.
    
    // check if channel exists
    //if (m_channels.find(channel_name) == m_channels.end())
    //    throw OpenLF_Exception("Lightfield_4D::getLoxel -> channels doesn't exist!");
    float val = 0;
    
    if(type()==LF_4D) {
        // check if requested image is in range
        //if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        //    throw OpenLF_Exception("Lightfield_4D::getLoxel -> out of light field bounds!");
        
        try {
            val = m_channels[channel_name](h*imgWidth()+x,v*imgHeight()+y);
        }
        catch(std::exception &e)
        {
            e = OpenLF_Exception("Lightfield_4D::getLoxel -> channel access exception!");
            std::cout << e.what() << std::endl;
        }
        return val;
    }
    else throw OpenLF_Exception("Lightfield_4D::getLoxel -> unknown LF_TYPE!");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield_4D::getHorizontalEpiChannel(std::string channel_name, int y, int v, int focus) 
{
    vigra::MultiArrayView<2,float> tmp;
    
    if(type()==LF_4D) {
        if(v>=0 && v<=cams_v() && y>=0 && y<imgHeight())
            tmp = getHorizontalEpiChannel_parent(channel_name,y,v,focus);
        else
            throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> out of bounce!");
    }
    
    return tmp;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
vigra::MultiArrayView<2,float> OpenLF::lightfield::Lightfield_4D::getVerticalEpiChannel(std::string channel_name, int x, int h, int focus) 
{
    vigra::MultiArrayView<2,float> tmp;
    
    if(type()==LF_4D) {
        if(h>=0 && h<=cams_h() && x>=0 && x<imgWidth())
            // if channel exist
            if (hasChannel(channel_name)) {

                int offset = (cams_v()-1)*focus*width();
                vigra::MultiArrayView<1, float> col = m_channels[channel_name].viewToColumn(h * imgWidth() + x);
                shape epi_shape = shape(cams_v(),imgHeight()-(cams_v()-1)*focus);
                strideTag stride = strideTag((imgHeight()-focus)*width(),col.stride()[0]);
                tmp = view_2D(epi_shape, stride, col.data() + offset).transpose();

            } else
                throw OpenLF_Exception("Lightfield::_getHorizontalEpi_4D -> channel not available!");
        
        else
            throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> out of bounce!");
    }
    
    else
        throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> unknown light field type!");
    
    return tmp; 
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::EpiIterator_4D::EpiIterator_4D(Lightfield *lf, DIRECTION direction)
{
    this->m_lf = lf;
    this->m_direction = direction;
    m_finished = false;
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::EpiIterator_4D::~EpiIterator_4D()
{

}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::EpiIterator_4D::first()
{
    m_camera_index = 0;
    m_epi_index = 0;
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::EpiIterator_4D::next()
{
    m_epi_index++;
    
    if(m_lf->type() == LF_4D)
    {
        if(m_direction == VERTICAL)
        {
            if(m_epi_index >= m_lf->imgWidth())
            {
                m_epi_index = 0;
                m_camera_index++;
            }
            if(m_camera_index >= m_lf->cams_h())
                m_finished = true;
        }
        else if(m_direction == HORIZONTAL)
        {
            if(m_epi_index >= m_lf->imgHeight())
            {
                m_epi_index = 0;
                m_camera_index++;
            }
            if(m_camera_index >= m_lf->cams_v())
                m_finished = true;
        }
    }
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::EpiIterator_4D::end()
{
    return m_finished;
}

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::EpiIterator_4D::get(std::string channel_name, int focus)
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