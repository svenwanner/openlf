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
        DspParameter pmincoh = DspParameter(DspParameter::Float, 0.5f);
                
        // add parameter
        pInnerScale = AddParameter_("InnerScale", pinner);
        pOuterScale = AddParameter_("OuterScale", pouter);   
        pMinCoherence = AddParameter_("MinCoherence", pmincoh); 
        
        // set parameter
        SetParameter(pInnerScale, pinner);
        SetParameter(pOuterScale, pouter);  
        SetParameter(pMinCoherence, pmincoh);
    
        // add components
        AddComponent(inner_gauss, "InnerSmoothing");
        AddComponent(scharr_yx, "Gradients");
        AddComponent(normalize, "Normalize");
        AddComponent(mergeChannel_0, "AverageChannel_0");
        AddComponent(mergeChannel_1, "AverageChannel_1");
        AddComponent(mergeChannel_2, "AverageChannel_2");
        AddComponent(outer_gauss_0, "OuterSmoothing_0");
        AddComponent(outer_gauss_1, "OuterSmoothing_1");
        AddComponent(outer_gauss_2, "OuterSmoothing_2");
        AddComponent(tensor, "Tensor");
        AddComponent(tensor2orientation, "Tensor2Orientation");
        
        
        
        // ################## DEBUG #########################
        DspParameter pfilename_1 = DspParameter(DspParameter::String, "");
        DspParameter pfilename_2 = DspParameter(DspParameter::String, "");
        DspParameter pfilename_3 = DspParameter(DspParameter::String, "");
        DspParameter pfilename_4 = DspParameter(DspParameter::String, "");
        DspParameter pfilename_5 = DspParameter(DspParameter::String, "");
        DspParameter pfilename_6 = DspParameter(DspParameter::String, "");
        DspParameter pfilename_7 = DspParameter(DspParameter::String, "");
        DspParameter pfilename_8 = DspParameter(DspParameter::String, "");
        pFilename_1 = AddParameter_("Filename1", pfilename_1);
        pFilename_2 = AddParameter_("Filename2", pfilename_2);
        pFilename_3 = AddParameter_("Filename3", pfilename_3);
        pFilename_4 = AddParameter_("Filename4", pfilename_4);
        pFilename_5 = AddParameter_("Filename5", pfilename_4);
        pFilename_6 = AddParameter_("Filename6", pfilename_5);
        pFilename_7 = AddParameter_("Filename7", pfilename_7);
        pFilename_8 = AddParameter_("Filename8", pfilename_8);
        SetParameter(pFilename_1, pfilename_1);
        SetParameter(pFilename_2, pfilename_2);
        SetParameter(pFilename_3, pfilename_3);
        SetParameter(pFilename_4, pfilename_4);
        SetParameter(pFilename_5, pfilename_5);
        SetParameter(pFilename_6, pfilename_6); 
        SetParameter(pFilename_7, pfilename_7); 
        SetParameter(pFilename_8, pfilename_8);
        AddComponent(saveImage_1, "SaveImage1");
        AddComponent(saveImage_2, "SaveImage2");
        AddComponent(saveImage_3, "SaveImage3");
        AddComponent(saveImage_4, "SaveImage4");
        AddComponent(saveImage_5, "SaveImage5");
        AddComponent(saveImage_6, "SaveImage6");
        AddComponent(saveImage_7, "SaveImage7");
        AddComponent(saveImage_8, "SaveImage8");
        // ##################################################
        
        //========== Connect Operators =============
        
        // inner smoothing
        ConnectInToIn(0, inner_gauss, 0);
//save --------
        SetParameter(pFilename_1, DspParameter(DspParameter::String, "./inner_scale.tif"));
        ConnectOutToIn(inner_gauss, 0, saveImage_1, 0);
//-------------
        // normalize input
        ConnectOutToIn(inner_gauss, 0, normalize, 0);
        // compute gradients
        ConnectOutToIn(normalize, 0, scharr_yx, 0);
//save --------
        SetParameter(pFilename_2, DspParameter(DspParameter::String, "./scharr_y.tif"));
        ConnectOutToIn(scharr_yx, 0, saveImage_2, 0);
        SetParameter(pFilename_3, DspParameter(DspParameter::String, "./scharr_x.tif"));
        ConnectOutToIn(scharr_yx, 1, saveImage_3, 0);
//-------------
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
//save --------
        SetParameter(pFilename_4, DspParameter(DspParameter::String, "./st_0.tif"));
        ConnectOutToIn(tensor, 0, saveImage_4, 0);
        SetParameter(pFilename_5, DspParameter(DspParameter::String, "./st_1.tif"));
        ConnectOutToIn(tensor, 1, saveImage_5, 0);
        SetParameter(pFilename_6, DspParameter(DspParameter::String, "./st_2.tif"));
        ConnectOutToIn(tensor, 2, saveImage_6, 0);
//-------------
        // connect st channels to  merge operator
        ConnectOutToIn(outer_gauss_0, 0, tensor2orientation, 0);
        ConnectOutToIn(outer_gauss_1, 0, tensor2orientation, 1);
        ConnectOutToIn(outer_gauss_2, 0, tensor2orientation, 2);
//save --------
        SetParameter(pFilename_7, DspParameter(DspParameter::String, "./orientation.tif"));
        ConnectOutToIn(tensor2orientation, 0, saveImage_7, 0);
        SetParameter(pFilename_8, DspParameter(DspParameter::String, "./coherence.tif"));
        ConnectOutToIn(tensor2orientation, 1, saveImage_8, 0);
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
        if (index == pMinCoherence) {
            min_coherence = *param.GetFloat();
            std::cout << "Parameter Update min_coherence: " << min_coherence << std::endl;
            tensor2orientation.SetParameter(0, DspParameter(DspParameter::ParamType::Float, min_coherence));
            return true;
        }
        
        
        
        if (index == pFilename_1) {
            std::cout << "Parameter Update filename 1 : " << *param.GetString() << std::endl;
            saveImage_1.SetParameter(0, DspParameter(DspParameter::ParamType::String, *param.GetString()));
            return true;
        }
        if (index == pFilename_2) {
            std::cout << "Parameter Update filename 2 : " << *param.GetString() << std::endl;
            saveImage_2.SetParameter(0, DspParameter(DspParameter::ParamType::String, *param.GetString()));
            return true;
        }
        if (index == pFilename_3) {
            std::cout << "Parameter Update filename 3 : " << *param.GetString() << std::endl;
            saveImage_3.SetParameter(0, DspParameter(DspParameter::ParamType::String, *param.GetString()));
            return true;
        }
        if (index == pFilename_4) {
            std::cout << "Parameter Update filename 4 : " << *param.GetString() << std::endl;
            saveImage_4.SetParameter(0, DspParameter(DspParameter::ParamType::String, *param.GetString()));
            return true;
        }
        if (index == pFilename_5) {
            std::cout << "Parameter Update filename 5 : " << *param.GetString() << std::endl;
            saveImage_5.SetParameter(0, DspParameter(DspParameter::ParamType::String, *param.GetString()));
            return true;
        }
        if (index == pFilename_6) {
            std::cout << "Parameter Update filename 6 : " << *param.GetString() << std::endl;
            saveImage_6.SetParameter(0, DspParameter(DspParameter::ParamType::String, *param.GetString()));
            return true;
        }
        if (index == pFilename_7) {
            std::cout << "Parameter Update filename 7 : " << *param.GetString() << std::endl;
            saveImage_7.SetParameter(0, DspParameter(DspParameter::ParamType::String, *param.GetString()));
            return true;
        }
        if (index == pFilename_8) {
            std::cout << "Parameter Update filename 8 : " << *param.GetString() << std::endl;
            saveImage_8.SetParameter(0, DspParameter(DspParameter::ParamType::String, *param.GetString()));
            return true;
        }
    }
    
    WKF_StructureTensor::~WKF_StructureTensor() { 
 
    };
}}