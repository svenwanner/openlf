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

#include "openlf/operator_macro.hpp"

#include <opencv2/highgui/highgui.hpp>

using namespace clif;
using namespace vigra;

template<class FROM> struct _is_convertible_to_float : public std::is_convertible<FROM,float> {};

class OP_Imwrite : public DspComponent {
public:
  OP_Imwrite();
  DSPCOMPONENT_TRIVIAL_CLONE(OP_Imwrite);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
};

OP_Imwrite::OP_Imwrite()
{
  setTypeName_("OP_Imwrite"); 
  AddInput_("input");
  AddParameter_("filename", DspParameter(DspParameter::ParamType::String));
}

void OP_Imwrite::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  bool stat;
  Mat *in;
  const std::string* filename;
  
  errorCond(inputs.GetValue(0, in), "OP_Imwrite : input not found - possible type mismatch?\n"); RETURN_ON_ERROR
  
  filename = GetParameter(0)->GetString();
  errorCond(filename && filename->size(), "missing file name"); RETURN_ON_ERROR
  
  if (configOnly())
    return;
  
  cv::Mat img;
  cv::normalize(cvImg(*in), img, 0, 255, cv::NORM_MINMAX, CV_8UC1);
  imwrite(filename->c_str(), img);
}

EXPORT_DSPCOMPONENT(OP_Imwrite)
