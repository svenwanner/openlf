#include "openlf.hpp"

#include "components/comp_mav.hpp"

#include "openlf/types.hpp"
#include "dspatch/DspComponent.h"
#include "dspatch/DspCircuit.h"
#include "dspatch/DspPluginLoader.h"

#include "operators/operators.hpp"
#include "operators/op_loadimage.hpp"
#include "components/comp_epi.hpp"
#include "components/comp_lfwrite.hpp"
#include "components/comp_dispwrite.hpp"

#include <dirent.h>

const std::vector<DspComponent*> OpenLF::componentList()
{
  static std::vector<DspComponent*> _comp_list;
  
  if (!_comp_list.size()) {
    std::vector<path> plugin_paths;
    std::vector<path> comp_paths;
    
    
    _comp_list.push_back(new openlf::components::COMP_Epi);
    //_comp_list.push_back(new openlf::components::COMP_LFRead);
    _comp_list.push_back(new openlf::components::COMP_LFWrite);
    //_comp_list.push_back(loader.Create(emptymap));
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

    const char *c_path = getenv("OPENLF_COMPONENT_PATH");
    printf("plugin path: %s\n", c_path);
    std::string path;
#if _WIN32
    const char delimiter = ';';
#else
    const char delimiter = ':';
#endif

    if (!c_path || !strlen(c_path)) {
      printf("OpenLF: no plugin path found!\n");
      return _comp_list;
    }
    else
      path = std::string(c_path);

    int last = 0;
    int found = path.find(delimiter);
    while(found != std::string::npos)
    {
        plugin_paths.push_back(path.substr(last, found-last));
        last=found+1;
        found = path.find(delimiter, last);
    }
    if (path.size())
      plugin_paths.push_back(path.substr(last));
    
    DIR *dir;
    struct dirent *d_it;
    for(int i=0;i<plugin_paths.size();i++) {
      dir = opendir(plugin_paths[i].string().c_str());
      if (!dir)
        continue;
      
      while ((d_it = readdir(dir)) != NULL)
        comp_paths.push_back(plugin_paths[i] / d_it->d_name);
      closedir (dir);
    }

    DspComponent *comp;
    for(int i=0;i<comp_paths.size();i++) {
      printf("loading plugin %s\n", comp_paths[i].string().c_str());
      DspPluginLoader *loader = new DspPluginLoader(comp_paths[i].string());
      if (!loader->IsLoaded()) {
        //FIXME error msg
        printf("error loading %s!\n", comp_paths[i].c_str());
        continue;
      }
      comp = loader->Create();
      if (!comp) {
        //FIXME error msg
        printf("error creating component!\n");
        continue;
      }
      _comp_list.push_back(comp);
    }
  }
  
  return _comp_list;
}

DspComponent *OpenLF::getComponent(const std::string &typeName)
{
  std::vector<DspComponent*> list = componentList();
  
  for(auto it=list.begin();it!=list.end();++it)
    if (!typeName.compare((*it)->getTypeName())) {
      DspComponent *comp = *it;
      return comp->clone();
    }
    
  return NULL;
}