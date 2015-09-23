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

#ifndef _OPENLF_OP_MACRO_H
#define _OPENLF_OP_MACRO_H

#include "clif/clif_vigra.hpp"
#include "clif/flexmav.hpp"

#define OPENLF_OP_CLASS_HEADER(NAME) \
    class NAME : public DspComponent { \
        public: \
            NAME(); \
        protected: \
          virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs); \
          virtual bool ParameterUpdating_ (int i, DspParameter const &p); \
        private: \
          clif::FlexMAV<2> _output_image; \
    };
    

#define OPENLF_OP_START(NAME) \
  namespace openlf { namespace components { \
\
  using namespace vigra;\
  using namespace clif;\
\
  namespace { \
\
  template<typename T> class NAME##dispatcher {\
  public:\
    void operator()(NAME *op, FlexMAV<2> *in_mav, FlexMAV<2> *out_mav, DspSignalBus *inputs, DspSignalBus *outputs)\
    {\
      MultiArrayView<2,T> *in = in_mav->template get<T>();\
      MultiArrayView<2,T> *out = out_mav->template get<T>();
      
      
#define OPENLF_OP_END(NAME) \
}\
};\
\
}\
\
NAME::NAME()\
{\
  AddInput_("input");\
  AddOutput_("output");\
  OPENLF_OP_CONSTRUCT_PARAMS \
}\
\
void NAME::Process_(DspSignalBus& inputs, DspSignalBus& outputs)\
{\
  bool stat;\
  FlexMAV<2> *in;\
  \
  stat = inputs.GetValue(0, in);\
  assert(stat);\
  \
  FlexMAV<2> *out_ptr = &_output_image;\
  \
  _output_image.create(in->shape(), in->type());\
\
  in->call<NAME##dispatcher>(this, in, out_ptr, &inputs, &outputs);\
  \
  stat = outputs.SetValue(0, out_ptr);\
}\
bool NAME::ParameterUpdating_ (int i, DspParameter const &p) \
{ \
  SetParameter_(i, p); \
  return true;\
}\
}}

#endif
