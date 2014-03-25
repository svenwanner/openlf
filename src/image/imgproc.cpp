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


bool OpenLF::image::imgproc::shape_check(vigra::Shape2 s1, vigra::Shape2 s2) 
{
    bool status = true;
    if(s1[0]!=s2[0]) status = false;
    if(s1[1]!=s2[1]) status = false;
    return status;
}


void OpenLF::image::imgproc::difference(map<string,vigra::MultiArray<2,float>> &channels1,
                                        map<string,vigra::MultiArray<2,float>> &channels2,
                                        vigra::MultiArray<2,float> &result) 
{
    try {
        result=0;
        string key;
        vigra::MultiArray<2,float> tmp(vigra::Shape2(result.width(),result.height()));
        
        for ( auto& iter : channels1 ) {
            key=iter.first;
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


void OpenLF::image::imgproc::difference(vigra::MultiArray<2,float> &img1, 
                                        vigra::MultiArray<2,float> &img2, 
                                        vigra::MultiArray<2,float> &result) 
{
    try {
        result=0;
        
        if(!shape_check(img1.shape(),img2.shape()))
            throw OpenLF_Exception("Input/input shape mismatch in compute difference!");
        if(!shape_check(img1.shape(),result.shape()))
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


void OpenLF::image::imgproc::abs_difference(map<string,vigra::MultiArray<2,float>> &channels1,
                                            map<string,vigra::MultiArray<2,float>> &channels2,
                                            vigra::MultiArray<2,float> &result) 
{
    try {
        string key;
        result=0;
        
        vigra::MultiArray<2,float> tmp(vigra::Shape2(result.width(),result.height()));
        
        for ( auto& iter : channels1 ) {
            key=iter.first;
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


void OpenLF::image::imgproc::abs_difference(vigra::MultiArray<2,float> &img1, 
                                        vigra::MultiArray<2,float> &img2, 
                                        vigra::MultiArray<2,float> &result) 
{
    try {
        result=0;
        if(!shape_check(img1.shape(),img2.shape()))
            throw OpenLF_Exception("Input/input shape mismatch in compute difference!");
        if(!shape_check(img1.shape(),result.shape()))
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


void OpenLF::image::imgproc::MSE(map<string,vigra::MultiArray<2,float>> &channels1,
         map<string,vigra::MultiArray<2,float>> &channels2,
         map<string,float> &results) 
{
    try {
        string key;
        double mse;
        
        for ( auto& iter : channels1 ) {
            key=iter.first;
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



double OpenLF::image::imgproc::MSE(vigra::MultiArray<2,float> &img1, 
                                   vigra::MultiArray<2,float> &img2) 

{
    if(!shape_check(img1.shape(),img2.shape()))
        throw OpenLF_Exception("Input/input shape mismatch in compute difference!");

    float* data_ptr1 = img1.data();
    float* data_ptr2 = img2.data();
    double sum = 0;

    for(int n=0; n<img1.width()*img1.height(); n++)
        sum += ((data_ptr1[n]-data_ptr2[n])*(data_ptr1[n]-data_ptr2[n]));

    return sum/(img1.width()*img1.height());
}