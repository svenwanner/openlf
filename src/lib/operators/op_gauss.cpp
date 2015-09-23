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

#include <vigra/convolution.hxx>
#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>

#include "op_gauss.hpp"



#include "clif/flexmav.hpp"



namespace openlf { namespace components {

using namespace vigra;
using namespace clif;

//anonymous namespace to hide dispatcher
namespace {

template<typename T> class op_gauss_dispatcher {
public:
  void operator()(FlexMAV<2> *in_mav, FlexMAV<2> *out_mav)
  {
    MultiArrayView<2,T> *in = in_mav->template get<T>();
    MultiArrayView<2,T> *out = out_mav->template get<T>();
    
    gaussianSmoothing(*in, *out, 5.0, 5.0);
  }
};

}

OP_Gauss::OP_Gauss()
{
  AddInput_("input");
  AddOutput_("output");
  
  printf("gauss constructor!\n");
}

void OP_Gauss::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  bool stat;
  FlexMAV<2> *in;
  
  stat = inputs.GetValue(0, in);
  assert(stat);
  assert(stat);
  
  FlexMAV<2> *out_ptr = &_output_image;
  
  _output_image.create(in->shape(), in->type());
  
  printf("gauss process %p!\n", in, &_output_image);

  in->call<op_gauss_dispatcher>(in, out_ptr);
  
  stat = outputs.SetValue(0, out_ptr);
}

}} //namespace openlf::components