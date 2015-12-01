#include "clif/dataset.hpp"
#include "openlf/types.hpp"
#include "dspatch/DspPlugin.h"

#include <opencv2/highgui/highgui.hpp>

using namespace clif;
using namespace openlf;

class OpenLF_Tutorial : public DspComponent {
public:
  OpenLF_Tutorial();
  DSPCOMPONENT_TRIVIAL_CLONE(OpenLF_Tutorial);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  LF _out;
  Dataset _out_set;
};

OpenLF_Tutorial::OpenLF_Tutorial()
{
  setTypeName_("openlf_tutorial");
  AddInput_("input");
  AddOutput_("output");
  AddParameter_("img_filename", DspParameter(DspParameter::ParamType::String));
}

void OpenLF_Tutorial::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  cv::Mat img;
  const std::string *filename;
  
  errorCond(inputs.GetValue(0, in), "missing input"); RETURN_ON_ERROR
  
  filename = GetParameter(0)->GetString();
  errorCond(filename, "missing filename"); RETURN_ON_ERROR

  _out.data = &_out_set;
  _out_set.reset();
  _out.path = "tutorial_data";
  _out.data->memory_link(in->data);
  outputs.SetValue(0, &_out);
    
  if (!configOnly()) {
    Datastore *store = _out.data->addStore("tutorial_data", 2);
    img = cv::imread(filename->c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    store->write(img);
  }
  
  outputs.SetValue(0, &_out);
}

EXPORT_DSPCOMPONENT(OpenLF_Tutorial)
