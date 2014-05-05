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

#include "OpenLF/image/utils.hpp"






/*!
 \note the user has to ensure that the range of the float channels is as expected,
 the values are converted to uint8 as they are without automatic range adjustments
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
void OpenLF::image::utils::mergeChannels(vigra::MultiArray<2,float> &r, 
                                         vigra::MultiArray<2,float> &g, 
                                         vigra::MultiArray<2,float> &b,
                                         vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8>> &img) 
{
    if(!img.hasData()) 
        img = vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8>>(vigra::Shape2(r.width(),r.height()));
    if(img.shape()!=r.shape()) 
        throw OpenLF_Exception("utils::mergeChannels -> shape mismatch");
    
    for(int y=0; y<r.height(); y++) {
        for(int x=0; x<r.width(); x++) {
            img(x,y)[0] = (vigra::UInt8)r(x,y);
            img(x,y)[1] = (vigra::UInt8)g(x,y);
            img(x,y)[2] = (vigra::UInt8)b(x,y);
        }
    }
}


/*!
 \note the user has to ensure that the range of the float channels is as expected,
 the values are converted to uint8 as they are without automatic range adjustments
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
void OpenLF::image::utils::mergeChannels(vigra::MultiArray<2,float> &r, 
                                         vigra::MultiArray<2,float> &g, 
                                         vigra::MultiArray<2,float> &b,
                                         vigra::MultiArray<2,vigra::UInt8> &img) 
{
    if(!img.hasData()) {
        img = vigra::MultiArray<2,vigra::UInt8>(vigra::Shape2(r.width(),r.height()));
    }
    else {
        if(img.shape()!=r.shape()) throw OpenLF_Exception("utils::mergeChannels -> shape mismatch");
        for(int y=0; y<r.height(); y++) {
            for(int x=0; x<r.width(); x++) {
                img(x,y) = (vigra::UInt8)(0.3*r(x,y)+0.59*g(x,y)+0.11*b(x,y));
            }
        }
    }
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
void OpenLF::image::utils::mergeChannels(vigra::MultiArray<2,float> &r, 
                                         vigra::MultiArray<2,float> &g, 
                                         vigra::MultiArray<2,float> &b,
                                         vigra::MultiArray<2, vigra::RGBValue<float>> &img) 
{
    if(!img.hasData()) {
        img = vigra::MultiArray<2, vigra::RGBValue<float>>(vigra::Shape2(r.width(),r.height()));
    }
    else {
        if(img.shape()!=r.shape()) throw OpenLF_Exception("utils::mergeChannels -> shape mismatch");
        for(int y=0; y<r.height(); y++) {
            for(int x=0; x<r.width(); x++) {
                img(x,y)[0] = r(x,y);
                img(x,y)[1] = g(x,y);
                img(x,y)[2] = b(x,y);
            }
        }
    }
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
void OpenLF::image::utils::mergeChannels(vigra::MultiArrayView<2,float> &r, 
                                         vigra::MultiArrayView<2,float> &g, 
                                         vigra::MultiArrayView<2,float> &b,
                                         vigra::MultiArray<2, vigra::RGBValue<float>> &img) 
{
    if(!img.hasData()) {
        img = vigra::MultiArray<2, vigra::RGBValue<float>>(vigra::Shape2(r.width(),r.height()));
    }
    else {
        if(img.shape()!=r.shape()) throw OpenLF_Exception("utils::mergeChannels -> shape mismatch");
        for(int y=0; y<r.height(); y++) {
            for(int x=0; x<r.width(); x++) {
                img(x,y)[0] = r(x,y);
                img(x,y)[1] = g(x,y);
                img(x,y)[2] = b(x,y);
            }
        }
    }
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
void OpenLF::image::utils::mergeChannels(vigra::MultiArray<2,float> &r, 
                                         vigra::MultiArray<2,float> &g, 
                                         vigra::MultiArray<2,float> &b,
                                         vigra::MultiArray<2,float> &img) 
{
    if(!img.hasData()) {
        img = vigra::MultiArray<2,float>(vigra::Shape2(r.width(),r.height()));
    }
    else {
        if(img.shape()!=r.shape()) throw OpenLF_Exception("utils::mergeChannels -> shape mismatch");
        for(int y=0; y<r.height(); y++) {
            for(int x=0; x<r.width(); x++) {
                img(x,y) = (0.3*r(x,y)+0.59*g(x,y)+0.11*b(x,y));
            }
        }
    }
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
void OpenLF::image::utils::mergeChannels(vigra::MultiArrayView<2,float> &r, 
                                         vigra::MultiArrayView<2,float> &g, 
                                         vigra::MultiArrayView<2,float> &b,
                                         vigra::MultiArray<2,float> &img) 
{
    if(!img.hasData()) 
        img = vigra::MultiArray<2,float>(vigra::Shape2(r.width(),r.height()));
    if(img.shape()!=r.shape()) 
        throw OpenLF_Exception("utils::mergeChannels -> shape mismatch");
    
    for(int y=0; y<r.height(); y++) {
        for(int x=0; x<r.width(); x++) {
            img(x,y) = (0.3*r(x,y)+0.59*g(x,y)+0.11*b(x,y));
        }
    }
}