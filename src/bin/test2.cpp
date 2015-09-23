#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>

#include "openlf.hpp"

#include "clif/clif.hpp"
#include "clif/clif_vigra.hpp"
#include "clif/flexmav.hpp"
#include "comp_mav.hpp"
#include "operators.hpp"


using namespace clif;
using namespace vigra;
using namespace openlf::components;

template<typename T> class save_flexmav {
public:
void operator()(FlexMAV<2> *img, const char *name)
{    
  exportImage(*img->get<T>(), ImageExportInfo(name));
}
};

int main(const int argc, const char *argv[])
{
  assert(argc == 3);
  
  ClifFile f(argv[1], H5F_ACC_RDONLY);
  Dataset *set = f.openDataset();
  
  Subset3d *subset = new Subset3d(set);
  
  FlexMAV<2> source;
  FlexMAV<2> *sink;
  
  FlexMAVSource<2> comp_source;
  FlexMAVSink  <2> comp_sink;
  OP_VigraGauss comp_gauss;
  
  DspCircuit outer_circuit;
  outer_circuit.AddComponent(comp_source, "source");
  outer_circuit.AddComponent(comp_sink, "sink");
  outer_circuit.AddComponent(comp_gauss, "blur");
  
  comp_gauss.SetParameter(0, DspParameter(DspParameter::ParamType::Float, 21.0f));
  comp_gauss.SetParameter(1, DspParameter(DspParameter::ParamType::Float, 21.0f));
  
  outer_circuit.ConnectOutToIn(comp_source, 0, comp_gauss, 0);
  outer_circuit.ConnectOutToIn(comp_gauss, 0, comp_sink, 0);
  
  readEPI(subset, 1, source, 100, 5.0);
      
  //outer_circuit.Tick();
  
  comp_source.set(&source);
  
  outer_circuit.Tick();
  
  sink = comp_sink.get();
  
  sink->call<save_flexmav>(sink, argv[2]);
  
  return EXIT_SUCCESS;
}