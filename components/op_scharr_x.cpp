/*
* Copyright (c) 2015 Heidelberg Collaboratory for Image Processing
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
*
* Author Sven Wanner, Maximilian Diebold, Hendrik Siedelmann 
*
*/

#include <vigra/separableconvolution.hxx>
#include <vigra/multi_convolution.hxx>
#include "openlf/operator_macro.hpp"

#define OPENLF_OP_CONSTRUCT_PARAMS

OPENLF_OP_START_T(OP_ScharrX, 1, 1, 3, 3, float)
        
    Kernel1D<float> scharr;
    scharr.initExplicitly(-1,1) = -1.0/2.0, 0.0, 1.0/2.0;
    scharr.setBorderTreatment(BORDER_TREATMENT_REFLECT);
    convolveMultiArrayOneDimension(*in[0], *out[0], 1, scharr);
    scharr.initExplicitly(-1,1) = 3.0/16.0, 10.0/16.0, 3.0/16.0;
    convolveMultiArrayOneDimension(*out[0], *out[0], 0, scharr);
    
OPENLF_OP_END_T(OP_ScharrX, 1, 1, 3, 3, BaseType::FLOAT)

#undef OPENLF_OP_CONSTRUCT_PARAMS
