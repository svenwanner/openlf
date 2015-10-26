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

#include "opencv2/core/core.hpp"

#include "openlf/types.hpp"

#include "dspatch/DspPlugin.h"

using namespace clif;
using namespace vigra;
using namespace openlf;

class COMP_DispWrite : public DspComponent {
public:
  COMP_DispWrite();
  DSPCOMPONENT_TRIVIAL_CLONE(COMP_DispWrite);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  virtual bool ParameterUpdating_ (int i, DspParameter const &p);
};
  
COMP_DispWrite::COMP_DispWrite()
{
  setTypeName_("writeMesh");
  AddInput_("input");
  AddParameter_("obj_filename", DspParameter(DspParameter::ParamType::String));
  AddParameter_("ply_filename", DspParameter(DspParameter::ParamType::String));
  //AddParameter_("dataset", DspParameter(DspParameter::ParamType::String));
}

void write_ply(const char *name, MultiArrayView<2,float> &disp, cv::Mat &view, Subset3d &subset)
{
  FILE *pointfile = fopen(name, "w");
  
  int point_count = 0;
  
  int w = disp.shape(0);
  int h = disp.shape(1);
  
  Shape2 p;
  for(p[1] = 0; p[1] < h; ++p[1])
    for (p[0] = 0; p[0] < w; ++p[0]) {
      double depth;
      if (!std::isnan(disp[p]) && disp[p] > 0) 
        point_count++;
    }
    
  printf("write ply: %d valid points\n", point_count);
  
  fprintf(pointfile, "ply\n"
          "format ascii 1.0\n"
          "element vertex %d\n"
          "property float x\n"
          "property float y\n"
          "property float z\n"
          "property uchar diffuse_red\n"
          "property uchar diffuse_green\n"
          "property uchar diffuse_blue\n"
          "end_header\n", point_count);
  
  for(p[1] = 0; p[1] < h; ++p[1])
    for (p[0] = 0; p[0] < w; ++p[0]) {
      double depth;
      if (std::isnan(disp[p]) || disp[p] <= 0)
        depth = -1;
      else
        depth = subset.disparity2depth(disp[p]);
      if (depth >= 0) {
        if (view.type() == CV_8UC3) {
          cv::Vec3b col = view.at<cv::Vec3b>(p[1],p[0]);
          fprintf(pointfile, "%.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f[0], depth*(p[1]-h/2)/subset.f[1], depth,col[0],col[1],col[2]);
        }
        else if (view.type() == CV_8UC1) {
          uchar col = view.at<uchar>(p[1],p[0]);
          fprintf(pointfile, "%.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f[0], depth*(p[1]-h/2)/subset.f[1], depth,col,col,col);
        }
        else
          fprintf(pointfile, "%.3f %.3f %.3f 127 127 127\n", depth*(p[0]-w/2)/subset.f[0], depth*(p[1]-h/2)/subset.f[1], depth);
          
      }
    }
    if (std::isnan(disp[p]) || disp[p] <= 0)
  fprintf(pointfile,"\n");
  fclose(pointfile);
}

void write_obj(const char *name, MultiArrayView<2,float> &disp, cv::Mat &view, Subset3d &subset)
{
  int v_idx = 1;
  
  const int w = disp.shape(0);
  const int h = disp.shape(1);
  
  int *buf1 = new int[w];
  int *buf2 = new int[w];
  int *valid = buf1;
  int *valid_last = buf2;
  int *valid_tmp;
  Shape2 p;
  
  FILE *pointfile = fopen(name, "w");
  if (!pointfile) {
	  printf("could not open %s for write\n", name);
	  abort();
  }
  //fprintf(pointfile, "vn 0 0 -1\n");
  
  for(int i=0;i<w;i++) {
      buf1[i] = 0;
      buf2[i] = 0;
  }
  
  printf("write obj!\n");
  
  for(p[1]=0;p[1]<h;++p[1]) {
    valid_tmp = valid_last;
    valid_last = valid;
    valid = valid_tmp;
    
    for(p[0]=0;p[0]<w;++p[0]) {
      if (std::isnan(disp[p]) || disp[p] <= 0)
        valid[p[0]] = 0;
      else {
        valid[p[0]] = v_idx;
        
        double depth = subset.disparity2depth(disp[p]);
        
        if (view.type() == CV_8UC3) {
          cv::Vec3b col = view.at<cv::Vec3b>(p[1],p[0]);
          fprintf(pointfile, "v %.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f[0], depth*(p[1]-h/2)/subset.f[1], depth,col[2],col[1],col[0]);
        }
        else if (view.type() == CV_8UC1) {
          uchar col = view.at<uchar>(p[1],p[0]);
          fprintf(pointfile, "v %.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f[0], depth*(p[1]-h/2)/subset.f[1], depth,col,col,col);
        }
        else
          fprintf(pointfile, "v %.3f %.3f %.3f 127 127 127\n", depth*(p[0]-w/2)/subset.f[0], depth*(p[1]-h/2)/subset.f[1], depth);
        
        v_idx ++;
        
        if (p[0]) {
          if (valid[p[0]-1] && valid[p[0]] && valid_last[p[0]-1] && valid_last[p[0]]) {
            fprintf(pointfile, "f %d %d %d %d\n", valid[p[0]-1], valid[p[0]], valid_last[p[0]], valid_last[p[0]-1]);
            //more correct in some way but whatever
            //fprintf(pointfile, "f %d %d %d\n", valid[p[0]-1], valid_last[p[0]], valid_last[p[0]-1]);
            //fprintf(pointfile, "f %d %d %d\n", valid[p[0]-1], valid[p[0]], valid_last[p[0]]);
          }
        }
      }
    }
  }
  delete buf1;
  delete buf2;
  fprintf(pointfile,"\n");
  fclose(pointfile);
}

void COMP_DispWrite::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  const std::string *obj_filename;
  const std::string *ply_filename;
  
  
  obj_filename = GetParameter(0)->GetString();
  ply_filename = GetParameter(1)->GetString();
  
  errorCond(obj_filename || ply_filename, "no output specified");
  RETURN_ON_ERROR
  
  inputs.GetValue(0, in);
  errorCond(in, "no input!"); RETURN_ON_ERROR
  
  if (configOnly())
    return;
  
  /*assert(in);
  assert(filename->size());
  
  H5::H5File f_out(filename->c_str(), H5F_ACC_TRUNC);
  Dataset out_set;
  out_set.link(f_out, in->data);
  out_set.writeAttributes();
  f_out.close();*/
  
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
  
  if (ply_filename)
    write_ply(ply_filename->c_str(), centerview, img, subset);
  if (obj_filename)
    write_obj(obj_filename->c_str(), centerview, img, subset);
  
  /*ClifFile *debugfile = new ClifFile();
  debugfile->create("debug.clif");
  Dataset *debugset = debugfile->createDataset("default");
  disp.write(debugset, "testimage");
  delete debugfile;*/
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

class Plugin : public DspPlugin
{
  virtual DspComponent* Create() const { return new COMP_DispWrite; }
  virtual ~Plugin() {}
};
EXPORT_DSPPLUGIN(Plugin);