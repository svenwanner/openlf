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

#include <omp.h>
#include <unordered_set>

//for printprogress
#include <cstdarg>

using namespace clif;
using namespace vigra;
using namespace std;
using namespace openlf;

//typedef unsigned int _uint;

#define DPPT DspParameter::ParamType
  
class COMP_Epi : public DspComponent {
public:
  COMP_Epi();
  DSPCOMPONENT_TRIVIAL_CLONE(COMP_Epi);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:  
  DspComponent *_default_tensort_circuit = NULL;
  DspComponent *_default_orientation_circuit = NULL;
  DspComponent *_default_merge_circuit = NULL;
  LF _out;
  clif::Dataset _out_set;
  
  template<typename T> void openlf_add_param(const char *name, T val, DspParameter::ParamType type, int idx);
  void openlf_add_param(const char *name, DspParameter::ParamType type, int idx);
  bool ParameterUpdating_(int index, const DspParameter& param);
};
  
namespace {
  enum P_IDX {Tensor_Circuit = 0,Orientation_Circuit,Merge_Circuit,DispStart,DispStop,DispStep,StartLine,StopLine};
}

template<typename T> void COMP_Epi::openlf_add_param(const char *name, T val, DspParameter::ParamType type, int idx)
{
  int i;
  i = AddParameter_(name, DspParameter(type, val));
  assert(i == idx);
}

void COMP_Epi::openlf_add_param(const char *name, DspParameter::ParamType type, int idx)
{
  int i;
  i = AddParameter_(name, DspParameter(type));
  assert(i == idx);
}
  
//FIXME selectively (all but some specified) expose params as alias
void expose_params(DspComponent *parent, cpath path, DspComponent *child, const std::unordered_set<std::string> &exclude = std::unordered_set<std::string>())
{
  if (!parent || !child)
    return;
  
  for(int i=0;i<child->GetParameterCount();i++)
    if (!exclude.count(child->GetParameterName(i)))
      parent->SetComponentParameterAlias((path/child->GetParameterName(i)).generic_string(), child, i);
}
  
COMP_Epi::COMP_Epi()
{
  setTypeName_("procEPI2.5D");
  AddInput_("input");
  AddInput_("config");
  AddOutput_("output");
  
  openlf_add_param("tensorCircuit", (DspComponent*)NULL, DPPT::Pointer, P_IDX::Tensor_Circuit);
  openlf_add_param("orienationCircuit", (DspComponent*)NULL, DPPT::Pointer, P_IDX::Orientation_Circuit);
  openlf_add_param("mergeCircuit", (DspComponent*)NULL, DPPT::Pointer, P_IDX::Merge_Circuit);
  
  openlf_add_param("DispStart", DPPT::Float, P_IDX::DispStart);
  openlf_add_param("DispStop", DPPT::Float, P_IDX::DispStop);
  openlf_add_param("DispStep", DPPT::Float, P_IDX::DispStep);
  
  openlf_add_param("StartLine", DPPT::Int, P_IDX::StartLine);
  openlf_add_param("StopLine", DPPT::Int, P_IDX::StopLine);
}

template<typename T> class subarray_copy {
public:
void operator()(int line, int epi_w, int epi_h, Mat *sink_mat, Mat *disp_store, float disp_scale)
{
  for(int c=0;c<(*sink_mat)[2];c++) {
    MultiArrayView<2,T> sink = vigraMAV<3,T>(*sink_mat).bindAt(2, c);
    MultiArrayView<3,T> store = vigraMAV<4,T>(*disp_store).bindAt(2, c);
    
    for(int i=0;i<epi_h;i++) {
      //bind store y to epi line
      MultiArrayView<2,T> epi = store.bindAt(1, line);
      epi = sink;
      //if (disp_scale != 1.0)
        //epi *= 1.0/disp_scale;
    }
  }
}
};

template<typename T> class subarray_uncopy {
public:
void operator()(int line, int epi_w, int epi_h, Mat *sink_mat, Mat *disp_store, float disp_scale)
{
  for(int c=0;c<(*sink_mat)[2];c++) {
    MultiArrayView<2,T> sink = vigraMAV<3,T>(*sink_mat).bindAt(2, c);
    MultiArrayView<3,T> store = vigraMAV<4,T>(*disp_store).bindAt(2, c);
    
    for(int i=0;i<epi_h;i++) {
      //bind store y to epi line
      MultiArrayView<2,T> epi = store.bindAt(1, line);
      sink = epi;
      //if (disp_scale != 1.0)
        //epi *= 1.0/disp_scale;
    }
  }
}
};

//FIXME not yet working...
/*template<typename T> class subarray_copy {
public:
void operator()(int line, int epi_w, int epi_h, Mat *sink_mat, Mat *disp_store, float disp_scale)
{
  for(int c=0;c<(*sink_mat)[2];c++) {
    Mat sink = sink_mat->bind(2, c);
    Mat store = disp_store->bind(2, c);
    
    for(int i=0;i<epi_h;i++) {
      //bind store y to epi line
      //MultiArrayView<2,T> epi = store.bindAt(1, line);
      //epi = sink;
      Mat epi = store.bind(1,line);
      sink.copyTo(epi);
    }
  }
}
};*/

//for all params apply config keys if found
//config_path: e.g. "/openlf/componentname/merge"
//a attribute name in config may also conatin "*" for matching
void forward_config(DspComponent *comp, Dataset *config)
{
  if (!config)
    return;
  
  for(int i=0;i<comp->GetParameterCount();i++) {
    Attribute *attr;
    const DspParameter *param = comp->GetParameter(i);
    cpath param_path = cpath("/openlf") / comp->GetComponentName() / comp->GetParameterName(i);
    
    //printf("search config %s\n", param_path.c_str());
    
    attr = config->getMatch(param_path);
    if (attr) {  
      //TODO abstract this (add call... to DspType??)
      switch (param->Type()) {
        case DPPT::Float : 
          float fval;
          attr->convert(&fval);
          comp->SetParameter(i, DspParameter(param->Type(), fval));
          //printf("DEBUG: set param %s to %f\n", param_path.string().c_str(), fval);
          break;
        case DPPT::Int : 
          int ival;
          attr->convert(&ival);
          comp->SetParameter(i, DspParameter(param->Type(), ival));
          //printf("DEBUG: set param %s to %d\n", param_path.string().c_str(), ival);
          break;
        default:
          printf("FIXME: unhandled parameter type! (comp_epi)\n");
      }
    }
    //else
      //printf("no match for %s\n", param_path.string().c_str());
  }
}

template<typename T> void get_float_param(DspComponent *comp, T &val, int idx)
{
  const float *ptr;
  const DspParameter *p = comp->GetParameter(idx);

  if (!p) return;
  ptr = p->GetFloat();
  if (!ptr) return;
  val = *ptr;
  
  printf("got %d copm %p\n", val, comp);
}

template<typename T> void get_int_param(DspComponent *comp, T &val, int idx)
{
  const int *ptr;
  const DspParameter *p = comp->GetParameter(idx);

  if (!p) return;
  ptr = p->GetInt();
  if (!ptr) return;
  val = *ptr;
  
  printf("got %d copm %p\n", val, comp);
}

static void printprogress(int curr, int max, int &last, const char *fmt = NULL, ...)
{
  last = (last + 1) % 4;
  int pos = curr*60/max;
  char unf[] = "                                                             ]";
  char fin[] = "[============================================================]";
  char buf[100];
  
  char cs[] = "-\\|/";
  memcpy(buf, fin, pos+1);
  buf[pos+1] = cs[last];
  memcpy(buf+pos+2, unf+pos+2, 62-pos-2+1);
  if (!fmt) {
    printf("%s\r", buf);
  }
  else {
    printf("%s", buf);
    va_list arglist;
    va_start(arglist, fmt);
    vprintf(fmt, arglist);
    va_end(arglist);
    printf("\r");
  }
  fflush(NULL);
}

namespace {
  class _sub_circuit {
  public:
    _sub_circuit() {};
    void init(DspComponent *comp, int threads = 1)
    {
      int inputs = comp->GetInputCount();
      int outputs = comp->GetOutputCount();
      
      Idx source_size({threads, inputs});
      Idx sink_size({threads, outputs});
      
      printf("init with %d sources!\n", inputs);
      
      _sources.create(source_size);
      _mats_source.create(source_size);
      
      _sinks.create(sink_size);
      
      _comps.resize(threads);
      _circuits.resize(threads);
      
      for(int t=0;t<threads;t++) {
        _comps[t] = comp->clone();
        
        char buf[16];
        
        for(int i=0;i<inputs;i++) {
          sprintf(buf, "source%d", i);
          _circuits[t].AddComponent(_sources(t, i), buf);
        }
        _circuits[t].AddComponent(_comps[t], "proc");
        for(int o=0;o<outputs;o++) {
          sprintf(buf, "sink%d", o);
          _circuits[t].AddComponent(_sinks(t, o), buf);
        }
        
        bool res;
        for(int i=0;i<inputs;i++) {
          res = _circuits[t].ConnectOutToIn(_sources(t, i), 0, _comps[t], i);
          assert(res);
        }
        for(int o=0;o<outputs;o++) {
          res = _circuits[t].ConnectOutToIn(_comps[t], o, _sinks(t, o), 0);
          assert(res);
        }
      }
    }
      
    void setSource(int thread, int input, Mat *m)
    {
      _sources(thread, input).set(m);
    }
    
    clif::Mat* getSink(int thread, int output)
    {
      return _sinks(thread, output).get();
    }
    
    DspComponent *component(int thread)
    {
      return _comps[thread];
    }
    
    void process(int thread)
    {
      _circuits[thread].Tick();
      _circuits[thread].Reset();
    }

  private:
    //x threads, y inputs
    Mat_<MatSource> _sources;
    Mat_<MatSink> _sinks;
    Mat_<Mat> _mats_source;
    
    std::vector<DspComponent*> _comps;
    std::vector<DspCircuit> _circuits;
  };
}


Mat *proc_epi_tensor(int t, Subset3d *subset, float d, int line, float scale, std::vector<Mat> &source_mats, _sub_circuit &tensor_circuits, vigra::MultiArrayView<4,float> &st_data, int st_start)
{
  DspComponent *tensor = tensor_circuits.component(t);
  
  cv::Mat tmp = cvMat(source_mats[t]);
  subset->readEPI(&tmp, line, d, Unit::PIXELS, Improc::UNDISTORT, Interpolation::LINEAR, scale);
  
  tensor_circuits.process(t);
  
  Mat *xx = tensor_circuits.getSink(t, 0);
  Mat *xy = tensor_circuits.getSink(t, 1);
  Mat *yy = tensor_circuits.getSink(t, 2);
  
  vigra::MultiArrayView<3,float> v3_xx = vigraMAV<3,float>(xx);
  vigra::MultiArrayView<3,float> v3_xy = vigraMAV<3,float>(xy);
  vigra::MultiArrayView<3,float> v3_yy = vigraMAV<3,float>(yy);
  
  vigra::MultiArrayView<2,float> v_xx = v3_xx.bindAt(2, 0);
  vigra::MultiArrayView<2,float> v_xy = v3_xy.bindAt(2, 0);
  vigra::MultiArrayView<2,float> v_yy = v3_yy.bindAt(2, 0);
  
  vigra::MultiArrayView<2,float> dst_xx = st_data.bindAt(3, 0).bindAt(2, line-st_start);
  vigra::MultiArrayView<2,float> dst_xy = st_data.bindAt(3, 1).bindAt(2, line-st_start);
  vigra::MultiArrayView<2,float> dst_yy = st_data.bindAt(3, 2).bindAt(2, line-st_start);
  
  dst_xx = v_xx;
  dst_xy = v_xy;
  dst_yy = v_yy;
}


template<class FROM> struct _is_convertible_to_float : public std::is_convertible<FROM,float> {};

Mat *proc_epi_ori_merge(int t, Subset3d *subset, float d, int line, float scale, vigra::MultiArrayView<4,float> &st_data, int st_start, _sub_circuit &orientation_circuits, _sub_circuit &merge_circuits, Mat *disp_mat, Mat *coh_mat, bool copy, bool store_res)
{
  int epi_w = st_data.shape(0);
  int epi_h = st_data.shape(1);
  
  if (!copy) {
    disp_mat->callIf<subarray_uncopy,_is_convertible_to_float>(line,epi_w,epi_h,merge_circuits.getSink(t, 0),disp_mat,scale);
    coh_mat->callIf<subarray_uncopy,_is_convertible_to_float>(line,epi_w,epi_h,merge_circuits.getSink(t, 1),coh_mat,scale);
  }
  
  DspComponent *orientation = orientation_circuits.component(t);
  DspComponent *merge = merge_circuits.component(t);
  
  merge->SetParameter(0, DspParameter(DspParameter::ParamType::Bool, copy));
  
  for(int p=0;p<orientation->GetParameterCount();p++)
    if (!orientation->GetParameterName(p).compare("input_disparity")) {
      bool res = orientation->SetParameter(p, DspParameter(DspParameter::ParamType::Float, d));
      assert(res);
    }
  for(int p=0;p<merge->GetParameterCount();p++)
    if (!merge->GetParameterName(p).compare("input_disparity")) {
      bool res = merge->SetParameter(p, DspParameter(DspParameter::ParamType::Float, d));
      assert(res);
    }
    

  vigra::MultiArrayView<2,float> src_xx = st_data.bindAt(3, 0).bindAt(2, line-st_start);
  vigra::MultiArrayView<2,float> src_xy = st_data.bindAt(3, 1).bindAt(2, line-st_start);
  vigra::MultiArrayView<2,float> src_yy = st_data.bindAt(3, 2).bindAt(2, line-st_start);
  
  std::vector<Mat> sources(3);
  
  for(int i=0;i<3;i++)
    sources[i].create(BaseType::FLOAT, {epi_w,epi_h,1});
  
  vigra::MultiArrayView<2,float> dst_xx = vigraMAV<3,float>(sources[0]).bindAt(2, 0);
  vigra::MultiArrayView<2,float> dst_xy = vigraMAV<3,float>(sources[1]).bindAt(2, 0);
  vigra::MultiArrayView<2,float> dst_yy = vigraMAV<3,float>(sources[2]).bindAt(2, 0);
  
  dst_xx = src_xx;
  dst_xy = src_xy;
  dst_yy = src_yy;
  
  orientation_circuits.setSource(t, 0, &sources[0]);
  orientation_circuits.setSource(t, 1, &sources[1]);
  orientation_circuits.setSource(t, 2, &sources[2]);
  
  orientation_circuits.process(t);
  
  merge_circuits.setSource(t, 0, orientation_circuits.getSink(t, 0));
  merge_circuits.setSource(t, 1, orientation_circuits.getSink(t, 1));
  
  merge_circuits.process(t);

  if (store_res) {
    disp_mat->callIf<subarray_copy,_is_convertible_to_float>(line,epi_w,epi_h,merge_circuits.getSink(t, 0),disp_mat,scale);
    coh_mat->callIf<subarray_copy,_is_convertible_to_float>(line,epi_w,epi_h,merge_circuits.getSink(t, 1),coh_mat,scale);
  }
}

//different example:
//template <class FROM> struct _is_valid : public std::integral_constant<bool, std::is_convertible<FROM,float>::value && !std::is_same<unsigned char,FROM>::value> {};


void COMP_Epi::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  LF *config = NULL;
  LF *out = NULL;
  DspComponent *tensor_circuit;
  DspComponent *orientation_circuit;
  DspComponent *merge_circuit;
  
  errorCond(inputs.GetValue(0, in) && in, "missing input"); RETURN_ON_ERROR
  
  inputs.GetValue(1, config);
  
  out = &_out;
  out->data = &_out_set;
  out->data->memory_link(in->data);
  
  outputs.SetValue(0, out);
  
  errorCond(out, "output creation failed"); RETURN_ON_ERROR
    
  //subset_idx -- extrinsics path
  Subset3d subset(in->data);
  
  Mat *disp_mat = NULL;
  Mat *coh_mat = NULL;
  
  int epi_w = subset.EPIWidth();
  int epi_h = subset.EPIHeight();
  
  float scale = 1.0;
  
  const std::unordered_set<std::string> exclude_params = {"input_disparity","copy"};
  const DspParameter *p;
  
  //FIXME handle sub-circuit as parameter?
  //FIXME remove/add aliases?
  p = GetParameter(P_IDX::Tensor_Circuit);
  errorCond(p, "no tensort circuit parameter!"); RETURN_ON_ERROR
  p->GetPointer(tensor_circuit);
  if (!tensor_circuit) {
    _default_tensort_circuit = OpenLF::getComponent("StructureTensor_Part1");
    errorCond(_default_tensort_circuit, "could not load default epi circuit: \"StructureTensor_Part1\""); RETURN_ON_ERROR
    SetParameter(P_IDX::Tensor_Circuit, DspParameter(DPPT::Pointer, _default_tensort_circuit));
    tensor_circuit = _default_tensort_circuit;
  }
  
  p = GetParameter(P_IDX::Orientation_Circuit);
  errorCond(p, "no tensort circuit parameter!"); RETURN_ON_ERROR
  p->GetPointer(orientation_circuit);
  if (!orientation_circuit) {
    _default_orientation_circuit = OpenLF::getComponent("StructureTensor_Part2");
    errorCond(_default_orientation_circuit, "could not load default epi circuit: \"StructureTensor_Part2\""); RETURN_ON_ERROR
    SetParameter(P_IDX::Orientation_Circuit, DspParameter(DPPT::Pointer, _default_orientation_circuit));
    orientation_circuit = _default_orientation_circuit;
  }
  
  p = GetParameter(P_IDX::Merge_Circuit);
  errorCond(p, "no merge circuit parameter!"); RETURN_ON_ERROR
  p->GetPointer(merge_circuit);
  if (!merge_circuit) {
    _default_merge_circuit = OpenLF::getComponent("OP_MergeDispByCoherence");
    errorCond(_default_merge_circuit, "could not load default merge circuit: \"OP_MergeDispByCoherence\""); RETURN_ON_ERROR
    SetParameter(P_IDX::Merge_Circuit, DspParameter(DPPT::Pointer, _default_merge_circuit));
    merge_circuit = _default_merge_circuit;
  }

  float disp_start = 3.0;
  float disp_step = 1.0;
  float disp_stop = 7.0;
  int start_line = 0;
  int stop_line = subset.EPICount();
  
  
  //FIXME here automatically derive from input (horopter etc.)
  //for now defaults
  SetParameter_(P_IDX::DispStart, DspParameter(DPPT::Float, disp_start));
  SetParameter_(P_IDX::DispStep, DspParameter(DPPT::Float, disp_step));
  SetParameter_(P_IDX::DispStop, DspParameter(DPPT::Float, disp_stop));
  
  SetParameter_(P_IDX::StartLine, DspParameter(DPPT::Int, start_line));
  SetParameter_(P_IDX::StopLine, DspParameter(DPPT::Int, stop_line));
  
  //apply configs
  forward_config(this, in->data);
  if (config)
    forward_config(this, config->data);
  
  disp_start = *GetParameter(P_IDX::DispStart)->GetFloat();
  disp_step  = *GetParameter(P_IDX::DispStep)->GetFloat();
  disp_stop  = *GetParameter(P_IDX::DispStop)->GetFloat();
  
  //FIXME set/get default!
  get_int_param(this, start_line, P_IDX::StartLine);
  get_int_param(this, stop_line, P_IDX::StopLine);
  
  //setup circuit and threading
  int t_count = omp_get_max_threads();
  
  if (configOnly())
    return;

  _sub_circuit tensor_circuits;
  _sub_circuit orientation_circuits;
  _sub_circuit merge_circuits;
  
  tensor_circuits.init(tensor_circuit, t_count);
  orientation_circuits.init(orientation_circuit, t_count);
  merge_circuits.init(merge_circuit, t_count);
  std::vector<Mat> source_mats(t_count);
  
  //FIXME hack add imgType(int flags) to datastore? 
  cv::Mat tmp;
  subset.readEPI(&tmp, 0, disp_start, Unit::PIXELS, Improc::UNDISTORT, Interpolation::LINEAR, scale);
  
  for(int t=0;t<t_count;t++) {
    source_mats[t].create(CvDepth2BaseType(tmp.depth()), {tmp.size[2],tmp.size[1],tmp.size[0]});
  
    tensor_circuits.setSource(t, 0, &source_mats[t]);
    //FIXME not yet known, tick once?
  }  
  
  //Mat *epi_disp, *epi_coh;
  int done = 0;
  //FIXME third dimension should be derived from circuit!
  Idx size = {subset.EPIWidth(), subset.EPICount(), 1, subset.EPIHeight()};
  disp_mat = new Mat(BaseType::FLOAT, size);
  coh_mat = new Mat(BaseType::FLOAT, size);
  
  //store st-data (x*x ,x*y, y*y) for all epis
  //dims: x, y, line, st-component
  Mat st_data;
  Mat st_blur;
  
  float integrate_sigma = 5.0;
  int integrate_r = 3*integrate_sigma;
  
  int st_lines = stop_line-start_line;
  
  st_data.create(BaseType::FLOAT, {epi_w, epi_h, st_lines, 3});
  st_blur.create(BaseType::FLOAT, {epi_w, epi_h, st_lines, 3});
  
  vigra::MultiArrayView<4,float> st_data_v = vigraMAV<4,float>(st_data);
  vigra::MultiArrayView<4,float> st_blur_v = vigraMAV<4,float>(st_blur);
  
  
  int work = (2*(stop_line-start_line) + epi_h*3)*(disp_stop-disp_start+1);
  
  for(float d=disp_start;d<=disp_stop;d+=disp_step) {
printf("calc tensor\n");
#pragma omp parallel for
    for(int i=start_line;i<stop_line;i++) {
  #pragma omp critical 
      {
        progress_((float)done/work);
        done++;
      }
      
      int t = omp_get_thread_num();
      
      proc_epi_tensor(
        t,
        &subset, d, i, scale,
        source_mats,
        tensor_circuits,
        st_data_v,
        start_line
      );
    }
    
  printf("integrate 3d\n");
#pragma omp parallel for
    for(int c=0;c<3;c++)
      for(int i=0;i<epi_h;i++) {
  #pragma omp critical 
        {
          progress_((float)done/work);
          done++;
        }
        cv::Mat src = cvMat(st_data.bind(3, c).bind(1, i));
        cv::Mat dst = cvMat(st_blur.bind(3, c).bind(1, i));
        /*cv::Mat src2 = cvMat(st_data.bind(3, c).bind(1, i));
        cv::Mat dst2 = cvMat(st_blur.bind(3, c).bind(1, i));
        abort();*/
        cv::GaussianBlur(src, dst, cv::Size(1, integrate_r), 0.0, integrate_sigma);
      }
    
  printf("calc orientation\n");
#pragma omp parallel for
    for(int i=start_line;i<stop_line;i++) {
  #pragma omp critical 
      {
        progress_((float)done/work);
        done++;
      }
      
      int t = omp_get_thread_num();
      
      proc_epi_ori_merge(
        t,
        &subset, d, i, scale,
        st_blur_v,
        start_line,
        orientation_circuits,
        merge_circuits,
        disp_mat,
        coh_mat,
        d == disp_start, //first run
        d+disp_step > disp_stop //last run
      );
        
      //assert(epi_disp->type() == BaseType::FLOAT);
      
    }
  }
  
  
  
  assert(disp_mat);

  
  //FIXME write!
  Datastore *disp_store = out->data->addStore("disparity/default/data");
  disp_store->write(disp_mat);
  out->path = "disparity/default/data";
  delete disp_mat;
  
  
  //FIXME write!
  Datastore *coh_store = out->data->addStore("disparity/default/coherence");
  coh_store->write(coh_mat);
  //out->path = "disparity/default/coherence";
  delete coh_mat;
}

//FIXME remove alias for replaced sub-component!
bool COMP_Epi::ParameterUpdating_(int index, const DspParameter& param)
{
  const std::unordered_set<std::string> exclude_params = {"input_disparity","copy"};
  
  if (index == P_IDX::Tensor_Circuit) {
    DspComponent *comp;
    const DspParameter *p = GetParameter(P_IDX::Tensor_Circuit);
    p->GetPointer(comp);
    RemoveComponentAlias(comp);
    SetParameter_(index, param);
    param.GetPointer(comp);
    expose_params(this, "disparity", comp, exclude_params);
  }
  else if (index == P_IDX::Orientation_Circuit) {
    DspComponent *comp;
    const DspParameter *p = GetParameter(P_IDX::Orientation_Circuit);
    p->GetPointer(comp);
    RemoveComponentAlias(comp);
    SetParameter_(index, param);
    param.GetPointer(comp);
    expose_params(this, "orientation", comp, exclude_params);
  }
  else if (index == P_IDX::Merge_Circuit) {
    DspComponent *comp;
    const DspParameter *p = GetParameter(P_IDX::Merge_Circuit);
    p->GetPointer(comp);
    RemoveComponentAlias(comp);
    SetParameter_(index, param);
    param.GetPointer(comp);
    expose_params(this, "merge", comp, exclude_params);
  }
  else 
    //just store parameter 
    SetParameter_(index, param);

  //FIXME range chack should be implement at some central location
  
  return true;      
}

EXPORT_DSPCOMPONENT(COMP_Epi)
