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

namespace OpenLF {
namespace operators {

//Operator_4D::Operator_4D(const Operator_4D& orig) {
//}

Operator_4D::~Operator_4D() {
}

void Operator_4D::process(lightfield::Lightfield &lf)
{
    if(lf.type()!=LF_4D)
        throw OpenLF_Exception("Wrong lightfield input type exception!");

    allocate();
    precompute(lf);

    compute(lf);
    postcompute(lf);

    cleanup();
}

void Operator_4D::cleanup()
{
    tmp_memory.clear();
}

} // namespace operators
} // namespace OpenLF
