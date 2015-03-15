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

#include "OpenLF/operators/Operator_4D.hpp"

//OpenLF::operators::Operator_4D::Operator_4D(const Operator_4D& orig) {
//}

OpenLF::operators::Operator_4D::~Operator_4D() 
{
    print(1,"Operator_4D::~Operator_4D() called...");
}

void OpenLF::operators::Operator_4D::process() 
{
    if(lf!=NULL) {
        if(lf->type()==LF_4D) {
            
            allocate();
            precompute();
            
            compute();
            postcompute();
            
            cleanup();
        }
        else throw OpenLF_Exception("Wrong lightfield input type exception!");
    }   
    else throw OpenLF_Exception("missing lightfield exception!");
}

void OpenLF::operators::Operator_4D::cleanup() 
{
    tmp_memory.clear();
}
