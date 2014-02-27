/**
 *
 * \brief ...
 *
 * ...
 *
 * \note ...
 *
 * \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 * 
 */

#ifndef IMGSHOW_HPP
#define	IMGSHOW_HPP

#include "global.hpp"
#include "image/image.hpp"

namespace OpenLF {
    
    void linearRangeMapping(vigra::MultiArray<2, float>&,vigra::MultiArray<2, vigra::UInt8>&);
    void linearRangeMapping(vigra::MultiArray<2, double>&,vigra::MultiArray<2, vigra::UInt8>&);
    
    void show(vigra::MultiArray<2, float>&,const char*);
    void show(vigra::MultiArray<2, vigra::UInt8>&,const char*);
    void show(vigra::MultiArray<2, double>&,const char*);
    void show(cv::Mat,const char*);
    //void imshow(OpenLF::Image&,const char*);
    //void imshow(OpenLF::Image&,int,const char*);
}

#endif	/* IMGSHOW_HPP */

