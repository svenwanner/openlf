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
  Dataset _out_set;
};
  
component::component()
{
  setTypeName_("COMP_subset");
  AddInput_("extrinsics");
  AddOutput_("subset");
  AddParameter_("subset_name", DspParameter(DspParameter::ParamType::String, "default"));
  AddParameter_("scale", DspParameter(DspParameter::ParamType::Float, 1.0f));
}


void component::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  LF *out = NULL;
  cpath subset_name;
  
  subset_name = *GetParameter(0)->GetString();
  float scale = *GetParameter(1)->GetFloat();
  
  inputs.GetValue(0, in);
  errorCond(in && in->path.size(), "input missing!"); RETURN_ON_ERROR
  
  out = &_out;
  out->data = &_out_set;
  out->data->memory_link(in->data);
  out->path = "subset"/subset_name;
  outputs.SetValue(0, out);
  
  errorCond(scale <= 1.0 && scale >= 0.0 && scale <= 1.0 && int(log2(1.0/scale)) - log2(1.0/scale) == 0.0, "invalid scale"); RETURN_ON_ERROR
  
  ProcData opts;
  opts.set_scale(scale);
  Subset3d subset;
  
  errorCond(subset.create(in->data, in->path, opts), "subset creation failed"); RETURN_ON_ERROR
  
  subset.save(out->data, "subset"/subset_name);
}

class Plugin : public DspPlugin
{
	virtual DspComponent* Create() const { return new component; }
    virtual ~Plugin() {}
};
EXPORT_DSPPLUGIN(Plugin);
