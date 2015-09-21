#ifndef _OPENLF_GAUSS_H
#define _OPENLF_GAUSS_H

#include <vigra/convolution.hxx>

#include "openlf.hpp"

namespace openlf { namespace components {

class GaussianBlur : public DspComponent {
public:
  GaussianBlur();
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
};

}} //namespace openlf::components

#endif