#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>

#include "openlf.hpp"

#include "clif/clif.hpp"
#include "clif/clif_vigra.hpp"
#include "clif/flexmav.hpp"
#include "comp_lfread.hpp"
#include "comp_lfwrite.hpp"
#include "comp_epi.hpp"
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
  
  DspCircuit graph;
  
  COMP_LFRead in;
  COMP_LFWrite out;
  COMP_Epi epi;
  
  
  OP_Test gauss;
  
  graph.AddComponent(in, "in");
  graph.AddComponent(out, "out");
  graph.AddComponent(epi, "epi");
  graph.ConnectOutToIn(in, 0, epi, 0);
  graph.ConnectOutToIn(epi, 0, out, 0);
  
  //epi.set(&gauss);
  
  in.SetParameter(0, DspParameter(DspParameter::ParamType::String, argv[1]));
  out.SetParameter(0, DspParameter(DspParameter::ParamType::String, argv[2]));
  
  graph.Tick();
  graph.Reset();
  
  return EXIT_SUCCESS;
}