#ifndef _OPENLF_TYPES_H
#define _OPENLF_TYPES_H

#include "clif/dataset.hpp"
#include "dspatch/DspCircuit.h"

namespace openlf {

class LF {
public:
  clif::Dataset *data;
  clif::cpath path;
  //time_t timestamp
};
/*
class OLFCircuit : public DspCircuit {
public:
  //clone must not share resoures - used for threading
  virtual OLFCircuit* clone() = 0;
protected:
  //add and set float paramtere
  inline int AddParameterFloat_(const char *name, float f)
  {
    DspParameter p(DspParameter::Float, f);
    //TODO ask DspPatch devs - shouldn't addparameter call parameterupdating by itself?
    int idx = AddParameter_(name, p);
    return idx;
  }
};*/

}

#endif