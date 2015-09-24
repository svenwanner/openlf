#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>

#include "openlf.hpp"

#include "clif/clif.hpp"
#include "clif/clif_vigra.hpp"
#include "clif/flexmav.hpp"
#include "comp_mav.hpp"
#include "wkf_structuretensor.hpp"

#include "clif/clif.hpp"

#include <H5Cpp.h>
#include <H5File.h>

using namespace clif;
using namespace vigra;
using namespace openlf::components;

//template<typename T> class save_flexmav {
//public:
//void operator()(FlexMAV<3> *img, const char *name)
//{    
//  //exportImage(*img->get<T>(), ImageExportInfo(name));
//}
//};

template<typename T> class save_flexmav {
public:
void operator()(FlexMAV<3> *img, const char *name)
{    
  MultiArrayView<3,T> *i = img->get<T>();
  MultiArrayView<2,T> channel = i->bindAt(2, 1);
  exportImage(channel, ImageExportInfo(name));
}
};

int main(const int argc, const char *argv[])
{
  assert(argc == 3);
  
  // create clif dataset
  ClifFile f(argv[1]);
  Dataset *set = f.openDataset();
  
  // get slice of clif dataset
  Subset3d *subset = new Subset3d(set);
  
  // define outer sink and source
  FlexMAV<3> source;
  FlexMAV<3> *sink;
  
  // define outer components
  FlexMAVSource<3> comp_source;
  FlexMAVSink  <3> comp_sink;
  
  // add outer component slots to outer circuit
  DspCircuit outer_circuit;
   // define inner circuit to keep programm flow
  WKF_StructureTensor circ_structuretensor;
  //OP_Gauss circ_structuretensor;

  //add components to circuit
  outer_circuit.AddComponent(comp_source, "source");
  outer_circuit.AddComponent(comp_sink, "sink");
  outer_circuit.AddComponent(circ_structuretensor, "structureTensor");
  
  // connect outer source and sink
  outer_circuit.ConnectOutToIn(comp_source, 0, circ_structuretensor, 0);
  outer_circuit.ConnectOutToIn(circ_structuretensor, 0, comp_sink, 0);
  
  // read epi data into source

  readEPI(subset, source, 1000, 3.5);
      
  //outer_circuit.Tick();
  
  // set incoming data
  comp_source.set(&source);
  
  // emit tick
  outer_circuit.Tick();
  
  // get results
  sink = comp_sink.get();
  
  // save results
  sink->call<save_flexmav>(sink, argv[2]);
  
  return EXIT_SUCCESS;
}
