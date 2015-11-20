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

#include "clif/flexmav.hpp"
#include "dspatch/DspPlugin.h"
#include "dspatch/DspComponent.h"

#define STRINGIFY(STR) #STR

/*
#define OPENLF_OP_SINGLE2D_CLASS_HEADER(NAME) \
    class NAME : public DspComponent { \
        public: \
            NAME(); \
            DSPCOMPONENT_TRIVIAL_CLONE(NAME); \
        protected: \
          virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs); \
          virtual bool ParameterUpdating_ (int i, DspParameter const &p); \
        private: \
          clif::FlexMAV<2> _output_image; \
    };
    

#define OPENLF_OP_SINGLE2D_START(NAME) \
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
      
      
#define OPENLF_OP_SINGLE2D_END(NAME) \
}\
};\
\
}\
\
NAME::NAME()\
{\
  setTypeName_(#NAME); \
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
  errorCond(inputs.GetValue(0, in), #NAME ":missing input 0"); RETURN_ON_ERROR \
  \
  FlexMAV<2> *out_ptr = &_output_image;\
  \
  _output_image.create(in->shape(), in->type());\
\
  if (!configOnly()) \
    in->call<NAME##dispatcher>(this, in, out_ptr, &inputs, &outputs);\
  \
  stat = outputs.SetValue(0, out_ptr);\
}\
bool NAME::ParameterUpdating_ (int i, DspParameter const &p) \
{ \
  SetParameter_(i, p); \
  return true;\
}\
EXPORT_DSPCOMPONENT(NAME)*/







#define OPENLF_OLDAPI_OP_CLASS_HEADER(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM) \
class NAME : public DspComponent { \
    public: \
        NAME(); \
        DSPCOMPONENT_TRIVIAL_CLONE(NAME); \
    protected: \
      virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs); \
      virtual bool ParameterUpdating_ (int i, DspParameter const &p); \
    private: \
      clif::FlexMAV<OUTDIM> _output_image[OUTCOUNT]; \
};




#define OPENLF_OP_START_T(NAME,_INCOUNT,_OUTCOUNT, OUTCTYPE) \
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
  Mat *in[INCOUNT];\
\
  for(int i=0;i<INCOUNT;i++) { \
    errorCond(inputs.GetValue(i, in[i]), STRINGIFY(NAME) ": input not found - possible type mismatch?"); RETURN_ON_ERROR \
    errorCond(in[i]->type() > BaseType::INVALID, STRINGIFY(NAME) ": input %d no valid type!", i); RETURN_ON_ERROR \
  }\
\
  Mat *out_ptr[OUTCOUNT];\
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
    void operator()(NAME *op, Mat **in_mat, Mat **out_mat, DspSignalBus *inputs, DspSignalBus *outputs)\
    { \
      const BaseType BASETYPE = toBaseType<OUTCTYPE>(); \
      for(int i=0;i<OUTCOUNT;i++) \
        out_mat[i]->create(BASETYPE, *(Idx*)in_mat[0]);


      
#define OPENLF_OP_START(NAME,_INCOUNT,_OUTCOUNT) \
  OPENLF_OP_START_T(NAME,_INCOUNT,_OUTCOUNT,T)

      

#define OPENLF_VIGRA_OP_START_OUTTYPE(_NAME, _INCOUNT,_OUTCOUNT,INDIM,OUTDIM,OUTTYPE) \
OPENLF_OP_START(_NAME, _INCOUNT,_OUTCOUNT) \
      MultiArrayView<INDIM, OUTTYPE> in[INCOUNT]; \
      MultiArrayView<OUTDIM, OUTTYPE> out[OUTCOUNT]; \
      for(int i=0;i<INCOUNT;i++) \
        in[i] = vigraMAV<INDIM,OUTTYPE>(*in_mat[i]);  \
      for(int i=0;i<OUTCOUNT;i++) \
        out[i] = vigraMAV<OUTDIM,OUTTYPE>(*out_mat[i]); 
    
#define OPENLF_VIGRA_OP_START(_NAME, _INCOUNT,_OUTCOUNT,INDIM,OUTDIM) \
  OPENLF_VIGRA_OP_START_OUTTYPE(_NAME, _INCOUNT,_OUTCOUNT,INDIM,OUTDIM,T)
      
      
      
      
      
      
#define OPENLF_OLDAPI_OP_START(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM) \
class NAME : public DspComponent { \
    public: \
        NAME(); \
        DSPCOMPONENT_TRIVIAL_CLONE(NAME); \
    protected: \
      virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs); \
      virtual bool ParameterUpdating_ (int i, DspParameter const &p); \
    private: \
      clif::FlexMAV<OUTDIM> _output_image[OUTCOUNT]; \
}; \
\
  using namespace vigra;\
  using namespace clif;\
\
  namespace { \
\
  template<typename T> class NAME##dispatcher {\
  public:\
    void operator()(NAME *op, FlexMAV<INDIM> **in_mav, FlexMAV<OUTDIM> **out_mav, DspSignalBus *inputs, DspSignalBus *outputs)\
    {\
      MultiArrayView<INDIM, T> *in[INCOUNT]; \
      MultiArrayView<OUTDIM, T> *out[OUTCOUNT]; \
      for(int i=0;i<INCOUNT;i++) \
        in[i] = in_mav[i]->template get<T>();  \
      for(int i=0;i<OUTCOUNT;i++) \
        out[i] = out_mav[i]->template get<T>(); 


      
      
      
      
      
      
      
      
#define OPENLF_OLDAPI_OP_IGNORE_VECTOR_TYPES(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM) \
  namespace { \
\
  template<typename T> class NAME##dispatcher<std::vector<T>>{\
  public:\
    void operator()(NAME *op, FlexMAV<INDIM> **in_mav, FlexMAV<OUTDIM> **out_mav, DspSignalBus *inputs, DspSignalBus *outputs)\
    {\
      printf("vector types not supported by this component\n");\
      abort(); \
    }\
  };\
}

#define OPENLF_OLDAPI_OP_IGNORE_STRING(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM) \
  namespace { \
\
  template<> class NAME##dispatcher<char>{\
  public:\
    void operator()(NAME *op, FlexMAV<INDIM> **in_mav, FlexMAV<OUTDIM> **out_mav, DspSignalBus *inputs, DspSignalBus *outputs)\
    {\
      printf("char type not supported by this component\n");\
      abort(); \
    }\
  };\
}
#define OPENLF_OLDAPI_OP_IGNORE_T(NAME,T,INCOUNT,OUTCOUNT,INDIM,OUTDIM) \
  namespace { \
\
  template<> class NAME##dispatcher<T>{\
  public:\
    void operator()(NAME *op, FlexMAV<INDIM> **in_mav, FlexMAV<OUTDIM> **out_mav, DspSignalBus *inputs, DspSignalBus *outputs)\
    {\
      printf("char type not supported by this component\n");\
      abort(); \
    }\
  };\
}
   

#define OPENLF_OP_END \
}\
};\
\
}\
\




      
#define OPENLF_OLDAPI_OP_END(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM) \
}\
};\
\
}\
\
NAME::NAME()\
{\
  setTypeName_(#NAME); \
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
OPENLF_OLDAPI_OP_IGNORE_VECTOR_TYPES(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM)\
OPENLF_OLDAPI_OP_IGNORE_STRING(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM)\
OPENLF_OLDAPI_OP_IGNORE_T(NAME,cv::Point2f, INCOUNT,OUTCOUNT,INDIM,OUTDIM)\
\
void NAME::Process_(DspSignalBus& inputs, DspSignalBus& outputs)\
{\
  bool stat;\
  FlexMAV<INDIM> *in[INCOUNT];\
\
  for(int i=0;i<INCOUNT;i++) { \
    errorCond(inputs.GetValue(i, in[i]), #NAME ": input not found - possible type mismatch?"); RETURN_ON_ERROR \
    errorCond(in[i]->type() > BaseType::INVALID, #NAME ": input %d no valid type!", i); RETURN_ON_ERROR \
  }\
\
  FlexMAV<OUTDIM> *out_ptr[OUTCOUNT];\
  for(int i=0;i<OUTCOUNT;i++) { \
    out_ptr[i] = &_output_image[i]; \
    _output_image[i].create(in[0]->shape(), in[0]->type());\
  } \
\
  if (!configOnly()) \
    in[0]->call<NAME##dispatcher>(this, in, out_ptr, &inputs, &outputs);\
\
  for(int i=0;i<OUTCOUNT;i++) { \
    stat = outputs.SetValue(i, out_ptr[i]);\
    if (!stat) { \
      printf(#NAME ": output %d set failed\n", i); \
      abort(); \
    }\
    errorCond(_output_image[i].type() > BaseType::INVALID, #NAME ": output %d no valid type!", i); \
  }\
}\
bool NAME::ParameterUpdating_ (int i, DspParameter const &p)\
{\
  SetParameter_(i, p);\
  return true;\
} \
EXPORT_DSPCOMPONENT(NAME)

#define OPENLF_OLDAPI_OP_START_T(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM,OUTCTYPE) \
class NAME : public DspComponent { \
    public: \
        NAME(); \
        DSPCOMPONENT_TRIVIAL_CLONE(NAME); \
    protected: \
      virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs); \
      virtual bool ParameterUpdating_ (int i, DspParameter const &p); \
    private: \
      clif::FlexMAV<OUTDIM> _output_image[OUTCOUNT]; \
}; \
\
  using namespace vigra;\
  using namespace clif;\
\
  namespace { \
\
  template<typename T> class NAME##dispatcher {\
  public:\
    void operator()(NAME *op, FlexMAV<INDIM> **in_mav, FlexMAV<OUTDIM> **out_mav, DspSignalBus *inputs, DspSignalBus *outputs)\
    {\
      MultiArrayView<INDIM, T> *in[INCOUNT]; \
      MultiArrayView<OUTDIM, OUTCTYPE> *out[OUTCOUNT]; \
      for(int i=0;i<INCOUNT;i++) \
        in[i] = in_mav[i]->template get<T>();  \
      for(int i=0;i<OUTCOUNT;i++) \
        out[i] = out_mav[i]->template get<OUTCTYPE>(); 
      
#define OPENLF_OLDAPI_OP_END_T(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM,OUTBASETYPE) \
}\
};\
\
}\
\
NAME::NAME()\
{\
  setTypeName_(#NAME); \
  char buf[64]; \
  for(int i=0;i<INCOUNT;i++) { \
    sprintf(buf, "input_%d", i); \
    AddInput_(buf); \
  } \
  for(int i=0;i<OUTCOUNT;i++) { \
    sprintf(buf, "output_%d", i); \
    AddOutput_(buf); \
  } \
  OPENLF_OP_CONSTRUCT_PARAMS \
}\
\
OPENLF_OLDAPI_OP_IGNORE_VECTOR_TYPES(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM)\
OPENLF_OLDAPI_OP_IGNORE_STRING(NAME,INCOUNT,OUTCOUNT,INDIM,OUTDIM)\
OPENLF_OLDAPI_OP_IGNORE_T(NAME,cv::Point2f, INCOUNT,OUTCOUNT,INDIM,OUTDIM)\
\
void NAME::Process_(DspSignalBus& inputs, DspSignalBus& outputs)\
{\
  bool stat;\
  FlexMAV<INDIM> *in[INCOUNT];\
  \
  for(int i=0;i<INCOUNT;i++) { \
    errorCond(inputs.GetValue(i, in[i]), #NAME ": input not found - possible type mismatch?"); \
    RETURN_ON_ERROR \
    errorCond(in[i]->type() > BaseType::INVALID, #NAME ": input %d no valid type!", i); \
    RETURN_ON_ERROR \
  } \
  \
  FlexMAV<OUTDIM> *out_ptr[OUTCOUNT];\
  for(int i=0;i<OUTCOUNT;i++) { \
    out_ptr[i] = &_output_image[i]; \
    _output_image[i].create(in[0]->shape(), OUTBASETYPE);\
  } \
\
  if (!configOnly()) \
    in[0]->call<NAME##dispatcher>(this, in, out_ptr, &inputs, &outputs);\
  \
  for(int i=0;i<OUTCOUNT;i++) { \
    stat = outputs.SetValue(i, out_ptr[i]);\
    if (!stat) { \
      printf(#NAME ": output %d set failed\n", i); \
      abort(); \
    } \
  } \
}\
bool NAME::ParameterUpdating_ (int i, DspParameter const &p) \
{ \
  SetParameter_(i, p); \
  return true;\
} \
EXPORT_DSPCOMPONENT(NAME)


#endif