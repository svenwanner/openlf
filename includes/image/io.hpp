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

            
#ifndef IO_IMAGE_HPP
#define	IO_IMAGE_HPP

#include "global.hpp"
#include "utils/helpers.hpp"

namespace OpenLF { 
    namespace image { 
        namespace io {
            
void reduce_channels(map<string,vigra::MultiArray<2,float>> &channels,vector<string> keys_to_keep);
            
void linear_range_mapping(vigra::MultiArray<2,float>& fimg, vigra::MultiArray<2, vigra::UInt8>& img);

bool imread(string filename, map<string,vigra::MultiArray<2,float>> &channels);

bool imsave(string filename, vigra::MultiArray<2,float> img);

bool imsave(string filename, map<string,vigra::MultiArray<2,float>> channels); 

bool imsave(string filename, map<string,vigra::MultiArray<2,float>> channels,vector<string> keys_to_save);
     
}}}

#endif	/* IMAGE_IO_HPP */

