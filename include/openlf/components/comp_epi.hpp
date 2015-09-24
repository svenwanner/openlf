/*
* Copyright (c) 2015 Heidelberg Collaboratory for Image Processing
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
* Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Author Sven Wanner, Maximilian Diebold, Hendrick Siedelmann 
*
*/

#ifndef _OPENLF_COMP_EPI_H
#define _OPENLF_COMP_EPI_H

#include "clif/flexmav.hpp"

#include "dspatch/DspComponent.h"
#include "dspatch/DspCircuit.h"

#include "comp_mav.hpp"

namespace openlf { namespace components {

class COMP_Epi : public DspComponent {
public:
  COMP_Epi();
  
  //TODO discuss:: use method or settings from DSPatch?
  void set(DspComponent *circuit);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  DspCircuit _circuit;
  FlexMAVSource<3> _source;
  FlexMAVSink  <3> _sink;
  clif::FlexMAV<3> _source_mav;
  
  //user provided circuit (which has FlexMAV input and output)
  DspComponent *_epi_circuit = NULL;
};

}} //namespace openlf::components

#endif