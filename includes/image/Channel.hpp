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
    
        
//! Vigra MultiArray wrapper to provide a single 2D image channel
/*!
 * This class is used to be a wrapper of Vigra MultiArray's of type
 * vigra::MultiArray<2,float>. The intention is to provide a 2D image
 * channel as part of a multi-channel structure to handle an arbitrary 
 * number of image and result data in a common structure. The data are
 * stored in a vigra::MultiArray<2,float>. One has access to the data 
 * via pointer passing of either the array itself or the float pointer 
 * to the memory block. The class behaves quite similar to a vigra Multi-
 * Array 
 */
class ImageChannel {
public:
    
    //! Default constructor
    ImageChannel();
    
    //! Empty image constructor
    /*!
     \param width image width
     \param height image height
    */
    ImageChannel(int width, int height);
    
    //! Empty image constructor
    /*!
     \param shape of the empty image
    */
    ImageChannel(vigra::Shape2 shape);
    
    //! Initialize with float array constructor
    /*!
     \param width image width
     \param height image height
     \param data_ptr image data 
    */
    ImageChannel(int width, int height, float* data_ptr);
    
    //! Initialize with float array constructor
    /*!
     \param shape
     \param data_ptr image data 
    */
    ImageChannel(vigra::Shape2 shape, float* data_ptr);
    
    //! Initialize with uint8 array constructor
    /*!
     \param width image width
     \param height image height
     \param data_ptr image data 
    */
    ImageChannel(int width, int height, vigra::UInt8* data_ptr);
    
    //! Initialize with uint8 array constructor
    /*!
     \param shape
     \param data_ptr image data 
    */
    ImageChannel(vigra::Shape2 shape, vigra::UInt8* data_ptr);
    
    //! Initialize with vigra MultiArray constructor
    /*!
     \param vmarr vigra MultiArray<2,float> 
    */
    ImageChannel(array_2d &vmarr);
    
    //! Initialize with vigra MultiArray constructor
    /*!
     \param vmarr vigra MultiArray<2,Uint8> 
    */
    ImageChannel(vigra::MultiArray<2,vigra::UInt8> &vmarr);
    
    //! copy constructor
    /*!
     \param orig ImageChannel reference to copy from 
    */
    ImageChannel(const ImageChannel& orig);
    
    //! default destructor
    /*!
    */
    virtual ~ImageChannel();
    
    
    
    
    
////////////////////////////////////////////////////////////////////////////////
//////                    I N I T I A L I Z E R S 
////////////////////////////////////////////////////////////////////////////////
    
    //! allocate empty memory from image size 
    /*!
     \param width image width
     \param height image height
    */
    void init(int width, int height);
    
    
    //!  allocate empty memory from shape
    /*!
     \param shape image shape
    */
    void init(vigra::Shape2 shape);
    
    
    //!  allocate memory from shape and float data pointer
    /*!
     \param shape image shape
     \param data_ptr float pointer to data 
    */
    void init(vigra::Shape2 shape, float* data_ptr);
    
    
    //!  allocate memory from image size and float data pointer
    /*!
     \param width image width
     \param height image height
     \param data_ptr float pointer to data 
    */
    void init(int width, int height, float* data_ptr);
    
    
    //!  allocate memory from shape and uint8 data pointer
    /*!
     \param shape image shape
     \param data_ptr uint8 pointer to data 
    */
    void init(vigra::Shape2 shape, vigra::UInt8* data_ptr);
    
    
    //!  allocate memory from image size and uint8 data pointer
    /*!
     \param width image width
     \param height image height
     \param data_ptr uint8 pointer to data 
    */
    void init(int width, int height, vigra::UInt8* data_ptr);
    
    
    
    
    
    
////////////////////////////////////////////////////////////////////////////////
//////                S E T / G E T   M E T H O D S  
////////////////////////////////////////////////////////////////////////////////
    
    bool hasData() const { return pixel.hasData(); };
    
    
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
    
    
    //! set all pixels to value passed 
    /*!
     \param float value to set
    */
    void set(float value);
    
    //! get pixel 
    /*!
     \param x position
     \param y position
    */
    float get(int x, int y);
    
    //! get pixel 
    /*!
     \param x position
     \param y position
     \param float value reference
    */
    void get(int x, int y, float &value);
    
    
    //! get sum over all image pixels
    double sum() { return pixel.sum<double>(); };
    
    
    //! get a pointer to the data as MultiArray<2,float>
    float* data() const;
    
    
    //! get a pointer to the data as MultiArray<2,float>
    vigra::MultiArray<2,float>* image();
    
    
    //! set the passed MultiArray<2,float> pointer to internal data address
    /*!
     \param pixel a pointer to a pointer to a MultiArray
    */
    void image(vigra::MultiArray<2,float> **pixel);
   
   
   
   
////////////////////////////////////////////////////////////////////////////////
//////            O P E R A T O R    O V E R L O A D S
////////////////////////////////////////////////////////////////////////////////
    
    //! overload of () operator 
    float & operator() (int x, int y) { return pixel(x,y); }
    
    //! overload of = operator 
    ImageChannel & operator=(float value);
    
    //! overload of + operator 
    ImageChannel & operator+(float value);
    
    //! overload of - operator 
    ImageChannel & operator-(float value);
    
    //! overload of += operator 
    ImageChannel & operator+=(float value);
    
    //! overload of -= operator
    ImageChannel & operator-=(float value);
    
    //! overload of += operator pixelwise
    ImageChannel & operator+=(ImageChannel &rhs);
    
    //! overload of -= operator pixelwise
    ImageChannel & operator-=(ImageChannel &rhs);
    
    //! overload of *= operator 
    ImageChannel & operator*=(float value);
    
    //! overload of /= operator 
    ImageChannel & operator/=(float value);
    
    //! overload of *= operator pixelwise
    ImageChannel & operator*=(ImageChannel &rhs);
    
    //! overload of /= operator pixelwise
    ImageChannel & operator/=(ImageChannel &rhs);
    
    
    

    
    
    
private:
    array_2d pixel;
};


}}




//! overload of == operator 
bool operator==(const OpenLF::image::ImageChannel & lhs, const OpenLF::image::ImageChannel & rhs);

//! overload of != operator 
bool operator!=(const OpenLF::image::ImageChannel & lhs, const OpenLF::image::ImageChannel & rhs);


#endif	/* CHANNEL_HPP */