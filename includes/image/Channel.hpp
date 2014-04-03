/* 
 * File:   Channel.hpp
 * Author: swanner
 *
 * Created on April 3, 2014, 11:27 AM
 */

#ifndef CHANNEL_HPP
#define	CHANNEL_HPP

#include "global.hpp"
#include "debug.hpp"

typedef vigra::MultiArray<2,float> array_2d;

namespace OpenLF {
    namespace image {
    


class Channel {
public:
    Channel();
    Channel(const Channel& orig);
    virtual ~Channel();
    
    //! allocate memory
    /*!
     \param width image width
     \param height image height
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init(int width, int height);
    
    
    //!  allocate memory
    /*!
     \param shape image shape
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init(vigra::Shape2 shape);
    
    
    //!  allocate memory
    /*!
     \param shape image shape
     \param data_ptr float pointer to data 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init(vigra::Shape2 shape, float* data_ptr);
    
    
    //!  allocate memory
    /*!
     \param width image width
     \param height image height
     \param data_ptr float pointer to data 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init(int width, int height, float* data_ptr);
    
    
    
    
    
    
    
    //! get width
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    int width() { return pixel->width(); };
    
    
    //! get height
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    int height() { return pixel->height(); };
    
    
    //! get shape
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    vigra::Shape2 shape() { return pixel->shape(); };
    
    
    
    
    
    
    
    
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
    array_2d *pixel;
};


}}
#endif	/* CHANNEL_HPP */

