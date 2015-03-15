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




/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::Lightfield::Lightfield() 
{
    print(1,"lightfield::Lightfield::Lightfield() called...");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::Lightfield::Lightfield(const std::string filename) 
{
    print(1,"lightfield::Lightfield::Lightfield(filename) called...");
    
    open(filename);
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
//OpenLF::lightfield::Lightfield::Lightfield(const Lightfield& orig) {
//}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::Lightfield::~Lightfield() 
{
    print(1,"lightfield::~Lightfield() called...");
}







////////////////////////////////////////////////////////////////////////////////
//////                        I/O  M E T H O D S
////////////////////////////////////////////////////////////////////////////////


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::open(const std::string filename) 
{
    print(1,"lightfield::Lightfield::open(filename) called");
    
    m_properties.clear();
    m_channels.clear();
    
    std::string ftype;
    ftype = OpenLF::helpers::find_ftype(filename);
    
    if(ftype=="h5" || ftype=="lf" || ftype=="hdf5") {
        return OpenLF::lightfield::io::load_from_hdf5(filename, m_channels, &m_properties ); 
    }
    else if(ftype=="cfg") {
        m_dataHandler.reset(new OpenLF::lightfield::io::FileHandler(filename,&m_properties));
        return m_dataHandler->readData(m_channels);
    }
    else {
        return false;
        throw OpenLF_Exception("Lightfield IO Error: Filetype not specified!");
    }
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::open(const char* filename) 
{
    return open(std::string(filename));
}









////////////////////////////////////////////////////////////////////////////////
//////                        G E T    I N F O S 
////////////////////////////////////////////////////////////////////////////////

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::hasRGB() const
{
    if (m_channels.find("r") == m_channels.end()) return false;
    if (m_channels.find("g") == m_channels.end()) return false;
    if (m_channels.find("b") == m_channels.end()) return false;
    return true;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::hasBW() const
{
    if (m_channels.find("bw") == m_channels.end()) return false;
    return true;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::hasChannel(const std::string name) const
{
    if (m_channels.find(name) == m_channels.end()) return false;
    else return true;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
std::vector<std::string> OpenLF::lightfield::Lightfield::getListOfChannelNames()
{
  
    std::vector<std::string> v;
    for(std::map<std::string,OpenLF::image::ImageChannel>::iterator it = m_channels.begin(); it != m_channels.end(); ++it) 
        v.push_back(it->first);
        return v;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::hasProperty(const std::string name){
    return m_properties.has_field(name);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(const std::string name, int &value)
{
    return m_properties.get_field(name,value);
}
    

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(const std::string name, float &value)
{
    return m_properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(const std::string name, double &value)
{
    return m_properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(const std::string name, std::string &value)
{
    return m_properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
LF_TYPE OpenLF::lightfield::Lightfield::type()
{
    LF_TYPE lftype;
    m_properties.get_lftype(lftype);
    return lftype;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::imgWidth()
{
    int sx;
    m_properties.get_field("width",sx);
    return sx;
}

    
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::imgHeight()
{
    int sy;
    m_properties.get_field("height",sy);
    return sy;
}
    

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::width()
{
    int sx;
    m_properties.get_field("width",sx);
    return sx*cams_h();
}

    
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::height()
{
    int sy;
    m_properties.get_field("height",sy);
    return sy*cams_v();
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::cams_h()
{
    int sh;
    m_properties.get_field("cams_h",sh);
    return sh;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::cams_v()
{
    int sv;
    m_properties.get_field("cams_v",sv);
    return sv;
}
    







////////////////////////////////////////////////////////////////////////////////
//////                      A C C E S S    D A T A
//////////////////////////////////////////////////////////////////////////////// 
   

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield::getLoxel(int h, int v, int x, int y, const std::vector<std::string> channel_names, std::vector<float> &values)
{
    if(!values.empty())
        values.clear();
    
    for(unsigned int n=0; n<channel_names.size(); n++)
    {
        try {
            values.push_back(m_channels[channel_names[n]](h*imgWidth()+x,v*imgHeight()+y));
        }
        catch(std::exception &e)
        {
            e = OpenLF_Exception("Lightfield::getLoxel -> channel access exception!");
            std::cout << e.what() << std::endl;
        }
    }
}


/*!
 Returns the data pointer to the channel specified by the channel_name.
 If the channel key doesn't exist a NULL pointer is returned.
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
float* OpenLF::lightfield::Lightfield::channel_ptr(const std::string channel_name) {
    print(1,"lightfield::Lightfield::channel_ptr(channel_name,channel_data) called...");
    
    // check if channel exists
    if (m_channels.find(channel_name) == m_channels.end()) return NULL;
    else return m_channels[channel_name].data();
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield::data(std::map<std::string,OpenLF::image::ImageChannel> **channels) {
    print(1,"lightfield::Lightfield::data(channels) called...");
    
    *channels = &this->m_channels;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
std::map<std::string,OpenLF::image::ImageChannel> * OpenLF::lightfield::Lightfield::data() {
    print(1,"lightfield::Lightfield::data(channels) called...");
    
    return &this->m_channels;
}


/*!
 Returns a pointer to the channel specified by the channel_name.
 If the channel key doesn't exist a NULL pointer is returned.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::image::ImageChannel *OpenLF::lightfield::Lightfield::data(const std::string channel_name) {
    print(1,"lightfield::Lightfield::data(channel_name,channel_data) called...");
    
    // check if channel exists
    if (m_channels.find(channel_name) == m_channels.end()) return NULL;
    else return &m_channels[channel_name];
}


/*!
 Returns a pointer to the channel specified by the channel_name.
 If the channel key doesn't exist a NULL pointer is returned.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield::data(const std::string channel_name, OpenLF::image::ImageChannel **channel_data) {
    print(1,"lightfield::Lightfield::data(channel_name,channel_data) called...");
    
    // check if channel exists
    if (m_channels.find(channel_name) == m_channels.end()) *channel_data = NULL;
    else *channel_data = &m_channels[channel_name];
}


/*!
 Allocates a new channel with the name passed. The channels size is defined by
 the size of the light field.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield::allocateChannel(const std::string channel_name) 
{
    print(1,"lightfield::Lightfield::allocateChannel(channel_name) called...");
    
    // check if channel doesn't exists otherwise throw Exception
    if (m_channels.find(channel_name) == m_channels.end()) {
        m_channels[channel_name] = OpenLF::image::ImageChannel(width(),height());
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

void OpenLF::lightfield::Lightfield::appendProperties(OpenLF::lightfield::Properties &properties) {
    this->m_properties += properties;
}

/*!
 This method returns a MultiArray of an image of the light field at position 
 (h,v). If a bw channel is present it returns this, if rgb data are present they
 are converted to an bw image.
 * 
 The exception cases of cross and 3D vertical light fields where images 
 are stored in a transposed manner are handled correctly, so the function will 
 return a view to the transposed version of the image channel.
 *
 If one would get images from a cross light field, the row is accessed by setting
 the parameter v=0, the column vice versa by setting h=0. So always one of the
 camera dimension needs to be zero, otherwise an Exception is fired!
 *  
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/

void OpenLF::lightfield::Lightfield::getImage(int h, int v, vigra::MultiArray<2,float> &img)
{
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
}


/*!
 This method returns a rgb MultiArray of an image of the light field at position 
 (h,v).
 *
 The exception cases of cross and 3D vertical light fields where images 
 are stored in a transposed manner are handled correctly, so the function will 
 return a view to the transposed version of the image channel.
 *
 If one would get images from a cross light field, the row is accessed by setting
 the parameter v=0, the column vice versa by setting h=0. So always one of the 
 camera dimension needs to be zero, otherwise an Exception is fired!
 *
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/

void OpenLF::lightfield::Lightfield::getImage(int h, int v, vigra::MultiArray<2,vigra::RGBValue<float>> &img) 
{
    if(!img.hasData())
    {
        img = vigra::MultiArray<2,vigra::RGBValue<float>>(shape(imgWidth(),imgHeight()));
    }
    else
    {
        if(img.width() != imgWidth() || img.height() != imgHeight())
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
            for(int y=0; y<imgHeight(); y++)
            {
                for(int x=0; x<imgWidth(); x++)
                {
                    img(x,y)[c] = img_bw(x,y);
                }
            }
        }
    }
    else throw OpenLF_Exception("Lightfield::getImage -> no rgb or bw image data available!");
}


/*!
 This method returns a rgb MultiArray of an image of the light field at position 
 (h,v).
 * 
 The exception cases of cross and 3D vertical light fields where images 
 are stored in a transposed manner are handled correctly, so the function will 
 return a view to the transposed version of the image channel.
 *
 If one would get images from a cross light field, the row is accessed by setting
 the parameter v=0, the column vice versa by setting h=0. So always one of the 
 camera dimension needs to be zero, otherwise an Exception is fired!
 *  
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/

void OpenLF::lightfield::Lightfield::getImage(int h, int v, vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>> &img) 
{
    if(!img.hasData())
    {
        img = vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>>(shape(imgWidth(),imgHeight()));
    }
    else
    {
        if(img.width() != imgWidth() || img.height() != imgHeight())
            throw OpenLF_Exception("Lightfield::getImage -> shape mismatch!");
    }
    
    if(hasRGB()) {
        vigra::MultiArrayView<2,float> img_r;
        getImage(h,v,"r",img_r);
        vigra::MultiArrayView<2,float> img_g;
        getImage(h,v,"g",img_g);
        vigra::MultiArrayView<2,float> img_b;
        getImage(h,v,"b",img_b);
        
        vigra::MultiArray<2,float> fimg_r = vigra::MultiArrayView<2,float>(img_r);
        vigra::MultiArray<2,float> fimg_g = vigra::MultiArrayView<2,float>(img_g);
        vigra::MultiArray<2,float> fimg_b = vigra::MultiArrayView<2,float>(img_b);
        
        OpenLF::image::io::linear_range_mapping(img_r,fimg_r);
        OpenLF::image::io::linear_range_mapping(img_g,fimg_g);
        OpenLF::image::io::linear_range_mapping(img_b,fimg_b);
        
        OpenLF::image::utils::mergeChannels(fimg_r,fimg_g,fimg_b,img);
    }
    else if(hasBW())
    {
        vigra::MultiArrayView<2,float> img_bw;
        getImage(h,v,"bw",img_bw);
        
        vigra::MultiArray<2,float> fimg_bw = vigra::MultiArrayView<2,float>(img_bw);
        OpenLF::image::io::linear_range_mapping(img_bw,fimg_bw);
        
        for(int c=0; c<3; c++)
        {
            for(int y=0; y<imgHeight(); y++)
            {
                for(int x=0; x<imgWidth(); x++)
                {
                    img(x,y)[c] = (vigra::UInt8)(fimg_bw(x,y));
                }
            }
        }
    }
    else throw OpenLF_Exception("Lightfield::getImage -> no rgb image data available!");
}










////////////////////////////////////////////////////////////////////////////////
//////             E P I   H A N D L I N G     M E T H O D S
////////////////////////////////////////////////////////////////////////////////

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/

void OpenLF::lightfield::Lightfield::getHorizontalEpi(int y, int v, int focus, vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >& img)
{
    if(hasRGB()) {
        vigra::MultiArrayView<2,float> r = getHorizontalEpiChannel("r", y, v, focus);
        vigra::MultiArrayView<2,float> g = getHorizontalEpiChannel("g", y, v, focus);
        vigra::MultiArrayView<2,float> b = getHorizontalEpiChannel("b", y, v, focus);
        
        if(img.hasData()) {
            if(img.shape() != r.shape())
                throw OpenLF_Exception("Lightfield::getHorizontalEpi -> shape mismatch!");
        }
        else
            img = vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >(r.shape());
        
        for(int y=0; y<r.shape()[1]; y++) {
            for(int x=0; x<r.shape()[0]; x++) {
                img(x,y)[0] = (vigra::UInt8)(r(x,y)*255);
                img(x,y)[1] = (vigra::UInt8)(g(x,y)*255);
                img(x,y)[2] = (vigra::UInt8)(b(x,y)*255);
            }
        }
    }
    else if(hasBW()) {
        vigra::MultiArrayView<2,float> bw = getHorizontalEpiChannel("bw", y, v, focus);
        
        if(img.hasData()) 
        {
            if(img.shape() != bw.shape())
                throw OpenLF_Exception("Lightfield::getHorizontalEpi -> shape mismatch!");
        }
        else
            img = vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >(bw.shape());
        
        for(int y=0; y<bw.shape()[1]; y++) {
            for(int x=0; x<bw.shape()[0]; x++) {
                for(int c=0; c<3; c++)
                    img(x,y)[c] = (vigra::UInt8)(bw(x,y)*255);
            }
        }
    }
    else throw OpenLF_Exception("Lightfield::getHorizontalEpi -> no suitable channel available!");
}



/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/

void OpenLF::lightfield::Lightfield::getVerticalEpi(int x, int h, int focus, vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >& img)
{
    if(hasRGB()) {
        vigra::MultiArrayView<2,float> r = getVerticalEpiChannel("r", x, h, focus);
        vigra::MultiArrayView<2,float> g = getVerticalEpiChannel("g", x, h, focus);
        vigra::MultiArrayView<2,float> b = getVerticalEpiChannel("b", x, h, focus);
        
        if(img.hasData()) {
            if(img.shape() != r.shape())
                throw OpenLF_Exception("Lightfield::getVerticalEpi -> shape mismatch!");
        }
        else
            img = vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >(r.shape());
        
        for(int y=0; y<r.shape()[1]; y++) {
            for(int x=0; x<r.shape()[0]; x++) {
                img(x,y)[0] = (vigra::UInt8)(r(x,y)*255);
                img(x,y)[1] = (vigra::UInt8)(g(x,y)*255);
                img(x,y)[2] = (vigra::UInt8)(b(x,y)*255);
            }
        }
    }
    else if(hasBW()) {
        vigra::MultiArrayView<2,float> bw = getHorizontalEpiChannel("bw", x, h, focus);
        
        if(img.hasData()) 
        {
            if(img.shape() != bw.shape())
                throw OpenLF_Exception("Lightfield::getHorizontalEpi -> shape mismatch!");
        }
        else
            img = vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >(bw.shape());
        
        for(int y=0; y<bw.shape()[1]; y++) {
            for(int x=0; x<bw.shape()[0]; x++) {
                for(int c=0; c<3; c++)
                    img(x,y)[c] = (vigra::UInt8)(bw(x,y)*255);
            }
        }
    }
    else throw OpenLF_Exception("Lightfield::getHorizontalEpi -> no suitable channel available!");
}

 
/*!
This is the efficient variant of accessing epipolar plane images due to the concatenated memory access.
Accessing the vertical epipolar plane images using _getVerticalEpiChannel_4D is inefficient compared to this
due to the column accessing. To achieve the same efficiency for vertical access transpose the data and use
the horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
 
view_2D OpenLF::lightfield::Lightfield::getHorizontalEpiChannel_parent(std::string channel_name, int y,  int v, int focus) 
{
    // if channel exist
    if (hasChannel(channel_name)) {
        
        int offset = (cams_h()-1)*focus;
        vigra::MultiArrayView<1, float> row = m_channels[channel_name].viewToRow(v * imgHeight() + y);
        shape epi_shape = shape(imgWidth()-(cams_h()-1)*focus,cams_h());//imgWidth()-2*(cams_h()-1)*focus?
        strideTag stride = strideTag(1, imgWidth() - focus);//-2 x focus?
        return view_2D(epi_shape, stride, row.data() + offset);
        
    } else
        throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel_parent -> channel not available!");
}
