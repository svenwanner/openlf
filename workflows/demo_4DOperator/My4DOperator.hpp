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

#ifndef MY4DOPERATOR_HPP
#define	MY4DOPERATOR_HPP

#include <iostream>
#include "OpenLF/operators/Operator.hpp"

using namespace std;
using namespace OpenLF;

class My4DOperator : public operators::Operator {
public:
    My4DOperator(vector<string> inslots, vector<string> outslots) :
        Operator(inslots,outslots) {};
    //My4DOperator(const My4DOperator& orig);
    virtual ~My4DOperator();

    
protected:
    void allocate();
    void cleanup();
    void precompute(lightfield::Lightfield_base &lf);
    void compute(lightfield::Lightfield_base &lf);
    void postcompute(lightfield::Lightfield_base &lf);
    
private:
    
};

#endif	/* MY4DOPERATOR_HPP */

