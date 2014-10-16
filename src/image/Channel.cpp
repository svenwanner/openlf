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

#include "OpenLF/image/Channel.hpp"



/*! 
\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel::ImageChannel() {
    print(1,"image::ImageChannel::ImageChannel() called...");
    pixel = array_2d();
    external_flag=false;
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
 * Initialize empty ImageChannel instance with shape (width,height).
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel::ImageChannel(int width, int height, float value)
{
    print(1,"image::ImageChannel::ImageChannel(width,height) called...");
    
    init(width,height,value);
    
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
 * Initialize empty ImageChannel instance with shape passed.  
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel::ImageChannel(vigra::Shape2 shape, float value)
{
    print(1,"image::ImageChannel::ImageChannel(shape) called...");
    
    init(shape, value);
    
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
OpenLF::image::ImageChannel::ImageChannel(vigra::MultiArray<2,float> &vmarr) 
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

OpenLF::image::ImageChannel::ImageChannel(vigra::MultiArrayView<2,vigra::UInt8> &vmarr) 
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
    internal_data_ptr = new vigra::MultiArray<2,float>(vigra::Shape2(orig.width(), orig.height()), orig.data());
    pixel = *internal_data_ptr;
    external_flag = false;

}

OpenLF::image::ImageChannel::~ImageChannel() 
{
    if(!internal_data_ptr==NULL) { 
    delete internal_data_ptr;
    internal_data_ptr = nullptr;
    }
}



////////////////////////////////////////////////////////////////////////////////
//////                    I N I T I A L I Z E R S 
////////////////////////////////////////////////////////////////////////////////

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(int width, int height) 
{   
    internal_data_ptr = new vigra::MultiArray<2,float>(vigra::Shape2(width, height));
    internal_data_ptr->init(0.0f);
    pixel = *internal_data_ptr;
    external_flag = false;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(int width, int height, float value) 
{   
    internal_data_ptr = new vigra::MultiArray<2,float>(vigra::Shape2(width, height));
    internal_data_ptr->init(value);
    pixel = *internal_data_ptr;
    external_flag = false;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */ 
void OpenLF::image::ImageChannel::init(vigra::Shape2 shape) 
{
    internal_data_ptr = new vigra::MultiArray<2,float>(shape); 
    internal_data_ptr->init(0.0f); 
    pixel = *internal_data_ptr;
    external_flag = false;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */ 
void OpenLF::image::ImageChannel::init(vigra::Shape2 shape, float value) 
{
    internal_data_ptr = new vigra::MultiArray<2,float>(shape); 
    internal_data_ptr->init(value); 
    pixel = *internal_data_ptr;
    external_flag = false;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(int width, int height, float* data_ptr) 
{
    pixel = array_2d(vigra::Shape2(width,height), data_ptr);
    external_flag = true;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(vigra::Shape2 shape, float* data_ptr)
{   
    pixel = array_2d(shape, data_ptr); 
    external_flag = true;
}   

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */

void OpenLF::image::ImageChannel::init(int width, int height, vigra::UInt8* data_ptr) 
{
    float *local_ptr = NULL;
    float local_array[width*height];
    local_ptr = local_array;
    for(int n=0; n < width * height; n++) {
        local_ptr[n] = (float)data_ptr[n]/255.0;
    }
    internal_data_ptr = new vigra::MultiArray<2,float>(vigra::Shape2(width, height), local_ptr);
    pixel = *internal_data_ptr;
    external_flag = false;
}   

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */

void OpenLF::image::ImageChannel::init(vigra::Shape2 shape, vigra::UInt8* data_ptr) 
{
    float *local_ptr = NULL;
    float local_array[shape[0] * shape[1]];
    local_ptr = local_array;
    for(int n=0; n < shape[0] * shape[1]; n++) {
        local_ptr[n] = (float)data_ptr[n]/255.0;
    }
    internal_data_ptr = new vigra::MultiArray<2,float>(shape, local_ptr);
    pixel = *internal_data_ptr; 
    external_flag = false;
}   



////////////////////////////////////////////////////////////////////////////////
//////                S E T / G E T   M E T H O D S  
////////////////////////////////////////////////////////////////////////////////
void OpenLF::image::ImageChannel::deepcopy(OpenLF::image::ImageChannel& channel)
{
    if(hasData())
        throw OpenLF_Exception("already has data");
    else
    {
        internal_data_ptr = new vigra::MultiArray<2,float>(vigra::Shape2(channel.width(), channel.height()), channel.data());
        pixel = *internal_data_ptr;
        external_flag = false;
    }
}
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
void OpenLF::image::ImageChannel::set(float value)
{ 
    if(!hasData())
        throw OpenLF_Exception("uninitialized channel");
    else pixel = value;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
float OpenLF::image::ImageChannel::get(int x, int y) 
{   if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    if(x>=0 && x<pixel.width() && y>=0 && y<pixel.height())
        return pixel(x,y);
    else throw OpenLF_Exception("Out of bounce");
}
 
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::image::ImageChannel::get(int x, int y, float &value) 
{
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    if(x>=0 && x<pixel.width() && y>=0 && y<pixel.height())
        value = pixel(x,y);
    else throw OpenLF_Exception("Out of bounce");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
float* OpenLF::image::ImageChannel::data() const
{   if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        print(1,"image::Channel::data() called...");
        return pixel.data();
    }
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
vigra::MultiArray<2,float>* OpenLF::image::ImageChannel::image() 
{
    print(1,"image::Channel::image() called...");
    if(!internal_data_ptr==NULL){
       return internal_data_ptr;
    }
    else if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
       internal_data_ptr = new vigra::MultiArray<2,float>(pixel.shape(), pixel.data()); 
       pixel = *internal_data_ptr; 
       return internal_data_ptr;
    } 
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
void OpenLF::image::ImageChannel::image(vigra::MultiArray<2,float> **pixel) 
{
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        print(1,"image::Channel::image(**pixel) called...");
        if(!internal_data_ptr==NULL){
            *pixel = internal_data_ptr;
        }
        else {
            internal_data_ptr = new vigra::MultiArray<2,float>(this->pixel.shape(), this->pixel.data()); 
            this->pixel = *internal_data_ptr;
            *pixel = internal_data_ptr;
        } 
    }
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
vigra::MultiArrayView<2,float> OpenLF::image::ImageChannel::viewToROI(int x, int y, int width, int height) {
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        if(x<0 || y<0 || x+width-1>=pixel.width() || y+height-1>=pixel.height())
            throw OpenLF_Exception("ImageChannel::viewToROI -> out of bounce!");
        else {
            vigra::MultiArrayView<2, float> roi_view = pixel.subarray(vigra::Shape2(x,y), vigra::Shape2(x+width,y+height));
            return roi_view;
        }
    }
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
vigra::MultiArrayView<1,float> OpenLF::image::ImageChannel::viewToRow(int fix_y)
{
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        if(fix_y>=0 && fix_y<pixel.height()) {
            return pixel.bind<1>(fix_y);
        }
        else {
            throw OpenLF_Exception("viewToRow access out of bounce!");
        }
    }
}
    

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
vigra::MultiArrayView<1,float> OpenLF::image::ImageChannel::viewToColumn(int fix_x)
{
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        if(fix_x>=0 && fix_x<pixel.width())
        {
            return pixel.bind<0>(fix_x);
        }
        else
            throw OpenLF_Exception("viewToRow access out of bounce!");
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
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        pixel = value;
        return *this;
    }
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */

OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator+(float value)
{ 
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
            this->pixel.data()[n] += value;
        }
        return *this;
    }
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator-(float value)
{ 
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
            this->pixel.data()[n] -= value;
        }
        return *this;
    }
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */

OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator+=(float value)
{ 
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
            this->pixel.data()[n] += value;
        }
        return *this;
    }
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator-=(float value)
{ 
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
            this->pixel.data()[n] -= value;
        }
        return *this;
    }
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
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
            this->pixel.data()[n] *= value;
        }
        return *this;
    }
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator/=(float value)
{   if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        if(value!=0.0f) {
            for(int n=0; n<this->pixel.width()*this->pixel.height(); n++) {
                this->pixel.data()[n] /= value;
            }
            return *this;
        } else throw std::overflow_error("Divide by zero exception");
    }
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
            catch(std::exception &e) {
                std::cout << e.what() << std::endl;
                this->pixel.data()[n] = std::numeric_limits<float>::max();
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

