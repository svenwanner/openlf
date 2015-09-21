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

class LFSource : public DspComponent {
public:
  LFSource()
  {
    AddOutput_("output");
  }
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs)
  {
    const DspParameter *filepath = GetParameter(0);
    const DspParameter *set = GetParameter(1);
    
    ClifFile f_in(*filepath->GetString(), H5F_ACC_RDONLY);

    Dataset *out = f_in.openDataset(*set->GetInt());
    
    outputs.SetValue(0, out);
  }
};

class LFSink : public DspComponent {
public:
  LFSource()
  {
    AddOutput_("input");
  }
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs)
  {
    const DspParameter *filepath = GetParameter(0);
    
    ClifFile f_out(*filepath->GetString(), H5F_ACC_RDWR);

    //TODO implement flush
    //f_out.write();
  }
};

class LF2EPI : public DspComponent {
public:
  LFSource()
  {
    AddInput_("input");
    AddOutput_("LF");
    AddOutput_("EPI");
  }
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs)
  {

  }
};

class EPI2LF : public DspComponent {
public:
  LFSource()
  {
    AddInput_("input");
    AddOutput_("LF");
    AddOutput_("EPI");
  }
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs)
  {

  }
};

int main(const int argc, const char *argv[])
{
  DspCircuit circuit;
  
  LFSource source;
  GaussianBlur blur;
  
  LF2EPI epi_in;
  EPI2LF epi_out;
  
  circuit.AddComponent(source, "source");
  circuit.AddComponent(blur, "blur");
  circuit.AddComponent(epi_in, "epi_in");
  circuit.AddComponent(epi_out, "epi_out");
  
  circuit.ConnectOutToIn(source, 0, epi_in, 0);
  
  circuit.ConnectOutToIn(epi_in, 1, blur, 0);
  circuit.ConnectOutToIn(blur, 0, epi_out, 1);
  
  circuit.ConnectOutToIn(source, 0, epi_out, 0);
  
  //allocate data objects for signals
  openlf::circuitSetup(circuit);
  
  circuit.Tick();
  circuit.Reset();
  
  openlf::circuitBreakdown(circuit);
  
  return EXIT_SUCCESS;
}