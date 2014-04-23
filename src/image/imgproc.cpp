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

#include "image/imgproc.hpp"




void OpenLF::image::imgproc::difference(channel_map &channels1,
                                        channel_map &channels2,
                                        OpenLF::image::ImageChannel &result) 
{
    try {
        result=0.0f;
        string key;
        OpenLF::image::ImageChannel tmp(result.width(),result.height());
        
        for ( channel_map_iter iter = channels1.begin(); iter != channels1.end(); iter++ ) {
            key=iter->first;
            if ( channels2.find(key) == channels2.end() ) {
                throw OpenLF_Exception("Key match Error in compute difference!");
            } else {
                
                difference(channels1[key],channels2[key],tmp);
                for(int n=0; n<result.height()*result.width(); n++) {
                    result.data()[n]=result.data()[n]+tmp.data()[n];
                }
                
            }
        } 
    } catch(exception &e) {
        warning(e.what());
    }
}



void OpenLF::image::imgproc::difference(OpenLF::image::ImageChannel &img1, 
                                        OpenLF::image::ImageChannel &img2, 
                                        OpenLF::image::ImageChannel &result)
{
    try {
        
        if(img1!=img2)
            throw OpenLF_Exception("Input/input shape mismatch in compute difference!");
        if(img1!=result)
            throw OpenLF_Exception("input/result shape mismatch in compute difference!");
        float* data_ptr1 = img1.data();
        float* data_ptr2 = img2.data();
        float* data_ptr_res = result.data();

        for(int n=0; n<img1.width()*img1.height(); n++)
            data_ptr_res[n] = data_ptr1[n]-data_ptr2[n];
        
    } catch(exception &e) {
        warning(e.what());
    }
}


void OpenLF::image::imgproc::abs_difference(channel_map &channels1,
                                            channel_map &channels2,
                                            OpenLF::image::ImageChannel &result) 
{
    try {
        string key;
        result = 0.0;
        
        OpenLF::image::ImageChannel tmp(result.width(),result.height());
        tmp.set(0.0f);
        
        for ( channel_map_iter iter = channels1.begin(); iter != channels1.end(); iter++ ) {
            key=iter->first;
            if ( channels2.find(key) == channels2.end() ) {
                throw OpenLF_Exception("Key match Error in compute abs_difference!");
            } else {
                abs_difference(channels1[key],channels2[key],tmp);
                result+=tmp;
            }
        }        
    } catch(exception &e) {
        warning(e.what());
    }
}



void OpenLF::image::imgproc::abs_difference(OpenLF::image::ImageChannel &img1, 
                                            OpenLF::image::ImageChannel &img2, 
                                            OpenLF::image::ImageChannel &result) 
{
    try {
        if(img1!=img2)
            throw OpenLF_Exception("Input/input shape mismatch in compute difference!");
        if(img1!=result)
            throw OpenLF_Exception("input/result shape mismatch in compute difference!");
        
        float* data_ptr1 = img1.data();
        float* data_ptr2 = img2.data();
        float* data_ptr_res = result.data();

        for(int n=0; n<img1.width()*img1.height(); n++)
            data_ptr_res[n] = abs(data_ptr1[n]-data_ptr2[n]);
        
    } catch(exception &e) {
        warning(e.what());
    }
}



void OpenLF::image::imgproc::MSE(channel_map &channels1,
                                 channel_map &channels2,
                                 map<string,double> &results)
{
    try {
        string key;
        double mse;
        
        for ( channel_map_iter iter = channels1.begin(); iter != channels1.end(); iter++ ) {
            key=iter->first;
            if ( channels2.find(key) == channels2.end() ) {
                throw OpenLF_Exception("Key match Error in compute MSE!");
            } else {
                
                mse = MSE(channels1[key],channels2[key]);
                results[key]=mse;
            }
        } 
    } catch(exception &e) {
        warning(e.what());
    }
}



double OpenLF::image::imgproc::MSE(OpenLF::image::ImageChannel &img1, 
                                   OpenLF::image::ImageChannel &img2) 

{
    if(img1!=img2)
        throw OpenLF_Exception("Input/input shape mismatch in compute difference!");

    float* data_ptr1 = img1.data();
    float* data_ptr2 = img2.data();
    double sum = 0;

    for(int n=0; n<img1.width()*img1.height(); n++)
        sum += ((data_ptr1[n]-data_ptr2[n])*(data_ptr1[n]-data_ptr2[n]));

    return sum/(img1.width()*img1.height());
}