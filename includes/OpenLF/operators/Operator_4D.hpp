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

#ifndef OPERATOR_4D_HPP
#define	OPERATOR_4D_HPP

#include "OpenLF/debug.hpp"
#include "OpenLF/global.hpp"
#include "Operator.hpp"

//------
#include "OpenLF/lightfield/io.hpp"
#include "OpenLF/image/io.hpp"
//------

namespace OpenLF {
    namespace operators {

class Operator_4D : public Operator {
public:
    Operator_4D(std::vector<std::string> inslots, std::vector<std::string> outslots) : Operator(inslots,outslots) {};
    //Operator_4D(const Operator_4D& orig);
    virtual ~Operator_4D();
    
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
#endif	/* OPERATOR_4D_HPP */

