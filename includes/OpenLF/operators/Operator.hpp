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

#ifndef OPERATOR_HPP
#define	OPERATOR_HPP


#include "OpenLF/debug.hpp"
#include "OpenLF/global.hpp"
#include "OpenLF/lightfield/Lightfield.hpp"

#include <vigra/basicgeometry.hxx>


typedef vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>> RGB_Array;

namespace OpenLF {
    namespace operators {
     
    

class Operator {
public:
    Operator(std::vector<std::string> inslots, std::vector<std::string> outslots);
    //Operator(const Operator& orig);
    virtual ~Operator();
    virtual void cleanup();
    
    //! set interface to set a lightfield 
    /*!
     \param lf pointer to a light field instance
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    virtual void set(OpenLF::lightfield::Lightfield *lf);
    
    //! set interface to set additional properties
    /*!
     \param properties pointer to a Properties instance
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void set(OpenLF::lightfield::Properties *properties);

    vigra::MultiArrayView<2, float> lf_channel(std::string channel);

    vigra::MultiArrayView<2, float> * memory_ptr(std::string channel);

    //OpenLF::image::ImageChannel * tmp_channels_ptr(std::string channel);

    virtual void process();
        
    // store temporary any computed ImageChannel 
    std::map<std::string,OpenLF::image::ImageChannel> m_tmp_memory;

    // store temporary any MultiArray result
    std::map<std::string,vigra::MultiArrayView<2, float>> m_tmp_views;

protected:
    
    virtual void allocate() = 0;
    virtual void precompute() = 0;
    virtual void compute() = 0;
    virtual void postcompute() = 0;
    
    
    OpenLF::lightfield::Lightfield *lf;
    OpenLF::lightfield::Properties *properties;
    
    
    std::vector<std::string> inslots;
    std::vector<std::string> outslots;
};

}}
#endif	/* OPERATOR_HPP */

