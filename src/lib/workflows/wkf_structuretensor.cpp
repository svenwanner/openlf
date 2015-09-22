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
        
        circ_structuretensor = new DspCircuit;
        
        AddInput_("EpiIn");
        AddOutput_("EpiOut");
        
        pInnerScale = AddParameter_("InnerScale", DspParameter(DspParameter::Float, 0.6f));
        
        gauss = new OP_Gauss;
        
        circ_structuretensor->AddComponent(gauss, "GaussSmoothing");
        
        circ_structuretensor->ConnectInToIn(0, gauss, 0);
        circ_structuretensor->ConnectOutToOut(gauss, 0, 0);
    }
    
    bool WKF_StructureTensor::ParameterUpdating_(int index, const DspParameter& param) {
        
        if (index == pInnerScale) {
            inner_scale = *param.GetFloat();
            return true;
        }
    }
    
    WKF_StructureTensor::~WKF_StructureTensor() { 
        delete circ_structuretensor;
    };
}}