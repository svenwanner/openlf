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
#include "clif/mat_helpers.hpp"
#include "openlf/types.hpp"

#include "dspatch/DspPlugin.h"

using namespace clif;
using namespace vigra;
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
  setTypeName_("calcIntensity");
  AddInput_("disparity");
  AddInput_("data");
  AddOutput_("shifted");
  AddParameter_("disparity_idx", DspParameter(DspParameter::ParamType::Int, 0));
  AddParameter_("output_group_name", DspParameter(DspParameter::ParamType::String, "default"));
}

void component::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in_disp = NULL;
  LF *in_col = NULL;
  LF *out = NULL;
  bool proc_col = true;
  
  cpath output_group = *GetParameter(1)->GetString();
  
  
  inputs.GetValue(0, in_disp);
  errorCond(in_disp && !in_disp->path.empty(), "disparity input missing!"); RETURN_ON_ERROR
  
  inputs.GetValue(1, in_col);
  errorCond(in_col && !in_col->path.empty(), "color input missing!"); RETURN_ON_ERROR
  
  Subset3d subset;
  
  errorCond(subset.create(in_disp->data, in_disp->path/"subset"), "invalid subset"); RETURN_ON_ERROR
  
  out = &_out;
  out->data = &_out_set;
  out->data->memory_link(in_disp->data);
  outputs.SetValue(0, out);
  
  out->path =  "disparity_shifted" / output_group / "data";
  
  Datastore *brdf_store = _out_set.addStore(out->path);
  
  if (configOnly())
    return;
  
  Mat_<float> disp; 
  Mat col, raw_brdf;
  Datastore *disp_store = in_disp->data->store(in_disp->path / "data");  
  disp_store->read(disp);
  
  Datastore *col_store = NULL;
  col_store = in_col->data->store(in_col->path);
  if (col_store)
    proc_col = false;
  else {
    //path points to subset - use undistortion and scale according to subset
    col_store = in_col->data->store(in_col->path / "extrinsics/data");
    proc_col = true;
  }

  //FIXME set default according to input store size! Needs to look at store ?! 
  int disp_n = max(min(disp[3]/2 + *GetParameter(0)->GetInt(), disp[3]-1), 0);
  
  std::vector<int> idx(disp_store->dims(), 0);
  
  ProcData opts;
  opts.set_store(col_store);
  if (proc_col)
    opts = subset.proc();
  opts.set_flags(opts.flags());
  col_store->read(col, opts);
  ///////////////////////////////////
 
  
  raw_brdf.create(col.type(), col);
  
  for(int y= 0; y<col[1]; y++)	
  {
    progress_((float)y/col[1]);
#pragma omp parallel for
    for(int x = 0; x<col[0]; x++ )
      
    {
      Mat brdf = raw_brdf.bind(1,y).bind(0,x);
      if (!std::isnan( disp(x,y,0,disp_n)))
	get_intensities(col, brdf,  x, y, disp(x,y,0,disp_n));
    }
  }
  
  brdf_store->write(raw_brdf);
}

EXPORT_DSPCOMPONENT(component)
