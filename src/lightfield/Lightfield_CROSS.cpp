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

bool OpenLF::lightfield::Lightfield_CROSS::open(const std::string filename)
{
    int b = this->OpenLF::lightfield::Lightfield::open(filename);
    // The intersec coordinates are the coordinates describing where the
    // vertical axis intersects the horizontal axis. So far, this is set to
    // the middle of both axises and we assume that both axises have an
    // odd number of pictures!
    m_properties.set_field("intersec_h",int(cams_h()/2));
    m_properties.set_field("intersec_v", int(cams_v()/2));
    return b;
}

/*!
 \author LukasDSauer
*/
int OpenLF::lightfield::Lightfield_CROSS::intersec_h(){
    int ih;
    m_properties.get_field("intersec_h",ih);
    return ih;
}

/*!
 \author LukasDSauer
*/
int OpenLF::lightfield::Lightfield_CROSS::intersec_v(){
    int iv;
    m_properties.get_field("intersec_v",iv);
    return iv;
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
        if(v==intersec_v()) img = m_channels[channel_name].viewToROI(h*imgWidth(),0,imgWidth(),imgHeight());
        else if(h==intersec_h()) img = m_channels[channel_name].viewToROI(v*imgHeight(),imgHeight(),imgHeight(),imgWidth());
    }
    
    else throw OpenLF_Exception("Lightfield::getImage -> unknown LF_TYPE!");
}

void OpenLF::lightfield::Lightfield_CROSS::getImage(int h, int v, vigra::MultiArray<2,float> &img){
    if(v==intersec_v()){
        OpenLF::lightfield::Lightfield::getImage(h, v, img);
    } else if(h==intersec_h()){
        if(!img.hasData())
        {
            //Height and Width are switched around, because the vertical axis is saved transposed.
            img = vigra::MultiArray<2,float>(shape(imgHeight(),imgWidth()));
        }
        else
        {
            //Height and Width are switched around, because the vertical axis is saved transposed.
            if(img.width() != imgHeight() || img.height() != imgWidth())
                throw OpenLF_Exception("Lightfield::getImage -> shape mismatch!");
        }

        if(hasRGB()) {
            vigra::MultiArrayView<2,float> img_r;
            getImage(h,v,"r",img_r);
            vigra::MultiArrayView<2,float> img_g;
            getImage(h,v,"g",img_g);
            vigra::MultiArrayView<2,float> img_b;
            getImage(h,v,"b",img_b);

            OpenLF::image::utils::mergeChannels(img_r,img_b,img_b,img);
        }
        else if(hasBW()) {
            vigra::MultiArrayView<2,float> img_bw;
            getImage(h,v,"bw",img_bw);
            img = vigra::MultiArray<2,float>(img_bw);
        }
        else throw OpenLF_Exception("Lightfield::getImage -> no image data available!");
    } else throw OpenLF_Exception("Lightfield_CROSS::getImage -> Either h or v must be an intersection point coordinate!");
}

void OpenLF::lightfield::Lightfield_CROSS::getImage(int h, int v, vigra::MultiArray<2,vigra::RGBValue<float>> &img){
    if(v==intersec_v()){
        OpenLF::lightfield::Lightfield::getImage(h, v, img);
    } else if(h==intersec_h()){
        if(!img.hasData())
        {
            //Height and Width are switched around, because the vertical axis is saved transposed.
            img = vigra::MultiArray<2,vigra::RGBValue<float>>(shape(imgHeight(),imgWidth()));
        }
        else
        {
            //Height and Width are switched around, because the vertical axis is saved transposed.
            if(img.width() != imgHeight() || img.height() != imgWidth())
                throw OpenLF_Exception("Lightfield::getImage -> shape mismatch!");
        }

        if(hasRGB()) {
            vigra::MultiArrayView<2,float> img_r;
            getImage(h,v,"r",img_r);
            vigra::MultiArrayView<2,float> img_g;
            getImage(h,v,"g",img_g);
            vigra::MultiArrayView<2,float> img_b;
            getImage(h,v,"b",img_b);

            OpenLF::image::utils::mergeChannels(img_r,img_g,img_b,img);
        }
        else if(hasBW())
        {
            vigra::MultiArrayView<2,float> img_bw;
            getImage(h,v,"bw",img_bw);

            for(int c=0; c<3; c++)
            {
                //Height and Width are switched around, because the vertical axis is saved transposed.
                for(int y=0; y<imgWidth(); y++)
                {
                    //Height and Width are switched around, because the vertical axis is saved transposed.
                    for(int x=0; x<imgHeight(); x++)
                    {
                        img(x,y)[c] = img_bw(x,y);
                    }
                }
            }
        }
        else throw OpenLF_Exception("Lightfield::getImage -> no rgb or bw image data available!");
    } else throw OpenLF_Exception("Lightfield_CROSS::getImage -> Either h or v must be an intersection point coordinate!");

}

void OpenLF::lightfield::Lightfield_CROSS::getImage(int h, int v, vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> > &img) {
    if (v == intersec_v()) {
        OpenLF::lightfield::Lightfield::getImage(h, v, img);
    } else if (h == intersec_h()) {
        if(!img.hasData())
        {
            //Height and Width are switched around, because the vertical axis is saved transposed.
            img = vigra::MultiArray<2,vigra::RGBValue<float>>(shape(imgHeight(),imgWidth()));
        }
        else
        {
            //Height and Width are switched around, because the vertical axis is saved transposed.
            if(img.width() != imgHeight() || img.height() != imgWidth())
                throw OpenLF_Exception("Lightfield::getImage -> shape mismatch!");
        }

        if(hasRGB()) {
            vigra::MultiArrayView<2,float> img_r;
            getImage(h,v,"r",img_r);
            vigra::MultiArrayView<2,float> img_g;
            getImage(h,v,"g",img_g);
            vigra::MultiArrayView<2,float> img_b;
            getImage(h,v,"b",img_b);

            OpenLF::image::utils::mergeChannels(img_r,img_g,img_b,img);
        }
        else if(hasBW())
        {
            vigra::MultiArrayView<2,float> img_bw;
            getImage(h,v,"bw",img_bw);

            for(int c=0; c<3; c++)
            {
                //Height and Width are switched around, because the vertical axis is saved transposed.
                for(int y=0; y<imgWidth(); y++)
                {
                    //Height and Width are switched around, because the vertical axis is saved transposed.
                    for(int x=0; x<imgHeight(); x++)
                    {
                        img(x,y)[c] = img_bw(x,y);
                    }
                }
            }
        }
        else throw OpenLF_Exception("Lightfield::getImage -> no rgb or bw image data available!");
    } else throw OpenLF_Exception("Lightfield_CROSS::getImage -> Either h or v must be an intersection point coordinate!");

}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
float OpenLF::lightfield::Lightfield_CROSS::getLoxel(int h, int v, int x, int y, const std::string channel_name)
{   
    float val = 0;
    
    // check if channel exists
    if (m_channels.find(channel_name) == m_channels.end())
        throw OpenLF_Exception("Lightfield::getImage -> channels doesn't exist!");
    
    
    if(type()==LF_CROSS) {
        // check if requested image is in range
        if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
            throw OpenLF_Exception("Lightfield::getLoxel -> out of light field bounds!");
        // If the vertival coordinate is intersec_v, then the image is on the horizontal axis.
        if(v==intersec_v()) {
            try {
                // The horizontal row of the CROSS lightfield is saved in the first row of the ImageChannel.
                val = m_channels[channel_name](h * imgWidth() + x, y);
            }
            catch (std::exception &e) {
                e = OpenLF_Exception("Lightfield::getLoxel -> channel access exception!");
                std::cout << e.what() << std::endl;
            }
        }//If the horizontal coordinate is intersec_h, then the image is on the vertical axis.
        else if(h==intersec_h()){
            try {
                // The vertival column of the CROSS is  saved transposed (!) in the second row of ImageChannel
                val = m_channels[channel_name](v*imgHeight()+y,imgHeight()+x);
            }
            catch(std::exception &e){
                e = OpenLF_Exception("Lightfield::getLoxel -> channel access exception!");
                std::cout << e.what() << std::endl;
            }    
        } else
            throw OpenLF_Exception(string("Lightfield_CROSS::getLoxel() -> either h or v must be the intersection point coordinate (H: ") + string(to_string(intersec_h())) + string(", V: ") + string(to_string(intersec_v())) +string( ")") );
        
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


view_2D OpenLF::lightfield::Lightfield_CROSS::getVerticalEpiChannel(std::string channel_name, int x, int h) {
    return OpenLF::lightfield::Lightfield_CROSS::getVerticalEpiChannel(channel_name, x, h, 0);
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

vigra::MultiArrayView<2,float> OpenLF::lightfield::Lightfield_CROSS::_getVerticalEpiChannel_CROSS(std::string channel_name, int x) {
    return OpenLF::lightfield::Lightfield_CROSS::_getVerticalEpiChannel_CROSS(channel_name, x, 0); 
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

vigra::MultiArrayView<2,float> OpenLF::lightfield::Lightfield_CROSS::getHorizontalEpiChannel(std::string channel_name, int y, int v){ 
    return OpenLF::lightfield::Lightfield_CROSS::getHorizontalEpiChannel(channel_name, y, v, 0);
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
