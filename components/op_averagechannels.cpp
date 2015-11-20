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

#include "clif/clif_vigra.hpp"
#include "clif/flexmav.hpp"

#include "openlf/operator_macro.hpp"

#define INCOUNT 1
#define OUTCOUNT 1
#define INDIM 3
#define OUTDIM 3

using namespace clif;
using namespace vigra;

template<class FROM> struct _is_convertible_to_float : public std::is_convertible<FROM,float> {};

class OP_AverageChannels : public DspComponent {
public:
  OP_AverageChannels();
  DSPCOMPONENT_TRIVIAL_CLONE(OP_AverageChannels);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
  virtual bool ParameterUpdating_ (int i, DspParameter const &p);
private:
  clif::Mat _output_image[OUTCOUNT]; \
};

template<typename T> class OP_AverageChannelsdispatcher {
public:
  void operator()(OP_AverageChannels *op, Mat **in_mat, Mat **out_mat, DspSignalBus *inputs, DspSignalBus *outputs)
  {
    MultiArrayView<INDIM, T> in[INCOUNT]; 
    MultiArrayView<OUTDIM, T> out[OUTCOUNT]; 
    for(int i=0;i<INCOUNT;i++) 
      in[i] = vigraMAV<INDIM, T>(in_mat[i]);  
    for(int i=0;i<OUTCOUNT;i++) {
      out_mat[i]->create(toBaseType<T>(), *(Idx*)in_mat[0]);
      out[i] = vigraMAV<OUTDIM, T>(out_mat[i]);
    }
    
    
    if (in[0].shape()[2] != 3)
      out[0] = in[0];
    else {
      vigra::MultiArrayView<2, T> r_in;
      r_in = in[0].bindAt(2, 0);
      vigra::MultiArrayView<2, T> g_in;
      g_in = in[0].bindAt(2, 1);
      vigra::MultiArrayView<2, T> b_in;
      b_in = in[0].bindAt(2, 2);
      
      for (int i=0; i<in[0].shape()[0]*in[0].shape()[1]; i++)
        out[0].data()[i] = (r_in.data()[i]+g_in.data()[i]+b_in.data()[i])/3.0f;
    }
    
  };
  
};

OP_AverageChannels::OP_AverageChannels()
{
  setTypeName_("OP_AverageChannels"); 
  char buf[64]; 
  for(int i=0;i<INCOUNT;i++) { 
    sprintf(buf, "input_%d", i); 
    AddInput_(buf); 
  } 
  for(int i=0;i<OUTCOUNT;i++) { 
    sprintf(buf, "output_%d", i); 
    AddOutput_(buf); 
  }
}

void OP_AverageChannels::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  bool stat;
  Mat *in[INCOUNT];
  
  for(int i=0;i<INCOUNT;i++) { 
    errorCond(inputs.GetValue(i, in[i]), "OP_AverageChannels : input not found - possible type mismatch?\n"); RETURN_ON_ERROR
  } 
  
  Mat *out_ptr[OUTCOUNT];
  for(int i=0;i<OUTCOUNT;i++)
    out_ptr[i] = &_output_image[i]; 
  
  if (!configOnly())
    in[0]->callIf<OP_AverageChannelsdispatcher,_is_convertible_to_float>(this, in, out_ptr, &inputs, &outputs);
  
  for(int i=0;i<OUTCOUNT;i++) { 
    stat = outputs.SetValue(i, out_ptr[i]);
    if (!stat) { 
      printf("OP_AverageChannels: output %d set failed\n", i); 
      abort(); 
    } 
  } 
}
bool OP_AverageChannels::ParameterUpdating_ (int i, DspParameter const &p) 
{ 
  SetParameter_(i, p); 
  return true;
}

EXPORT_DSPCOMPONENT(OP_AverageChannels)
