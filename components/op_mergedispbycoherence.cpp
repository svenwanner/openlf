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
  AddParameter_("copy", DspParameter(DspParameter::ParamType::Bool, true)); \
  AddParameter_("input_disparity", DspParameter(DspParameter::ParamType::Float, 0.0f));
    
OPENLF_VIGRA_OP_START(OP_MergeDispByCoherence, 2, 2, 3, 3)

  /*T *in0 = (T*)in_mat[0]->data();
  T *in1 = (T*)in_mat[1]->data();
  T *out0 = (T*)out_mat[0]->data();
  T *out1 = (T*)out_mat[1]->data();
  
  int total = in_mat[0]->total();

  bool copy = *op->GetParameter(0)->GetBool();
    
  if (copy) {
    out[0] = in[0];
    out[1] = in[1];
  }
  else {
    for (int i=0; i < total; ++i) {
      if (in1[i] > out1[i]) {
        out0[i] = in0[i];
        out1[i] = in1[i];
      }
    }
  }*/
  
  bool copy = *op->GetParameter(0)->GetBool();
  float input_disparity = *op->GetParameter(1)->GetFloat();
  
  for(int ch=0;ch<(*in_mat[0])[2];ch++)
    for(int j=0;j<(*in_mat[0])[1];j++) {
      T *in0 = &(*in_mat[0]).operator()<T>(0, j, ch);
      T *in1 = &(*in_mat[1]).operator()<T>(0, j, ch);
      T *out0 = &(*out_mat[0]).operator()<T>(0, j, ch);
      T *out1 = &(*out_mat[1]).operator()<T>(0, j, ch);
      
      int offset = -input_disparity*(j-(*in_mat[0])[1]/2);
      
      int start = 0;
      int stop = (*in_mat[0])[0];
      
      if (offset > 0)
        start = offset;
      if (stop - offset > (*in_mat[0])[0])
        stop = (*in_mat[0])[0] + offset;
      int size = stop - start;
      
      if (copy) {
        for(int i=0;i<start;i++) {
          out0[i] = std::numeric_limits<float>::quiet_NaN();
          out1[i] = -1;
        }
        for(int i=start;i<start+size;i++) {
          out0[i] = in0[i-offset];
          out1[i] = in1[i-offset];
        }
        for(int i=start+size;i<stop;i++) {
          out0[i] = std::numeric_limits<float>::quiet_NaN();
          out1[i] = -1;
        }
      }
      else {
        for(int i=start;i<start+size;i++)
          if (in1[i-offset] > out1[i]) {
            out0[i] = in0[i-offset];
            out1[i] = in1[i-offset];
          }
      }
    }

OPENLF_OP_END

#undef OPENLF_OP_CONSTRUCT_PARAMS
