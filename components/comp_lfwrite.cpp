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

#include "clif/subset3d.hpp"

#include "openlf/types.hpp"

#include "dspatch/DspPlugin.h"

using namespace clif;
using namespace vigra;
using namespace openlf;

class COMP_LFWrite : public DspComponent {
public:
  COMP_LFWrite();
  DSPCOMPONENT_TRIVIAL_CLONE(COMP_LFWrite);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  virtual bool ParameterUpdating_ (int i, DspParameter const &p);
};

COMP_LFWrite::COMP_LFWrite()
{
  setTypeName_("writeCLIF");
  AddInput_("input");
  AddParameter_("filename", DspParameter(DspParameter::ParamType::String));
  AddParameter_("dataset", DspParameter(DspParameter::ParamType::String));
}

void COMP_LFWrite::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  const std::string *filename;
  const std::string *dataset_name = NULL;
  
  errorCond(inputs.GetValue(0, in), "missing input"); RETURN_ON_ERROR
  
  filename = GetParameter(0)->GetString();
  if (GetParameter(1))
    dataset_name = GetParameter(1)->GetString();
  
  errorCond(filename, "missing filename"); RETURN_ON_ERROR

  if (configOnly())
	return;
  
  ClifFile *f_out = new ClifFile;
  f_out->create(filename->c_str());
  Dataset out_set;
  out_set.link(*f_out, in->data);
  //out_set.writeAttributes();
  delete f_out;
}

bool COMP_LFWrite::ParameterUpdating_ (int i, DspParameter const &p)
{
  //we only have two parameters
  if (i >= 2)
    return false;
  
  if (p.Type() != DspParameter::ParamType::String)
    return false;
  
  SetParameter_(i, p);
  return true;
}

EXPORT_DSPCOMPONENT(COMP_LFWrite)
