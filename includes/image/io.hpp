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

#include "debug.hpp"
#include "global.hpp"
#include "image/utils.hpp"
#include "utils/helpers.hpp"
#include "image/Channel.hpp"

namespace OpenLF { 
    namespace image { 
        
        struct ROI {
            int pos_x;
            int pos_y;
            int width;
            int height;
        };
        
        namespace io {
            

//! reduces a passed ImageChannel map
/*!
 The passed ImageChannel map is reduced to only the channels with the labels passed in
 keys_to_keep. 
 \param channels map object of string labels as keys and MultiArrays as data
 \param keys_to_keep string vector of labels to keep in map
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/     
void reduce_channels(map<string,ImageChannel> &channels,vector<string> keys_to_keep);
   

//! map the pixel values to a range of [0,255]
/*!
 \param fimg float MultiArray to map
 \param img result MultiArray 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void linear_range_mapping(vigra::MultiArray<2,float>& fimg, vigra::MultiArray<2, vigra::UInt8>& img);


//! map the pixel values to a range of [0,255]
/*!
 \param fimg float MultiArray to map
 \param img result MultiArray 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void linear_range_mapping(vigra::MultiArray<2,float>& fimg, vigra::MultiArray<2,float>& img);


//! map the pixel values to a range of [0,255]
/*!
 \param fimg float MultiArray to map
 \param img result MultiArray 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void linear_range_mapping(vigra::MultiArrayView<2,float>& fimg, vigra::MultiArray<2,float>& img);


//! map the pixel values to a range of [0,255]
/*!
 \param ImageChannel& img_channel instance of ImageChannel class
 \param img result MultiArray 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void linear_range_mapping(ImageChannel& img_channel, vigra::MultiArray<2, vigra::UInt8>& img);


//! read an image from file and store channels in map structure
/*!
 Load an image from file and stores the image channels in the passed map structure.
 Labels "bw" for a gray value image and "r","g","b" for color images are set automatically.
 The passed channel map isn't cleared. If one of the channels above already exist
 it's overwritten, if other channels are present they will be kept. 
 \param filename full path of the image file
 \param channels map of string labels as keys and Channel instance as data 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
bool imread(string filename, map<string,OpenLF::image::ImageChannel> &img_channel);


//! read an region of interest of an image from file and store channels in map structure
/*!
 Load an region of interest from an image from file and stores the image channels in the passed 
 map structure. Labels "bw" for a gray value image and "r","g","b" for color images are set 
 automatically. The passed channel map isn't cleared. If one of the channels above already exist
 it's overwritten, if other channels are present they will be kept. 
 \param filename full path of the image file
 \param channels map of string labels as keys and Channel instance as data 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
bool imread(string filename, ROI roi, map<string,OpenLF::image::ImageChannel> &img_channel);


//! saves an image to file
/*!
 Saves a 2D MultiArray float image to file.
 \param filename path to save the file
 \param img MultiArray float image
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
bool imsave(string filename, vigra::MultiArray<2,float> img);

//! saves an rgb image to file
/*!
 Saves a 2D rgb MultiArray uint8 image to file.
 \param filename path to save the file
 \param img MultiArray float image
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
bool imsave(string filename, vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>> img);


//! saves an image view to file
/*!
 Saves a 2D MultiArray float image to file.
 \param filename path to save the file
 \param img MultiArray float image
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
bool imsave(string filename, vigra::MultiArrayView<2,float> img);

//! saves an image view to file
/*!
 Saves a 2D MultiArray float image to file.
 \param filename path to save the file
 \param img MultiArray uint8 image
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
bool imsave(string filename, vigra::MultiArrayView<2,vigra::UInt8> img);

//! saves an Channel instance to file
/*!
 Saves a Channel instance float image to file.
 \param filename path to save the file
 \param channel_img instance of the Channel class 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
bool imsave(string filename, ImageChannel img_channel);


//! saves a single channel of a channel map
/*!
 Saves a single channel of a channel map object to file. 
 \param filename path to save the file
 \param channels map of string labels as keys and ImageCHannel instances as data
 \param key of the channel
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/     
bool imsave(string filename, map< string,ImageChannel> channels, string key);


//! saves all channels of an ImageChannel map to file
/*!
Saves an entire channel map object to file. Channels with labels "bw" and "r","g","b"
are automatically saved as gray value or color image respectively. The type or in
case of other labels the label itself are automatically added to the filename as 
an appendix. 
 \param filename full path of the image file
 \param channels map of string labels as keys and MultiArrays as data 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
bool imsave(string filename, map<string,ImageChannel> channels);


//! saves a ImageChannel instance to file
/*!
Saves specific channels with labels passed via keys_to_save of a channel map object 
to file. Channels with labels "bw" and "r","g","b" are automatically saved as gray 
value or color image respectively. The type or in case of other labels the label 
itself are automatically added to the filename as an appendix.  
 \param filename full path of the image file
 \param channels map of string labels as keys and MultiArrays as data 
 \param keys_to_save vector of labels to be kept for saving
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
bool imsave(string filename, map<string,ImageChannel> channels,vector<string> keys_to_save);
     
}}}

#endif	/* IMAGE_IO_HPP */

