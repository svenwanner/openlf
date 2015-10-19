#ifndef _OPENLF_OPENLF_H
#define _OPENLF_OPENLF_H

#include "openlf/types.hpp"
#include "dspatch/DspComponent.h"
#include "dspatch/DspCircuit.h"

#include "operators/operators.hpp"
#include "components/comp_epi.hpp"
#include "components/comp_lfread.hpp"
#include "components/comp_lfwrite.hpp"
#include "components/comp_mav.hpp"
#include "components/comp_dispwrite.hpp"

class OpenLF {
public:
  //TODO initialize this from list using cmake and/or plugin structure
  static const std::vector<DspComponent*> componentList()
  {
    static std::vector<DspComponent*> _comp_list;
    
    if (!_comp_list.size()) {
      _comp_list.push_back(new openlf::components::COMP_Epi);
      _comp_list.push_back(new openlf::components::COMP_LFRead);
      _comp_list.push_back(new openlf::components::COMP_LFWrite);
      _comp_list.push_back(new openlf::components::COMP_DispWrite);
    }
    
    return _comp_list;
  }
  
private:  
   OpenLF(OpenLF const&)          = delete;
   void operator=(OpenLF const&)  = delete;
};

#endif