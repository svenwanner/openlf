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
* Author Sven Wanner, Maximilian Diebold, Hendrick Siedelmann 
*
*/

#include "clif/clif_vigra.hpp"
#include "clif/subset3d.hpp"
#include "clif/clif_cv.hpp"

#include "opencv2/core/core.hpp"

#include "comp_dispwrite.hpp"
#include "openlf.hpp"

using namespace clif;
using namespace vigra;

namespace openlf { namespace components {
  
COMP_DispWrite::COMP_DispWrite()
{
  AddInput_("input");
  AddParameter_("filename", DspParameter(DspParameter::ParamType::String));
  //AddParameter_("dataset", DspParameter(DspParameter::ParamType::String));
}

void COMP_DispWrite::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  const std::string *filename;
  const std::string *dataset_name = NULL;
  
  inputs.GetValue(0, in);
  
  filename = GetParameter(0)->GetString();
  if (GetParameter(1))
    dataset_name = GetParameter(1)->GetString();
  
  assert(in);
  assert(filename->size());
  
  H5::H5File f_out(filename->c_str(), H5F_ACC_TRUNC);
  Dataset out_set;
  out_set.link(f_out, in->data);
  out_set.writeAttributes();
  
  FlexMAV<4> disp;
  Datastore *disp_store = in->data->getStore("disparity/default/data");
  
  disp.read(disp_store);
  
  //FIXME read/pass actual datastore!
  Subset3d subset(in->data, 0);
  
  float scale = 1.0;
  
  cv::Mat img;
  readCvMat(in->data, disp.shape()[2]/2, img, UNDISTORT | CVT_8U);
  
  //centerview, channel 0
  MultiArrayView<2,float> centerview = disp.get<float>()->bindAt(3,0).bindAt(2,disp.shape()[2]/2);
  
  FILE *pointfile = fopen("debug.ply", "w");
  
  fprintf(pointfile, "ply\n"
          "format ascii 1.0\n"
          "element vertex %d\n"
          "property float x\n"
          "property float y\n"
          "property float z\n"
          "property uchar diffuse_red\n"
          "property uchar diffuse_green\n"
          "property uchar diffuse_blue\n"
          "end_header\n", centerview.shape(0)*centerview.shape(1));
  
  int w = centerview.shape(0);
  int h = centerview.shape(1);
  Shape2 p;
  for(p[1] = 0; p[1] < h; ++p[1])
    for (p[0] = 0; p[0] < w; ++p[0]) {
      double depth = subset.disparity2depth(centerview[p], scale);
      if (depth >= 0 && depth <= 2000) {
        if (img.type() == CV_8UC3) {
          cv::Vec3b col = img.at<cv::Vec3b>(p[1],p[0]);
          fprintf(pointfile, "%.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f[0], depth*(p[1]-h/2)/subset.f[1], depth,col[0],col[1],col[2]);
        }
        else if (img.type() == CV_8UC1) {
          uchar col = img.at<uchar>(p[1],p[0]);
          fprintf(pointfile, "%.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f[0], depth*(p[1]-h/2)/subset.f[1], depth,col,col,col);
        }
        else
          fprintf(pointfile, "%.3f %.3f %.3f 127 127 127\n", depth*(p[0]-w/2)/subset.f[0], depth*(p[1]-h/2)/subset.f[1], depth);
          
      }
      else
        fprintf(pointfile, "0 0 0 0 0 0\n");
    }
    
  fprintf(pointfile,"\n");
  fclose(pointfile);
  
  ClifFile debugfile;
  debugfile.create("debug.clif");
  Dataset *debugset = debugfile.createDataset("default");
  disp.write(debugset, "testimage");
}

bool COMP_DispWrite::ParameterUpdating_ (int i, DspParameter const &p)
{
  //we only have two parameters
  if (i >= 2)
    return false;
  
  if (p.Type() != DspParameter::ParamType::String)
    return false;
  
  SetParameter_(i, p);
  return true;
}

}} //namespace openlf::components
