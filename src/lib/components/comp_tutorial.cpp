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
#include "comp_tutorial.hpp"

#include "types.hpp"

using namespace clif;

namespace openlf { namespace components {

COMP_Tutorial::COMP_Tutorial()
{
  setTypeName_("tutorial");
  AddInput_("input");
  AddOutput_("output");
  
  AddParameter_("path", DspParameter(DspParameter::ParamType::String));
  AddParameter_("message", DspParameter(DspParameter::ParamType::String));
}

void COMP_Tutorial::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  LF *out = NULL;
  const std::string *path;
  const std::string *message;
  
  //get input and produce error if not available
  errorCond(inputs.GetValue(0, in)); RETURN_ON_ERROR

  //get settings
  path = GetParameter(0)->GetString();
  message = GetParameter(1)->GetString();
  
  //check for errors
  errorCond(path); RETURN_ON_ERROR
  errorCond(message); RETURN_ON_ERROR
  
  //create output LF dataset by linking input
  out = new LF();
  out->data = new Dataset();
  out->data->memory_link(in->data);
  outputs.SetValue(0, out);
  
  //skip actual processing
  if (configOnly())
    return;
  
  //create attribute for path
  Attribute attr(*path);
  //set image
  attr.set(message->c_str());
  //append to output dataset
  out->data->append(attr);
}

bool COMP_Tutorial::ParameterUpdating_(int index, const DspParameter& param)
{  
  //just store parameter 
  return SetParameter_(index, param);
}

}} //namespace openlf::components
