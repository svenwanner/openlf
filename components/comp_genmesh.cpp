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
#include "clif/clif_cv.hpp"
#include "clif/mesh.hpp"
#include "opencv2/core/core.hpp"
#include "openlf/types.hpp"

#include "clif/preproc.hpp"

#include "dspatch/DspPlugin.h"

#include <locale.h>

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
  virtual bool ParameterUpdating_ (int i, DspParameter const &p);
  Mesh _mesh;
};
  
component::component()
{
  setTypeName_("disp2mesh");
  AddInput_("input");
  AddParameter_("obj_filename", DspParameter(DspParameter::ParamType::String));
  AddParameter_("ply_filename", DspParameter(DspParameter::ParamType::String));
  AddParameter_("viewer", DspParameter(DspParameter::ParamType::Bool, false));
  AddParameter_("block", DspParameter(DspParameter::ParamType::Bool, true));
}

void gen_mesh(Mesh &mesh, MultiArrayView<2,float> &disp, cv::Mat &view, Subset3d &subset)
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
  
  int point_count = 0;
  int face_count = 0;
  int face_idx = 0;
  
  for(int i=0;i<w;i++) {
      buf1[i] = 0;
      buf2[i] = 0;
  }
  
  //walk center view points and count vertices and faces
  for(p[1]=0;p[1]<h;++p[1]) {
    valid_tmp = valid_last;
    valid_last = valid;
    valid = valid_tmp;
    
    for(p[0]=0;p[0]<w;++p[0]) {
      if (std::isnan(disp[p]) || disp[p] <= 0)
        valid[p[0]] = 0;
      else {
        valid[p[0]] = 1;
        
        point_count++;
        
        if (p[0]) {
          if (valid[p[0]-1] && valid[p[0]] && valid_last[p[0]-1] && valid_last[p[0]]) {
            face_count+=2;
          }
        }
      }
    }
  }
  
  mesh.size(point_count, face_count);
  mesh.color(true);
  
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
        cv::Point3d wp;
        cv::Vec3b col;
        
        mesh.V(v_idx-1, 0) = depth*(p[0]-w/2)/subset.f(0);
        mesh.V(v_idx-1, 1) = depth*(p[1]-h/2)/subset.f(1);
        mesh.V(v_idx-1, 2) = depth;
        
        if (view.type() == CV_8UC3)
          col = view.at<cv::Vec3b>(p[1],p[0]);
        else if (view.type() == CV_8UC1) {
          uchar px = view.at<uchar>(p[1],p[0]);
          col = cv::Vec3b(px,px,px);
        }
        else
          col = cv::Vec3b(127,127,127);
        
        mesh.C(v_idx-1, 0) = col[0]/255.0;
        mesh.C(v_idx-1, 1) = col[1]/255.0;
        mesh.C(v_idx-1, 2) = col[2]/255.0;
        
        v_idx ++;
        
        if (p[0]) {
          if (valid[p[0]-1] && valid[p[0]] && valid_last[p[0]-1] && valid_last[p[0]]) {
            mesh.F(face_idx, 0) = valid[p[0]-1]-1;
            mesh.F(face_idx, 1) = valid[p[0]]-1;
            mesh.F(face_idx, 2) = valid_last[p[0]]-1;
            //FIXME add second face!
            //fprintf(pointfile, "f %d %d %d %d\n", valid[p[0]-1], valid[p[0]], valid_last[p[0]], valid_last[p[0]-1]);
            face_idx++;
            mesh.F(face_idx, 0) = valid[p[0]-1]-1;
            mesh.F(face_idx, 1) = valid_last[p[0]]-1;
            mesh.F(face_idx, 2) = valid_last[p[0]-1]-1;
            face_idx++;
          }
        }
      }
    }
  }
  delete buf1;
  delete buf2;
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
          fprintf(pointfile, "%.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth,col[0],col[1],col[2]);
        }
        else if (view.type() == CV_8UC1) {
          uchar col = view.at<uchar>(p[1],p[0]);
          fprintf(pointfile, "%.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth,col,col,col);
        }
        else
          fprintf(pointfile, "%.3f %.3f %.3f 127 127 127\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth);
          
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
          fprintf(pointfile, "v %.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth,col[0],col[1],col[2]);
        }
        else if (view.type() == CV_8UC1) {
          uchar col = view.at<uchar>(p[1],p[0]);
          fprintf(pointfile, "v %.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth,col,col,col);
        }
        else
          fprintf(pointfile, "v %.3f %.3f %.3f 127 127 127\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth);
        
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

float disps_error(const std::vector<std::pair<float,float>> &ar, int start, float sum, float &avg)
{
  float error = 0.0;
  avg = 0.0;
  float count = 0.0;
  
  int end;
  for(int i=start;i<ar.size();i++) {
    count += ar[i].second;
    if (count >= sum) {
      end = i+1;
      break;
    }
  }
  if (count < sum)
    return 10000000000000.0;
  
  
  for(int i=start;i<end;i++) {
    avg += ar[i].first*ar[i].second;
  }
  
  avg /= count;
  
  for(int i=start;i<end;i++) {
    float d = avg - ar[i].first;
    error += d*d*ar[i].second;
  }
  
  return error;
}

int outliers = 0;


float disps_split_error(const std::vector<std::pair<float,float>> &ar, int split, float &avg, float centerview)
{
  float error = 0.0;
  float error_single = 0.0;
  float avg1 = 0.0;
  float avg2 = 0.0;
  float count = 0.0;
  int ol = outliers;
  
  if (split <= 2*ol || ar.size()-split <= 2*ol)
    return 100000000000000000000000.0;
  
  
  for(int i=ol;i<split-ol;i++) {
    avg1 += ar[i].first*ar[i].second;
    count += ar[i].second;
  }
  
  avg1 /= count;
  
  count = 0.0;
  for(int i=split+ol;i<ar.size()-ol;i++) {
    avg2 += ar[i].first*ar[i].second;
    count += ar[i].second;
  }
  
  avg2 /= count;
  
  //FIXME calc
  count = 0.0;
  avg = 0.0;
  for(int i=2*ol;i<ar.size()-2*ol;i++) {
    avg += ar[i].first*ar[i].second;
    count += ar[i].second;
  }
  avg /= count;
  
  for(int i=2*ol;i<ar.size()-2*ol;i++) {
    float d = abs(avg - ar[i].first);
    error_single += d*d*ar[i].second*0.1;
  }
  
  for(int i=ol;i<split-ol;i++) {
    float d = abs(avg1 - ar[i].first);
    error += d*d*ar[i].second;
  }
  
  for(int i=split+ol;i<ar.size()-ol;i++) {
    float d = abs(avg2 - ar[i].first);
    error += d*d*ar[i].second;
  }
  
  if (error_single <= error)
    return error_single;
  
  
  if (ar[split].first < centerview) {
    avg = avg2;
  }
  else {
    avg = avg1;
  }
  
  return error;
  
  //float outlier_rejection = 0.1;
  //int re = outlier_rejection*0.5*std::max<int>(split, ar.size() - split);
  
  if (split > ar.size() - split) {
    /*if (re) {
      avg1 = 0.0;
      count = 0.0;
      for(int i=re;i<split-re;i++) {
        avg1 += ar[i].first*ar[i].second;
        count += ar[i].second;
      }
      avg1 /= count;
    }*/
    
    avg = avg1;
  }
  else {
    /*if (outlier_rejection != 0.0) {
      avg2 = 0.0;
      count = 0.0;
      for(int i=split+re;i<ar.size()-re;i++) {
        avg2 += ar[i].first*ar[i].second;
        count += ar[i].second;
      }
      avg2 /= count;
    }*/
    
    avg = avg2;
  }
  
  return error;
}

void write_merge_obj(const char *name, MultiArrayView<3,float> &disp, MultiArrayView<3,float> &coh, cv::Mat &view, Subset3d &subset)
{
  int v_idx = 1;
  
  const int w = disp.shape(0);
  const int h = disp.shape(1);
  const int views = disp.shape(2);
  
  int *buf1 = new int[w];
  int *buf2 = new int[w];
  int *valid = buf1;
  int *valid_last = buf2;
  int *valid_tmp;
  Shape3 p;
  Shape2 pc;
  
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
  
  Shape2 imgsize(w,h);
  MultiArray<2,std::vector<std::pair<float,float>>> disp_array(imgsize);
  MultiArray<2,float> disp_merged(imgsize);
  //MultiArray<2,float> disp_counts(imgsize);
  
  disp_merged.init(0);
  //disp_counts.init(0);
  
  float min_coherence = 0.0;
  for(p[2]=0;p[2]<views;p[2]++) 
    for(p[1]=0;p[1]<h;++p[1]) {
      for(p[0]=0;p[0]<w;++p[0]) {
        if (std::isnan(disp[p]) || disp[p] <= 0 || coh[p] <= min_coherence)
          continue;
        
        float coh_v = (coh[p]-min_coherence)/(1.0-min_coherence);
        
        float off = -disp[p]*(views/2-p[2]);
        float ndist = 1.0;//-fabs(views/2-p[2])/4.0;
        
        pc[0] = p[0]+off;
        pc[1] = p[1];
        
        //scatter around for smoother results
        /*int r = 2; 
        for(int i=std::max(0, int(p[0]+off-r));i<std::min(w,int(p[0]+off+r+1));i++) {
          pc[0] = i;
          disp_array[pc].push_back(std::make_pair(disp[p],coh_v*ndist));
        }*/
        
        float frac = off - floor(off);
        
        if (pc[0] >= w || pc[0] < 0)
          continue;
        
        disp_array[pc].push_back(std::make_pair(disp[p],coh_v*(1.0-frac)*ndist));
        
        pc[0]++;
        
        if (pc[0] >= w || pc[0] < 0)
          continue;
        
        disp_array[pc].push_back(std::make_pair(disp[p],coh[p]*frac*ndist));
      }
    }
    
    struct rgreater
    {
      bool operator()( const std::pair<float,float> & l, const std::pair<float,float>& r) const {
        return l.first < r.first;
      }
    };
    
#pragma omp parallel for private(pc) schedule(dynamic)
  for(int j=0;j<h;j++) {
    pc[1] = j;
    Shape3 p_centerview;
    printf("%d/%d\n", pc[1], h);
    for(pc[0]=0;pc[0]<w;++pc[0]) {
      if (disp_array[pc].size() == 0)
        continue;      
      
      std::vector<std::pair<float,float>> &ar = disp_array[pc];
      
      p_centerview[0] = pc[0];
      p_centerview[1] = pc[1];
      p_centerview[2] = views/2;
      
      
      std::sort(ar.begin(), ar.end(),rgreater());
      
      //param!
      float avg_best = 0.0, error_best = 1000000000000.0;
      float avg, error;
      
      //float sum = 0.0;
      //for(int i=0;i<ar.size();i++)
      //  sum += ar[i].second;
      
      for(int i=0;i<ar.size();i++) {
        //error = disps_error(ar, i, sum*0.4, avg);
        error = disps_split_error(ar, i, avg, disp[p_centerview]);
        if (error < error_best) {
          error_best = error;
          avg_best = avg;
        }
      }
      disp_merged[pc] = avg_best;
      
      /*float sum = 0.0;
      float avg_best = 0.0;
      for(int i=0;i<ar.size();i++) {
        sum += ar[i].second;
        avg_best += ar[i].first*ar[i].second;
      }
      disp_merged[pc] = avg_best / sum;*/
    }
  }
      
  
  printf("write obj!\n");
  
  for(pc[1]=0;pc[1]<h;++pc[1]) {
    valid_tmp = valid_last;
    valid_last = valid;
    valid = valid_tmp;
    
    for(pc[0]=0;pc[0]<w;++pc[0]) {
      if (std::isnan(disp_merged[pc]) || disp_merged[pc] <= 0)
        valid[pc[0]] = 0;
      else {
        valid[pc[0]] = v_idx;
        
        double depth = subset.disparity2depth(disp_merged[pc]);
        
        if (view.type() == CV_8UC3) {
          cv::Vec3b col = view.at<cv::Vec3b>(pc[1],pc[0]);
          fprintf(pointfile, "v %.3f %.3f %.3f %d %d %d\n", depth*(pc[0]-w/2)/subset.f(0), depth*(pc[1]-h/2)/subset.f(1), depth,col[0],col[1],col[2]);
        }
        else if (view.type() == CV_8UC1) {
          uchar col = view.at<uchar>(pc[1],pc[0]);
          fprintf(pointfile, "v %.3f %.3f %.3f %d %d %d\n", depth*(pc[0]-w/2)/subset.f(0), depth*(pc[1]-h/2)/subset.f(1), depth,col,col,col);
        }
        else
          fprintf(pointfile, "v %.3f %.3f %.3f 127 127 127\n", depth*(pc[0]-w/2)/subset.f(0), depth*(pc[1]-h/2)/subset.f(1), depth);
        
        v_idx ++;
        
        if (pc[0]) {
          if (valid[pc[0]-1] && valid[pc[0]] && valid_last[pc[0]-1] && valid_last[pc[0]]) {
            fprintf(pointfile, "f %d %d %d %d\n", valid[pc[0]-1], valid[pc[0]], valid_last[pc[0]], valid_last[pc[0]-1]);
            //more correct in some way but whatever
            //fprintf(pointfile, "f %d %d %d\n", valid[pc[0]-1], valid_last[pc[0]], valid_last[pc[0]-1]);
            //fprintf(pointfile, "f %d %d %d\n", valid[pc[0]-1], valid[pc[0]], valid_last[pc[0]]);
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

void component::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  const std::string *obj_filename = GetParameter(0)->GetString();
  const std::string *ply_filename = GetParameter(1)->GetString();
  bool use_viewer = GetParameter(2)->GetBool();
  bool block_viewer = GetParameter(3)->GetBool();
  cv::Mat img3d, img;
  
  errorCond(obj_filename || ply_filename || use_viewer, "no output specified");
  RETURN_ON_ERROR
  
  inputs.GetValue(0, in);
  errorCond(in, "no input!"); RETURN_ON_ERROR
  
  if (configOnly())
    return;

  
  //FIXME if disparity_root is empty use first available
  cpath disparity_root = in->path;
  
  Mat disp;
  Datastore *disp_store = in->data->getStore(disparity_root/"data");
  disp_store->read(disp);

  float scale = 1.0;
  
  Attribute *attr;
  
  attr = in->data->get(disparity_root/"subset/scale");
  if (attr)
    attr->get(scale);
  
  ProcData opts;
  opts.set_scale(scale);
  
  //FIXME read/pass actual datastore!
  Subset3d subset(in->data, disparity_root/"subset/source", opts);
  //FIXME add read function to subset3d
  
  Datastore *store = in->data->getStore(subset.extrinsics_group()/"data");
  
  //FIXME should add a readimage to subset3d!
  std::vector<int> idx(store->dims(), 0);
  idx[3] = disp[3]/2;
  
  opts.set_flags(UNDISTORT | CVT_8U);
  store->readImage(idx, &img3d, opts);
  clifMat2cv(&img3d,&img);
  
  //centerview, channel 0
  //FIXME flexmav!
  MultiArrayView<2,float> centerview = vigraMAV<4,float>(disp).bindAt(3,disp[3]/2).bindAt(2,0);
  
  char* locale_old = setlocale(LC_NUMERIC, "C");

  gen_mesh(_mesh, centerview, img, subset);

  if (obj_filename && obj_filename->size())
    _mesh.writeOBJ(obj_filename->c_str());
  
  if (use_viewer)
#ifdef CLIF_WITH_LIBIGL_VIEWER
    printf("show viewer, block %d\n", int(block_viewer));
  _mesh.show(block_viewer);
#else
  printf("ERROR could not launch viewer, clif compiled without libigl_viewer!\n");
#endif
  
  
  setlocale(LC_NUMERIC, locale_old);
}

bool component::ParameterUpdating_ (int i, DspParameter const &p)
{
  //we only have four parameters
  if (i >= 4)
    return false;
  
  if (i < 2 && p.Type() != DspParameter::ParamType::String)
    return false;
  
  if (i >= 2 && p.Type() != DspParameter::ParamType::Bool)
    return false;
  
  SetParameter_(i, p);
  return true;
}

class Plugin : public DspPlugin
{
  virtual DspComponent* Create() const { return new component; }
  virtual ~Plugin() {}
};
EXPORT_DSPPLUGIN(Plugin);
