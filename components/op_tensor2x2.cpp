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

#include "openlf/operator_macro.hpp"

#define OPENLF_OP_CONSTRUCT_PARAMS

OPENLF_VIGRA_OP_START(OP_Tensor2x2, 2, 3, 3, 3)

  T * __restrict inx;
  T * __restrict iny;
  T * __restrict outxx;
  T * __restrict outxy;
  T * __restrict outyy;

  //assume continuous array
  assert(in[0].isUnstrided());
  assert(in[1].isUnstrided());
  assert(out[0].isUnstrided());
  assert(out[1].isUnstrided());
  assert(out[2].isUnstrided());

  inx = in[0].data();
  iny = in[1].data();
  outxx = out[0].data();
  outxy = out[1].data();
  outyy = out[2].data();

  int total = in[0].size();

  for (int i=0;i<total;++i) {
    outxx[i] = inx[i] * inx[i];
	outxy[i] = inx[i] * iny[i];
	outyy[i] = iny[i] * iny[i];
  }
    
OPENLF_OP_END

#undef OPENLF_OP_CONSTRUCT_PARAMS
