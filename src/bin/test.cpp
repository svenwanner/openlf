#include "openlf.hpp"

#include <vigra/convolution.hxx>

using namespace vigra;
using namespace clif;

template<typename T> class gaussian_blur_dispatcher {
public:
  void operator()(FlexMAV<2> *in_mav, FlexMAV<2> *out_mav)
  {
    MultiArrayView<2,T> *in = in_mav->template get<T>();
    MultiArrayView<2,T> *out = out_mav->template get<T>();
    
    gaussianSmoothing(*in, *out, 3.0, 3.0);
  }
};

//FlexMAV
class GaussianBlur : public DspComponent {
public:
  GaussianBlur()
  {
    AddInput_("input");
    AddOutput_("output");
  }
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs)
  {
    FlexMAV<2> *in;
    FlexMAV<2> *out;
    
    inputs.GetValue(0, in);
    outputs.GetValue(0, out);
    
    in->call<gaussian_blur_dispatcher>(in, out);
  }
};