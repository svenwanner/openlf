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


#include "wkf_structuretensor.hpp"

namespace openlf {
  namespace components {
    
    void WKF_StructureTensor::setup()
    {
      
      // define inputs
      setTypeName_("WKF_StructureTensor");
      AddInput_("EpiIn");
      AddOutput_("disparity");
      AddOutput_("coherence");
      
      //input disparity
      pInDisp = AddParameter_("input disparity", DspParameter(DspParameter::Float, 0.0f));
      
      // add parameter with defaults values
      pInnerScale = AddParameter_("InnerScale", DspParameter(DspParameter::Float, 0.6f));
      pOuterScale = AddParameter_("OuterScale", DspParameter(DspParameter::Float, 1.0f));
      pMinCoherence = AddParameter_("MinCoherence", DspParameter(DspParameter::Float, 0.5f));
      
      //vertical blur separate
      pInnerScaleV = AddParameter_("InnerScaleV", DspParameter(DspParameter::Float, -1.0f));
      pOuterScaleV = AddParameter_("OuterScaleV", DspParameter(DspParameter::Float, -1.0f));
      
      setup_component_parameters();
      
      // add components
      AddComponent(inner_gauss, "InnerSmoothing");
      AddComponent(scharr_yx, "Gradients");
      //AddComponent(normalize, "Normalize");
      AddComponent(mergeChannel_0, "AverageChannel_0");
      AddComponent(mergeChannel_1, "AverageChannel_1");
      AddComponent(mergeChannel_2, "AverageChannel_2");
      AddComponent(outer_gauss_0, "OuterSmoothing_0");
      AddComponent(outer_gauss_1, "OuterSmoothing_1");
      AddComponent(outer_gauss_2, "OuterSmoothing_2");
      AddComponent(tensor, "Tensor");
      AddComponent(tensor2orientation, "Tensor2Orientation");
      
      
      //========== Connect Operators =============
      
      // inner smoothing
      ConnectInToIn(0, inner_gauss, 0);
      // normalize input
      //ConnectOutToIn(inner_gauss, 0, normalize, 0);
      // compute gradients
      ConnectOutToIn(inner_gauss, 0, scharr_yx, 0);
      // make tensor from gradients
      ConnectOutToIn(scharr_yx, 0, tensor, 0);
      ConnectOutToIn(scharr_yx, 1, tensor, 1);
      // merge channels
      ConnectOutToIn(tensor, 0, mergeChannel_0, 0);
      ConnectOutToIn(tensor, 1, mergeChannel_1, 0);
      ConnectOutToIn(tensor, 2, mergeChannel_2, 0);
      // smooth tensor components
      ConnectOutToIn(mergeChannel_0, 0, outer_gauss_0, 0);
      ConnectOutToIn(mergeChannel_1, 0, outer_gauss_1, 0);
      ConnectOutToIn(mergeChannel_2, 0, outer_gauss_2, 0);
      // connect st channels to  merge operator
      ConnectOutToIn(outer_gauss_0, 0, tensor2orientation, 0);
      ConnectOutToIn(outer_gauss_1, 0, tensor2orientation, 1);
      ConnectOutToIn(outer_gauss_2, 0, tensor2orientation, 2);
      // return orientation
      ConnectOutToOut(tensor2orientation, 0, 0);
      ConnectOutToOut(tensor2orientation, 1, 1);
    }
    
    void WKF_StructureTensor::setup_component_parameters()
    {
      const DspParameter *p, *p_v;
      
      p = GetParameter(pInnerScale);
      p_v = GetParameter(pInnerScaleV);
      
      //horizontal inner scale
      inner_gauss.SetParameter(0, *p);
      
      //vertical inner scale 
      if (*p_v->GetFloat() >= 0)
        inner_gauss.SetParameter(1, *p_v);
      else
        inner_gauss.SetParameter(1, *p);
      
      
      p = GetParameter(pOuterScale);
      p_v = GetParameter(pOuterScaleV);
      
      //horizontal outer scale
      outer_gauss_0.SetParameter(0, *p);
      outer_gauss_1.SetParameter(0, *p);
      outer_gauss_2.SetParameter(0, *p);
      
      //vertical outer scale 
      if (*p_v->GetFloat() >= 0) {
        outer_gauss_0.SetParameter(1, *p_v);
        outer_gauss_1.SetParameter(1, *p_v);
        outer_gauss_2.SetParameter(1, *p_v);
      }
      else {
        outer_gauss_0.SetParameter(1, *p);
        outer_gauss_1.SetParameter(1, *p);
        outer_gauss_2.SetParameter(1, *p);
      }

      //min_coherence = *GetParameter(MinCoherence, DspParameter::ParamType::Float).GetFloat();
      //std::cout << "Parameter Update min_coherence: " << min_coherence << std::endl;
      tensor2orientation.SetParameter(0, *GetParameter(pMinCoherence));
      tensor2orientation.SetParameter(1, *GetParameter(pInDisp));
      

    }
    
    WKF_StructureTensor::WKF_StructureTensor()
    {
      setup();
    }
    
    bool WKF_StructureTensor::ParameterUpdating_(int index, const DspParameter& param)
    {
      float v;
      
      //all params are float
      if (!param.GetFloat())
        return false;
      
      v = *param.GetFloat();
      
      //check if coherence is valid (for all others all ranges are fine
      if (index == pMinCoherence && (v < 0 || v > 1))
        return false;

      //just store parameter 
      SetParameter_(index, param);
      
      setup_component_parameters();
      
      return true;      
    }
    
    /*WKF_StructureTensor* WKF_StructureTensor::clone()
    {
      WKF_StructureTensor *dup = new WKF_StructureTensor();
      
      //copy parameters
      for(int i=0;i<GetParameterCount();i++)
        dup->SetParameter(i, *GetParameter(i));
      
      return dup;
    }*/
}} //namespace openlf::components
