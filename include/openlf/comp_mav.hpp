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
* Author Sven Wanner, Maximilian Diebold, Hendrik Siedelmann 
*
*/

#ifndef _OPENLF_COMP_MAV_H
#define _OPENLF_COMP_MAV_H

#include "dspatch/DspComponent.h"

#include "clif/dataset.hpp"

namespace openlf {

class MatSource : public DspComponent {
public:
  MatSource()
  {
    AddOutput_("output");
  }
  void set(clif::Mat *m)
  {
    _m = m;
  }

protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs)
  {
    bool stat;
    assert(_m);
    stat = outputs.SetValue(0, _m); 
    assert(stat);
  }
  
private:
  clif::Mat *_m = NULL;
};

class MatSink : public DspComponent {
public:
  MatSink()
  {
    AddInput_("input");
  }
  clif::Mat* get()
  {
    return _m;
  }

protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs)
  {
    inputs.GetValue(0, _m);
    assert(_m);
  }
  
private:
  clif::Mat *_m = NULL;
};

} //namespace openlf

#endif