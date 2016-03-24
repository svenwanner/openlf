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
#include "opencv2/core/core.hpp"
#include "openlf/types.hpp"
#include <opencv2/highgui/highgui.hpp>

#include "clif/preproc.hpp"

#include "dspatch/DspPlugin.h"

#include <locale.h>

using namespace clif;
using namespace vigra;
using namespace openlf;

class COMP_writeMesh : public DspComponent {
public:
	COMP_writeMesh();
	DSPCOMPONENT_TRIVIAL_CLONE(COMP_writeMesh);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  virtual bool ParameterUpdating_ (int i, DspParameter const &p);
  bool initialize = false;
};
  
COMP_writeMesh::COMP_writeMesh()
{
  setTypeName_("COMP_writeMesh");
  AddInput_("disparity");
  AddInput_("color");
  AddParameter_("obj_filename", DspParameter(DspParameter::ParamType::String));
  AddParameter_("ply_filename", DspParameter(DspParameter::ParamType::String));
  AddParameter_("max_depth", DspParameter(DspParameter::ParamType::Float, 5000));
  AddParameter_("disparity_idx", DspParameter(DspParameter::ParamType::Int, 0));
  AddParameter_("color_idx", DspParameter(DspParameter::ParamType::Int, 0));
  AddParameter_("normalize", DspParameter(DspParameter::ParamType::Bool, true));
}

void write_ply(const char *name, MultiArrayView<2,float> &disp, cv::Mat *view, Subset3d &subset, float &cutoff)
{
  FILE *pointfile = fopen(name, "w");
  
  int point_count = 0;
  
  int w = disp.shape(0);
  int h = disp.shape(1);
  
  float maxValue = 0;

  Shape2 p;
  for(p[1] = 0; p[1] < h; ++p[1])
	  for (p[0] = 0; p[0] < w; ++p[0]) {
		  double depth;
		  if (!std::isnan(disp[p]) && disp[p] > 0) {
		  point_count++;
	  }
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
	  else{
        depth = subset.disparity2depth(disp[p]);
		if (depth > cutoff) depth = cutoff;
	  }
	  if (depth >= 0) {
        if (view && view->type() == CV_8UC3) {
          cv::Vec3b col = view->at<cv::Vec3b>(p[1],p[0]);
          fprintf(pointfile, "%.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth,col[0],col[1],col[2]);
        }
        else if (view && view->type() == CV_8UC1) {
          uchar col = view->at<uchar>(p[1],p[0]);
          fprintf(pointfile, "%.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth,col,col,col);
        }
        else
          fprintf(pointfile, "%.3f %.3f %.3f 127 127 127\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth);
          
      }
    }
    //if (std::isnan(disp[p]) || disp[p] <= 0) fprintf(pointfile,"\n");
  fclose(pointfile);
}

void write_obj(const char *name, MultiArrayView<2, float> &disp, cv::Mat *view, Subset3d &subset, float &cutoff)
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
        if (depth > cutoff) depth = cutoff;
        
        if (view && view->type() == CV_8UC3) {
          cv::Vec3b col = view->at<cv::Vec3b>(p[1],p[0]);
          fprintf(pointfile, "v %.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth,col[0],col[1],col[2]);
        }
        else if (view && view->type() == CV_8UC1) {
          uchar col = view->at<uchar>(p[1],p[0]);
          fprintf(pointfile, "v %.3f %.3f %.3f %d %d %d\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth,col,col,col);
        }
        else
          fprintf(pointfile, "v %.3f %.3f %.3f 127 127 127\n", depth*(p[0]-w/2)/subset.f(0), depth*(p[1]-h/2)/subset.f(1), depth);
        
        v_idx ++;
        
        if (p[0]) {
          if (valid[p[0] - 1] && valid[p[0]] && valid_last[p[0] - 1] && valid_last[p[0]]) {
            fprintf(pointfile, "f %d %d %d %d\n", valid[p[0] - 1], valid[p[0]], valid_last[p[0]], valid_last[p[0] - 1]);
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

void COMP_writeMesh::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in_disp = NULL;
  LF *in_col = NULL;
  const std::string *obj_filename;
  const std::string *ply_filename;
  bool use_col = false;
  bool proc_col = true;
  
  obj_filename = GetParameter(0)->GetString();
  ply_filename = GetParameter(1)->GetString();
  float cutoff = *GetParameter(2)->GetFloat();
  bool normalize = *GetParameter(5)->GetBool();
  
  inputs.GetValue(0, in_disp);
  errorCond(in_disp && !in_disp->path.empty(), "disparity input missing!"); RETURN_ON_ERROR
  
  inputs.GetValue(1, in_col);
  if (in_col && !in_col->path.empty())
    use_col = true;
  
  errorCond(obj_filename || ply_filename, "no output specified"); RETURN_ON_ERROR
  
  Subset3d subset;
  
  errorCond(subset.create(in_disp->data, in_disp->path/"subset"), "invalid subset"); RETURN_ON_ERROR
  
  if (configOnly())
    return;
  
  Mat disp, col;
  Datastore *disp_store = in_disp->data->store(in_disp->path / "data");  
  disp_store->read(disp);
  
  Datastore *col_store = NULL;
  if (use_col) {
    col_store = in_col->data->store(in_col->path);
    if (col_store)
      proc_col = false;
    else {
      //path points to subset - use undistortion and scale according to subset
      col_store = in_col->data->store(in_col->path / "extrinsics/data");
      proc_col = true;
    }
  }
  
  //FIXME set default according to input store size! Needs to look at store ?! 
  int disp_n = max(min(disp[3]/2 + *GetParameter(3)->GetInt(), disp[3]-1), 0);
  int col_n = 0;
  if (use_col)
    col_n = max(min(col_store->extent()[3]/2 + *GetParameter(4)->GetInt(), col_store->extent()[3]-1), 0);
  
  cv::Mat *img = NULL;
  std::vector<int> idx(disp_store->dims(), 0);
  
  if (use_col) {
    cv::Mat img3d;
    std::vector<int> col_idx(col_store->dims(), 0);
    idx[3] = col_n;
    
    ProcData opts;
    opts.set_store(col_store);
    if (proc_col)
      opts = subset.proc();
    opts.set_flags(opts.flags());
    col_store->readImage(idx, &img3d, opts);
    
    img = new cv::Mat;
    clifMat2cv(&img3d,img);
  }
  
  if (img) {
    if (normalize)
      cv::normalize(*img, *img, 0, 255, cv::NORM_MINMAX);
    img->convertTo(*img, CV_8U);
  }

  //FIXME rework according to new subset handling
  //FIXME path has no meaning?
  
  MultiArrayView<2, float> centerview = vigraMAV<4, float>(disp).bindAt(3, disp_n).bindAt(2, 0);
  
  char* locale_old = setlocale(LC_NUMERIC, "C");
  
  if (ply_filename && ply_filename->size())
    write_ply(ply_filename->c_str(), centerview, img, subset, cutoff);
  
  if (obj_filename && obj_filename->size())
    write_obj(obj_filename->c_str(), centerview, img, subset, cutoff);
  
  setlocale(LC_NUMERIC, locale_old);
  
  if (img)
    delete img;
}

bool COMP_writeMesh::ParameterUpdating_(int i, DspParameter const &p)
{
  //we only have four parameters
  if (i >= 7)
    return false;
  
  if (p.Type() != DspParameter::ParamType::String && p.Type() != DspParameter::ParamType::Float && p.Type() != DspParameter::ParamType::Int)
    return false;
  
  SetParameter_(i, p);
  return true;
}

class Plugin : public DspPlugin
{
	virtual DspComponent* Create() const { return new COMP_writeMesh; }
    virtual ~Plugin() {}
};
EXPORT_DSPPLUGIN(Plugin);
