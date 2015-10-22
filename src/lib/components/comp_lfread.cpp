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

#include "clif/clif_vigra.hpp"
#include "clif/subset3d.hpp"

#include "clif/clif_cv.hpp"

#include "comp_lfread.hpp"
#include "openlf.hpp"


using namespace clif;
using namespace vigra;

namespace openlf { namespace components {
  
COMP_LFRead::COMP_LFRead()
{
  setTypeName_("readCLIF");
  AddOutput_("output");
  AddParameter_("filename", DspParameter(DspParameter::ParamType::String));
  AddParameter_("dataset", DspParameter(DspParameter::ParamType::String));
}

void COMP_LFRead::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *out = NULL;
  const std::string *filename = NULL;
  const std::string *dataset_name = NULL;
  
  printf("tick reader!\n");
  
  filename = GetParameter(0)->GetString();
  if (GetParameter(1))
    dataset_name = GetParameter(1)->GetString();
  
  errorCond(filename && filename->size()); RETURN_ON_ERROR
  
  //FIXME reuse previous out!
  
  //FIXME move ini/clif handling decision into dataset class!
  if (!strcmp(path(*filename).extension().generic_string().c_str(), ".ini")) {
    out = new LF;
    outputs.SetValue(0, out);
    out->data = new Dataset();
    
    out->data->Attributes::open(filename->c_str(), NULL);
    out->path = std::string();
  }
  else {
    //FIXME error handling
    ClifFile f(*filename, H5F_ACC_RDONLY);
    
    errorCond(f.valid()); RETURN_ON_ERROR
    
    out = new LF;
    outputs.SetValue(0, out);
    //FIXME error handling
    if (dataset_name)
      out->data = f.openDataset(*dataset_name);
    else
      out->data = f.openDataset();
    
    assert(out->data->Datastore::valid());
    
    //cv::Mat img;
    //readCvMat(out->data, 0, img);
    
    printf("lfread out data: %p store id %d\n", out->data, out->data->H5DataSet().getId());
    Subset3d *subset = new Subset3d(out->data, 0);
    printf("%d\n", subset->EPICount()); 
    
    //TODO dataset name
    out->path = path();
  }
}

bool COMP_LFRead::ParameterUpdating_ (int i, DspParameter const &p)
{
  //we only have two parameters
  printf("a\n");
  if (i >= 2)
    return false;
  
  printf("b\n");
  if (p.Type() != DspParameter::ParamType::String) {
    abort();
    return false;
  }
  
  SetParameter_(i, p);
  printf("c\n");
  return true;
}

}} //namespace openlf::components
