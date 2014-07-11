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

#ifndef OPERATOR_EPI_HPP
#define	OPERATOR_EPI_HPP

#include "OpenLF/debug.hpp"
#include "OpenLF/global.hpp"
#include "Operator.hpp"

typedef vigra::MultiArrayView<2, float> view_2D;

namespace OpenLF {
    namespace operators {

class Operator_EPI : public Operator {
public:
    Operator_EPI(std::vector<std::string> inslots, std::vector<std::string> outslots) : Operator(inslots,outslots) {};
    virtual ~Operator_EPI();
    
    void process();
    
protected:
    
    virtual void allocate() = 0;
    virtual void precompute() = 0;
    virtual void compute() = 0;
    virtual void postcompute() = 0;
    
    
private:
    void cleanup();

};

}}
#endif	/* OPERATOR_EPI_HPP */

