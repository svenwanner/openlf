#include "op_gauss.hpp"

#include "vigra/convolution.hxx"
#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>

#include "clif/flexmav.hpp"



namespace openlf { namespace components {

using namespace vigra;
using namespace clif;

//anonymous namespace to hide dispatcher
namespace {

template<typename T> class op_gauss_dispatcher {
public:
  void operator()(FlexMAV<2> *in_mav, FlexMAV<2> *out_mav)
  {
    MultiArrayView<2,T> *in = in_mav->template get<T>();
    MultiArrayView<2,T> *out = out_mav->template get<T>();
    
    gaussianSmoothing(*in, *out, 5.0, 5.0);
  }
};

}

OP_Gauss::OP_Gauss()
{
  AddInput_("input");
  AddOutput_("output");
}

void OP_Gauss::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  bool stat;
  FlexMAV<2> *in;
  
  stat = inputs.GetValue(0, in);
  assert(stat);
  assert(stat);
  
  FlexMAV<2> *out_ptr = &_output_image;
  
  _output_image.create(in->shape(), in->type());

  in->call<op_gauss_dispatcher>(in, out_ptr);
  
  stat = outputs.SetValue(0, out_ptr);
}

}} //namespace openlf::components