#include "openlf.hpp"

#include "openlf/comp_mav.hpp"

#include <boost/filesystem.hpp>
#include "dirent.h"

#include "openlf/types.hpp"

#include "dspatch/DspComponent.h"
#include "dspatch/DspCircuit.h"
#include "dspatch/DspPluginLoader.h"



const std::vector<DspComponent*> OpenLF::componentList()
{
  static bool _loaded = false;
  static std::vector<DspComponent*> _comp_list;
  
  if (!_loaded) {
    _loaded = true;
    std::vector<boost::filesystem::path> plugin_paths;
    std::vector<boost::filesystem::path> comp_paths;

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
		printf("plugin path: %s\n", plugin_paths[i].string().c_str());
      dir = opendir(plugin_paths[i].string().c_str());
      if (!dir)
        continue;
      
      while ((d_it = readdir(dir)) != NULL)
        comp_paths.push_back(plugin_paths[i] / d_it->d_name);
      closedir (dir);
    }

    DspComponent *comp;
    //first load component dll's
    for(int i=0;i<comp_paths.size();i++) {
      printf("loading component from file %s\n", comp_paths[i].string().c_str());

      
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
    
    //then load circuits
    //FIXME what if circuit requires itself some circuit to be loaded?
    for(int i=0;i<comp_paths.size();i++) {
      if (comp_paths[i].extension().string().compare(".gml"))
        continue;
      
      printf("loading circuit file %s\n", comp_paths[i].string().c_str());
      comp = DspCircuit::load(comp_paths[i].string(), &getComponent);
      if (!comp) {
        //FIXME error msg
        printf("error loading circuit!\n");
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