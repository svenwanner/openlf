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

OpenLF::lightfield::Lightfield::Lightfield() 
{
    print(1,"lightfield::Lightfield::Lightfield() called...");
}

OpenLF::lightfield::Lightfield::Lightfield(string filename) 
{
    print(1,"lightfield::Lightfield::Lightfield(filename) called...");
    
    open(filename);
}

OpenLF::lightfield::Lightfield::Lightfield(const Lightfield& orig) {
}

OpenLF::lightfield::Lightfield::~Lightfield() {
}







////////////////////////////////////////////////////////////////////////////////
//////                        I/O  M E T H O D S
////////////////////////////////////////////////////////////////////////////////


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

bool OpenLF::lightfield::Lightfield::open(const char* filename) 
{
    return open(string(filename));
}









////////////////////////////////////////////////////////////////////////////////
//////                        G E T    I N F O S 
////////////////////////////////////////////////////////////////////////////////

bool OpenLF::lightfield::Lightfield::hasChannel(string name)
{
    if (channels.find(name) == channels.end()) return false;
    else return true;
}


bool OpenLF::lightfield::Lightfield::hasProperty(string name) {
    return properties.has_field(name);
}


bool OpenLF::lightfield::Lightfield::getProperty(string name, int &value) 
{
    return properties.get_field(name,value);
}
    

bool OpenLF::lightfield::Lightfield::getProperty(string name, float &value)
{
    return properties.get_field(name,value);
}


bool OpenLF::lightfield::Lightfield::getProperty(string name, double &value)
{
    return properties.get_field(name,value);
}


bool OpenLF::lightfield::Lightfield::getProperty(string name, string &value)
{
    return properties.get_field(name,value);
}


LF_TYPE OpenLF::lightfield::Lightfield::type()
{
    LF_TYPE lftype;
    properties.get_lftype(lftype);
    return lftype;
}


int OpenLF::lightfield::Lightfield::imgWidth()
{
    int sx;
    properties.get_field("width",sx);
    return sx;
}

    
int OpenLF::lightfield::Lightfield::imgHeight()
{
    int sy;
    properties.get_field("height",sy);
    return sy;
}
    

int OpenLF::lightfield::Lightfield::width()
{
    int sx;
    properties.get_field("width",sx);
    return sx*cams_h();
}

    
int OpenLF::lightfield::Lightfield::height()
{
    int sy;
    properties.get_field("height",sy);
    return sy*cams_v();
}


int OpenLF::lightfield::Lightfield::cams_h()
{
    int sh;
    properties.get_field("cams_h",sh);
    return sh;
}


int OpenLF::lightfield::Lightfield::cams_v()
{
    int sv;
    properties.get_field("cams_v",sv);
    return sv;
}
    







////////////////////////////////////////////////////////////////////////////////
//////                      A C C E S S    D A T A
//////////////////////////////////////////////////////////////////////////////// 
    
float* OpenLF::lightfield::Lightfield::channel_ptr(string channel_name) {
    print(1,"lightfield::Lightfield::channel_ptr(channel_name,channel_data) called...");
    if (channels.find(channel_name) == channels.end()) return NULL;
    else return channels[channel_name].data();
}


void OpenLF::lightfield::Lightfield::data(map<string,OpenLF::image::ImageChannel> **channels) {
    print(1,"lightfield::Lightfield::data(channels) called...");
    *channels = &this->channels;
}


map<string,OpenLF::image::ImageChannel> * OpenLF::lightfield::Lightfield::data() {
    print(1,"lightfield::Lightfield::data(channels) called...");
    return &this->channels;
}


OpenLF::image::ImageChannel *OpenLF::lightfield::Lightfield::data(string channel_name) {
    print(1,"lightfield::Lightfield::data(channel_name,channel_data) called...");
    if (channels.find(channel_name) == channels.end()) return NULL;
    else return &channels[channel_name];
}


void OpenLF::lightfield::Lightfield::data(string channel_name, OpenLF::image::ImageChannel **channel_data) {
    print(1,"lightfield::Lightfield::data(channel_name,channel_data) called...");
    if (channels.find(channel_name) == channels.end()) *channel_data = NULL;
    else *channel_data = &channels[channel_name];
}


void OpenLF::lightfield::Lightfield::allocateChannel(string channel_name) 
{
    print(1,"lightfield::Lightfield::allocateChannel(channel_name) called...");
    if (channels.find(channel_name) == channels.end()) {
        channels[channel_name] = OpenLF::image::ImageChannel(width(),height());
    }
    else {
       throw OpenLF_Exception("Cannot allocate channel that already exist!");
    }
}


void OpenLF::lightfield::Lightfield::appendProperties(OpenLF::lightfield::Properties &properties) {
    this->properties += properties;
}


vigra::MultiArrayView<2,float> OpenLF::lightfield::Lightfield::getImage(int h, int v, string channel_name) 
{
    if (channels.find(channel_name) == channels.end())
        throw OpenLF_Exception("channels doesn't exist!");
    if(h<0 || h>=cams_h() || v<0 || v>=cams_v())
        throw OpenLF_Exception("out of image bounds!");
    return channels[channel_name].viewToROI(h*imgWidth(),v*imgHeight(),imgWidth(),imgHeight());
}