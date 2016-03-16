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
#include <opencv2/highgui/highgui.hpp>

#include "dspatch/DspPlugin.h"

using namespace clif;
using namespace vigra;
using namespace openlf;

class COMP_warpToRefView : public DspComponent {
public:
	COMP_warpToRefView();
	DSPCOMPONENT_TRIVIAL_CLONE(COMP_warpToRefView);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  virtual bool ParameterUpdating_ (int i, DspParameter const &p);
  LF _out;
  clif::Dataset _out_set;
  bool initialize = true;
};

COMP_warpToRefView::COMP_warpToRefView()
{
  setTypeName_("COMP_warpToRefView");
  AddInput_("input");
  AddOutput_("ouput");
  AddParameter_("in_group", DspParameter(DspParameter::ParamType::String, "2DTV"));
  AddParameter_("out_group", DspParameter(DspParameter::ParamType::String, "warped"));
  AddParameter_("refView", DspParameter(DspParameter::ParamType::Int, 0));
}

void COMP_warpToRefView::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
	//generate IOs
	LF *in = NULL;
	LF *out = NULL;

	// Check if inputs are connected
	errorCond(inputs.GetValue(0, in), "missing input"); RETURN_ON_ERROR

	//Link memouy from input data to output
	out = &_out;
	out->data = &_out_set;
	out->data->memory_link(in->data);

	//connect ouput to module output
	outputs.SetValue(0, out);

	//Check if output exists
	errorCond(out, "output creation failed"); RETURN_ON_ERROR

	const std::string in_dataset_name = *GetParameter(0)->GetString();
	const std::string out_dataset_name = *GetParameter(1)->GetString();


	//get location of disparity and coherence map
	cpath TV_root;
	try{
		TV_root = in->data->getSubGroup(in_dataset_name);
		std::cout << "Found TV results!" << std::endl;
	}
	catch (const std::exception& e){
		errorCond(false, "Dataset not found"); RETURN_ON_ERROR
	}
	
	//define storages used for TV
	Datastore *TV_store = in->data->getStore(TV_root / "data");
	Datastore *lf_store = in->data->getStore(TV_root / "source_LF/data");

	std::cout << "lf_store Dims : " << lf_store->extent() << std::endl;
	std::cout << "disp_store Dims : " << TV_store->extent() << std::endl;

	int refView = 0;
	//The TV should be adapted onto the center view image.
	if (initialize) {
		try{
			in->data->get(TV_root / "refView", refView);
			SetParameter_(2, DspParameter(DspParameter::ParamType::Int, refView));
		}
		catch (const std::exception& e) {
			SetParameter_(2, DspParameter(DspParameter::ParamType::Int, (lf_store->extent()[3] - 1) / 2)); initialize = false;
		}
	}
	refView = *GetParameter(2)->GetInt();																							//AddParameter_("TVposition", DspParameter(DspParameter::ParamType::Int, 0));

	if (refView >= lf_store->extent()[3] || refView < 0){
		refView = lf_store->extent()[3] / 2;
	}


	//Set some output Metadata
	std::string tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/data");
	Datastore *store = out->data->addStore(tmp_dataset_name);
	out->path = tmp_dataset_name;

	//FIXME: Reference View is always the central view modify get_intensities function in clif
	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/refView");
	out->data->setAttribute(tmp_dataset_name, refView);

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/source_LF");
	cpath tmp = TV_root;
	tmp.append("/source_LF");
	out->data->addLink(tmp_dataset_name, tmp);

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/source");
	out->data->addLink(tmp_dataset_name, TV_root);


	if (configOnly())
		return;
  
	
//Load Light Field itself
	Mat_<uint16_t> lf;
	lf_store->read(lf, ProcData(UNDISTORT));

//read TV result
	Mat_<float> TV;
	TV_store->read(TV);

//Allocate memory for warped output images
	Mat_<uint16_t> result;
	result.create(lf.type(), lf);

	for (int x = 0; x < lf_store->extent()[0]; x++) {
		for (int y = 0; y < lf_store->extent()[1]; y++) {
			for (int z = 0; z < lf_store->extent()[2]; z++) {
				for (int a = 0; a < lf_store->extent()[3]; a++) {
					result(x, y, z, a) = 0;
				}
			}
		}
	}


  for(int y= 0; y<lf[1]; y++)	
  {
    progress_((float)y/lf[1]);

	#pragma omp parallel for
    for(int x = 0; x < lf[0]; x++ )
		{
			Mat IntensityStack = result.bind(1, y).bind(0, x);
			get_intensities(lf, IntensityStack, x, y, TV(x, y, 0, 0));
		}
	}

  store->write(result);
  
}

bool COMP_warpToRefView::ParameterUpdating_(int i, DspParameter const &p)
{
  //we only have two parameters
  if (i >= 4)
    return false;
  
  if (p.Type() != DspParameter::ParamType::String && p.Type() != DspParameter::ParamType::Int)
    return false;
  
  SetParameter_(i, p);
  return true;
}

EXPORT_DSPCOMPONENT(COMP_warpToRefView)
