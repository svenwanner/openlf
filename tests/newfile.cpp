test_channel.hpp (currently in Line 88)


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

#include "OpenLF/global.hpp"
#include "OpenLF/debug.hpp"


typedef vigra::MultiArrayView<2,float> array_2d;





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
    
    //! Initialize with a float value
    /*!
     \param width image width
     \param height image height
     \param value initial value
    */
    ImageChannel(int width, int height, float value);
    
    
    
    //! Initialize with a float value
    /*!
     \param shape of the empty image
     \param value initial value
    */
    ImageChannel(const vigra::Shape2 shape, float value);
    
    //! Initialize with float array constructor
    /*!
     \param width image width
     \param height image height
     \param data_ptr image data 
    */
    ImageChannel(int width, int height, const float* data_ptr);
    
    //! Initialize with float array constructor
    /*!
     \param shape
     \param data_ptr image data 
    */
    ImageChannel(const vigra::Shape2 shape, const float* data_ptr);
    
    //! Initialize with uint8 array constructor
    /*!
     \param width image width
     \param height image height
     \param data_ptr image data 
    */
    ImageChannel(int width, int height, const vigra::UInt8* data_ptr);
    
    //! Initialize with uint8 array constructor
    /*!
     \param shape
     \param data_ptr image data 
    */
    ImageChannel(const vigra::Shape2 shape, const vigra::UInt8* data_ptr);
    
    //! Initialize with vigra MultiArrayView constructor 
    /*!
     \param vmarr vigra MultiArrayView<2,float> 
    */
    ImageChannel(const array_2d &vmarr);

    //! Initialize with vigra MultiArrayView constructor 
    /*!
     \param vmarr vigra MultiArrayView<2,Uint8> 
    */
    ImageChannel(const vigra::MultiArrayView<2,vigra::UInt8> &vmarr); 

    //! copy constructor
    /*!
     \param orig ImageChannel reference to copy from 
    */
    ImageChannel(const ImageChannel& orig);

    virtual ~ImageChannel();
    

    
    
    
    
    
////////////////////////////////////////////////////////////////////////////////
//////                    I N I T I A L I Z E R S 
////////////////////////////////////////////////////////////////////////////////
    
    
    
    //!  initialize with a float value 
    /*!
     \param width image width
     \param height image height
     \param value initial value
    */
    void init(int width, int height, float value);
    
    
    //!  allocate empty memory from shape
    /*!
     \param shape image shape
    */
    void init(const vigra::Shape2 shape);
    
    //!  initialize with a float value 
    /*!
     \param shape image shape
    */
    void init(const vigra::Shape2 shape, float value);
    
    
    //!  allocate memory from shape and float data pointer
    /*!
     \param shape image shape
     \param data_ptr float pointer to data 
     \param value initial value
    */
    void init(const vigra::Shape2 shape, const float* data_ptr);
    
    
    //!  allocate memory from image size and float data pointer
    /*!
     \param width image width
     \param height image height
     \param data_ptr float pointer to data 
    */
    void init(int width, int height, const float* data_ptr);
    
    
    //!  allocate memory from shape and uint8 data pointer
    /*!
     \param shape image shape
     \param data_ptr uint8 pointer to data 
    */
    void init(const vigra::Shape2 shape, const vigra::UInt8* data_ptr);
    
    
    //!  allocate memory from image size and uint8 data pointer
    /*!
     \param width image width
     \param height image height
     \param data_ptr uint8 pointer to data 
    */
    void init(int width, int height, const vigra::UInt8* data_ptr);
    
    
    
////////////////////////////////////////////////////////////////////////////////
//////                S E T / G E T   M E T H O D S  
////////////////////////////////////////////////////////////////////////////////
    //!* deep copy of an image channel, no external linking 
    /*! Works only with default counstructor. Data is allocates as 
    an internal multiarray*/
    void deepcopy(OpenLF::image::ImageChannel& channel);
    
    //!* indicates the use of this class as a pointer to external data.
    /*! If external_flag is true, one should be aware that any manipulation with ImageChannel 
     * will result in overwriting this data. Instead if the value of the flag is false, 
     * ImageChannel is decoupled from any external data.  
     */
    bool externalData() const { return m_external_flag; };
    
     


    
    
    
    
    
    
    
    //! get pixel 
    /*!
     \param x position
     \param y position
     \param float value reference
    */
    void get(int x, int y, float &value) const;
    
    
    
    
    
    
    
    
    
   
   
    
    //! get a view to a region of interest
    /*!
     \param x ROI x position
     \param y ROI y position
     \param width of the ROI
     \param height of the ROI
    */
    vigra::MultiArrayView<2,float> viewToROI(int x, int y, int width, int height) const;
    
    
    //! get a view to a row of the channel image
    /*!
     \param fix_y the y coordinate of the row
    */
    vigra::MultiArrayView<1,float> viewToRow(int fix_y) const;
    
    
    //! get a view to a column of the channel image
    /*!
     \param fix_y the y coordinate of the column
    */
    vigra::MultiArrayView<1,float> viewToColumn(int fix_x) const;
    
   
   
////////////////////////////////////////////////////////////////////////////////
//////            O P E R A T O R    O V E R L O A D S
////////////////////////////////////////////////////////////////////////////////
    
    //! overload of () operator 
    float & operator() (int x, int y) { return m_pixel(x,y); }
    
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
    ImageChannel & operator+=(ImageChannel const&rhs);
    
    //! overload of -= operator pixelwise
    ImageChannel & operator-=(ImageChannel const&rhs);
    
    //! overload of *= operator 
    ImageChannel & operator*=(float value);
    
    //! overload of /= operator 
    ImageChannel & operator/=(float value);
    
    //! overload of *= operator pixelwise
    ImageChannel & operator*=(ImageChannel const&rhs);
    
    //! overload of /= operator pixelwise
    ImageChannel & operator/=(ImageChannel const&rhs);
    
    
    

    
    
    
private:
    array_2d m_pixel; 
    vigra::MultiArray<2,float> *m_internal_data_ptr=NULL; 
    bool m_external_flag;
  
};


}}




//! overload of == operator 
bool operator==(const OpenLF::image::ImageChannel & lhs, const OpenLF::image::ImageChannel & rhs);

//! overload of != operator 
bool operator!=(const OpenLF::image::ImageChannel & lhs, const OpenLF::image::ImageChannel & rhs);


#endif	/* CHANNEL_HPP */

