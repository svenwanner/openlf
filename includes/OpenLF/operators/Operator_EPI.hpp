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

//#include "OpenLF/debug.hpp"
//#include "OpenLF/global.hpp"
#include "OpenLF/operators/Operator.hpp"

typedef vigra::MultiArrayView<2, float> view_2D;
typedef vigra::MultiArrayView<1, float> view_1D;
typedef vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>> RGB_Array;
typedef std::vector<view_2D> epi_vector;

namespace OpenLF {
    namespace operators {

class Operator_EPI : public Operator {
public:
    Operator_EPI(std::vector<std::string> inslots, std::vector<std::string> outslots) : Operator(inslots,outslots) {};
    virtual ~Operator_EPI();

    void load_epi_containers(std::string channel);
    view_2D refocus(int focus, view_2D epi);
    epi_vector refocus(int focus);
    void set(OpenLF::lightfield::Lightfield *lf);
    epi_vector * horizontal_epis_ptr();
    epi_vector * vertical_epis_ptr();
    view_2D get_horizontal_epi(int where);
    view_2D get_vertical_epi(int where);

private:
    epi_vector m_horizontal_epis; 
    epi_vector m_vertical_epis;
    

};

}}
#endif	/* OPERATOR_EPI_HPP */

