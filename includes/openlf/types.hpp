#ifndef _OPENLF_TYPES_H
#define _OPENLF_TYPES_H

#include <clif/flexmav.hpp>
#include <clif/clif_vigra.hpp>

namespace openfl {

struct LF
{
  clif::Dataset *dataset;
  std::string path;
};

}

#endif