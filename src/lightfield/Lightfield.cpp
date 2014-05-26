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
OpenLF::lightfield::Lightfield::Lightfield(std::string filename) 
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
OpenLF::lightfield::Lightfield::~Lightfield() {
}







////////////////////////////////////////////////////////////////////////////////
//////                        I/O  M E T H O D S
////////////////////////////////////////////////////////////////////////////////


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::open(std::string filename) 
{
    print(1,"lightfield::Lightfield::open(filename) called");
    
    properties.clear();
    channels.clear();
    
    std::string ftype;
    ftype = OpenLF::helpers::find_ftype(filename);
    
    if(ftype=="h5" || ftype=="lf" || ftype=="hdf5") {
        return OpenLF::lightfield::io::load_from_hdf5( filename, channels, &properties ); 
    }
    else if(ftype=="cfg") {
        dataHandler = new OpenLF::lightfield::io::FileHandler(filename,&properties);
        return dataHandler->readData(channels);
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
bool OpenLF::lightfield::Lightfield::hasRGB()
{
    if (channels.find("r") == channels.end()) return false;
    if (channels.find("g") == channels.end()) return false;
    if (channels.find("b") == channels.end()) return false;
    return true;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::hasBW()
{
    if (channels.find("bw") == channels.end()) return false;
    return true;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::hasChannel(std::string name)
{
    if (channels.find(name) == channels.end()) return false;
    else return true;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
std::vector<std::string> OpenLF::lightfield::Lightfield::getListOfChannelNames()
{
  
    std::vector<std::string> v;
    for(std::map<std::string,OpenLF::image::ImageChannel>::iterator it = channels.begin(); it != channels.end(); ++it) 
        v.push_back(it->first);
        return v;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::hasProperty(std::string name) {
    return properties.has_field(name);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(std::string name, int &value) 
{
    return properties.get_field(name,value);
}
    

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(std::string name, float &value)
{
    return properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(std::string name, double &value)
{
    return properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(std::string name, std::string &value)
{
    return properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
LF_TYPE OpenLF::lightfield::Lightfield::type()
{
    LF_TYPE lftype;
    properties.get_lftype(lftype);
    return lftype;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::imgWidth()
{
    int sx;
    properties.get_field("width",sx);
    return sx;
}

    
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::imgHeight()
{
    int sy;
    properties.get_field("height",sy);
    return sy;
}
    

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::width()
{
    int sx;
    properties.get_field("width",sx);
    return sx*cams_h();
}

    
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::height()
{
    int sy;
    properties.get_field("height",sy);
    return sy*cams_v();
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::cams_h()
{
    int sh;
    properties.get_field("cams_h",sh);
    return sh;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
int OpenLF::lightfield::Lightfield::cams_v()
{
    int sv;
    properties.get_field("cams_v",sv);
    return sv;
}
    







////////////////////////////////////////////////////////////////////////////////
//////                      A C C E S S    D A T A
//////////////////////////////////////////////////////////////////////////////// 
   

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
float OpenLF::lightfield::Lightfield::getLoxel(int h, int v, int x, int y, std::string channel_name)
{
    float val = 0;
    
    if(type()==LF_4D) {
        
        try {
            val = channels[channel_name](h*imgWidth()+x,v*imgHeight()+y);
        }
        catch(std::exception &e)
        {
            e = OpenLF_Exception("Lightfield::loxel -> channel access exception!");
            std::cout << e.what() << std::endl;
        }
        return val;
    }
    else if(type()==LF_3DV) {
        return val;
    }
    
    else if(type()==LF_3DH) {
        
        try {
            val = channels[channel_name](h*imgWidth()+x,y);
        }
        catch(std::exception &e)
        {
            e = OpenLF_Exception("Lightfield::loxel -> channel access exception!");
            std::cout << e.what() << std::endl;
        }
        return val;
    }
    
    else if(type()==LF_CROSS) {
        return val;
    }
    
    else throw OpenLF_Exception("Lightfield::loxel -> unknown LF_TYPE!");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield::getLoxel(int h, int v, int x, int y, std::vector<std::string> channel_names, std::vector<float> &values)
{
    if(!values.empty())
        values.clear();
    
    for(unsigned int n=0; n<channel_names.size(); n++)
    {
        try {
            values.push_back(channels[channel_names[n]](h*imgWidth()+x,v*imgHeight()+y));
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
float* OpenLF::lightfield::Lightfield::channel_ptr(std::string channel_name) {
    print(1,"lightfield::Lightfield::channel_ptr(channel_name,channel_data) called...");
    
    // check if channel exists
    if (channels.find(channel_name) == channels.end()) return NULL;
    else return channels[channel_name].data();
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield::data(std::map<std::string,OpenLF::image::ImageChannel> **channels) {
    print(1,"lightfield::Lightfield::data(channels) called...");
    
    *channels = &this->channels;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
std::map<std::string,OpenLF::image::ImageChannel> * OpenLF::lightfield::Lightfield::data() {
    print(1,"lightfield::Lightfield::data(channels) called...");
    
    return &this->channels;
}


/*!
 Returns a pointer to the channel specified by the channel_name.
 If the channel key doesn't exist a NULL pointer is returned.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::image::ImageChannel *OpenLF::lightfield::Lightfield::data(std::string channel_name) {
    print(1,"lightfield::Lightfield::data(channel_name,channel_data) called...");
    
    // check if channel exists
    if (channels.find(channel_name) == channels.end()) return NULL;
    else return &channels[channel_name];
}


/*!
 Returns a pointer to the channel specified by the channel_name.
 If the channel key doesn't exist a NULL pointer is returned.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield::data(std::string channel_name, OpenLF::image::ImageChannel **channel_data) {
    print(1,"lightfield::Lightfield::data(channel_name,channel_data) called...");
    
    // check if channel exists
    if (channels.find(channel_name) == channels.end()) *channel_data = NULL;
    else *channel_data = &channels[channel_name];
}


/*!
 Allocates a new channel with the name passed. The channels size is defined by
 the size of the light field.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield::allocateChannel(std::string channel_name) 
{
    print(1,"lightfield::Lightfield::allocateChannel(channel_name) called...");
    
    // check if channel doesn't exists otherwise throw Exception
    if (channels.find(channel_name) == channels.end()) {
        channels[channel_name] = OpenLF::image::ImageChannel(width(),height());
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
    this->properties += properties;
}


/*!
 This method returns a MultiArrayView to an image of the light field at position 
 (h,v). The exception cases of cross and 3D vertical light fields where images 
 are stored in a transposed manner are handled correctly, so the function will 
 return a view to the transposed version of the image channel.
 *
 If one would get images from a cross light field, the row is accessed by setting
 the parameter v=0, the column vice versa by setting h=0. So always one of the 
 camera dimension needs to be zero, otherwise an Exception is fired!
 *  
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield::getImage(int h, int v, std::string channel_name, vigra::MultiArrayView<2,float> &img) 
{
    // check if channel exists
    if (channels.find(channel_name) == channels.end())
        throw OpenLF_Exception("Lightfield::getImage -> channels doesn't exist!");
    
    // check if requested image is in range
    if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        throw OpenLF_Exception("Lightfield::getImage -> out of light field bounds!");
    
    // handle all light field cases
    if(type()==LF_CROSS) {
        if(v==0) img = channels[channel_name].viewToROI(h*imgWidth(),0,imgWidth(),imgHeight());
        else if(h==0) img = channels[channel_name].viewToROI(v*imgHeight(),imgHeight(),imgHeight(),imgWidth());
    }
    else if(type()==LF_3DV) img = channels[channel_name].viewToROI(v*imgHeight(),0,imgHeight(),imgWidth());
    
    else if(type()==LF_3DH) img = channels[channel_name].viewToROI(h*imgWidth(),0,imgWidth(),imgHeight());
    
    else if(type()==LF_4D) img = channels[channel_name].viewToROI(h*imgWidth(),v*imgHeight(),imgWidth(),imgHeight());
    
    else throw OpenLF_Exception("Lightfield::getImage -> unknown LF_TYPE!");
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
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
vigra::MultiArrayView<2,float> OpenLF::lightfield::Lightfield::getHorizontalEpiChannel(std::string channel_name, int y, int v, int focus)
{
    vigra::MultiArrayView<2,float> tmp;
      
    if(type()==LF_4D) {
        if(v>=0 && v<=cams_v() && y>=0 && y<imgHeight())
            tmp = _getHorizontalEpiChannel_4D(v,y,channel_name,focus);
        else
            throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> out of bounce!");
    }
    else if(type()==LF_3DH) {
        if(y>=0 && y<imgHeight())
            tmp = _getHorizontalEpiChannel_4D(0,y,channel_name,focus);
        else
            throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> out of bounce!");
    }
    else if(type()==LF_3DV) {
        throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> no epis available for this LF_TYPE!");
    }
    else if(type()==LF_CROSS) {
        if(y>=0 && y<imgHeight())
            tmp = _getHorizontalEpiChannel_4D(0,y,channel_name,focus);
        else
            throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> out of bounce!");
    }
    else
        throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> unknown light field type!");
    
    return tmp;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
 vigra::MultiArrayView<2,float> OpenLF::lightfield::Lightfield::getVerticalEpiChannel(std::string channel_name, int x, int h, int focus)
{
    vigra::MultiArrayView<2,float> tmp;
    
    if(type()==LF_4D) {
        if(h>=0 && h<=cams_h() && x>=0 && x<imgWidth())
            tmp = _getVerticalEpiChannel_4D(h,x,channel_name,focus);
        else
            throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> out of bounce!");
    }
    else if(type()==LF_3DH) {
        throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> no epis available for this LF_TYPE!");
    }
    else if(type()==LF_3DV) {
        if(x>=0 && x<imgWidth())
            tmp = _getVerticalEpiChannel_3DV(x,channel_name,focus);
        else
            throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> out of bounce!");
    }
    else if(type()==LF_CROSS) {
        if(x>=0 && x<imgWidth())
            tmp = _getVerticalEpiChannel_Cross(x,channel_name,focus);
        else
            throw OpenLF_Exception("Lightfield::getVerticalEpiChannel -> out of bounce!");
    }
    else
        throw OpenLF_Exception("Lightfield::getHorizontalEpiChannel -> unknown light field type!");
    
    return tmp;
}
 
 
/*!
This is the efficient variant of accessing epipolar plane images due to the concatenated memory access.
Accessing the vertical epipolar plane images using _getVerticalEpiChannel_4D is inefficient compared to this
due to the column accessing. To achieve the same efficiency for vertical access transpose the data and use
the horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield::_getHorizontalEpiChannel_4D(int v, int y, std::string channel_name, int focus) 
{
    // if channel exist
    if (hasChannel(channel_name)) {
        
        int offset = (cams_h()-1)*focus;
        vigra::MultiArrayView<1, float> row = channels[channel_name].viewToRow(v * imgHeight() + y);
        shape epi_shape = shape(imgWidth()-(cams_h()-1)*focus,cams_h());
        strideTag stride = strideTag(1, imgWidth() - focus);
        return view_2D(epi_shape, stride, row.data() + offset);
        
    } else
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_4D -> channel not available!");
}


/*!
This is the efficient variant of accessing epipolar plane images due to the concatenated memory access.
Accessing the vertical epipolar plane images using _getVerticalEpiChannel_4D is inefficient compared to this
due to the column accessing. To achieve the same efficiency for vertical access transpose the data and use
the horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield::_getVerticalEpiChannel_3DV(int x, std::string channel_name, int focus) 
{
    // if channel exist
    if (hasChannel(channel_name)) {
        
        int offset = (cams_v()-1)*focus;
        vigra::MultiArrayView<1, float> row = channels[channel_name].viewToRow(x);
        shape epi_shape = shape(imgHeight()-(cams_v()-1)*focus,cams_v());
        strideTag stride = strideTag(1, imgHeight() - focus);
        return view_2D(epi_shape, stride, row.data() + offset);        
    } else
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_3DV -> channel not available!");
}


/*!
This is the efficient variant of accessing epipolar plane images due to the concatenated memory access.
Accessing the vertical epipolar plane images using _getVerticalEpiChannel_4D is inefficient compared to this
due to the column accessing. To achieve the same efficiency for vertical access transpose the data and use
the horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield::_getVerticalEpiChannel_Cross(int x, std::string channel_name, int focus) 
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
        vigra::MultiArrayView<1, float> row = channels[channel_name].viewToRow(imgHeight() + x);
        shape epi_shape = shape(imgHeight()-(cams_v()-1)*focus,cams_v());
        strideTag stride = strideTag(1, imgHeight() - focus);
        return view_2D(epi_shape, stride, row.data() + offset);
        
    } else
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_3DV -> channel not available!");
}


/*!
This is the inefficient variant of accessing epipolar plane images due to the unstrided memory access.
For optimal performance during computation transpose the whole lightfield and use horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield::_getVerticalEpiChannel_4D(int h, int x, std::string channel_name, int focus) 
{
    // if channel exist
    if (hasChannel(channel_name)) {
        
        int offset = (cams_v()-1)*focus*width();
        vigra::MultiArrayView<1, float> col = channels[channel_name].viewToColumn(h * imgWidth() + x);
        shape epi_shape = shape(cams_v(),imgHeight()-(cams_v()-1)*focus);
        strideTag stride = strideTag((imgHeight()-focus)*width(),col.stride()[0]);
        return view_2D(epi_shape, stride, col.data() + offset).transpose();
        
    } else
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_4D -> channel not available!");
}















/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::EpiIterator::EpiIterator(OpenLF::lightfield::Lightfield *lf, DIRECTION direction) 
{
    this->lf = lf;
    this->direction = direction;
    finished = false;
}


/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::EpiIterator::~EpiIterator() 
{
    
}


/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::EpiIterator* OpenLF::lightfield::Lightfield::createEpiIterator(DIRECTION direction)
{
    return new OpenLF::lightfield::EpiIterator(this,direction);
}


/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::EpiIterator::first()
{
    camera_index = 0;
    epi_index = 0;
}


/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::EpiIterator::next()
{
    epi_index++;
    
    if(lf->type() == LF_4D)
    {
        if(direction == VERTICAL)
        {
            if(epi_index >= lf->imgWidth())
            {
                epi_index = 0;
                camera_index++;
            }
            if(camera_index >= lf->cams_h())
                finished = true;
        }
        else if(direction == HORIZONTAL)
        {
            if(epi_index >= lf->imgHeight())
            {
                epi_index = 0;
                camera_index++;
            }
            if(camera_index >= lf->cams_v())
                finished = true;
        }
    }
    if(lf->type() == LF_3DH)
    {
        if(direction == VERTICAL)
        {
            throw OpenLF_Exception("EpiIterator::get -> unknown direction!");
        }
        else if(direction == HORIZONTAL)
        {
            if(epi_index >= lf->imgHeight())
            {
                finished = true;
            }
                
        }
    }
    if(lf->type() == LF_3DV)
    {
        if(direction == VERTICAL)
        {
            if(epi_index >= lf->imgWidth())
            {
                finished = true;
            }
        }
        else if(direction == HORIZONTAL)
        {
            throw OpenLF_Exception("EpiIterator::get -> unknown direction!");
        }
    }
    if(lf->type() == LF_CROSS)
    {
        if(direction == VERTICAL)
        {
            if(epi_index >= lf->imgWidth())
            {
                finished = true;
            }
        }
        else if(direction == HORIZONTAL)
        {
            if(epi_index >= lf->imgHeight())
            {
                finished = true;
            }
        }
    }
}


/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::EpiIterator::end()
{
    return finished;
}
    

/*!
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::EpiIterator::get(std::string channel_name, int focus)
{
    if(!this->lf->hasChannel(channel_name))
        throw OpenLF_Exception("EpiIterator::get -> channel not available!");
    
    if(direction == VERTICAL)
        return lf->getVerticalEpiChannel(channel_name, epi_index, camera_index, focus);
    else if(direction == HORIZONTAL)
        return lf->getHorizontalEpiChannel(channel_name, epi_index, camera_index, focus);
    else
        throw OpenLF_Exception("EpiIterator::get -> unknown direction!");
}







