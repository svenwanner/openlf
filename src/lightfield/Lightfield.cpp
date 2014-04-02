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





bool OpenLF::lightfield::Lightfield::has_property(string name) {
    return properties.has_field(name);
}


bool OpenLF::lightfield::Lightfield::get_property(string name, int &value) 
{
    return properties.get_field(name,value);
}
    

bool OpenLF::lightfield::Lightfield::get_property(string name, float &value)
{
    return properties.get_field(name,value);
}


bool OpenLF::lightfield::Lightfield::get_property(string name, double &value)
{
    return properties.get_field(name,value);
}


bool OpenLF::lightfield::Lightfield::get_property(string name, string &value)
{
    return properties.get_field(name,value);
}

LF_TYPE OpenLF::lightfield::Lightfield::type()
{
    LF_TYPE lftype;
    properties.get_lftype(lftype);
    return lftype;
}
    
    
    



void OpenLF::lightfield::Lightfield::data(map< string,vigra::MultiArray<2,float> > **channels) {
    print(1,"lightfield::Lightfield::data(channels) called...");
    *channels = &this->channels;
}


map< string,vigra::MultiArray<2,float> > * OpenLF::lightfield::Lightfield::data() {
    print(1,"lightfield::Lightfield::data(channels) called...");
    cout << "address of channels : " << &this->channels << endl;
    return &this->channels;
}

vigra::MultiArray<2,float> *OpenLF::lightfield::Lightfield::data(string channel_name) {
    print(1,"lightfield::Lightfield::data(channel_name,channel_data) called...");
    cout << "address of single channel : " << &channels[channel_name] << endl;
    if (channels.find(channel_name) == channels.end()) return NULL;
    else return &channels[channel_name];
}

void OpenLF::lightfield::Lightfield::data(string channel_name, vigra::MultiArray<2,float> **channel_data) {
    print(1,"lightfield::Lightfield::data(channel_name,channel_data) called...");
    if (channels.find(channel_name) == channels.end()) *channel_data = NULL;
    else *channel_data = &channels[channel_name];
}
