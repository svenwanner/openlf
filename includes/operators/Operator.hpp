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

#include "global.hpp"
#include "lightfield/Lightfield.hpp"


namespace OpenLF {
    namespace operators {
     
    

class Operator {
public:
    Operator();
    Operator(const Operator& orig);
    virtual ~Operator();
    void clear();
    
    //! input interface to set a lightfield 
    /*!
     \param lf pointer to a light field instance
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void input(OpenLF::lightfield::Lightfield *lf);
    
    //! input interface to set additional properties
    /*!
     \param properties pointer to a Properties instance
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void input(OpenLF::lightfield::Properties *properties);

protected:
    OpenLF::lightfield::Lightfield *lf;
    OpenLF::lightfield::Properties *properties;

};

}}
#endif	/* OPERATOR_HPP */

