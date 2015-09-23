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


#include "wkf_structuretensor.hpp"

namespace openlf { 
    namespace components {

    WKF_StructureTensor::WKF_StructureTensor() {
                
        AddInput_("EpiIn");
        AddOutput_("EpiOut");
        
        DspParameter pinner = DspParameter(DspParameter::Float, 0.3f);
        DspParameter pouter = DspParameter(DspParameter::Float, 6.0f);
        
        pInnerScale = AddParameter_("InnerScale", pinner);
        pOuterScale = AddParameter_("OuterScale", pouter);
    
        AddComponent(inner_gauss, "InnerSmoothing");
        AddComponent(outer_gauss, "OuterSmoothing");
        //AddComponent(scharr_xy, "Gradients");
//        AddComponent(scharr_x, "ScharrX");
//        AddComponent(scharr_y, "ScharrY");
        
//        ConnectInToIn(0, inner_gauss, 0);
//        ConnectOutToIn(inner_gauss, 0, scharr_x, 0);
//        ConnectOutToIn(inner_gauss, 0, scharr_y, 0);
//        ConnectOutToIn(scharr_x, 0, outer_gauss, 0);
//        ConnectOutToOut(outer_gauss, 0, 0);
        
        SetParameter(pInnerScale, pinner);
        SetParameter(pOuterScale, pouter);
    }
    
    bool WKF_StructureTensor::ParameterUpdating_(int index, const DspParameter& param) {
        
        if (index == pInnerScale) {
            inner_scale = *param.GetFloat();
            std::cout << "Parameter Update inner_scale: " << inner_scale << std::endl;
            inner_gauss.SetParameter(0, DspParameter(DspParameter::ParamType::Float, inner_scale));
            inner_gauss.SetParameter(1, DspParameter(DspParameter::ParamType::Float, inner_scale));
            return true;
        }
        if (index == pOuterScale) {
            outer_scale = *param.GetFloat();
            std::cout << "Parameter Update outer_scale : " << outer_scale << std::endl;
            outer_gauss.SetParameter(0, DspParameter(DspParameter::ParamType::Float, outer_scale));
            //outer_gauss.SetParameter(1, DspParameter(DspParameter::ParamType::Float, outer_scale));
            return true;
        }
    }
    
    WKF_StructureTensor::~WKF_StructureTensor() { 
        delete circ_structuretensor;
    };
}}