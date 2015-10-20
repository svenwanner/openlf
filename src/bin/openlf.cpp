#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>

#include "openlf.hpp"
#include "cliini.h"

using namespace openlf;
using namespace openlf::components;

cliini_opt opts[] = {
  {
    "help",
    0, //argcount
    0, //argcount
    CLIINI_NONE, //type
    0, //flags
    'h'
  },
  {
    "circuit",
    1, //argcount min
    1, //argcount max
    CLIINI_STRING, //type
    0, //flags
    'c'
  }
};

cliini_optgroup group = {
  opts,
  NULL,
  sizeof(opts)/sizeof(*opts),
  0,
  0
};

int main(const int argc, const char *argv[])
{
  cliini_args *args = cliini_parsopts(argc, argv, &group);

  cliini_arg *circuit_arg = cliargs_get(args, "circuit");
  
  if (!circuit_arg) {
    printf("FIXME print help\n");
    return EXIT_SUCCESS;
  }
  
  const char *c_name = cliarg_str(circuit_arg);
  DspCircuit *c = DspCircuit::load(c_name, &OpenLF::getComponentClone);
  
  if (!c)
    printf("could not load circuit from %s\n", c_name);
  else {
    printf("running circuit\n");
    c->Tick();
    c->Reset();
  }
  
  return EXIT_SUCCESS;
}