/* 
 * File:   Channel.cpp
 * Author: swanner
 * 
 * Created on April 3, 2014, 11:27 AM
 */

#include "image/Channel.hpp"



OpenLF::image::Channel::Channel() {
}

OpenLF::image::Channel::Channel(const Channel& orig) {
}

OpenLF::image::Channel::~Channel() {
}



void OpenLF::image::Channel::init(int width, int height) 
{
    pixel = new array_2d(vigra::Shape2(width,height));
    *pixel = 0;
}


void OpenLF::image::Channel::init(vigra::Shape2 shape)
{
    pixel = new array_2d(shape);
    *pixel=0;
}


void OpenLF::image::Channel::init(int width, int height, float* data_ptr) 
{
    pixel = new array_2d(vigra::Shape2(width,height));
    
    float *local_ptr = pixel->data();
    for(int n=0; n<width*height; n++) {
        local_ptr[n] = data_ptr[n];
    }
}


void OpenLF::image::Channel::init(vigra::Shape2 shape, float* data_ptr)
{
    pixel = new array_2d(shape);
    
    float *local_ptr = pixel->data();
    for(int n=0; n<shape[0]*shape[1]; n++) {
        local_ptr[n] = data_ptr[n];
    }
}





vigra::MultiArray<2,float>* OpenLF::image::Channel::data() 
{
    print(1,"image::Channel::data(channels) called...");
    
    return this->pixel;
}


void OpenLF::image::Channel::data(vigra::MultiArray<2,float> **pixel) 
{
    print(1,"image::Channel::data(channel_name,channel_data) called...");
    
    *pixel = this->pixel;
}