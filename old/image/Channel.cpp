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
    m_pixel = array_2d();
   m_external_flag=false;
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
OpenLF::image::ImageChannel::ImageChannel(const vigra::Shape2 shape)
{
    print(1,"image::ImageChannel::ImageChannel(shape) called...");
    
    init(shape);
    
}

/*! 
 * Initialize empty ImageChannel instance with shape passed.  
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel::ImageChannel(const vigra::Shape2 shape, float value)
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
OpenLF::image::ImageChannel::ImageChannel(int width, int height, const float* data_ptr)
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
OpenLF::image::ImageChannel::ImageChannel(const vigra::Shape2 shape, const float* data_ptr)
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
OpenLF::image::ImageChannel::ImageChannel(int width, int height, const vigra::UInt8* data_ptr)
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
OpenLF::image::ImageChannel::ImageChannel(const vigra::Shape2 shape, const vigra::UInt8* data_ptr)
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
OpenLF::image::ImageChannel::ImageChannel(const array_2d &vmarr) 
{
    init(vmarr.width(),vmarr.height(),vmarr.data());
    
    
}

/*! 
 * Initialize ImageChannel instance with by copying data from a passed vigra
 * MultiArrayView reference.
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
OpenLF::image::ImageChannel::ImageChannel(const vigra::MultiArrayView<2,vigra::UInt8> &vmarr) 
{
    init(vmarr.width(),vmarr.height(),vmarr.data());
   
}

/*! 
 * This copy constructor is a a deep copy constructor copying 
 * properties and the data as well.
 * 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
OpenLF::image::ImageChannel::ImageChannel(const ImageChannel& orig)
{   
    m_internal_data_ptr = new vigra::MultiArray<2,float>(vigra::Shape2(orig.width(), orig.height()), orig.data());
    m_pixel = *m_internal_data_ptr;
    m_external_flag = false;

}

OpenLF::image::ImageChannel::~ImageChannel() 
{
    if(m_internal_data_ptr!=nullptr) { 
    delete m_internal_data_ptr;
    m_internal_data_ptr = nullptr;
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
    m_internal_data_ptr = new vigra::MultiArray<2,float>(vigra::Shape2(width, height));
    m_internal_data_ptr->init(0.0f);
    m_pixel = *m_internal_data_ptr;
    m_external_flag = false;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(int width, int height, float value) 
{   
    m_internal_data_ptr = new vigra::MultiArray<2,float>(vigra::Shape2(width, height));
    m_internal_data_ptr->init(value);
    m_pixel = *m_internal_data_ptr;
    m_external_flag = false;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */ 
void OpenLF::image::ImageChannel::init(const vigra::Shape2 shape) 
{
    m_internal_data_ptr = new vigra::MultiArray<2,float>(shape); 
    m_internal_data_ptr->init(0.0f); 
    m_pixel = *m_internal_data_ptr;
    m_external_flag = false;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */ 
void OpenLF::image::ImageChannel::init(const vigra::Shape2 shape, float value) 
{
    m_internal_data_ptr = new vigra::MultiArray<2,float>(shape); 
    m_internal_data_ptr->init(value); 
    m_pixel = *m_internal_data_ptr;
    m_external_flag = false;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(int width, int height, const float* data_ptr) 
{
    m_pixel = array_2d(vigra::Shape2(width,height), data_ptr);
    m_external_flag = true;
}

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */
void OpenLF::image::ImageChannel::init(const vigra::Shape2 shape, const float* data_ptr)
{   
    m_pixel = array_2d(shape, data_ptr); 
    m_external_flag = true;
}   

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */

void OpenLF::image::ImageChannel::init(const int width, const int height, const vigra::UInt8* data_ptr) 
{
    float *local_ptr =  new float[width * height];
    for(int n=0; n < width * height; n++) {
        local_ptr[n] = (float)data_ptr[n]/255.0;
    }
    m_internal_data_ptr = new vigra::MultiArray<2,float>(vigra::Shape2(width, height), local_ptr);
    m_pixel = *m_internal_data_ptr;
    m_external_flag = false;
    delete [] local_ptr;
}   

/*! 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
 */

void OpenLF::image::ImageChannel::init(const vigra::Shape2 shape, const vigra::UInt8* data_ptr) 
{
    float *local_ptr = new float[shape[0] * shape[1]];
    for(int n=0; n < shape[0] * shape[1]; n++) {
        local_ptr[n] = (float)data_ptr[n]/255.0;
    }
    m_internal_data_ptr = new vigra::MultiArray<2,float>(shape, local_ptr);
    m_pixel = *m_internal_data_ptr; 
    m_external_flag = false;
    delete [] local_ptr;
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
        m_internal_data_ptr = new vigra::MultiArray<2,float>(vigra::Shape2(channel.width(), channel.height()), channel.data());
        m_pixel = *m_internal_data_ptr;
        m_external_flag = false;
    }
}
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
void OpenLF::image::ImageChannel::set(float value)
{ 
    if(!hasData())
        throw OpenLF_Exception("uninitialized channel");
    else m_pixel = value;
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/ 
float OpenLF::image::ImageChannel::get(int x, int y) const
{   if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    if(x>=0 && x<m_pixel.width() && y>=0 && y<m_pixel.height())
        return m_pixel(x,y);
    else throw OpenLF_Exception("Out of bounce");
}
 
/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void OpenLF::image::ImageChannel::get(int x, int y, float &value) const
{
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    if(x>=0 && x<m_pixel.width() && y>=0 && y<m_pixel.height())
        value = m_pixel(x,y);
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
        return m_pixel.data();
    }
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
vigra::MultiArrayView<2,float>* OpenLF::image::ImageChannel::image() 
{
    print(1,"image::Channel::image() called...");

    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
       return &m_pixel;
    } 
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
void OpenLF::image::ImageChannel::image(vigra::MultiArrayView<2,float> **pixel) 
{
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        print(1,"image::Channel::image(**pixel) called...");
        *pixel = &(this->m_pixel);
    }
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
vigra::MultiArrayView<2,float> OpenLF::image::ImageChannel::viewToROI(int x, int y, int width, int height) const {
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        if(x<0 || y<0 || x+width-1>=m_pixel.width() || y+height-1>=m_pixel.height())
            throw OpenLF_Exception("ImageChannel::viewToROI -> out of bounce!");
        else {
            vigra::MultiArrayView<2, float> roi_view = m_pixel.subarray(vigra::Shape2(x,y), vigra::Shape2(x+width,y+height));
            return roi_view;
        }
    }
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
vigra::MultiArrayView<1,float> OpenLF::image::ImageChannel::viewToRow(int fix_y) const
{
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        if(fix_y>=0 && fix_y<m_pixel.height()) {
            return m_pixel.bind<1>(fix_y);
        }
        else {
            throw OpenLF_Exception("viewToRow access out of bounce!");
        }
    }
}
    

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
vigra::MultiArrayView<1,float> OpenLF::image::ImageChannel::viewToColumn(int fix_x) const
{
    if(!hasData()) 
        throw OpenLF_Exception("uninitialized channel");
    else {
        if(fix_x>=0 && fix_x<m_pixel.width())
        {
            return m_pixel.bind<0>(fix_x);
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
        m_pixel = value;
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
        for(int n=0; n<this->m_pixel.width()*this->m_pixel.height(); n++) {
            this->m_pixel.data()[n] += value;
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
        for(int n=0; n<this->m_pixel.width()*this->m_pixel.height(); n++) {
            this->m_pixel.data()[n] -= value;
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
        for(int n=0; n<this->m_pixel.width()*this->m_pixel.height(); n++) {
            this->m_pixel.data()[n] += value;
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
        for(int n=0; n<this->m_pixel.width()*this->m_pixel.height(); n++) {
            this->m_pixel.data()[n] -= value;
        }
        return *this;
    }
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator+=(OpenLF::image::ImageChannel const&rhs)
{ 
    if(this->shape() == rhs.shape()) {
        float *in_data = rhs.data();
        for(int n=0; n<this->m_pixel.width()*this->m_pixel.height(); n++) {
            this->m_pixel.data()[n] += in_data[n];
        }
        return *this;
    }
    else throw OpenLF_Exception("Shape mismatch");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator-=(OpenLF::image::ImageChannel const&rhs)
{ 
    if(this->shape() == rhs.shape()) {
        float *in_data = rhs.data();
        for(int n=0; n<this->m_pixel.width()*this->m_pixel.height(); n++) {
            this->m_pixel.data()[n] -= in_data[n];
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
        for(int n=0; n<this->m_pixel.width()*this->m_pixel.height(); n++) {
            this->m_pixel.data()[n] *= value;
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
            for(int n=0; n<this->m_pixel.width()*this->m_pixel.height(); n++) {
                this->m_pixel.data()[n] /= value;
            }
            return *this;
        } else throw std::overflow_error("Divide by zero exception");
    }
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator*=(OpenLF::image::ImageChannel const&rhs)
{ 
    if(this->shape() == rhs.shape()) {
        float *in_data = rhs.data();
        for(int n=0; n<this->m_pixel.width()*this->m_pixel.height(); n++) {
            this->m_pixel.data()[n] *= in_data[n];
        }
        return *this;
    }
    else throw OpenLF_Exception("Shape mismatch");
}

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 */
OpenLF::image::ImageChannel & OpenLF::image::ImageChannel::operator/=(OpenLF::image::ImageChannel const&rhs)
{ 
    if(this->shape() == rhs.shape()) {
        float *in_data = rhs.data();
        for(int n=0; n<this->m_pixel.width()*this->m_pixel.height(); n++) {
            try {
                this->m_pixel.data()[n] /= in_data[n];
            }
            catch(std::exception &e) {
                std::cout << e.what() << std::endl;
                this->m_pixel.data()[n] = std::numeric_limits<float>::max();
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

