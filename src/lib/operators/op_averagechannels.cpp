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

#include "operators.hpp"

#define NAME OP_AverageChannels
#define INCOUNT 1
#define OUTCOUNT 1
#define INDIM 3
#define OUTDIM 3
#define OPENLF_OP_CONSTRUCT_PARAMS 

OPENLF_OP_START(OP_AverageChannels, INCOUNT, OUTCOUNT, INDIM, OUTDIM)
        
    if (in[0]->shape()[2] == 1)
        *out[0] = *in[0];
    else {
        vigra::MultiArrayView<2, T> r_in;
        r_in = in[0]->bindAt(2, 0);
        vigra::MultiArrayView<2, T> g_in;
        g_in = in[0]->bindAt(2, 1);
        vigra::MultiArrayView<2, T> b_in;
        b_in = in[0]->bindAt(2, 2);

        for (int i=0; i<in[0]->shape()[0]*in[0]->shape()[1]; i++)
            out[0]->data()[i] = (r_in.data()[i]+g_in.data()[i]+b_in.data()[i])/3.0f;
    }

};

}

NAME::NAME()/*
{
  char buf[64]; 
  for(int i=0;i<INCOUNT;i++) { 
    sprintf(buf, "input_%d", i); 
    AddInput_(buf); 
  } 
  for(int i=0;i<OUTCOUNT;i++) { 
    sprintf(buf, "output_%d", i); 
    AddOutput_(buf); 
  } 
  OPENLF_OP_CONSTRUCT_PARAMS 
}

void NAME::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  bool stat;
  FlexMAV<INDIM> *in[INCOUNT];
  
  for(int i=0;i<INCOUNT;i++) { 
    stat = inputs.GetValue(i, in[i]); 
    if (!stat) { 
      printf("OP_AverageChannels : input %d not found - possible type mismatch?", i); 
      abort(); 
    } 
  } 
  
  FlexMAV<OUTDIM> *out_ptr[OUTCOUNT];
  for(int i=0;i<OUTCOUNT;i++) { 
    out_ptr[i] = &_output_image[i]; 
    _output_image[i].create(Shape3(in[0]->shape()[0], in[0]->shape()[1], 1), in[0]->type());
  } 

  in[0]->call<OP_AverageChannelsdispatcher>(this, in, out_ptr, &inputs, &outputs);
  
  for(int i=0;i<OUTCOUNT;i++) { 
    stat = outputs.SetValue(i, out_ptr[i]);
    if (!stat) { 
      printf("OP_AverageChannels: output %d set failed", i); 
      abort(); 
    } 
  } 
}
bool NAME::ParameterUpdating_ (int i, DspParameter const &p) 
{ 
  SetParameter_(i, p); 
  return true;
}
}}*/
     
