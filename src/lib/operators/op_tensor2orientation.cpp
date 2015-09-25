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
 * Author Sven Wanner, Maximilian Diebold, Hendrick Siedelmann 
 *
 */

#include "vigra/convolution.hxx"
#include "vigra/multi_math.hxx"
#include <vigra/matrix.hxx>
#include "operators.hpp"


#define OPENLF_OP_CONSTRUCT_PARAMS \
    AddParameter_("min_coherence", DspParameter(DspParameter::ParamType::Float, 0.8f)); \

OPENLF_OP_START(OP_Tensor2Orientation, 3, 2, 3, 3)

for (int i=0; i < in[0]->shape()[0]*in[0]->shape()[1]; ++i){
    
    // orientation
    out[0]->data()[i] = std::tan(std::atan2(2*in[1]->data()[i], in[2]->data()[i]-in[0]->data()[i] + 1e-25) / 2.0);
    
    // coherence
    float up = std::sqrt(std::pow(in[2]->data()[i] - in[0]->data()[i], 2) + 4 * std::pow(in[1]->data()[i], 2));
    float down = in[0]->data()[i] + in[2]->data()[i] + 1e-25;
    out[1]->data()[i] = up / down;
    
    // threshold orientation and check invalid coherence
    if (out[0]->data()[i] > 1 || out[0]->data()[i] < -1 || out[1]->data()[i] < *op->GetParameter(0)->GetFloat()) {
        out[0]->data()[i] = -1;
        out[1]->data()[i] = 0;
    }
}

OPENLF_OP_END(OP_Tensor2Orientation, 3, 2, 3, 3)
