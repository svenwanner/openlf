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

#include "comp_gauss.hpp"

#include "vigra/convolution.hxx"

#include "clif/flexmav.hpp"

namespace openlf { namespace components {

using namespace vigra;
using namespace clif;

//anonymous namespace to hide dispatcher
namespace {

template<typename T> class gaussian_blur_dispatcher {
public:
  void operator()(FlexMAV<2> *in_mav, FlexMAV<2> *out_mav)
  {
    MultiArrayView<2,T> *in = in_mav->template get<T>();
    MultiArrayView<2,T> *out = out_mav->template get<T>();
    
    gaussianSmoothing(*in, *out, 3.0, 3.0);
  }
};

}

GaussianBlur::GaussianBlur()
{
  AddInput_("input");
  AddOutput_("output");
}

void GaussianBlur::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  FlexMAV<2> *in;
  FlexMAV<2> *out;
  
  inputs.GetValue(0, in);
  outputs.GetValue(0, out);
  
  in->call<gaussian_blur_dispatcher>(in, out);
}

}} //namespace openlf::components