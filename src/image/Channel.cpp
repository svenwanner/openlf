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



/*! 
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel::ImageChannel() {
    print(1,"image::ImageChannel::ImageChannel() called...");
}

/*! 
 * Initialize empty ImageChannel instance with shape (width,height).
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel::ImageChannel(int width, int height)
{
    print(1,"image::ImageChannel::ImageChannel(width,height) called...");
    
    init(width,height);
}

/*! 
 * Initialize empty ImageChannel instance with shape passed.  
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel::ImageChannel(vigra::Shape2 shape)
{
    print(1,"image::ImageChannel::ImageChannel(shape) called...");
    
    init(shape);
}

/*! 
 * Initialize ImageChannel instance with shape (width,height) and data given
 * by the passed float array. The user has to ensure that shape passed and the
 * size of the float array passed are consistent. Data at data_ptr are copied. 
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
OpenLF::image::ImageChannel::ImageChannel(int width, int height, float* data_ptr)
{
    print(1,"image::ImageChannel::ImageChannel(width,height, data_ptr) called...");
    
    init(width,height,data_ptr);
}

/*! 
 * Initialize ImageChannel instance with shape and data given
 * by the passed float array. The user has to ensure that shape passed and the
 * size of the float array passed are consistent. Data at data_ptr are copied.
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
OpenLF::image::ImageChannel::ImageChannel(vigra::Shape2 shape, float* data_ptr)
{
    print(1,"image::ImageChannel::ImageChannel(shape, data_ptr) called...");
    
    init(shape,data_ptr);
}

/*! 
 * Initialize ImageChannel instance with shape (width,height) and data given
 * by the passed uint8 array. The user has to ensure that shape passed and the
 * size of the uint8 array passed are consistent. Data at data_ptr are copied. 
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
OpenLF::image::ImageChannel::ImageChannel(int width, int height, vigra::UInt8* data_ptr)
{
    print(1,"image::ImageChannel::ImageChannel(width,height, data_ptr) called...");
    
    init(width,height,data_ptr);
}

/*! 
 * Initialize ImageChannel instance with shape and data given
 * by the passed uint8 array. The user has to ensure that shape passed and the
 * size of the uint8 array passed are consistent. Data at data_ptr are copied.
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
OpenLF::image::ImageChannel::ImageChannel(vigra::Shape2 shape, vigra::UInt8* data_ptr)
{
    print(1,"image::ImageChannel::ImageChannel(shape, data_ptr) called...");
    
    init(shape,data_ptr);
}

/*! 
 * Initialize ImageChannel instance with by copying data from a passed vigra
 * MultiArray reference.
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
OpenLF::image::ImageChannel::ImageChannel(array_2d &vmarr) 
{
    init(vmarr.width(),vmarr.height(),vmarr.data());
}

/*! 
 * Initialize ImageChannel instance with by copying data from a passed vigra
 * MultiArray reference.
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
OpenLF::image::ImageChannel::ImageChannel(vigra::MultiArray<2,vigra::UInt8> &vmarr) 
{
    init(vmarr.width(),vmarr.height(),vmarr.data());
}

/*! 
 * This copy constructor is used to be a deep copy constructor copying the all
 * properties and the data as well.
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
OpenLF::image::ImageChannel::ImageChannel(const ImageChannel& orig) 
{
    int w = orig.width();
    int h = orig.height();
    this->pixel = array_2d(vigra::Shape2(w,h));
    
    float* d_ptr = orig.data();
    for(int n=0; n<h*w; n++) {
        this->pixel.data()[n] = d_ptr[n];
    }
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
OpenLF::image::ImageChannel::~ImageChannel() 
{
}




////////////////////////////////////////////////////////////////////////////////
//////                    I N I T I A L I Z E R S 
////////////////////////////////////////////////////////////////////////////////

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(int width, int height) 
{
    pixel = array_2d(vigra::Shape2(width,height));
    pixel = 0.0f;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(vigra::Shape2 shape)
{
    pixel = array_2d(shape);
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(int width, int height, float* data_ptr) 
{
    pixel = array_2d(vigra::Shape2(width,height));
    
    float *local_ptr = pixel.data();
    for(int n=0; n < width * height; n++) {
        local_ptr[n] = data_ptr[n];
    }
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(vigra::Shape2 shape, float* data_ptr)
{
    pixel = array_2d(shape);
    
    float *local_ptr = pixel.data();
    for(int n=0; n < shape[0] * shape[1]; n++) {
        local_ptr[n] = data_ptr[n];
    }
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(int width, int height, vigra::UInt8 * data_ptr) 
{
    pixel = array_2d(vigra::Shape2(width,height));
    
    float *local_ptr = pixel.data();
    for(int n=0; n < width * height; n++) {
        local_ptr[n] = (float)data_ptr[n]/255.0;
    }
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(vigra::Shape2 shape, vigra::UInt8* data_ptr)
{
    pixel = array_2d(shape);
    
    float *local_ptr = pixel.data();
    for(int n=0; n < shape[0] * shape[1]; n++) {
        local_ptr[n] = (float)data_ptr[n]/255.0;
    }
}





////////////////////////////////////////////////////////////////////////////////
//////                S E T / G E T   M E T H O D S  
////////////////////////////////////////////////////////////////////////////////

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
void OpenLF::image::ImageChannel::set(float value)
{ 
    for(int n=0; n<this->pixel.width()*this->pixel.height(); n++)
        this->pixel.data()[n] = value; 
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
float OpenLF::image::ImageChannel::get(int x, int y) 
{
    if(x>=0 && x<pixel.width() && y>=0 && y<pixel.height())
        return pixel(x,y);
    else throw OpenLF_Exception("Out of bounce");
}
 
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::image::ImageChannel::get(int x, int y, float &value) 
{
    if(x>=0 && x<pixel.width() && y>=0 && y<pixel.height())
        value = pixel(x,y);
    else throw OpenLF_Exception("Out of bounce");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
float* OpenLF::image::ImageChannel::data() const
{
    print(1,"image::Channel::data() called...");
    
    return pixel.data();
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
vigra::MultiArray<2,float>* OpenLF::image::ImageChannel::image()
{
    print(1,"image::Channel::image() called...");
    
    return &pixel;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
void OpenLF::image::ImageChannel::image(vigra::MultiArray<2,float> **pixel) 
{
    print(1,"image::Channel::image(**pixel) called...");
    
    *pixel = &this->pixel;
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
vigra::MultiArrayView<2,float> OpenLF::image::ImageChannel::viewToROI(int x, int y, int width, int height) {

    if(x<0 || y<0 || x+width>=pixel.width() || y+height>=pixel.height())
        throw OpenLF_Exception("out of bounce!");
    else {
        vigra::MultiArrayView<2, float> roi_view = pixel.subarray(vigra::Shape2(x,y), vigra::Shape2(x+width,y+height));
        return roi_view;
    }
}





////////////////////////////////////////////////////////////////////////////////
//////            O P E R A T O R    O V E R L O A D S
////////////////////////////////////////////////////////////////////////////////

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator=(float value)
{ 
    for(int n=0; n<this->pixel.width()*this->pixel.height(); n++)
        this->pixel.data()[n] = value; 
    return *this;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator+(float value)
{ 
    for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
        this->pixel.data()[n] += value;
    }
    return *this;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator-(float value)
{ 
    for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
        this->pixel.data()[n] -= value;
    }
    return *this;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator+=(float value)
{ 
    for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
        this->pixel.data()[n] += value;
    }
    return *this;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator-=(float value)
{ 
    for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
        this->pixel.data()[n] -= value;
    }
    return *this;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator+=(OpenLF::image::ImageChannel &rhs)
{ 
    if(this->shape() == rhs.shape()) {
        float *in_data = rhs.data();
        for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
            this->pixel.data()[n] += in_data[n];
        }
        return *this;
    }
    else throw OpenLF_Exception("Shape mismatch");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator-=(OpenLF::image::ImageChannel &rhs)
{ 
    if(this->shape() == rhs.shape()) {
        float *in_data = rhs.data();
        for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
            this->pixel.data()[n] -= in_data[n];
        }
        return *this;
    }
    else throw OpenLF_Exception("Shape mismatch");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator*=(float value)
{ 
    for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
        this->pixel.data()[n] *= value;
    }
    return *this;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator/=(float value)
{ 
    if(value!=0.0f) {
        for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
            this->pixel.data()[n] /= value;
        }
        return *this;
    } else throw overflow_error("Divide by zero exception");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator*=(OpenLF::image::ImageChannel &rhs)
{ 
    if(this->shape() == rhs.shape()) {
        float *in_data = rhs.data();
        for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
            this->pixel.data()[n] *= in_data[n];
        }
        return *this;
    }
    else throw OpenLF_Exception("Shape mismatch");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator/=(OpenLF::image::ImageChannel &rhs)
{ 
    if(this->shape() == rhs.shape()) {
        float *in_data = rhs.data();
        for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
            try {
                this->pixel.data()[n] /= in_data[n];
            }
            catch(exception &e) {
                cout << e.what() << endl;
                this->pixel.data()[n] = numeric_limits<float>::max();
            }
        }
        return *this;
    }
    else throw OpenLF_Exception("Shape mismatch");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
bool operator==(OpenLF::image::ImageChannel const& lhs, OpenLF::image::ImageChannel const& rhs)
{ 
    return (lhs.shape() == rhs.shape());
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
bool operator!=(OpenLF::image::ImageChannel const& lhs, OpenLF::image::ImageChannel const& rhs)
{ 
    return (lhs.shape() != rhs.shape());
}
