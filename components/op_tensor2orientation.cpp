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
#include "vigra/multi_math.hxx"
#include <vigra/matrix.hxx>
#include "openlf/operator_macro.hpp"

#define OPENLF_OP_CONSTRUCT_PARAMS \
    AddParameter_("min_coherence", DspParameter(DspParameter::ParamType::Float, 0.8f)); \
    AddParameter_("input_disparity", DspParameter(DspParameter::ParamType::Float, 0.0f));

OPENLF_VIGRA_OP_START(OP_Tensor2Orientation, 3, 2, 3, 3)

  float threshold = *op->GetParameter(0)->GetFloat();
  
  float add = *op->GetParameter(1)->GetFloat();

  /*for (int i=0; i < in[0].shape()[0]*in[0].shape()[1]; ++i) {
    
    // orientation
    out[0].data()[i] = std::tan(std::atan2(2*in[1].data()[i], in[2].data()[i]-in[0].data()[i] + 1e-25) / 2.0);
    
    // coherence
    float up = std::sqrt(std::pow(in[2].data()[i] - in[0].data()[i], 2) + 4 * std::pow(in[1].data()[i], 2));
    float down = in[0].data()[i] + in[2].data()[i] + 1e-25;
    out[1].data()[i] = up / down;
    
    // threshold orientation and check invalid coherence
    if (out[0].data()[i] > 1 || out[0].data()[i] < -1 || out[1].data()[i] < threshold) {
      out[0].data()[i] = -1;
      out[1].data()[i] = 0;
    }
    else
      out[0].data()[i] += add;
  }*/

  threshold *= threshold;
  
  float x,y,c_nom,c_denom,coherence,yx;
  
  //assume continuous array
  T *in0, *in1, *in2;
  float *out0, *out1;
  
  in0 = in[0].data();
  in1 = in[1].data();
  in2 = in[2].data();
  out0 = (float*)out[0].data();
  out1 = (float*)out[1].data();
  
  int total = in[0].shape()[0]*in[0].shape()[1];

  for (int i=0; i < total; ++i) {
    y = 2*in1[i];
    x = in2[i]-in0[i];
    
    float xyd2 = in2[i] - in0[i];
    xyd2 *= xyd2;
    c_nom = xyd2 + 4 * in1[i]*in1[i];
    c_denom = (in0[i] + in2[i]);
    c_denom *= c_denom;
    c_denom += FLT_MIN;;
    coherence = c_nom / c_denom;
    
    if (x <= 0) {
      out0[i] = std::numeric_limits<float>::quiet_NaN();
      out1[i] = -1;
    }
    else {
      yx = y/x;
    
      if (x > 0.0) {
        if (coherence < threshold) {
            out0[i] = std::numeric_limits<float>::quiet_NaN();
            out1[i] = -1;
        }
        else {
          out0[i] = add + (sqrt(yx*yx+1)-1)/yx;
          out1[i] = 1.0;//coherence;
        }
      }
      else {
        out0[i] = std::numeric_limits<float>::quiet_NaN();
        out1[i] = -1;
      }
    }
  }

OPENLF_OP_END

#undef OPENLF_OP_CONSTRUCT_PARAMS
