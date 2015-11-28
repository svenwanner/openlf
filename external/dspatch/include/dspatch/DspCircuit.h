/************************************************************************
DSPatch - Cross-Platform, Object-Oriented, Flow-Based Programming Library
Copyright (c) 2012-2015 Marcus Tomlinson

This file is part of DSPatch.

GNU Lesser General Public License Usage
This file may be used under the terms of the GNU Lesser General Public
License version 3.0 as published by the Free Software Foundation and
appearing in the file LGPLv3.txt included in the packaging of this
file. Please review the following information to ensure the GNU Lesser
General Public License version 3.0 requirements will be met:
http://www.gnu.org/copyleft/lgpl.html.

Other Usage
Alternatively, this file may be used in accordance with the terms and
conditions contained in a signed written agreement between you and
Marcus Tomlinson.

DSPatch is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
************************************************************************/

#ifndef DSPCIRCUIT_H
#define DSPCIRCUIT_H

//-------------------------------------------------------------------------------------------------

#include <dspatch/DspComponent.h>
#include <dspatch/DspWireBus.h>
#include <dspatch/DspCircuitThread.h>
#include <stdint.h>

//=================================================================================================
/// Workspace for adding and routing components

/**
DspComponents can be added to a DspCircuit and routed to and from other DspComponents. When a
DspComponent is added to a DspCircuit, a unique string ID is optional. This name can be used to
identify the component within the circuit's component collection. ConnectOutToIn and
DisconnectOutToIn provide a means of routing component outputs to other component inputs, while
ConnectInToIn / DisconnectInToIn and ConnectOutToOut / DisconnectOutToOut route the circuit's IO
signals to and from it's internal components.

*N.B. Each component input can only accept one wire at a time. When another wire is connected to an
input that already has a connected wire, that wire is replaced with the new one. One output, on the
other hand, can be distributed to multiple inputs.

For process intensive circuits, multi-threaded processing can be enabled via the SetThreadCount()
method. DspCircuit allows the user to specify the number of threads in which he/she requires the
circuit to process (0 threads: multi-threading disabled). A circuit's thread count can be adjusted
at runtime, allowing the user to increase / decrease the number of threads as required during
execution.

DspCircuit is derived from DspComponent and therefore inherits all DspComponent behavior. This
means that a DspCircuit can be added to, and routed within another DspCircuit as a component. This
also means a circuit object needs to be Tick()ed and Reset()ed as a component (see DspComponent).
The DspCircuit Process_() method simply runs through it's internal array of components and calls each
component's Tick() and Reset() methods.
*/

#include <unordered_map>

class Alias_List {
public:
  int count() const { printf("aliases: %d\n", _list.size()); return _list.size(); }
  
  void add(DspComponent *c, int i, std::string alias)
  {    
    std::vector<std::pair<DspComponent*,int>> *v = NULL;
    
    if (!alias.size())
      return;
    
    if (_map.count(alias))
      v = _map[alias];
    else {
      v = new std::vector<std::pair<DspComponent*,int>>();
      _list.push_back(std::make_pair(alias,v));
      _map[alias] = v;
    }
    
    v->push_back(std::make_pair(c,i));
  }
  
  void remove(DspComponent *c)
  {  
    for(auto a_v_pair : _list) {
      for(auto p : *a_v_pair.second)
        if (c == p.first) {
          remove(c, p.second, a_v_pair.first);
        }
    }
  }
  
  void remove(DspComponent *c, int i)
  {  
    for(auto a_v_pair : _list) {
      for(auto p : *a_v_pair.second)
        if (c == p.first && i == p.second) {
          remove(c, i, a_v_pair.first);
        }
    }
  }
  
  void remove(DspComponent *c, int index, std::string alias)
  {
    std::vector<std::pair<DspComponent*,int>> *v;
    
    if (!_map.count(alias))
      abort();
    
    v = _map[alias];
    
    for(int i=0;i<v->size();i++)
      if ((*v)[i].first == c && (*v)[i].second == index)
        v->erase(v->begin()+i);
      
    if (!v->size()) {
      _map.erase(alias);
      
      for(int i=0;i<_list.size();i++)
        if (_list[i].second == v) {
          _list.erase(_list.begin()+i);
        }
        
      delete v;
    }
  }
  
  std::string get(DspComponent *c, int i)
  {
    for(auto a_v_pair : _list) {
      for(auto p : *a_v_pair.second)
        if (c == p.first && i == p.second) {
          return a_v_pair.first;
        }
    }
    
    return std::string();
  }
  
  void set(int index, const DspParameter &param)
  {
    std::vector<std::pair<DspComponent*,int>> *v;
    
    v = _list[index].second;
    for(auto it : *v)
      it.first->SetParameter(it.second, param);
  }
  
  const DspParameter *getFirst(int index) const
  {
    std::vector<std::pair<DspComponent*,int>> *v;
    
    v = _list[index].second;
    for(auto it : *v)
      return it.first->GetParameter(it.second);
  }
  
  void replace(std::unordered_map<DspComponent*,DspComponent*> copies)
  {
    for(auto v : _map)
      for(auto it : *v.second)
        it.first = copies[it.first];
  }

  std::string getName(int index)
  {
    return _list[index].first;
  }
  
private:
  std::vector<std::pair<std::string,std::vector<std::pair<DspComponent*,int>>*>> _list;
  std::unordered_map<std::string,std::vector<std::pair<DspComponent*,int>>*> _map;
};

class DLLEXPORT DspCircuit : public DspComponent
{
public:
    DspCircuit(int threadCount = 0);
    ~DspCircuit();

    void SetThreadCount(int threadCount);
    int GetThreadCount() const;

    virtual DspComponent *clone();
    
    bool save(std::string filename);
    static DspCircuit* load(std::string filename, DspComponent *(*getComponentClone)(const std::string &typeName));

    bool AddComponent(DspComponent* component, std::string const& componentName = "");
    bool AddComponent(DspComponent& component, std::string const& componentName = "");

    void RemoveComponent(DspComponent const* component);
    void RemoveComponent(DspComponent const& component);
    void RemoveComponent(std::string const& componentName);
    
    DspWireBus *GetInToInWires();
    DspWireBus *GetOutToOutWires();

    void RemoveAllComponents();
    
    DspComponent *GetComponent(int n);
    
    template <class ComponentType>
    ComponentType* GetComponent(std::string const& componentName);

    int GetComponentCount() const;

    // component output to component input
    template <class FromComponentType, class FromOutputId, class ToComponentType, class ToInputId>
    bool ConnectOutToIn(FromComponentType& fromComponent, FromOutputId const& fromOutput, ToComponentType& toComponent, ToInputId const& toInput);

    // circuit input to component input
    template <class FromInputId, class ToComponentType, class ToInputId>
    bool ConnectInToIn(FromInputId const& fromInput, ToComponentType& toComponent, ToInputId const& toInput);

    // component output to circuit output
    template <class FromComponentType, class FromOutputId, class ToOutputId>
    bool ConnectOutToOut(FromComponentType& fromComponent, FromOutputId const& fromOutput, ToOutputId const& toOutput);

    // component output to component input
    template <class FromComponentType, class FromOutputId, class ToComponentType, class ToInputId>
    void DisconnectOutToIn(FromComponentType const& fromComponent, FromOutputId const& fromOutput, ToComponentType const& toComponent, ToInputId const& toInput);

    // circuit input to component input
    template <class FromInputId, class ToComponentType, class ToInputId>
    bool DisconnectInToIn(FromInputId const& fromInput, ToComponentType const& toComponent, ToInputId const& toInput);

    // component output to circuit output
    template <class FromComponentType, class FromOutputId, class ToOutputId>
    bool DisconnectOutToOut(FromComponentType const& fromComponent, FromOutputId const& fromOutput, ToOutputId const& toOutput);

    void DisconnectComponent(std::string const& component);

    bool AddInput(std::string const& inputName = "");
    bool AddOutput(std::string const& outputName = "");

    void RemoveInput();
    void RemoveOutput();

    void RemoveAllInputs();
    void RemoveAllOutputs();
    
    void configure();
    virtual void changed();
    
    void SetComponentParameterAlias(const std::string &alias, DspComponent *, int index);
    std::string GetComponentParameterAlias(DspComponent *, int index);

protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    
    virtual int GetParameterCount_() const;

    virtual DspParameter const* GetParameter_(int index) const;
    virtual bool SetParameter_(int index, DspParameter const& param);
    
    
    virtual std::string GetParameterName(int index);
    
    //FIXME TODO
    virtual void UnsetParameter_(int index);

private:
    virtual void _PauseAutoTick();

    bool _FindComponent(DspComponent const* component, int& returnIndex) const;
    bool _FindComponent(DspComponent const& component, int& returnIndex) const;
    bool _FindComponent(std::string const& componentName, int& returnIndex) const;
    bool _FindComponent(int componentIndex, int& returnIndex) const;

    void _DisconnectComponent(int componentIndex);
    void _RemoveComponent(int componentIndex);
    
    void _save_comp(FILE *f, int i);

private:
    std::vector<DspComponent*> _components;

    std::vector<DspCircuitThread> _circuitThreads;
    int _currentThreadIndex;
    uint64_t _generation = 1;
    uint64_t _configured_generation = 0;

    DspWireBus _inToInWires;
    DspWireBus _outToOutWires;
    
    Alias_List _alias;
};

//=================================================================================================

template <class ComponentType>
ComponentType* DspCircuit::GetComponent(std::string const& componentName)
{
    int componentIndex;

    if (_FindComponent(componentName, componentIndex))
    {
        return static_cast<ComponentType*>(_components[componentIndex]);
    }
    else
    {
        return NULL;
    }
}

//-------------------------------------------------------------------------------------------------

template <class FromComponentType, class FromOutputId, class ToComponentType, class ToInputId>
bool DspCircuit::ConnectOutToIn(FromComponentType& fromComponent,
                                FromOutputId const& fromOutput,
                                ToComponentType& toComponent,
                                ToInputId const& toInput)
{
    int fromComponentIndex;
    int toComponentIndex;

    // only interconnect components that have been added to this system
    if (!_FindComponent(fromComponent, fromComponentIndex) || !_FindComponent(toComponent, toComponentIndex))
    {
        return false;
    }

    PauseAutoTick();

    bool result = _components[toComponentIndex]->ConnectInput(_components[fromComponentIndex], fromOutput, toInput);

    ResumeAutoTick();

    return result;
}

//-------------------------------------------------------------------------------------------------

template <class FromInputId, class ToComponentType, class ToInputId>
bool DspCircuit::ConnectInToIn(FromInputId const& fromInput, ToComponentType& toComponent, ToInputId const& toInput)
{
    int fromInputIndex;
    int toComponentIndex;
    int toInputIndex;

    // only interconnect components that have been added to this system
    if (!_FindInput(fromInput, fromInputIndex) || !_FindComponent(toComponent, toComponentIndex) ||
        !_components[toComponentIndex]->_FindInput(toInput, toInputIndex))
    {
        return false;
    }

    PauseAutoTick();

    bool result = _inToInWires.AddWire(_components[toComponentIndex], fromInputIndex, toInputIndex);
    changed();

    ResumeAutoTick();

    return result;
}

//-------------------------------------------------------------------------------------------------

template <class FromComponentType, class FromOutputId, class ToOutputId>
bool DspCircuit::ConnectOutToOut(FromComponentType& fromComponent,
                                 FromOutputId const& fromOutput,
                                 ToOutputId const& toOutput)
{
    int fromComponentIndex;
    int fromOutputIndex;
    int toOutputIndex;

    // only interconnect components that have been added to this system
    if (!_FindComponent(fromComponent, fromComponentIndex) ||
        !_components[fromComponentIndex]->_FindOutput(fromOutput, fromOutputIndex) ||
        !_FindOutput(toOutput, toOutputIndex))
    {
      printf("WARNING component not part of circuit!\n");
        return false;
    }

    PauseAutoTick();

    bool result = _outToOutWires.AddWire(_components[fromComponentIndex], fromOutputIndex, toOutputIndex);
    changed();

    ResumeAutoTick();

    return result;
}

//-------------------------------------------------------------------------------------------------

template <class FromComponentType, class FromOutputId, class ToComponentType, class ToInputId>
void DspCircuit::DisconnectOutToIn(FromComponentType const& fromComponent,
                                   FromOutputId const& fromOutput,
                                   ToComponentType const& toComponent,
                                   ToInputId const& toInput)
{
    int fromComponentIndex;
    int toComponentIndex;

    // only interconnect components that have been added to this system
    if (!_FindComponent(fromComponent, fromComponentIndex) || !_FindComponent(toComponent, toComponentIndex))
    {
        return;
    }

    PauseAutoTick();

    _components[toComponentIndex]->DisconnectInput(_components[fromComponentIndex], fromOutput, toInput);

    ResumeAutoTick();
}

//-------------------------------------------------------------------------------------------------

template <class FromInputId, class ToComponentType, class ToInputId>
bool DspCircuit::DisconnectInToIn(FromInputId const& fromInput,
                                  ToComponentType const& toComponent,
                                  ToInputId const& toInput)
{
    int fromInputIndex;
    int toComponentIndex;
    int toInputIndex;

    // only interconnect components that have been added to this system
    if (!_FindInput(fromInput, fromInputIndex) || !_FindComponent(toComponent, toComponentIndex) ||
        !_components[toComponentIndex]->_FindInput(toInput, toInputIndex))
    {
        return false;
    }

    PauseAutoTick();

    bool result = _inToInWires.RemoveWire(_components[toComponentIndex], fromInputIndex, toInputIndex);
    changed();

    ResumeAutoTick();

    return result;
}

//-------------------------------------------------------------------------------------------------

template <class FromComponentType, class FromOutputId, class ToOutputId>
bool DspCircuit::DisconnectOutToOut(FromComponentType const& fromComponent,
                                    FromOutputId const& fromOutput,
                                    ToOutputId const& toOutput)
{
    int fromComponentIndex;
    int fromOutputIndex;
    int toOutputIndex;

    // only interconnect components that have been added to this system
    if (!_FindComponent(fromComponent, fromComponentIndex) ||
        !_components[fromComponentIndex]->_FindOutput(fromOutput, fromOutputIndex) ||
        !_FindOutput(toOutput, toOutputIndex))
    {
        return false;
    }

    PauseAutoTick();

    bool result = _outToOutWires.RemoveWire(_components[fromComponentIndex], fromOutputIndex, toOutputIndex);
    changed();

    ResumeAutoTick();

    return result;
}

//=================================================================================================

#endif  // DSPCIRCUIT_H
