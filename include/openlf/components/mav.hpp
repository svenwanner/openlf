#ifndef _OPENLF_MAV_H
#define _OPENLF_MAV_H

#include "clif/flexmav.hpp"
#include "dspatch/DspComponent.h"

#include "clif/dataset.hpp"

namespace openlf {
  
class LF {
public:
  clif::Dataset *dataset;
  std::string path;
};

namespace components {
  


template<uint DIM> class FlexMAVSource : public DspComponent {
public:
  FlexMAVSource()
  {
    AddOutput_("output");
  }
  void set(clif::FlexMAV<DIM> &mav)
  {
    _mav = mav;
  }

protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs)
  {
    outputs.SetValue(0, _mav); 
  }
  
private:
  clif::FlexMAV<DIM> *_mav;
};

template<uint DIM> class FlexMAVSink : public DspComponent {
public:
  FlexMAVSink()
  {
    AddInput_("input");
  }
  clif::FlexMAV<DIM> get()
  {
    return _mav;
  }

protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs)
  {
    inputs.GetValue(0, _mav); 
  }
  
private:
  clif::FlexMAV<DIM> *_mav;
};

}} //namespace openlf::components

#endif