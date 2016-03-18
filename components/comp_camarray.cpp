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
#include <vigra/impex.hxx>

#include "clif/subset3d.hpp"
#include "clif/preproc.hpp"

#include "dspatch/DspComponent.h"
#include "dspatch/DspPlugin.h"

#include "openlf.hpp"
#include "openlf/types.hpp"
#include "openlf/comp_mav.hpp"

#include "comp_camarray/cameraarray.h"

#ifdef OPENLF_WITH_OPENMP
	#include <omp.h>
#endif

#include <unordered_set>

//for printprogress
#include <cstdarg>

using namespace clif;
using namespace openlf;

//typedef unsigned int _uint;

#define DPPT DspParameter::ParamType
  
class component : public DspComponent {
public:
  component();
  DSPCOMPONENT_TRIVIAL_CLONE(component);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:  
  LF _out;
  clif::Dataset _out_set;
  camerarray::CameraArray	*cams = NULL;
  
  bool ParameterUpdating_(int index, const DspParameter& param);
  virtual ~component();
};
  
component::component()
{
  setTypeName_("COMP_camarray");
  AddInput_("input");
  AddOutput_("output");
  AddParameter_("camera_config", DspParameter(DspParameter::ParamType::String));
  AddParameter_("exposure", DspParameter(DspParameter::ParamType::Float, 1.0f));
}

//FIXME automatic/from config?
const int cam_count = 11;

void component::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  LF *out = NULL;
  std::vector<float> exposures(cam_count);
  std::vector<float> eff_exps(cam_count);
  
  errorCond(GetParameter(0) && 
            GetParameter(0)->GetString() &&
            GetParameter(0)->GetString()->size() && 
            boost::filesystem::exists(*GetParameter(0)->GetString()),
            "missing camera config");
  RETURN_ON_ERROR
  
  std::string camera_config = *GetParameter(0)->GetString();
  float exp = *GetParameter(1)->GetFloat();
  
  printf("cam config: %s\n", camera_config.c_str());
  
  errorCond(inputs.GetValue(0, in) && in, "missing input"); RETURN_ON_ERROR
  
  out = &_out;
  out->data = &_out_set;
  out->data->memory_link(in->data);
  
  outputs.SetValue(0, out);
  
  errorCond(out, "output creation failed"); RETURN_ON_ERROR
    
  if (!in->data->get("acquisition/exposure")) {
    printf("no exposure specified in input, using default\n");
    for (auto &e : exposures)
			e = 100000;
  }
  else
    in->data->get("acquisition/exposure", exposures);
  
  for (int i=0;i<cam_count;i++)
		eff_exps[i] = exposures[i]*exp;
  
printf("start init\n");  
  
  if (!cams) {
    cams = new camerarray::CameraArray(camera_config.c_str(), cam_count, 3);
    cams->PrintConnectedCameras();
    cams->SetTriggerMode(0);
    cams->Acquire();
    //cams->WaitToImage(1);
  }
  
  if (configOnly())
    return;
  
  cv::Mat* imgs = new cv::Mat[cam_count];
  
  for(int i=0;i<cam_count;i++) {
    int idx = cams->GetCamera(i)->GetCurrentImage()-1;
    if (idx < 0)
      idx = cam_count-1;
    imgs[i] = cams->GetImageFromBuffer(i, idx);
	}
  
  clif::Mat imgs_mat(CvDepth2BaseType(imgs[0].depth()), {imgs[0].size().width, imgs[0].size().height, 1, cam_count});
  for(int i=0;i<cam_count;i++)
    imgs[i].copyTo(cvMat(imgs_mat.bind(3, i).bind(2, 0)));
  
  Datastore *store = out->data->addStore("calibration/extrinsics/default/data");
  store->write(imgs_mat);
}

component::~component()
{
	if (cams)
		delete cams;
}

//FIXME remove alias for replaced sub-component!
bool component::ParameterUpdating_(int index, const DspParameter& param)
{
  //just store parameter 
  SetParameter_(index, param);
  
  return true;      
}

EXPORT_DSPCOMPONENT(component)
