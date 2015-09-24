#ifndef _OPENLF_TYPES_H
#define _OPENLF_TYPES_H

#include "clif/dataset.hpp"

namespace openlf {

class LF {
public:
  clif::Dataset *data;
  clif::path path;
  //time_t timestamp
};

}

#endif