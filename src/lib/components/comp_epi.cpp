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
#include "comp_epi.hpp"

#include "clif/subset3d.hpp"

#include "openlf/types.hpp"

using namespace clif;
using namespace vigra;

template<typename T> class save_flexmav {
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
  
  _circuit.AddComponent(_source, "source");
  _circuit.AddComponent(_sink, "sink");
  _circuit.ConnectOutToIn(_source, 0, _sink, 0);
}
  
void COMP_Epi::set(DspComponent *circuit)
{
  if (_epi_circuit)
    _circuit.RemoveComponent(_epi_circuit);
  
  _epi_circuit = circuit;
  _circuit.AddComponent(_epi_circuit, "epi_circuit");
  _circuit.ConnectOutToIn(_source, 0, _epi_circuit, 0);
  _circuit.ConnectOutToIn(_epi_circuit, 0, _sink, 0);
}

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
  double disparity = 5;
  int subset_idx = 0; //we could also loop over all subsets or specify subset using string name
  
  Subset3d subset(in->data, subset_idx);
  
  _source.set(&_source_mav);
  
  FlexMAV<3> *sink_mav;
  
  for(int i=0;i<subset.EPICount();i++) {
    printf("proc epi %d\n", i);
    readEPI(&subset, _source_mav, i, disparity);
    
    //tick the circuit to fill _sink_mav using _source_mav and the circuit
    _circuit.Tick();
    _circuit.Reset();
    
    
    if (i == 1000) {
      sink_mav = _sink.get();
      sink_mav->call<save_flexmav>(sink_mav, "oneepi.tiff");
    }
    
  }
  //TODO store whatever we accumulated into the clif file 
}

}} //namespace openlf::components
