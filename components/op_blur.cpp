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
#include <vigra/multi_convolution.hxx>
#include <vigra/convolution.hxx>
#include "openlf/operator_macro.hpp"

#include "opencv2/imgproc/imgproc.hpp"

#define OPENLF_OP_CONSTRUCT_PARAMS \
    AddParameter_("strength", DspParameter(DspParameter::ParamType::Float, 0.0f));

template<typename T> void scaledown_x(const vigra::MultiArrayView<2, T> &in, vigra::MultiArrayView<2, T> &out)
{
  const T *in_ptr;
  T *out_ptr;
  //FIXME x must be continuous
  for(int j=0;j<in.shape(1);j++) {
    in_ptr = &in(0, j);
    out_ptr = &out(0, j);
  
    for(int i=2;i<in.shape(0)-1;i+=2)
      out_ptr[i/2] = in_ptr[i-1]*0.25+in_ptr[i]*0.5+in_ptr[i+1]*0.25;
  }
}

template<typename T> void scaledown_y(const vigra::MultiArrayView<2, T> &in, vigra::MultiArrayView<2, T> &out)
{
  const T *in_ptr1, *in_ptr2, *in_ptr3;
  T *out_ptr;
  //FIXME x must be continuous
  for(int j=2;j<in.shape(1)-1;j+=2) {
    in_ptr1 = &in(0, j-1);
    in_ptr2 = &in(0, j);
    in_ptr3 = &in(0, j+1);
    out_ptr = &out(0, j/2);
  
    for(int i=0;i<in.shape(0);i++)
      out_ptr[i] = in_ptr1[i]*0.25+in_ptr2[i]*0.5+in_ptr3[i]*0.25;
  }
}

template<typename T> void scaleup_x(const vigra::MultiArrayView<2, T> &in, vigra::MultiArrayView<2, T> &out)
{
  const T *in_ptr;
  T *out_ptr;
  //FIXME x must be continuous
  for(int j=0;j<out.shape(1);j++) {
    in_ptr = &in(0, j);
    out_ptr = &out(0, j);
  
    for(int i=0;i<out.shape(0)-1;i+=2) {
      out_ptr[i] = in_ptr[i/2];
      out_ptr[i+1] = in_ptr[i/2]*0.5+in_ptr[i/2+1]*0.5;
    }
  }
}
  
template<typename T> void scaleup_y(const vigra::MultiArrayView<2, T> &in, vigra::MultiArrayView<2, T> &out)
{
  const T *in_ptr1, *in_ptr2;
  T *out_ptr1, *out_ptr2;
  //FIXME x must be continuous
  for(int j=0;j<out.shape(1)-1;j+=2) {
    in_ptr1 = &in(0, j/2);
    in_ptr2 = &in(0, j/2+1);
    out_ptr1 = &out(0, j);
    out_ptr2 = &out(0, j+1);
  
    for(int i=0;i<out.shape(0);i++) {
      out_ptr1[i] = in_ptr1[i];
      out_ptr2[i] = in_ptr1[i]*0.5+in_ptr2[i]*0.5;
    }
  }
}
    
OPENLF_VIGRA_OP_START(OP_Blur, 1, 1, 3, 3)

  //FIXME make buffers to class members
  clif::Mat_<T> by, bx;
  by.create(Idx{in[0].shape(0), (in[0].shape(1)+1)/2});
  bx.create(Idx{(in[0].shape(0)+1)/2, (in[0].shape(1)+1)/2});
  
  MultiArrayView<2,T> bx_v = vigraMAV<2,T>(bx);
  MultiArrayView<2,T> by_v = vigraMAV<2,T>(by);

  float strength = *op->GetParameter(0)->GetFloat();
        
  for (int i=0; i < in[0].shape()[2]; ++i) {
    MultiArrayView<2,T> out_view = out[0].bindAt(2, i);
    scaledown_y(in[0].bindAt(2, i), by_v);
    scaledown_x(by_v, bx_v);
    scaleup_x(bx_v, by_v);
    scaleup_y(by_v, out_view);
  }

OPENLF_OP_END

#undef OPENLF_OP_CONSTRUCT_PARAMS
