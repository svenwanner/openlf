#ifndef _OPENLF_OPENLF_H
#define _OPENLF_OPENLF_H

#include <vector>
#include <string>

class DspComponent;

class OpenLF {
public:
  //TODO initialize this from list using cmake and/or plugin structure
  static const std::vector<DspComponent*> componentList();
  static DspComponent *getComponent(const std::string &typeName);
  
private:  
   OpenLF(OpenLF const&)          = delete;
   void operator=(OpenLF const&)  = delete;
};

#endif