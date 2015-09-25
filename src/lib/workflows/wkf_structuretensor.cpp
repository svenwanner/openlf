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
               
        // define inputs
        AddInput_("EpiIn");
        AddOutput_("EpiOut");
        
        // create Parameter
        DspParameter pinner = DspParameter(DspParameter::Float, 0.6f);
        DspParameter pouter = DspParameter(DspParameter::Float, 1.0f);
        DspParameter pfilename = DspParameter(DspParameter::String, "");
        
        // add parameter
        pInnerScale = AddParameter_("InnerScale", pinner);
        pOuterScale = AddParameter_("OuterScale", pouter);
        pFilename = AddParameter_("Filename", pfilename);
        
        // set parameter
        SetParameter(pInnerScale, pinner);
        SetParameter(pOuterScale, pouter);
        SetParameter(pFilename, pfilename);
    
        // add components
        AddComponent(inner_gauss, "InnerSmoothing");
        AddComponent(scharr_xy, "Gradients");
        AddComponent(normalize, "Normalize");
        AddComponent(outer_gauss_0, "OuterSmoothing_0");
        AddComponent(outer_gauss_1, "OuterSmoothing_1");
        AddComponent(outer_gauss_2, "OuterSmoothing_2");
        AddComponent(tensor, "Tensor");
        AddComponent(tensor2orientation, "Tensor2Orientation");
        AddComponent(saveImage, "SaveImage");
        
        //========== Connect Operators =============
        
        // inner smoothing
        ConnectInToIn(0, inner_gauss, 0);
//save --------
//        SetParameter(pFilename, DspParameter(DspParameter::String, "/home/swanner/Projects/openlf/build/inner_scale.tif"));
//        ConnectOutToIn(inner_gauss, 0, saveImage, 0);
//-------------
        // normalize input
        ConnectOutToIn(inner_gauss, 0, normalize, 0);
//save --------
//        SetParameter(pFilename, DspParameter(DspParameter::String, "/home/swanner/Projects/openlf/build/normalize.tif"));
//        ConnectOutToIn(normalize, 0, saveImage, 0);
//-------------
        // compute gradients
        ConnectOutToIn(normalize, 0, scharr_xy, 0);
//save --------
//        SetParameter(pFilename, DspParameter(DspParameter::String, "/home/swanner/Projects/openlf/build/scharr_y.tif"));
//        ConnectOutToIn(scharr_xy, 0, saveImage, 0);
//        SetParameter(pFilename, DspParameter(DspParameter::String, "/home/swanner/Projects/openlf/build/scharr_x.tif"));
//        ConnectOutToIn(scharr_xy, 1, saveImage, 0);
//-------------
        // make tensor from gradients
        ConnectOutToIn(scharr_xy, 0, tensor, 0);
        ConnectOutToIn(scharr_xy, 1, tensor, 1);
        // smooth tensor components
        ConnectOutToIn(tensor, 0, outer_gauss_0, 0);
        ConnectOutToIn(tensor, 1, outer_gauss_1, 0);
        ConnectOutToIn(tensor, 2, outer_gauss_2, 0);
//save --------
//        SetParameter(pFilename, DspParameter(DspParameter::String, "/home/swanner/Projects/openlf/build/st_0.tif"));
//        ConnectOutToIn(tensor, 0, saveImage, 0);
//        SetParameter(pFilename, DspParameter(DspParameter::String, "/home/swanner/Projects/openlf/build/st_1.tif"));
//        ConnectOutToIn(tensor, 1, saveImage, 0);
//        SetParameter(pFilename, DspParameter(DspParameter::String, "/home/swanner/Projects/openlf/build/st_2.tif"));
//        ConnectOutToIn(tensor, 2, saveImage, 0);
//-------------
        // connect st channels to  merge operator
        ConnectOutToIn(outer_gauss_0, 0, tensor2orientation, 0);
        ConnectOutToIn(outer_gauss_1, 0, tensor2orientation, 1);
        ConnectOutToIn(outer_gauss_2, 0, tensor2orientation, 2);
//save --------
//        SetParameter(pFilename, DspParameter(DspParameter::String, "/home/swanner/Projects/openlf/build/orientation.tif"));
//        ConnectOutToIn(tensor2orientation, 0, saveImage, 0);
//-------------
        // return orientation
        ConnectOutToOut(tensor2orientation, 0, 0);
        
        //==========================================
        
        
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
            outer_gauss_0.SetParameter(0, DspParameter(DspParameter::ParamType::Float, outer_scale));
            outer_gauss_0.SetParameter(1, DspParameter(DspParameter::ParamType::Float, outer_scale));
            outer_gauss_1.SetParameter(0, DspParameter(DspParameter::ParamType::Float, outer_scale));
            outer_gauss_1.SetParameter(1, DspParameter(DspParameter::ParamType::Float, outer_scale));
            outer_gauss_2.SetParameter(0, DspParameter(DspParameter::ParamType::Float, outer_scale));
            outer_gauss_2.SetParameter(1, DspParameter(DspParameter::ParamType::Float, outer_scale));
            return true;
        }
        if (index == pFilename) {
            std::cout << "Parameter Update filename : " << *param.GetString() << std::endl;
            saveImage.SetParameter(0, DspParameter(DspParameter::ParamType::String, *param.GetString()));
            return true;
        }
    }
    
    WKF_StructureTensor::~WKF_StructureTensor() { 
 
    };
}}