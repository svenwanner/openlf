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

#include <dspatch/DspCircuit.h>
#include <dspatch/DspCircuitThread.h>
#include <dspatch/DspWire.h>

#include <assert.h>
#include <string.h>

#include <unordered_map>

extern "C" {
#include "gml_parser.h"
}

typedef unsigned int uint;

//=================================================================================================

DspCircuit::DspCircuit(int threadCount)
    : _currentThreadIndex(0)
    , _inToInWires(true)
    , _outToOutWires(false)
{
    SetThreadCount(threadCount);
}

//-------------------------------------------------------------------------------------------------

DspCircuit::~DspCircuit()
{
    StopAutoTick();
    RemoveAllComponents();
    SetThreadCount(0);
}

//=================================================================================================

void DspCircuit::SetThreadCount(int threadCount)
{
    if ((size_t)threadCount != _circuitThreads.size())
    {
        PauseAutoTick();

        // stop all threads
        for (size_t i = 0; i < _circuitThreads.size(); i++)
        {
            _circuitThreads[i].Stop();
        }

        // resize thread array
        _circuitThreads.resize(threadCount);

        // initialise and start all threads
        for (size_t i = 0; i < _circuitThreads.size(); i++)
        {
            _circuitThreads[i].Initialise(&_components, i);
            _circuitThreads[i].Start();
        }

        // set all components to the new thread count
        for (size_t i = 0; i < _components.size(); i++)
        {
            _components[i]->_SetBufferCount(threadCount);
        }

        ResumeAutoTick();
    }
}

//-------------------------------------------------------------------------------------------------

int DspCircuit::GetThreadCount() const
{
    return _circuitThreads.size();
}

//-------------------------------------------------------------------------------------------------

bool DspCircuit::AddComponent(DspComponent* component, std::string const& componentName)
{
    if (component != this && component != NULL)
    {
        std::string compName = componentName;

        // if the component has a name already
        if (component->GetComponentName() != "" && compName == "")
        {
            compName = component->GetComponentName();
        }

        int componentIndex;

        if (component->_GetParentCircuit() != NULL)
        {
            return false;  // if the component is already part of another circuit
        }
        if (_FindComponent(component, componentIndex))
        {
            return false;  // if the component is already in the array
        }
        if (_FindComponent(compName, componentIndex))
        {
            return false;  // if the component name is already in the array
        }

        // components within the circuit need to have as many buffers as there are threads in the circuit
        component->_SetParentCircuit(this);
        component->_SetBufferCount(_circuitThreads.size());
        component->SetComponentName(compName);

        PauseAutoTick();
        _components.push_back(component);
        ResumeAutoTick();

        changed();
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------

bool DspCircuit::AddComponent(DspComponent& component, std::string const& componentName)
{
    return AddComponent(&component, componentName);
}

//-------------------------------------------------------------------------------------------------

void DspCircuit::RemoveComponent(DspComponent const* component)
{
    int componentIndex;

    if (_FindComponent(component, componentIndex))
    {
        PauseAutoTick();
        _RemoveComponent(componentIndex);
        ResumeAutoTick();
    }
}

//-------------------------------------------------------------------------------------------------

void DspCircuit::RemoveComponent(DspComponent const& component)
{
    RemoveComponent(&component);
}

//-------------------------------------------------------------------------------------------------

void DspCircuit::RemoveComponent(std::string const& componentName)
{
    int componentIndex;

    if (_FindComponent(componentName, componentIndex))
    {
        PauseAutoTick();
        _RemoveComponent(componentIndex);
        ResumeAutoTick();
    }
}

//-------------------------------------------------------------------------------------------------

void DspCircuit::RemoveAllComponents()
{
    for (size_t i = 0; i < _components.size(); i++)
    {
        PauseAutoTick();
        _RemoveComponent(i--);  // size drops as one is removed
        ResumeAutoTick();
    }
}

//-------------------------------------------------------------------------------------------------

int DspCircuit::GetComponentCount() const
{
    return _components.size();
}

//-------------------------------------------------------------------------------------------------

void DspCircuit::DisconnectComponent(std::string const& component)
{
    int componentIndex;

    if (!_FindComponent(component, componentIndex))  // verify component exists
    {
        return;
    }

    PauseAutoTick();
    _DisconnectComponent(componentIndex);
    ResumeAutoTick();
}

//-------------------------------------------------------------------------------------------------

bool DspCircuit::AddInput(std::string const& inputName)
{
    PauseAutoTick();
    bool result = AddInput_(inputName);
    ResumeAutoTick();
    return result;
}

//-------------------------------------------------------------------------------------------------

bool DspCircuit::AddOutput(std::string const& outputName)
{
    PauseAutoTick();
    bool result = AddOutput_(outputName);
    ResumeAutoTick();
    return result;
}

//-------------------------------------------------------------------------------------------------

void DspCircuit::RemoveInput()
{
    PauseAutoTick();
    RemoveInput_();
    ResumeAutoTick();
}

//-------------------------------------------------------------------------------------------------

void DspCircuit::RemoveOutput()
{
    PauseAutoTick();
    RemoveOutput_();
    ResumeAutoTick();
}

//-------------------------------------------------------------------------------------------------

void DspCircuit::RemoveAllInputs()
{
    PauseAutoTick();
    RemoveAllInputs_();
    ResumeAutoTick();
}

//-------------------------------------------------------------------------------------------------

void DspCircuit::RemoveAllOutputs()
{
    PauseAutoTick();
    RemoveAllOutputs_();
    ResumeAutoTick();
}

//=================================================================================================

void DspCircuit::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
    DspWire* wire;
    DspSignal* signal;

    // process in a single thread if this circuit has no threads
    // =========================================================
    if (_circuitThreads.size() == 0)
    {
        // set all internal component inputs from connected circuit inputs
        for (int i = 0; i < _inToInWires.GetWireCount(); i++)
        {
            wire = _inToInWires.GetWire(i);
            signal = inputs.GetSignal(wire->fromSignalIndex);
            wire->linkedComponent->_SetInputSignal(wire->toSignalIndex, signal);
        }

        // tick all internal components
        for (size_t i = 0; i < _components.size(); i++)
        {
            _components[i]->Tick();
        }

        // reset all internal components
        for (size_t i = 0; i < _components.size(); i++)
        {
            _components[i]->Reset();
        }

        // set all circuit outputs from connected internal component outputs
        for (int i = 0; i < _outToOutWires.GetWireCount(); i++)
        {
            wire = _outToOutWires.GetWire(i);
            signal = wire->linkedComponent->_GetOutputSignal(wire->fromSignalIndex);
            outputs.SetSignal(wire->toSignalIndex, signal);
        }
    }
    // process in multiple thread if this circuit has threads
    // ======================================================
    else
    {
        _circuitThreads[_currentThreadIndex].Sync();  // sync with thread x

        // set all circuit outputs from connected internal component outputs
        for (int i = 0; i < _outToOutWires.GetWireCount(); i++)
        {
            wire = _outToOutWires.GetWire(i);
            signal = wire->linkedComponent->_GetOutputSignal(wire->fromSignalIndex, _currentThreadIndex);
            outputs.SetSignal(wire->toSignalIndex, signal);
        }

        // set all internal component inputs from connected circuit inputs
        for (int i = 0; i < _inToInWires.GetWireCount(); i++)
        {
            wire = _inToInWires.GetWire(i);
            signal = inputs.GetSignal(wire->fromSignalIndex);
            wire->linkedComponent->_SetInputSignal(wire->toSignalIndex, _currentThreadIndex, signal);
        }

        _circuitThreads[_currentThreadIndex].Resume();  // resume thread x

        if ((size_t)++_currentThreadIndex >= _circuitThreads.size())  // shift to thread x+1
        {
            _currentThreadIndex = 0;
        }
    }
}

//=================================================================================================

void DspCircuit::configure()
{
  //uhh ohh autotick stuff?!?
  bool old = _configOnly;
  
  if (_configured_generation < _generation) {
    _configOnly = true;
    Tick();
    _configOnly = old;
    _configured_generation = _generation;
  }
}

//=================================================================================================

void DspCircuit::_PauseAutoTick()
{
    // pause auto tick
    DspComponent::_PauseAutoTick();

    // manually tick until 0
    while (_currentThreadIndex != 0)
    {
        Tick();
        Reset();
    }

    // sync all threads
    for (size_t i = 0; i < _circuitThreads.size(); i++)
    {
        _circuitThreads[i].Sync();
    }
}

//-------------------------------------------------------------------------------------------------

bool DspCircuit::_FindComponent(DspComponent const* component, int& returnIndex) const
{
    for (size_t i = 0; i < _components.size(); i++)
    {
        if (_components[i] == component)
        {
            returnIndex = i;
            return true;
        }
    }

    return false;
}

//-------------------------------------------------------------------------------------------------

bool DspCircuit::_FindComponent(DspComponent const& component, int& returnIndex) const
{
    return _FindComponent(&component, returnIndex);
}

//-------------------------------------------------------------------------------------------------

bool DspCircuit::_FindComponent(std::string const& componentName, int& returnIndex) const
{
    for (size_t i = 0; i < _components.size(); i++)
    {
        if (_components[i]->GetComponentName() != "" && _components[i]->GetComponentName() == componentName)
        {
            returnIndex = i;
            return true;
        }
    }

    return false;
}

//-------------------------------------------------------------------------------------------------

bool DspCircuit::_FindComponent(int componentIndex, int& returnIndex) const
{
    if ((size_t)componentIndex < _components.size())
    {
        returnIndex = componentIndex;
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------

void DspCircuit::_DisconnectComponent(int componentIndex)
{
    changed();
    // remove component from _inputComponents and _inputWires
    _components[componentIndex]->DisconnectAllInputs();

    // remove any connections this component has to other components
    for (size_t i = 0; i < _components.size(); ++i)
    {
        _components[i]->DisconnectInput(_components[componentIndex]);
    }

    // remove component from _inToInWires
    DspWire* wire;
    for (int i = 0; i < _inToInWires.GetWireCount(); i++)
    {
        wire = _inToInWires.GetWire(i);
        if (wire->linkedComponent == _components[componentIndex])
        {
            _inToInWires.RemoveWire(i);
        }
    }

    // remove component from _outToOutWires
    for (int i = 0; i < _outToOutWires.GetWireCount(); i++)
    {
        wire = _outToOutWires.GetWire(i);
        if (wire->linkedComponent == _components[componentIndex])
        {
            _outToOutWires.RemoveWire(i);
        }
    }
}

//-------------------------------------------------------------------------------------------------

DspComponent *DspCircuit::GetComponent(int n)
{
  return _components[n];
}
    
//-------------------------------------------------------------------------------------------------


void DspCircuit::_RemoveComponent(int componentIndex)
{
    changed();
    _DisconnectComponent(componentIndex);

    // set the removed component's parent circuit to NULL
    if (_components[componentIndex]->_GetParentCircuit() != NULL)
    {
        _components[componentIndex]->_SetParentCircuit(NULL);
    }
    // setting a component's parent to NULL (above) calls _RemoveComponent (hence the following code will run)
    else if (_components.size() != 0)
    {
        _components.erase(_components.begin() + componentIndex);
    }
}

//-------------------------------------------------------------------------------------------------

DspWireBus *DspCircuit::GetInToInWires()
{
  return &_inToInWires;
}

DspWireBus *DspCircuit::GetOutToOutWires()
{
  return &_outToOutWires;
}

//=================================================================================================

void DspCircuit::changed()
{
  DspCircuit *c = this;
  while (c->_GetParentCircuit())
    c = c->_GetParentCircuit();
  
  c->_generation++;
  Reset();
}

void DspCircuit::_save_comp(FILE *f, int i)
{  
  DspComponent *comp = _components[i];
  
  fprintf(f, "node [\n");
  fprintf(f, "id %d\n", i);
  fprintf(f, "label \"%s\"\n", comp->GetComponentName().c_str());
  if (!comp->getTypeName().size())
    abort();
  fprintf(f, "type \"%s\"\n", comp->getTypeName().c_str());
  if (comp->GetParameterCount()) {
    fprintf(f, "params [\n");
    for(int i=0;i<comp->GetParameterCount();i++) {
      const DspParameter *p = comp->GetParameter(i);
      fprintf(f, "%s ", comp->GetParameterName(i).c_str());
      if (p->IsSet())
        switch (p->Type()) {
          case DspParameter::ParamType::String :
            fprintf(f, "\"%s\"\n", p->GetString()->c_str());
            break;
          case DspParameter::ParamType::Float :
            fprintf(f, "%f\n", *p->GetFloat());
            break;
          case DspParameter::ParamType::Int :
            fprintf(f, "%d\n", *p->GetInt());
            break;
          default:
            fprintf(f, "\"(UNKNOWN)\"\n");
        }
      else
        fprintf(f, "\"(UNSET)\"\n");
    }
    fprintf(f, "]\n");
  }
  
  fprintf(f, "]\n");
}

bool DspCircuit::save(std::string filename)
{
  FILE *f = fopen(filename.c_str(), "w");
  if (!f)
    return true;
  
  fprintf(f, "graph [\n");
  if (GetComponentName().size())
    fprintf(f, "label \"%s\"\n", GetComponentName().c_str());
  if (getTypeName().size())
    fprintf(f, "type \"%s\"\n", getTypeName().c_str());
    
  for(uint i=0;i<_components.size();i++)
    _save_comp(f, i);
  
  for(uint i=0;i<_components.size();i++)
    for(int j=0;j<_components[i]->_inputWires.GetWireCount();j++) {
      int idx;
      DspWire *wire = _components[i]->_inputWires.GetWire(j);
      _FindComponent(wire->linkedComponent, idx);
      fprintf(f, "edge [\n");
      fprintf(f, "source %d\n", idx);
      fprintf(f, "target %d\n", i);
      fprintf(f, "source_pad %d\n", wire->fromSignalIndex);
      fprintf(f, "target_pad %d\n", wire->toSignalIndex);
      fprintf(f, "]\n");
    }
    
  for(int i=0;i<_outToOutWires.GetWireCount();i++) {
      int idx;
      DspWire *wire = _outToOutWires.GetWire(i);
      _FindComponent(wire->linkedComponent, idx);
      fprintf(f, "outputedge [\n");
      fprintf(f, "source %d\n", idx);
      fprintf(f, "source_pad %d\n", wire->fromSignalIndex);
      fprintf(f, "target_pad %d\n", wire->toSignalIndex);
      fprintf(f, "]\n");
    }
    
  for(int i=0;i<_inToInWires.GetWireCount();i++) {
      int idx;
      DspWire *wire = _inToInWires.GetWire(i);
      _FindComponent(wire->linkedComponent, idx);
      fprintf(f, "inputedge [\n");
      fprintf(f, "target %d\n", idx);
      fprintf(f, "source_pad %d\n", wire->fromSignalIndex);
      fprintf(f, "target_pad %d\n", wire->toSignalIndex);
      fprintf(f, "]\n");
    }
  
  fprintf(f, "]\n");
  fclose(f);
    
  return false;
}

void print_keys (struct GML_list_elem* list) {
  
  while (list) {
    printf ("%s\n", list->key);
    list = list->next;
  }
}

#define DPPT DspParameter::ParamType

DspCircuit* DspCircuit::load(std::string filename, DspComponent *(*getComponentClone)(const std::string &typeName))
{
  
  static struct {
    void operator()(DspComponent *comp, GML_pair *node)
    {
      bool res;
      GML_pair *part;
      
      part = node;
      while(part) {
        const DspParameter *p = NULL;
        int p_idx;
        for(int i=0;i<comp->GetParameterCount();i++)
          if (!comp->GetParameterName(i).compare(part->key)) {
            p = comp->GetParameter(i);
            p_idx = i;
            break;
          }
        if (!p) {
          printf("skipping unknown parameter \"%s\" for component \"%s\"\n",
            part->key, comp->getTypeName().c_str());
        }
        else if (part->kind == GML_STRING
                 && (!strcmp(part->value.string,"(UNKNOWN)")
                     || !strcmp(part->value.string,"(UNSET)")
                )) {
          printf("skipping unset parameter \"%s\" for component \"%s\"\n",
            part->key, comp->getTypeName().c_str());
        }
        else {
          switch (p->Type()) {
            case DPPT::String :
              assert(part->kind = GML_STRING);
              res = comp->SetParameter(p_idx, DspParameter(DPPT::String, std::string(part->value.string)));
              assert(res);
              break;
            case DPPT::Float :
              assert(part->kind = GML_DOUBLE);
              comp->SetParameter(p_idx, DspParameter(DPPT::Float, (float)part->value.floating));
              break;
            case DPPT::Int :
              assert(part->kind = GML_INT);
              comp->SetParameter(p_idx, DspParameter(DPPT::Int, (int)part->value.integer));
              break;
            default :
              printf("skipping parameter \"%s\" with unknown type for component \"%s\"\n",
                part->key, comp->getTypeName().c_str());
          }
        }
        part = part->next;
      }
    }
  } _gml_parse_add_params;
  
  static struct {
    void operator()(DspCircuit *c, GML_pair *node, DspComponent *(*getComponentClone)(const std::string &typeName))
    {
      printf("add node\n");
      GML_pair *part;
      DspComponent *comp = NULL;
      const char *name = NULL;
      int id = -1;
      GML_pair *params = NULL;
      
      assert(node->kind == GML_LIST);
  
      part = node->value.list;
      while(part) {
        if (!strcmp(part->key, "type")) {
          assert(part->kind == GML_STRING);
          const char *type = part->value.string;
          printf("type %s\n", type);
          comp = getComponentClone(type);
        }
        else if (!strcmp(part->key, "label")) {
          assert(part->kind == GML_STRING);
          name = part->value.string;
          printf("name %s\n", name);
        }
        else if (!strcmp(part->key, "id")) {
          assert(part->kind == GML_INT);
          id = part->value.integer;
        }
        else if (!strcmp(part->key, "params")) {
          assert(part->kind == GML_LIST);
          params = part->value.list;
        }
        part = part->next;
      }
      
      //FIXME make parsing errors from this!
      assert(comp);
      assert(name);
      assert(id == c->GetComponentCount());
  
      bool suc = c->AddComponent(comp, name);
      assert(suc);
      
      if (params)
        _gml_parse_add_params(comp, params);
    }
  } _gml_parse_add_component;
  
  static struct {  
    void operator()(DspCircuit *c, GML_pair *node)
    {
      assert(node->kind == GML_LIST);
      int source = -1, target = -1, source_idx = -1, target_idx = -1;
      
      GML_pair *part = node->value.list;
      while(part) {
        if (!strcmp(part->key, "source")) {
          assert(part->kind == GML_INT);
          source = part->value.integer;
        }
        else if (!strcmp(part->key, "target")) {
          assert(part->kind == GML_INT);
          target = part->value.integer;
        }
        else if (!strcmp(part->key, "source_pad")) {
          assert(part->kind == GML_INT);
          source_idx = part->value.integer;
        }
        else if (!strcmp(part->key, "target_pad")) {
          assert(part->kind == GML_INT);
          target_idx = part->value.integer;
        }
        part = part->next;
      }
      
      assert(source != -1);
      assert(target != -1);
      assert(source_idx != -1);
      assert(target_idx != -1);
      
      //FIXME check a lot of other stuff (idx and comp max, ...
      assert(source_idx < c->_components.size());
      assert(target_idx < c->_components.size());
      assert(source_idx < c->_components[source]->GetOutputCount());
      assert(target_idx < c->_components[target]->GetInputCount());
      
      printf("connect edge\n");
      c->ConnectOutToIn(c->_components[source],source_idx,c->_components[target],target_idx);
    }
  } _gml_parse_add_edge;
  
  static struct {  
    void operator()(DspCircuit *c, GML_pair *node, bool is_source)
    {
      assert(node->kind == GML_LIST);
      int source = -1, target = -1, source_idx = -1, target_idx = -1;
      
      GML_pair *part = node->value.list;
      while(part) {
        if (!strcmp(part->key, "source")) {
          assert(part->kind == GML_INT);
          source = part->value.integer;
        }
        else if (!strcmp(part->key, "target")) {
          assert(part->kind == GML_INT);
          target = part->value.integer;
        }
        else if (!strcmp(part->key, "source_pad")) {
          assert(part->kind == GML_INT);
          source_idx = part->value.integer;
        }
        else if (!strcmp(part->key, "target_pad")) {
          assert(part->kind == GML_INT);
          target_idx = part->value.integer;
        }
        part = part->next;
      }
      
      assert(source != -1 || target != -1);
      assert(source_idx != -1);
      assert(target_idx != -1);
      
      //FIXME check a lot of other stuff (idx and comp max, ...
      
      char buf[64];
      if (is_source) {
        while (c->GetInputCount() <= source_idx) {
          sprintf(buf, "input_%d", c->GetInputCount());
          c->AddInput(buf);
        }
        printf("connect circuit source edge\n");
        c->ConnectInToIn(source_idx, c->_components[target],target_idx);
      }
      else {
        while (c->GetOutputCount() <= target_idx) {
          sprintf(buf, "output_%d", c->GetOutputCount());
          c->AddOutput(buf);
        }
        printf("connect circuit sink edge\n");
        c->ConnectOutToOut(c->_components[source], source_idx, target_idx);
      }
    }
  } _gml_parse_add_inout_edge;
  
  static struct {  
    DspCircuit *operator()(GML_pair *pair, DspComponent *(*getComponentClone)(const std::string &typeName))
    {
      DspCircuit *c = new DspCircuit;
      struct GML_pair *start;
      struct GML_pair *part;
      
      assert(pair->kind == GML_LIST);
      assert(!strcmp(pair->key, "graph"));
      
      start = pair->value.list;
      part = start;
     
      printf("parse circuit!\n");
      
      while (part) {
        if (!strcmp(part->key, "node"))
          _gml_parse_add_component(c, part,getComponentClone);
        part = part->next;
      }
      
      part = start;
      while (part) {
        if (!strcmp(part->key, "edge"))
          _gml_parse_add_edge(c, part);
        else if (!strcmp(part->key, "inputedge"))
          _gml_parse_add_inout_edge(c, part, true);
        else if (!strcmp(part->key, "outputedge"))
          _gml_parse_add_inout_edge(c, part, false);
        else if (!strcmp(part->key, "label")) {
          assert(part->kind == GML_STRING);
          c->SetComponentName(part->value.string);
        }
        else if (!strcmp(part->key, "type")) {
          assert(part->kind == GML_STRING);
          c->setTypeName(part->value.string);
        }
        part = part->next;
      }
      
      return c;
    }
  } _gml_parse_circuit;
  
  struct GML_pair* list;
  struct GML_stat* stat=(struct GML_stat*)malloc(sizeof(struct GML_stat));
  stat->key_list = NULL;
  
  FILE* file = fopen (filename.c_str(), "r");
  if (!file)
    return NULL;
  
  GML_init ();
  list = GML_parser(file, stat, 0);
  
  if (stat->err.err_num != GML_OK) {
    printf ("An error occured while reading line %d column %d of %s:\n", stat->err.line, stat->err.column, filename.c_str());
    
    switch (stat->err.err_num) {
      case GML_UNEXPECTED:
        printf ("UNEXPECTED CHARACTER");
        break;
        
      case GML_SYNTAX:
        printf ("SYNTAX ERROR"); 
        break;
        
      case GML_PREMATURE_EOF:
        printf ("PREMATURE EOF IN STRING");
        break;
        
      case GML_TOO_MANY_DIGITS:
        printf ("NUMBER WITH TOO MANY DIGITS");
        break;
        
      case GML_OPEN_BRACKET:
        printf ("OPEN BRACKETS LEFT AT EOF");
        break;
        
      case GML_TOO_MANY_BRACKETS:
        printf ("TOO MANY CLOSING BRACKETS");
        break;
        
      default:
        break;
    }
    
    printf ("\n");
  }      
  GML_print_list(list, 0);
  printf ("Keys used in %s: \n", filename.c_str());
  print_keys(stat->key_list);
  
  DspCircuit *c = NULL;
  
  if (list)
   c = _gml_parse_circuit(list, getComponentClone);
  
  GML_free_list (list, stat->key_list);
  
  return c;
}

DspComponent* DspCircuit::clone()
{
  DspCircuit *c = new DspCircuit();
  bool ret;
  
  printf("DspCircuit clone()\n");
  
  std::unordered_map<DspComponent*,DspComponent*> copies;
  
  for(int i=0;i<GetComponentCount();i++) {
    DspComponent *clone = GetComponent(i)->clone();
    assert(clone);
    copies[GetComponent(i)] = clone;
    c->AddComponent(clone, clone->GetComponentName());
  }
  
  for(auto it=copies.begin();it!=copies.end();++it) {
    DspWireBus *inputs = &it->first->_inputWires;
    for(int i=0;i<inputs->GetWireCount();i++) {
      DspWire *input = inputs->GetWire(i);
      printf("conn outin\n");
      ret = c->ConnectOutToIn(copies[input->linkedComponent], input->fromSignalIndex, it->second, input->toSignalIndex);
      assert(ret);
    }
  }
  
  for(int i=0;i<_inToInWires.GetWireCount();i++) {
    DspWire *input = _inToInWires.GetWire(i);
    c->AddInput(GetInputName(i));
    ret = c->ConnectInToIn(input->fromSignalIndex, copies[input->linkedComponent], input->toSignalIndex);
      assert(ret);
  }
  
  for(int i=0;i<_outToOutWires.GetWireCount();i++) {
    DspWire *output = _outToOutWires.GetWire(i);
    c->AddOutput(GetOutputName(i));
    ret = c->ConnectOutToOut(copies[output->linkedComponent], output->fromSignalIndex, output->toSignalIndex);
      assert(ret);
  }
  
  return c;
}


//=================================================================================================
