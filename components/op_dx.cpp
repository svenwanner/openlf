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

#include <vigra/convolution.hxx>
#include <vigra/multi_convolution.hxx>

#include <opencv2/imgproc/imgproc.hpp>

#include "openlf/operator_macro.hpp"


using namespace cv;
using namespace vigra;

#define OPENLF_OP_CONSTRUCT_PARAMS

OPENLF_VIGRA_OP_START_OUTTYPE(OP_dx, 1, 1, 3, 3, float)
        
for (int i=0; i < in[0].shape()[2]; ++i) {
  vigra::MultiArrayView<2,T> ch_in = in[0].bindAt(2, i);
  vigra::MultiArrayView<2,float> ch_out = out[0].bindAt(2, i);
  
  //FIXME check steps!
  for(int j=0;j<ch_in.shape(1);j++) {
    T *in_ptr = &ch_in(0, j);
    float *out_ptr = &ch_out(0, j);
    
    for(int i=1;i<ch_in.shape(0)-1;i++)
      out_ptr[i] = (float)in_ptr[i-1]-(float)in_ptr[i+1];
  }
}
    
OPENLF_OP_END

#undef OPENLF_OP_CONSTRUCT_PARAMS
