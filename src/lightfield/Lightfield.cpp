/* 
 * File:   Lightfield.cpp
 * Author: swanner
 * 
 * Created on March 31, 2014, 1:07 PM
 */

#include "lightfield/Lightfield.hpp"

OpenLF::lightfield::Lightfield::Lightfield() {
    print(1,"lightfield::Lightfield::Lightfield() called...");
}

OpenLF::lightfield::Lightfield::Lightfield(string filename) {
    print(1,"lightfield::Lightfield::Lightfield(filename) called...");
    dataHandler = new OpenLF::lightfield::io::FileHandler(filename,&properties);
    dataHandler->readData(channels);
}

OpenLF::lightfield::Lightfield::Lightfield(const Lightfield& orig) {
}

OpenLF::lightfield::Lightfield::~Lightfield() {
}










bool OpenLF::lightfield::Lightfield::open(string filename) {
    return OpenLF::lightfield::io::load_from_hdf5( filename, channels, &properties ); 
}

bool OpenLF::lightfield::Lightfield::open(const char* filename) {
    return open(string(filename));
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
