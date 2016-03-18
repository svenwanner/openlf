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

#include "openlf/types.hpp"

#include "dspatch/DspPlugin.h"

using namespace clif;
using namespace openlf;

class COMP_LFRead : public DspComponent {
public:
  COMP_LFRead();
  DSPCOMPONENT_TRIVIAL_CLONE(COMP_LFRead);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  LF _out;
  clif::Dataset _out_set;
  std::string filename_old = "tmp";
  virtual bool ParameterUpdating_ (int i, DspParameter const &p);
};
  
COMP_LFRead::COMP_LFRead()
{
  setTypeName_("COMP_readCLIF");
  AddOutput_("output");
  AddParameter_("filename", DspParameter(DspParameter::ParamType::String,""));
  AddParameter_("dataset", DspParameter(DspParameter::ParamType::String));
}

void COMP_LFRead::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *out = NULL;
   const std::string *filename = NULL;
   const std::string *dataset_name = NULL;
  
  filename = GetParameter(0)->GetString();

  if (filename->compare(filename_old) == 0){
	  std::cout << "String hasnt changed!" << std::endl;
	  out = &_out;
	  out->data = &_out_set;
	  outputs.SetValue(0, out);
	  if (configOnly())
	  return;
  }
  filename_old = *filename;

  std::cout << "String changed!" << std::endl;
  if (GetParameter(1))
    dataset_name = GetParameter(1)->GetString();
  
  errorCond(filename && filename->size(), "missing file name"); RETURN_ON_ERROR
  
  out = &_out;
  out->data = &_out_set;
  _out_set.reset();
 

  if (!strcmp(cpath(*filename).extension().generic_string().c_str(), ".ini")) {
    out->data->Attributes::open(filename->c_str());
    out->path = std::string();
  }
  else {
    //FIXME error handling
    ClifFile f(*filename, H5F_ACC_RDONLY);
    
    errorCond(f.valid(), "invalid file \"%s\"", filename->c_str()); RETURN_ON_ERROR
    
    //FIXME error handling
    if (dataset_name)
      out->data->open(f, *dataset_name);
    else
      out->data->open(f, f.datasetList()[0]);
    
    //TODO dataset name
    //out->path = path();
  }
  
  outputs.SetValue(0, out);
}

bool COMP_LFRead::ParameterUpdating_ (int i, DspParameter const &p)
{
  //we only have two parameters
  if (i >= 2)
    return false;
  
  if (p.Type() != DspParameter::ParamType::String) {
    abort();
    return false;
  }
  
  SetParameter_(i, p);
  return true;
}

EXPORT_DSPCOMPONENT(COMP_LFRead)
