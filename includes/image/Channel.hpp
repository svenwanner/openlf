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

#ifndef CHANNEL_HPP
#define	CHANNEL_HPP

#include "global.hpp"
#include "debug.hpp"

typedef vigra::MultiArray<2,float> array_2d;

namespace OpenLF {
    namespace image {
    


class ImageChannel {
public:
    ImageChannel();
    ImageChannel(int width, int height);
    ImageChannel(vigra::Shape2 shape);
    ImageChannel(int width, int height, float* data_ptr);
    ImageChannel(vigra::Shape2 shape, float* data_ptr);
    
    ImageChannel(const ImageChannel& orig);
    virtual ~ImageChannel();
    
    
    
    
    
    //! allocate empty memory from image size 
    /*!
     \param width image width
     \param height image height
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init(int width, int height);
    
    
    //!  allocate empty memory from shape
    /*!
     \param shape image shape
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init(vigra::Shape2 shape);
    
    
    //!  allocate memory from shape and float data pointer
    /*!
     \param shape image shape
     \param data_ptr float pointer to data 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init(vigra::Shape2 shape, float* data_ptr);
    
    
    //!  allocate memory from image size and float data pointer
    /*!
     \param width image width
     \param height image height
     \param data_ptr float pointer to data 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init(int width, int height, float* data_ptr);
    
    
    //!  allocate memory from shape and uint8 data pointer
    /*!
     \param shape image shape
     \param data_ptr uint8 pointer to data 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init(vigra::Shape2 shape, vigra::UInt8* data_ptr);
    
    
    //!  allocate memory from image size and uint8 data pointer
    /*!
     \param width image width
     \param height image height
     \param data_ptr uint8 pointer to data 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init(int width, int height, vigra::UInt8* data_ptr);
   
    
    
    
    
    //! get width
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    int width() const { return pixel.width(); };
    
    
    //! get height
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    int height() const { return pixel.height(); };
    
    
    //! get shape
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    vigra::Shape2 shape() const { return pixel.shape(); };
    
    
    
    
    
    
    
    //! returns a pointer to the data as MultiArray<2,float>
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    float* data_ptr() const;
    
    
    //! returns a pointer to the data as MultiArray<2,float>
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    vigra::MultiArray<2,float>* data();
    
    
    //! set the passed pointer to a MultiArray<2,float> pointer to point to internal data address
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void data(vigra::MultiArray<2,float> **pixel);
    
    
    
private:
    array_2d pixel;
};


}}
#endif	/* CHANNEL_HPP */