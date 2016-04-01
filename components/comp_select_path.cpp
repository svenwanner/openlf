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
#include "clif/preproc.hpp"

#include "openlf.hpp"
#include "types.hpp"

#include "dspatch/DspComponent.h"
#include "dspatch/DspPlugin.h"

#include <locale.h>

using namespace clif;
using namespace openlf;

class component : public DspComponent {
public:
  component();
  DSPCOMPONENT_TRIVIAL_CLONE(component);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  LF _out;
};
  
component::component()
{
  setTypeName_("COMP_select_path");
  AddInput_("dataset");
  AddOutput_("output");
  AddParameter_("path", DspParameter(DspParameter::ParamType::String));
  AddParameter_("ClifTree", DspParameter(DspParameter::ParamType::Pointer, (LF*)NULL));
}


void component::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  LF *out = NULL;
  cpath path;
  
  inputs.GetValue(0, in);
  errorCond(in, "input missing!"); RETURN_ON_ERROR
  
  SetParameter(1, DspParameter(DspParameter::ParamType::Pointer,in));

  errorCond(GetParameter(0)->GetString() && GetParameter(0)->GetString()->size(), "invalid path"); RETURN_ON_ERROR
  path = *GetParameter(0)->GetString();

  
  
  out = &_out;
  out->data = in->data;
  out->path = path;
  outputs.SetValue(0, out);
}

class Plugin : public DspPlugin
{
	virtual DspComponent* Create() const { return new component; }
    virtual ~Plugin() {}
};
EXPORT_DSPPLUGIN(Plugin);
