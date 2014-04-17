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

#include "lightfield/Lightfield.hpp"
#include "image/utils.hpp"

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
OpenLF::lightfield::Lightfield::Lightfield(string filename) 
{
    print(1,"lightfield::Lightfield::Lightfield(filename) called...");
    
    open(filename);
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::lightfield::Lightfield::Lightfield(const Lightfield& orig) {
}

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
bool OpenLF::lightfield::Lightfield::open(string filename) 
{
    print(1,"lightfield::Lightfield::open(filename) called");
    
    properties.clear();
    channels.clear();
    
    string ftype;
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
    return open(string(filename));
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
bool OpenLF::lightfield::Lightfield::hasChannel(string name)
{
    if (channels.find(name) == channels.end()) return false;
    else return true;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::hasProperty(string name) {
    return properties.has_field(name);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(string name, int &value) 
{
    return properties.get_field(name,value);
}
    

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(string name, float &value)
{
    return properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(string name, double &value)
{
    return properties.get_field(name,value);
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool OpenLF::lightfield::Lightfield::getProperty(string name, string &value)
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
 Returns the data pointer to the channel specified by the channel_name.
 If the channel key doesn't exist a NULL pointer is returned.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
float* OpenLF::lightfield::Lightfield::channel_ptr(string channel_name) {
    print(1,"lightfield::Lightfield::channel_ptr(channel_name,channel_data) called...");
    
    // check if channel exists
    if (channels.find(channel_name) == channels.end()) return NULL;
    else return channels[channel_name].data();
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::lightfield::Lightfield::data(map<string,OpenLF::image::ImageChannel> **channels) {
    print(1,"lightfield::Lightfield::data(channels) called...");
    
    *channels = &this->channels;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
map<string,OpenLF::image::ImageChannel> * OpenLF::lightfield::Lightfield::data() {
    print(1,"lightfield::Lightfield::data(channels) called...");
    
    return &this->channels;
}


/*!
 Returns a pointer to the channel specified by the channel_name.
 If the channel key doesn't exist a NULL pointer is returned.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
OpenLF::image::ImageChannel *OpenLF::lightfield::Lightfield::data(string channel_name) {
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
void OpenLF::lightfield::Lightfield::data(string channel_name, OpenLF::image::ImageChannel **channel_data) {
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
void OpenLF::lightfield::Lightfield::allocateChannel(string channel_name) 
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
void OpenLF::lightfield::Lightfield::getImage(int h, int v, string channel_name, vigra::MultiArrayView<2,float> &img) 
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
    if(hasRGB()) {
        vigra::MultiArrayView<2,float> img_r;
        getImage(h,v,"r",img_r);
        vigra::MultiArrayView<2,float> img_g;
        getImage(h,v,"g",img_g);
        vigra::MultiArrayView<2,float> img_b;
        getImage(h,v,"g",img_b);
        
        OpenLF::image::utils::mergeChannels(img_r,img_b,img_b,img);
    }
    else throw OpenLF_Exception("Lightfield::getImage -> no rgb image data available!");
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
    else throw OpenLF_Exception("Lightfield::getImage -> no rgb image data available!");
}