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

//#include "clif/clif_vigra.hpp"
//#include "clif/flexmav.hpp"

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

#define COMMA ,

#define M_REPEAT_1(X, N) X
#define M_REPEAT_2(X, N) X X
#define M_REPEAT_3(X, N) X X X
#define M_REPEAT_4(X, N) X X X X
#define M_REPEAT_5(X, N) X M_REPEAT_4(X)
#define M_REPEAT_6(X, N) M_REPEAT_3(X) M_REPEAT_3(X)

#define M_REPEAT2_1(X, Y, N) X Y 
#define M_REPEAT2_2(X, Y, N) X Y X Y
#define M_REPEAT2_3(X, Y, N) X Y X Y X Y 
#define M_REPEAT2_4(X, Y, N) X Y X Y X Y X Y 
#define M_REPEAT2_5(X, Y, N) X Y  M_REPEAT2_4(X, Y)
#define M_REPEAT2_6(X, Y, N) M_REPEAT2_3(X, Y) M_REPEAT2_3(X, Y)

#define M_EXPAND(...) __VA_ARGS__

#define M_REPEAT__(N, X) M_EXPAND(M_REPEAT_ ## N)(X, N)
#define M_REPEAT_(N, X) M_REPEAT__(N, X)
#define M_REPEAT(N, X) M_REPEAT_(M_EXPAND(N), X)

#define M_REPEAT2__(N, X, Y) M_EXPAND(M_REPEAT2_ ## N)(X, Y, N)
#define M_REPEAT2_(N, X, Y) M_REPEAT2__(N, X, Y)
#define M_REPEAT2(N, X, Y) M_REPEAT2_(M_EXPAND(N), X, Y)
    
#define OPENLF_OP_XY_CLASS_HEADER(NAME,INCOUNT,OUTCOUNT) \
class NAME : public DspComponent { \
    public: \
        NAME(); \
    protected: \
      virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs); \
      virtual bool ParameterUpdating_ (int i, DspParameter const &p); \
    private: \
      clif::FlexMAV<2> _output_image[OUTCOUNT]; \
};

#define OPENLF_OP_XY_START(NAME,INCOUNT,OUTCOUNT) \
  namespace openlf { namespace components { \
\
  using namespace vigra;\
  using namespace clif;\
\
  namespace { \
\
  template<typename T> class NAME##dispatcher {\
  public:\
    void operator()(NAME *op, FlexMAV<2> **in_mav, FlexMAV<2> **out_mav, DspSignalBus *inputs, DspSignalBus *outputs)\
    {\
      MultiArrayView<2, T> *in[INCOUNT]; \
      MultiArrayView<2, T> *out[OUTCOUNT]; \
      for(int i=0;i<INCOUNT;i++) \
        in[i] = in_mav[i]->template get<T>();  \
      for(int i=0;i<OUTCOUNT;i++) \
        out[i] = out_mav[i]->template get<T>(); 
      
      
#define OPENLF_OP_XY_END(NAME,INCOUNT,OUTCOUNT) \
}\
};\
\
}\
\
NAME::NAME()\
{\
  M_REPEAT(INCOUNT, AddInput_("input ## N");) \
  M_REPEAT(INCOUNT, AddOutput_("output ## N");) \
  OPENLF_OP_CONSTRUCT_PARAMS \
}\
\
void NAME::Process_(DspSignalBus& inputs, DspSignalBus& outputs)\
{\
  bool stat;\
  FlexMAV<2> *in[INCOUNT];\
  \
  for(int i=0;i<INCOUNT;i++) { \
    stat = inputs.GetValue(i, in[i]); \
    assert(stat); \
  } \
  \
  FlexMAV<2> *out_ptr[OUTCOUNT];\
  for(int i=0;i<OUTCOUNT;i++) { \
    out_ptr[i] = &_output_image[i]; \
    _output_image[i].create(in[0]->shape(), in[0]->type());\
  } \
\
  in[0]->call<NAME##dispatcher>(this, in, out_ptr, &inputs, &outputs);\
  \
  for(int i=0;i<OUTCOUNT;i++) { \
    stat = outputs.SetValue(i, out_ptr[i]);\
    assert(stat); \
  } \
}\
bool NAME::ParameterUpdating_ (int i, DspParameter const &p) \
{ \
  SetParameter_(i, p); \
  return true;\
}\
}}


#endif