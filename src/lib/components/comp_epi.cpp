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
#include "clif/clif_vigra.hpp"
#include "comp_epi.hpp"
#include "operators.hpp"

#include "clif/subset3d.hpp"

#include "openlf/types.hpp"

#include <omp.h>

using namespace clif;
using namespace vigra;
using namespace std;

template<typename T> class save_flexmav3 {
public:
void operator()(FlexMAV<3> *img, const char *name)
{    
  MultiArrayView<3,T> *i = img->get<T>();
  MultiArrayView<2,T> channel = i->bindAt(2, 1);
  exportImage(channel, ImageExportInfo(name));
}
};

namespace openlf { namespace components {
  
COMP_Epi::COMP_Epi()
{
  AddInput_("input");
  AddOutput_("output");
  
  AddParameter_("epi circuit", DspParameter(DspParameter::ParamType::Pointer, (DspCircuit*)&_default_epi_circuit));
  AddParameter_("epi circuit name", DspParameter(DspParameter::ParamType::String, "default"));
  
  AddParameter_("merge circuit", DspParameter(DspParameter::ParamType::Pointer, (DspCircuit*)&_default_epi_circuit));
  AddParameter_("epi circuit name", DspParameter(DspParameter::ParamType::String, "default"));
}

template<typename T> class save_flexmav {
public:
void operator()(FlexMAV<2> *img, const char *name)
{    
  exportImage(*img->get<T>(), ImageExportInfo(name));
}
};

template<typename T> class subarray_copy {
public:
void operator()(int line, int epi_w, int epi_h, FlexMAV<3> *sink_mav, FlexMAV<4> *disp_store, float disp_scale)
{
  for(int c=0;c<sink_mav->shape()[2];c++) {
    MultiArrayView<2,T> sink = sink_mav->get<T>()->bindAt(2, c);
    MultiArrayView<3,T> store = disp_store->get<T>()->bindAt(3, c);
    
    for(int i=epi_h/2;i<epi_h/2+1;i++) {
      //bind store y to epi line
      MultiArrayView<2,T> epi = store.bindAt(1, line);
      epi = sink;
      if (disp_scale != 1.0)
        epi *= 1.0/disp_scale;
    }
  }
}
};

void COMP_Epi::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  LF *out = NULL;
  
  assert(inputs.GetValue(0, in));
  
  out = new LF();
  out->data = new Dataset();
  out->data->memory_link(in->data);
  
  outputs.SetValue(0, out);
  
  assert(in);
  assert(out);
  
  //TODO get settings using DSPatch routines...
  float disparity = 6.3;
  int subset_idx = 0; //we could also loop over all subsets or specify subset using string name
  
  //subset_idx -- extrinsics path
  Subset3d subset(in->data, subset_idx);
  
  FlexMAV<4> *disp_store = NULL;
  
  int epi_w = subset.EPIWidth();
  int epi_h = subset.EPIHeight();
  
  float scale = 1.0;
  
  //setup circuit and threading
  
  int t_count = omp_get_max_threads();

  const DspParameter *p;
  DspCircuit *epi_circuit;
  const std::string *epi_name;
  
  p = GetParameter(0);
  assert(p);
  p->GetPointer(epi_circuit);
  
  p = GetParameter(1);
  assert(p);
  epi_name = p->GetString();
  
  
  vector<FlexMAVSource<3>> comp_source(t_count);
  vector<FlexMAVSink<3>>   comp_sink(t_count);
  vector<clif::FlexMAV<3>> mav_source(t_count);
  vector<OP_MergeDispByCoherence> merge(t_count);
  
  //epi_circuit->SetParameter(3, DspParameter(DspParameter::ParamType::Float, 0.95f));
  
 // epi_circuit->SetParameter(1, DspParameter(DspParameter::ParamType::Float, 0.0f));
  
  epi_circuit->SetParameter(2, DspParameter(DspParameter::ParamType::Float, 1.0f));
  epi_circuit->SetParameter(5, DspParameter(DspParameter::ParamType::Float, 27.0f));
  
  //FIXME delete!
  vector<DspComponent*>  epi_circuits(t_count);
  vector<DspCircuit>   outer_circuit(t_count);
  for(int i=0;i<t_count;i++) {
    epi_circuits[i] = epi_circuit->clone();
    
    outer_circuit[i].AddComponent(comp_source[i], "source");
    outer_circuit[i].AddComponent(epi_circuits[i], "epi");  
    outer_circuit[i].AddComponent(comp_sink[i], "sink");
    //temp
    outer_circuit[i].AddComponent(merge[i], "merge");  
    
    outer_circuit[i].ConnectOutToIn(comp_source[i], 0, epi_circuits[i], 0);
    //temp
    //outer_circuit[i].ConnectOutToIn(epi_circuits[i], 0, comp_sink[i], 0);
    outer_circuit[i].ConnectOutToIn(epi_circuits[i], 0, merge[i], 0);
    outer_circuit[i].ConnectOutToIn(epi_circuits[i], 1, merge[i], 1);
    outer_circuit[i].ConnectOutToIn(merge[i], 0, comp_sink[i], 0);
    
    comp_source[i].set(&mav_source[i]);
  }
  
  FlexMAV<3> *sink_mav;
      
  #pragma omp parallel for private(sink_mav)
  for(int i=380;i<480/*subset.EPICount()*/;i++) {
    if (i % 10 == 0)
      printf("proc epi %d\n", i);
    
    merge[omp_get_thread_num()].SetParameter(0, DspParameter(DspParameter::ParamType::Bool, true));
    
    for(float d=3.0f;d<=7.0f;d+=1.0f) {
      epi_circuits[omp_get_thread_num()]->SetParameter(0, DspParameter(DspParameter::ParamType::Float, d));
      
      #pragma omp critical
      readEPI(&subset, mav_source[omp_get_thread_num()], i, d, ClifUnit::PIXELS, UNDISTORT, Interpolation::LINEAR, scale);
      
      //tick the circuit to fill _sink_mav using _source_mav and the circuit
      outer_circuit[omp_get_thread_num()].Tick();
      outer_circuit[omp_get_thread_num()].Reset();
      
      merge[omp_get_thread_num()].SetParameter(0, DspParameter(DspParameter::ParamType::Bool, false));
    }
    
    sink_mav = comp_sink[omp_get_thread_num()].get();
    assert(sink_mav->type() == BaseType::FLOAT);
    
    //TODO this should not be necessary
    #pragma omp critical
    if (!disp_store)
      disp_store = new FlexMAV<4>(Shape4(subset.EPIWidth(), subset.EPICount(), subset.EPIHeight(), sink_mav->shape()[2]), sink_mav->type());
    
    disp_store->call<subarray_copy>(i,epi_w,epi_h,sink_mav,disp_store,scale);
    
  }
  
/*#pragma omp parallel for private(sink_mav)
  for(int i=0;i<subset.EPICount();i++) {
    if (i % 10 == 0)
      printf("proc epi %d\n", i);
#pragma omp critical
    readEPI(&subset, mav_source[omp_get_thread_num()], i, disparity, ClifUnit::PIXELS, UNDISTORT, Interpolation::LINEAR, scale);
    
    //tick the circuit to fill _sink_mav using _source_mav and the circuit
    outer_circuit[omp_get_thread_num()].Tick();
    outer_circuit[omp_get_thread_num()].Reset();
    
    sink_mav = comp_sink[omp_get_thread_num()].get();
    assert(sink_mav->type() == BaseType::FLOAT);

//TODO this should not be necessary
#pragma omp critical
    if (!disp_store)
      disp_store = new FlexMAV<4>(Shape4(subset.EPIWidth(), subset.EPICount(), subset.EPIHeight(), sink_mav->shape()[2]), sink_mav->type());
    
    disp_store->call<subarray_copy>(i,epi_w,epi_h,sink_mav,disp_store,scale);
    
  }*/
  
  out->path = std::string("disparity/default/data");
  Datastore *datastore = out->data->addStore("disparity/default/data");
  disp_store->write(datastore);
  
  delete disp_store;
}

}} //namespace openlf::components
