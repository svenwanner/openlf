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

#include "op_saveimage.hpp"

namespace openlf { 
    namespace components {

    OP_SaveImage::OP_SaveImage() {
        // add inputs
        AddInput_("ImgIn");
        // add parameter
        pFilePath = AddParameter_("OutPath", DspParameter(DspParameter::FilePath, ""));
    }
    
    void OP_LoadImage::Process_(DspSignalBus& inputs, DspSignalBus& outputs) {
        
    }
    
    bool OP_SaveImage::ParameterUpdating_(int index, const DspParameter& param) {
        
        if (index == pFilePath) {
            filePath = param.GetString()->c_str();
            return true;
        }
    }

}}