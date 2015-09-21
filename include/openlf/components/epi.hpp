#ifndef _OPENLF_EPI_H
#define _OPENLF_EPI_H

#include "clif/flexmav.hpp"

#include "dspatch/DspComponent.h"
#include "dspatch/DspCircuit.h"

#include "mav.hpp"

namespace openlf { namespace components {

class EpiCircuit : public DspComponent {
public:
  EpiCircuit();
  
  //TODO discuss:: use method or settings from DSPatch?
  void set(DspCircuit *circuit);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  DspCircuit _circuit;
  FlexMAVSource<2> _source;
  FlexMAVSink  <2> _sink;
  clif::FlexMAV<2> _source_mav;
  clif::FlexMAV<2> _sink_mav;
  
  //user provided circuit (which has FlexMAV input and output)
  DspCircuit *_epi_circuit = NULL;
};

}} //namespace openlf::components

#endif