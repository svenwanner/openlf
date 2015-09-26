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
#include <vigra/impex.hxx>
#include "clif/clif_vigra.hpp"
#include "comp_epi.hpp"

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
  
  /*_circuit.AddComponent(_source, "source");
  _circuit.AddComponent(_sink, "sink");
  _circuit.ConnectOutToIn(_source, 0, _sink, 0);*/
}
  
void COMP_Epi::set(OLFCircuit *circuit)
{
  /*if (_epi_circuit)
    _circuit.RemoveComponent(_epi_circuit);*/
  
  _epi_circuit = circuit;
  /*_circuit.AddComponent(_epi_circuit, "epi_circuit");
  _circuit.ConnectOutToIn(_source, 0, _epi_circuit, 0);
  _circuit.ConnectOutToIn(_epi_circuit, 0, _sink, 0);*/
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
void operator()(int line, int epi_w, int epi_h, FlexMAV<3> *sink_mav, FlexMAV<4> *disp_store, float disp_offset, float disp_scale)
{
  for(int c=0;c<sink_mav->shape()[2];c++) {
    MultiArrayView<2,T> sink = sink_mav->get<T>()->bindAt(2, c);
    MultiArrayView<3,T> store = disp_store->get<T>()->bindAt(3, c);
    
    for(int i=epi_h/2;i<epi_h/2+1;i++) {
      //bind store y to epi line
      MultiArrayView<2,T> epi = store.bindAt(1, line);
      epi = sink;
      epi += disp_offset;
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
  double disparity = 6.3;
  int subset_idx = 0; //we could also loop over all subsets or specify subset using string name
  
  //subset_idx -- extrinsics path
  Subset3d subset(in->data, subset_idx);
  
  FlexMAV<4> *disp_store = NULL;
  
  int epi_w = subset.EPIWidth();
  int epi_h = subset.EPIHeight();
  
  float scale = 1.0;
  
  //setup circuit and threading
  
  int t_count = omp_get_max_threads();
  /*
   * DspCircuit _circuit;
  FlexMAVSource<3> _source;
  FlexMAVSink  <3> _sink;
  clif::FlexMAV<3> _source_mav;*/
  
  vector<FlexMAVSource<3>> comp_source(t_count);
  vector<FlexMAVSink<3>>   comp_sink(t_count);
  vector<clif::FlexMAV<3>> mav_source(t_count);
  
  vector<OLFCircuit*>  epi_circuits(t_count);
  vector<DspCircuit>   outer_circuit(t_count);
  for(int i=0;i<t_count;i++) {
    epi_circuits[i] = _epi_circuit->clone();
    
    outer_circuit[i].AddComponent(comp_source[i], "source");
    outer_circuit[i].AddComponent(epi_circuits[i], "epi");
    outer_circuit[i].AddComponent(comp_sink[i], "sink");
    
    outer_circuit[i].ConnectOutToIn(comp_source[i], 0, epi_circuits[i], 0);
    outer_circuit[i].ConnectOutToIn(epi_circuits[i], 0, comp_sink[i], 0);
    
    comp_source[i].set(&mav_source[i]);
  }
  
  FlexMAV<3> *sink_mav;
  
#pragma omp parallel for private(sink_mav)
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
    
    /*if (i == 1000) {
      sink_mav->call<save_flexmav3>(sink_mav, "oneepi.tiff");
    }*/
    
    //disp_store.subarray(Shape2(0,i),Shape2(epi_w,i+1)) = sink_mav->subarray(Shape3(0,epi_h/2,0),Shape3(epi_w,epi_h/2+1));
    
    //bind color to green (for now)
    //FlexMAV<2> sink_mav = sink_mav_temp->bindAt(2, 1);
//TODO this should not be necessary
#pragma omp critical
    if (!disp_store)
      disp_store = new FlexMAV<4>(Shape4(subset.EPIWidth(), subset.EPICount(), subset.EPIHeight(), sink_mav->shape()[2]), sink_mav->type());
    
    disp_store->call<subarray_copy>(i,epi_w,epi_h,sink_mav,disp_store,disparity,scale);
    
  }
  
  out->path = std::string("disparity/default/data");
  Datastore *datastore = out->data->addStore("disparity/default/data");
  disp_store->write(datastore);
  
  delete disp_store;
}

}} //namespace openlf::components
