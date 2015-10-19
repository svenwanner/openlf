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

#ifndef WKF_STRUCTURETENSOR_HPP
#define WKF_STRUCTURETENSOR_HPP

#include "openlf/operators/operators.hpp"
#include "openlf/components/comp_mav.hpp"
#include "openlf/types.hpp"

using namespace clif;
using namespace vigra;
using namespace openlf::components;

namespace openlf { 
  namespace components {
    
    class WKF_StructureTensor : public DspCircuit {
    private:
      
      // declare parameter indices and container
      int pInnerScale;
      int pOuterScale;
      int pMinCoherence;
      
      int pInDisp;
      
      int pInnerScaleV;
      int pOuterScaleV;
      
      // define operators
      OP_VigraGauss inner_gauss;
      OP_VigraGauss outer_gauss_0;
      OP_VigraGauss outer_gauss_1;
      OP_VigraGauss outer_gauss_2;
      //OP_Normalize normalize;
      OP_AverageChannels mergeChannel_0;
      OP_AverageChannels mergeChannel_1;
      OP_AverageChannels mergeChannel_2;
      OP_Scharr scharr_yx;
      OP_Tensor2x2 tensor;
      OP_Tensor2Orientation tensor2orientation;
      
      void setup();
      
    public:
      WKF_StructureTensor();

      DSPCOMPONENT_TRIVIAL_CLONE(WKF_StructureTensor)
      
    protected:
      //virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
      virtual bool ParameterUpdating_(int index, DspParameter const& param);
      void setup_component_parameters();
      
      
    };
    
}} //namespace openlf::components
  
#endif /* WKF_STRUCTURETENSOR_HPP */
  