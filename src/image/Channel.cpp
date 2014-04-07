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

#include "image/Channel.hpp"



OpenLF::image::ImageChannel::ImageChannel() {
    print(1,"image::ImageChannel::ImageChannel() called...");
}

OpenLF::image::ImageChannel::ImageChannel(int width, int height)
{
    print(1,"image::ImageChannel::ImageChannel(width,height) called...");
    
    init(width,height);
}

OpenLF::image::ImageChannel::ImageChannel(vigra::Shape2 shape)
{
    print(1,"image::ImageChannel::ImageChannel(shape) called...");
    
    init(shape);
}

OpenLF::image::ImageChannel::ImageChannel(int width, int height, float* data_ptr)
{
    print(1,"image::ImageChannel::ImageChannel(width,height, data_ptr) called...");
    
    init(width,height,data_ptr);
}

OpenLF::image::ImageChannel::ImageChannel(vigra::Shape2 shape, float* data_ptr)
{
    print(1,"image::ImageChannel::ImageChannel(shape, data_ptr) called...");
    
    init(shape,data_ptr);
}

OpenLF::image::ImageChannel::ImageChannel(const ImageChannel& orig) 
{
    int w = orig.width();
    int h = orig.height();
    this->pixel = array_2d(vigra::Shape2(w,h));
    
    float* d_ptr = orig.data_ptr();
    for(int n=0; n<h*w; n++) {
        this->pixel.data()[n] = d_ptr[n];
    }
}

OpenLF::image::ImageChannel::~ImageChannel() 
{
}



void OpenLF::image::ImageChannel::init(int width, int height) 
{
    pixel = array_2d(vigra::Shape2(width,height));
}


void OpenLF::image::ImageChannel::init(vigra::Shape2 shape)
{
    pixel = array_2d(shape);
}


void OpenLF::image::ImageChannel::init(int width, int height, float* data_ptr) 
{
    pixel = array_2d(vigra::Shape2(width,height));
    
    float *local_ptr = pixel.data();
    for(int n=0; n < width * height; n++) {
        local_ptr[n] = data_ptr[n];
    }
}


void OpenLF::image::ImageChannel::init(vigra::Shape2 shape, float* data_ptr)
{
    pixel = array_2d(shape);
    
    float *local_ptr = pixel.data();
    for(int n=0; n < shape[0] * shape[1]; n++) {
        local_ptr[n] = data_ptr[n];
    }
}


void OpenLF::image::ImageChannel::init(int width, int height, vigra::UInt8 * data_ptr) 
{
    pixel = array_2d(vigra::Shape2(width,height));
    
    float *local_ptr = pixel.data();
    for(int n=0; n < width * height; n++) {
        local_ptr[n] = (float)data_ptr[n]/255.0;
    }
}


void OpenLF::image::ImageChannel::init(vigra::Shape2 shape, vigra::UInt8* data_ptr)
{
    pixel = array_2d(shape);
    
    float *local_ptr = pixel.data();
    for(int n=0; n < shape[0] * shape[1]; n++) {
        local_ptr[n] = (float)data_ptr[n]/255.0;
    }
}





float* OpenLF::image::ImageChannel::data_ptr() const
{
    print(1,"image::Channel::data_ptr() called...");
    
    return pixel.data();
}


vigra::MultiArray<2,float>* OpenLF::image::ImageChannel::data()
{
    print(1,"image::Channel::data() called...");
    
    return &pixel;
}


void OpenLF::image::ImageChannel::data(vigra::MultiArray<2,float> **pixel) 
{
    print(1,"image::Channel::data(**pixel) called...");
    
    *pixel = &this->pixel;
}