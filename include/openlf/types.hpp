#ifndef _OPENLF_TYPES_H
#define _OPENLF_TYPES_H

#include "clif/dataset.hpp"
#include "dspatch/DspCircuit.h"

namespace openlf {

class LF {
public:
  clif::Dataset *data;
  clif::path path;
  //time_t timestamp
};

class OLFCircuit : public DspCircuit {
public:
  //clone must not share resoures - used for threading
  virtual OLFCircuit* clone() = 0;
};

}

#endif