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

#include "vigra/convolution.hxx"
#include "vigra/multi_convolution.hxx"

#include "openlf/operator_macro.hpp"

#define OPENLF_OP_CONSTRUCT_PARAMS

OPENLF_OLDAPI_OP_START_T(OP_Normalize, 1, 1, 3, 3, float)

         
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::lowest();
    for (int i=0; i<in[0]->size(); ++i) {
        if (max < in[0]->data()[i])
            max = in[0]->data()[i];
        if (min > in[0]->data()[i])
            min = in[0]->data()[i];
    }
    float tmp = 0;
    for (int i=0; i < in[0]->size(); ++i) {
        tmp = (float)in[0]->data()[i];
        //std::cout << "map " << tmp << " to ";
        tmp -= min;
        tmp /= (max-min);
        out[0]->data()[i] = tmp;
        //std::cout << out_im.data()[i] << std::endl;
    }
    //std::cout << "mapping range from (" << min << "," << max << ") to (0,1)" << std::endl;
    
    
OPENLF_OLDAPI_OP_END_T(OP_Normalize, 1, 1, 3, 3, BaseType::FLOAT)

#undef OPENLF_OP_CONSTRUCT_PARAMS
