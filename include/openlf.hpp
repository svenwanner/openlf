#ifndef _OPENLF_OPENLF_H
#define _OPENLF_OPENLF_H

#include "components/comp_mav.hpp"

#include "openlf/types.hpp"
#include "dspatch/DspComponent.h"
#include "dspatch/DspCircuit.h"

#include "operators/operators.hpp"
#include "operators/op_loadimage.hpp"
#include "components/comp_epi.hpp"
#include "components/comp_lfread.hpp"
#include "components/comp_lfwrite.hpp"
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
      
      _comp_list.push_back(new openlf::components::OP_VigraGauss);
      _comp_list.push_back(new openlf::components::OP_VigraGradientMagnitude);
      _comp_list.push_back(new openlf::components::OP_ScharrX);
      _comp_list.push_back(new openlf::components::OP_ScharrY);
      _comp_list.push_back(new openlf::components::OP_Scharr);
      _comp_list.push_back(new openlf::components::OP_Tensor2x2);
      _comp_list.push_back(new openlf::components::OP_AverageChannels);
      _comp_list.push_back(new openlf::components::OP_Tensor2Orientation);
      _comp_list.push_back(new openlf::components::OP_SaveImage);
      //_comp_list.push_back(new openlf::components::OP_LoadImage);
      _comp_list.push_back(new openlf::components::OP_MergeDispByCoherence);
    }
    
    return _comp_list;
  }
  
  static DspComponent *getComponentClone(const std::string &typeName)
  {
    std::vector<DspComponent*> list = componentList();
    
    for(auto it=list.begin();it!=list.end();++it)
      if (!typeName.compare((*it)->getTypeName()))
        return (*it)->clone();
  }
  
private:  
   OpenLF(OpenLF const&)          = delete;
   void operator=(OpenLF const&)  = delete;
};

#endif