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

#ifndef _OPENLF_OP_MACRO_H
#define _OPENLF_OP_MACRO_H

#include <vigra/multi_array.hxx>

#include "dspatch/DspPlugin.h"
#include "dspatch/DspComponent.h"

#include "clif/dataset.hpp"

#define STRINGIFY(STR) #STR





#define OPENLF_OP_START_OUTTYPE(NAME,_INCOUNT,_OUTCOUNT, OUTCTYPE) \
namespace { \
  const int INCOUNT = _INCOUNT; \
  const int OUTCOUNT = _OUTCOUNT; \
  \
  template<typename T> class NAME##dispatcher; \
} \
class NAME : public DspComponent { \
    public: \
        NAME(); \
        DSPCOMPONENT_TRIVIAL_CLONE(NAME); \
    protected: \
      virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs); \
      virtual bool ParameterUpdating_ (int i, DspParameter const &p); \
    private: \
      clif::Mat _output_image[OUTCOUNT]; \
}; \
\
  using namespace vigra;\
  using namespace clif;\
  NAME::NAME()\
{\
  setTypeName_(STRINGIFY(NAME)); \
  char buf[64]; \
  for(int i=0;i<INCOUNT;i++) { \
    sprintf(buf, "input_%d", i); \
    AddInput_(buf); \
  }\
  for(int i=0;i<OUTCOUNT;i++) { \
    sprintf(buf, "output_%d", i); \
    AddOutput_(buf); \
  }\
  OPENLF_OP_CONSTRUCT_PARAMS \
}\
\
namespace { \
template <class FROM> struct _is_valid : public std::integral_constant<bool, std::is_convertible<FROM,float>::value> {}; \
} \
\
void NAME::Process_(DspSignalBus& inputs, DspSignalBus& outputs)\
{\
  bool stat;\
  clif::Mat *in[INCOUNT];\
\
  for(int i=0;i<INCOUNT;i++) { \
    errorCond(inputs.GetValue(i, in[i]), STRINGIFY(NAME) ": input not found - possible type mismatch?"); RETURN_ON_ERROR \
    errorCond(in[i]->type() > BaseType::INVALID, STRINGIFY(NAME) ": input %d no valid type!", i); RETURN_ON_ERROR \
  }\
\
  clif::Mat *out_ptr[OUTCOUNT];\
  for(int i=0;i<OUTCOUNT;i++) { \
    out_ptr[i] = &_output_image[i]; \
  } \
\
  if (!configOnly()) \
    in[0]->callIf<NAME##dispatcher,_is_valid>(this, in, out_ptr, &inputs, &outputs);\
\
  for(int i=0;i<OUTCOUNT;i++) { \
    stat = outputs.SetValue(i, out_ptr[i]);\
    if (!stat) { \
      printf(STRINGIFY(NAME) ": output %d set failed\n", i); \
      abort(); \
    }\
    errorCond(_output_image[i].type() > BaseType::INVALID, STRINGIFY(NAME) ": output %d no valid type!", i); \
  }\
}\
bool NAME::ParameterUpdating_ (int i, DspParameter const &p)\
{\
  SetParameter_(i, p);\
  return true;\
} \
EXPORT_DSPCOMPONENT(NAME)\
\
  namespace { \
\
  template<typename T> class NAME##dispatcher {\
  public:\
    void operator()(NAME *op, clif::Mat **in_mat, clif::Mat **out_mat, DspSignalBus *inputs, DspSignalBus *outputs)\
    { \
      const BaseType BASETYPE = toBaseType<OUTCTYPE>(); \
      for(int i=0;i<OUTCOUNT;i++) \
        out_mat[i]->create(BASETYPE, *(Idx*)in_mat[0]);




      
#define OPENLF_OP_START(NAME,_INCOUNT,_OUTCOUNT) \
  OPENLF_OP_START_OUTTYPE(NAME,_INCOUNT,_OUTCOUNT,T)

      
#define OPENLF_VIGRA_OP_START_OUTTYPE(_NAME, _INCOUNT,_OUTCOUNT,INDIM,OUTDIM,OUTTYPE) \
OPENLF_OP_START_OUTTYPE(_NAME, _INCOUNT,_OUTCOUNT, OUTTYPE) \
      MultiArrayView<INDIM, T> in[INCOUNT]; \
      MultiArrayView<OUTDIM, OUTTYPE> out[OUTCOUNT]; \
      for(int i=0;i<INCOUNT;i++) \
        in[i] = vigraMAV<INDIM,T>(*in_mat[i]);  \
      for(int i=0;i<OUTCOUNT;i++) \
        out[i] = vigraMAV<OUTDIM,OUTTYPE>(*out_mat[i]); 
    
      
#define OPENLF_VIGRA_OP_START(_NAME, _INCOUNT,_OUTCOUNT,INDIM,OUTDIM) \
  OPENLF_VIGRA_OP_START_OUTTYPE(_NAME, _INCOUNT,_OUTCOUNT,INDIM,OUTDIM,T)
      
      
#define OPENLF_OP_END \
}\
};\
\
}\


#endif