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

#include "OpenLF/lightfield/Lightfield.hpp"
#include "OpenLF/image/utils.hpp"


namespace OpenLF {
namespace lightfield {



////////////////////////////////////////////////////////////////////////////////
//////                        G E T    I N F O S 
////////////////////////////////////////////////////////////////////////////////

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool Lightfield_base::hasRGB()
{
    if (channels.find("r") == channels.end()) return false;
    if (channels.find("g") == channels.end()) return false;
    if (channels.find("b") == channels.end()) return false;
    return true;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool Lightfield_base::hasBW()
{
    if (channels.find("bw") == channels.end()) return false;
    return true;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool Lightfield_base::hasChannel(std::string name)
{
    if (channels.find(name) == channels.end()) return false;
    else return true;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
std::vector<std::string> Lightfield_base::getListOfChannelNames()
{
  
    std::vector<std::string> v;
    for(std::map<std::string,image::ImageChannel>::iterator it = channels.begin(); it != channels.end(); ++it)
        v.push_back(it->first);
        return v;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool Lightfield_base::hasProperty(std::string name) {
    return properties.has_field(name);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool Lightfield_base::getProperty(std::string name, int &value)
{
    return properties.get_field(name,value);
}
    

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool Lightfield_base::getProperty(std::string name, float &value)
{
    return properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool Lightfield_base::getProperty(std::string name, double &value)
{
    return properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool Lightfield_base::getProperty(std::string name, std::string &value)
{
    return properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
/*
LF_TYPE Lightfield_base::type()
{
    LF_TYPE lftype;
    properties.get_lftype(lftype);
    return lftype;
}
*/


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int Lightfield_base::imgWidth()
{
    int sx;
    properties.get_field("width",sx);
    return sx;
}

    
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int Lightfield_base::imgHeight()
{
    int sy;
    properties.get_field("height",sy);
    return sy;
}
    

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int Lightfield_base::width()
{
    int sx;
    properties.get_field("width",sx);
    return sx*cams_h();
}

    
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int Lightfield_base::height()
{
    int sy;
    properties.get_field("height",sy);
    return sy*cams_v();
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int Lightfield_base::cams_h()
{
    int sh;
    properties.get_field("cams_h",sh);
    return sh;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int Lightfield_base::cams_v()
{
    int sv;
    properties.get_field("cams_v",sv);
    return sv;
}
    
int Lightfield_base::cams(DIRECTION d)
{
    if (d == HORIZONTAL)
        return cams_h();
    else if (d == VERTICAL)
        return cams_v();
    throw OpenLF_Exception("invalid direction");
}







////////////////////////////////////////////////////////////////////////////////
//////                      A C C E S S    D A T A
//////////////////////////////////////////////////////////////////////////////// 
   

/*!
 Returns the data pointer to the channel specified by the channel_name.
 If the channel key doesn't exist a NULL pointer is returned.
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
float* Lightfield_base::channel_ptr(std::string channel_name) {
    print(1,"lightfield::Lightfield_base::channel_ptr(channel_name,channel_data) called...");
    
    // check if channel exists
    if (channels.find(channel_name) == channels.end()) return NULL;
    else return channels[channel_name].data();
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void Lightfield_base::data(std::map<std::string,image::ImageChannel> **channels) {
    print(1,"lightfield::Lightfield_base::data(channels) called...");
    
    *channels = &this->channels;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
std::map<std::string,image::ImageChannel> * Lightfield_base::data() {
    print(1,"lightfield::Lightfield_base::data(channels) called...");
    
    return &this->channels;
}


/*!
 Returns a pointer to the channel specified by the channel_name.
 If the channel key doesn't exist a NULL pointer is returned.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
image::ImageChannel *Lightfield_base::data(std::string channel_name) {
    print(1,"lightfield::Lightfield_base::data(channel_name,channel_data) called...");
    
    // check if channel exists
    if (channels.find(channel_name) == channels.end()) return NULL;
    else return &channels[channel_name];
}


/*!
 Returns a pointer to the channel specified by the channel_name.
 If the channel key doesn't exist a NULL pointer is returned.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void Lightfield_base::data(std::string channel_name, image::ImageChannel **channel_data) {
    print(1,"lightfield::Lightfield_base::data(channel_name,channel_data) called...");
    
    // check if channel exists
    if (channels.find(channel_name) == channels.end()) *channel_data = NULL;
    else *channel_data = &channels[channel_name];
}


/*!
 Allocates a new channel with the name passed. The channels size is defined by
 the size of the light field.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void Lightfield_base::allocateChannel(std::string channel_name)
{
    print(1,"lightfield::Lightfield_base::allocateChannel(channel_name) called...");
    
    // check if channel doesn't exists otherwise throw Exception
    if (channels.find(channel_name) == channels.end()) {
        channels[channel_name] = image::ImageChannel(width(),height());
    }
    else {
       throw OpenLF_Exception("Cannot allocate channel that already exist!");
    }
}


/*!
 Important: If a field of the passed properties instance already exist
 in the internal properties instance the internal value is overwritten.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void Lightfield_base::appendProperties(Properties &properties) {
    this->properties += properties;
}


template<>
float Lightfield<LF_4D>::getLoxel(int h, int v, int x, int y,
        std::string const & channel_name)
{
    try {
        return channels[channel_name](h*imgWidth()+x,v*imgHeight()+y);
    }
    catch(std::exception &e)
    {
        throw OpenLF_Exception("Lightfield::loxel -> channel access exception!");
    }
}

template<>
float Lightfield<LF_3DV>::getLoxel(int h, int v, int x, int y,
        std::string const & channel_name)
{
    // FIXME
    return 0.;
}

template<>
float Lightfield<LF_3DH>::getLoxel(int h, int v, int x, int y,
        std::string const & channel_name)
{
    try {
        return channels[channel_name](h*imgWidth()+x,y);
    }
    catch(std::exception &e)
    {
        throw OpenLF_Exception("Lightfield::loxel -> channel access exception!");
    }
}

template<>
float Lightfield<LF_CROSS>::getLoxel(int h, int v, int x, int y,
        std::string const & channel_name)
{
    //FIXME
    return 0.;
}

template<>
void Lightfield<LF_CROSS>::getImage(int h, int v,
        std::string const & channel_name,
        vigra::MultiArrayView<2,float> &img)
{
    // check if requested image is in range
    if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        throw OpenLF_Exception("Lightfield::getImage -> out of light field bounds!");

    // check if channel exists
    auto cur_channel = channels.find(channel_name);
    if (cur_channel == channels.end())
        throw OpenLF_Exception("Lightfield::getImage -> channels doesn't exist!");

    // handle all light field cases
    if(v==0)
        img = cur_channel->second.viewToROI(h*imgWidth(), 0,
                imgWidth(), imgHeight());
    else if(h==0)
        img = cur_channel->second.viewToROI(v*imgHeight(), imgHeight(),
                imgHeight(), imgWidth());
}

template<>
void Lightfield<LF_3DV>::getImage(int h, int v,
        std::string const & channel_name,
        vigra::MultiArrayView<2,float> &img)
{
    // check if requested image is in range
    if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        throw OpenLF_Exception("Lightfield::getImage -> out of light field bounds!");

    // check if channel exists
    auto cur_channel = channels.find(channel_name);
    if (cur_channel == channels.end())
        throw OpenLF_Exception("Lightfield::getImage -> channels doesn't exist!");

    img = cur_channel->second.viewToROI(v*imgHeight(), 0,
            imgHeight(), imgWidth());
}

template<>
void Lightfield<LF_3DH>::getImage(int h, int v,
        std::string const & channel_name,
        vigra::MultiArrayView<2,float> &img)
{
    // check if requested image is in range
    if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        throw OpenLF_Exception("Lightfield::getImage -> out of light field bounds!");

    // check if channel exists
    auto cur_channel = channels.find(channel_name);
    if (cur_channel == channels.end())
        throw OpenLF_Exception("Lightfield::getImage -> channels doesn't exist!");

    img = cur_channel->second.viewToROI(h*imgWidth(), 0,
            imgWidth(), imgHeight());
}

template<>
void Lightfield<LF_4D>::getImage(int h, int v,
        std::string const & channel_name,
        vigra::MultiArrayView<2,float> &img)
{
    // check if requested image is in range
    if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        throw OpenLF_Exception("Lightfield::getImage -> out of light field bounds!");

    // check if channel exists
    auto cur_channel = channels.find(channel_name);
    if (cur_channel == channels.end())
        throw OpenLF_Exception("Lightfield::getImage -> channels doesn't exist!");

    img = cur_channel->second.viewToROI(h*imgWidth(), v*imgHeight(),
            imgWidth(), imgHeight());
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<>
vigra::MultiArrayView<2, float> Lightfield<LF_4D>::getHorizontalEpiChannel(
        std::string const & channel_name, int y, int v, int focus)
{
    if(v>=0 && v<=cams_v() && y>=0 && y<imgHeight())
        return _getHorizontalEpiChannel_4D(v,y,channel_name,focus);
    else
        throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> out of bounce!");
}

template<>
vigra::MultiArrayView<2, float> Lightfield<LF_3DH>::getHorizontalEpiChannel(
        std::string const & channel_name, int y, int v, int focus)
{
    if(y>=0 && y<imgHeight())
        return _getHorizontalEpiChannel_4D(0,y,channel_name,focus);
    else
        throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> out of bounce!");
}

template<>
vigra::MultiArrayView<2, float> Lightfield<LF_3DV>::getHorizontalEpiChannel(
        std::string const & channel_name, int y, int v, int focus)
{
    throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> no epis available for this LF_TYPE!");
}

template<>
vigra::MultiArrayView<2, float> Lightfield<LF_CROSS>::getHorizontalEpiChannel(
        std::string const & channel_name, int y, int v, int focus)
{
    if(y>=0 && y<imgHeight())
        return  _getHorizontalEpiChannel_4D(0,y,channel_name,focus);
    else
        throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> out of bounce!");
}



template<>
vigra::MultiArrayView<2,float> Lightfield<LF_4D>::getVerticalEpiChannel(
        std::string const & channel_name, int x, int h, int focus)
{
    if (h < 0 || h >= cams_h() || x < 0 || x >= imgWidth())
        throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> out of bounce!");

    // if channel exist
    auto cur_channel = channels.find(channel_name);
    if (cur_channel == channels.end())
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_4D -> channel not available!");
        
    int offset = (cams_v()-1)*focus*width();
    vigra::MultiArrayView<1, float> col = cur_channel->second.viewToColumn(
            h * imgWidth() + x);
    shape epi_shape = shape(cams_v(),imgHeight()-(cams_v()-1)*focus);
    strideTag stride = strideTag((imgHeight()-focus)*width(),col.stride()[0]);
    return view_2D(epi_shape, stride, col.data() + offset).transpose();
}

template<>
vigra::MultiArrayView<2,float> Lightfield<LF_3DH>::getVerticalEpiChannel(
        std::string const & channel_name, int x, int h, int focus)
{
    throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> no epis available for this LF_TYPE!");
}

template<>
vigra::MultiArrayView<2,float> Lightfield<LF_3DV>::getVerticalEpiChannel(
        std::string const & channel_name, int x, int h, int focus)
{
    if (x < 0 || x >= imgWidth())
        throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> out of bounce!");

    // if channel exist
    auto cur_channel = channels.find(channel_name);
    if (cur_channel == channels.end())
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_3DV -> channel not available!");
        
    int offset = (cams_v()-1)*focus;
    vigra::MultiArrayView<1, float> row = cur_channel->second.viewToRow(x);
    shape epi_shape = shape(imgHeight()-(cams_v()-1)*focus,cams_v());
    strideTag stride = strideTag(1, imgHeight() - focus);
    return view_2D(epi_shape, stride, row.data() + offset);        
}


template<>
vigra::MultiArrayView<2,float> Lightfield<LF_CROSS>::getVerticalEpiChannel(
        std::string const & channel_name, int x, int h, int focus)
{
    if (x < 0 || x >= imgWidth())
        throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> out of bounce!");

    // if channel exist
    auto cur_channel = channels.find(channel_name);
    if (cur_channel == channels.end())
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_3DV -> channel not available!");
        
//        int offset = (cams_v()-1)*focus;
//        //vigra::MultiArrayView<2, float> row = channels[channel_name].viewToROI(0, imgHeight()+x, cams_v()*imgHeight());
//        vigra::MultiArrayView<1, float> row = channels[channel_name].viewToRow(imgHeight()+x);
//        shape epi_shape = shape(imgHeight()-(cams_v()-1)*focus,cams_v());
//        strideTag stride = strideTag(1, imgHeight() - focus);
//        return view_2D(epi_shape, stride, row.data() + offset);
        
    int offset = (cams_v()-1)*focus;
    vigra::MultiArrayView<1, float> row = cur_channel->second.viewToRow(
            imgHeight() + x);
    shape epi_shape = shape(imgHeight()-(cams_v()-1)*focus,cams_v());
    strideTag stride = strideTag(1, imgHeight() - focus);
    return view_2D(epi_shape, stride, row.data() + offset);
}
 
 



template<>
const EpiOffset Lightfield<LF_4D>::getEpiOffset(DIRECTION dir, size_t index,
        size_t focus)
{
    return EpiOffset( index, imgWidth(), focus, cams_h());
}















} // namespace lightfield
} // namespace OpenLF
