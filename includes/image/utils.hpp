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

#ifndef IMAGEUTILS_HPP
#define	IMAGEUTILS_HPP

#include "debug.hpp"
#include "global.hpp"

namespace OpenLF { 
    namespace image { 
        namespace utils {
            
            

//! converts single rgb channels to vigra rgb image
/*!
 \param r red channel
 \param g green channel
 \param b blue channel
 \param img reference to the result uint8 rgb image
*/  
void mergeChannels(vigra::MultiArray<2,float> &r, 
                   vigra::MultiArray<2,float> &g, 
                   vigra::MultiArray<2,float> &b,
                   vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8>> &img);


//! converts single rgb channels to vigra bw image
/*!
 \param r red channel
 \param g green channel
 \param b blue channel
 \param img reference to the result uint8 bw image
*/  
void mergeChannels(vigra::MultiArray<2,float> &r, 
                   vigra::MultiArray<2,float> &g, 
                   vigra::MultiArray<2,float> &b,
                   vigra::MultiArray<2, vigra::UInt8> &img);


//! converts single rgb channels to vigra rgb image
/*!
 \param r view to an red channel
 \param g view to an green channel
 \param b view to an blue channel
 \param img reference to the result loat rgb image
*/  
void mergeChannels(vigra::MultiArrayView<2,float> &r, 
                   vigra::MultiArrayView<2,float> &g, 
                   vigra::MultiArrayView<2,float> &b,
                   vigra::MultiArray<2, vigra::RGBValue<float>> &img);
   

//! converts single rgb channels to vigra rgb image
/*!
 \param r red channel
 \param g green channel
 \param b blue channel
 \param img reference to the result float rgb image
*/  
void mergeChannels(vigra::MultiArray<2,float> &r, 
                   vigra::MultiArray<2,float> &g, 
                   vigra::MultiArray<2,float> &b,
                   vigra::MultiArray<2, vigra::RGBValue<float>> &img);


//! converts single rgb channels to vigra bw image
/*!
 \param r view to an red channel
 \param g view to an green channel
 \param b view to an blue channel
 \param img reference to the result loat bw image
*/  
void mergeChannels(vigra::MultiArrayView<2,float> &r, 
                   vigra::MultiArrayView<2,float> &g, 
                   vigra::MultiArrayView<2,float> &b,
                   vigra::MultiArray<2, float> &img);
   

//! converts single rgb channels to vigra bw image
/*!
 \param r red channel
 \param g green channel
 \param b blue channel
 \param img reference to the result float bw image
*/  
void mergeChannels(vigra::MultiArray<2,float> &r, 
                   vigra::MultiArray<2,float> &g, 
                   vigra::MultiArray<2,float> &b,
                   vigra::MultiArray<2, float> &img);
     

}}}

#endif	/* IMAGEUTILS_HPP */

