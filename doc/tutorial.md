[TOC]

OpenLF Tutorial 1 - A First Component {#Tutorial}
======

This tutorial will teach you how to create your first high level %OpenLF component, which operates at the clif::Dataset level (TODO ref). The tutorial is split into three parts:
- \ref new - setup build system and source
- \ref comp - implementing a component
- \ref use - usage in OpenLF

## Step 1 : Setup the Project {#new}

If you haven't done so, set up clif and openlf according to [the readme](@ref index)


## Step 2 : A First Component {#comp}


## Header

```cpp
#ifndef _OPENLF_COMP_TUTORIAL_H
#define _OPENLF_COMP_TUTORIAL_H

#include "dspatch/DspComponent.h"

namespace openlf { namespace components {

class COMP_Tutorial : public DspComponent {
public:
  COMP_Tutorial();
  DSPCOMPONENT_TRIVIAL_CLONE(COMP_Tutorial);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:  
  bool ParameterUpdating_(int index, const DspParameter& param);
};

}} //namespace openlf::components

#endif
```

### Explanation

```cpp
#ifndef _OPENLF_COMP_TUTORIAL_H
#define _OPENLF_COMP_TUTORIAL_H

#include "dspatch/DspComponent.h"
```
Standard include guard and required header.

```cpp
namespace openlf { namespace components {
```
All components should go into openlf::components.

```cpp
class COMP_Tutorial : public DspComponent {
```
To create a new component we always derive from DspComponent.

```cpp
COMP_Tutorial();
```
Our constructor.

```cpp
DSPCOMPONENT_TRIVIAL_CLONE(COMP_Tutorial);
```
This is a macro which implements \a ::clone() by creating a new instance with **new** and then applies all parameters to the new instance. This should be sufficient for almost all cases. Clone is used by OpenLF to implement threading, as well as by the GUI to interactively add new components.


```cpp
virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
```
This method will implement the actual processing.

```cpp
bool ParameterUpdating_(int index, const DspParameter& param);
```
This method will be called when parameters are changed.

## Implementation

```cpp
#include "comp_tutorial.hpp"
#include "types.hpp"

using namespace clif;

namespace openlf { namespace components {

COMP_Tutorial::COMP_Tutorial()
{
  setTypeName_("tutorial");
  AddInput_("input");
  AddOutput_("output");
  
  AddParameter_("path", DspParameter(DspParameter::ParamType::String));
  AddParameter_("message", DspParameter(DspParameter::ParamType::String));
}

void COMP_Tutorial::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  LF *out = NULL;
  const std::string *path;
  const std::string *message;

  //get input and produce error if not available
  errorCond(inputs.GetValue(0, in)); RETURN_ON_ERROR

  //get settings
  path = GetParameter(0)->GetString();
  message = GetParameter(1)->GetString();

  //check for errors
  errorCond(path); RETURN_ON_ERROR
  errorCond(message); RETURN_ON_ERROR

  //create output LF dataset by linking input
  out = new LF();
  out->data = new Dataset();
  out->data->memory_link(in->data);
  outputs.SetValue(0, out);

  //skip actual processing
  if (configOnly())
    return;

  //create attribute for path
  Attribute attr(*path);
  //set message
  attr.set(message->c_str());
  //append to output dataset
  out->data->append(attr);
}

bool COMP_Tutorial::ParameterUpdating_(int index, const DspParameter& param)
{  
  //just store parameter 
  return SetParameter_(index, param);
}

}} //namespace openlf::components
```

### Explanation

```cpp
COMP_Tutorial::COMP_Tutorial()
{
  setTypeName_("tutorial");
  AddInput_("input");
  AddOutput_("output");

  AddParameter_("path", DspParameter(DspParameter::ParamType::String));
  AddParameter_("message", DspParameter(DspParameter::ParamType::String));
}
```
This is the constructor. The only mandatory part is *setTypeName()*, which will be used display our new component and identify it when storing circuits. Inputs and outputs are added with *AddInput_()*, *AddOutput_()* respectively, add as many inputs and outputs as desired.
*AddParameter_()* adds a new Paramter and specifies the type. You can also pass default values by using for example: `DspParameter(DspParameter::ParamType::Int, 17)`.


```cpp
void COMP_Tutorial::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  LF *out = NULL;
  const std::string *path;
  const std::string *message;
```
This marks the begin of our actual component implementation. *inputs* and *outputs* contain the input and output signals which are connected to different components. *LF* contains an actual clif::Dataset and an optional string to specify some component of the dataset.

```cpp
  //get input and produce error if not available
  errorCond(inputs.GetValue(0, in)); RETURN_ON_ERROR
```
*inputs.GetValue(0, in)* reads the first input into *in* if *in* is of the same type as got passed from the connected component. If *GetValue()* is successfull true is return, else false.

*errorCond()* provides error checking by setting an error on our component if the passed condition is false. You can also pass an error message as second parameter which can be displayed by the GUI. The error state can be checked with *hasError()*. 

Components can be executed in two modes, the method configOnly() shows wether this is only a configuration run or the actual execution. Config runs are used to find and display errors prior to actual execution, therefore only simple error checking and parameter passing should be executed if *configOnly()* returns true.

*RETURN_ON_ERROR* combines error checking with the config state and simply returns from the caller if there is an error in a config run, and aborts if an error is detected in actual execution. This macro should always be used, as it will later implement more advanced error handling.

```cpp
  //get settings
  path = GetParameter(0)->GetString();
  message = GetParameter(1)->GetString();

  //check for errors
  errorCond(path); RETURN_ON_ERROR
  errorCond(message); RETURN_ON_ERROR
```
Get parameters and check for errors again.

```cpp
  //create output LF dataset by linking input
  out = new LF();
  out->data = new Dataset();
  out->data->memory_link(in->data);
  outputs.SetValue(0, out);
```
Create our output and store it in outpus using *SetValue()*. *memory_link* will create a shallow copy of the dataset in memory. Only newly added elements will actually be stored in the dataset, all others will be linked from the original dataset. This is also partly true if the dataset is stored on disk again. In that case soft links within the hdf5 file are used to reference the original data, though this is true only for all hdf5 datasets (= clif::Datastore) within the file, all attributes are actually copied.

```cpp
  //skip actual processing
  if (configOnly())
    return;
```
We are now finished with the preparations, if we are in config mode we return now to skip any actual processing.

```cpp
  //create attribute for path
  Attribute attr(*path);
  //set message
  attr.set(message->c_str());
  //append to output dataset
  out->data->append(attr);
}
```
This is the code which represents our (quite heavy) processing. We simply create a new *clif::Attribute* for the specified path, store our message and append the attribute to our dataset.

```cpp
bool COMP_Tutorial::ParameterUpdating_(int index, const DspParameter& param)
{  
  //just store parameter 
  return SetParameter_(index, param);
}
```
This method must be implemented if we need any parameters. This implementation simply passes through the parameter, if desired more complex checks can be implemented checking parameter type and content and returning false when problems are found.

### Build

We will now add the component to the build system:
- Store the header in in *include/openlf/components/* for example as *comp_tutorial.hpp* and the implementation in *src/components/*.
- add the implementation to the list in src/components/CMakeLists.txt, so it will actually be compiled
- in *include/openlf.hpp* add our new header to the long list of includes at the top and our new component to the global \a _comp_list.
- rebuild the project and test the new component with the LF_Toolbox!

## Step 3 : Using external Components {#use}