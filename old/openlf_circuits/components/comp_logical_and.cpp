/*
* Copyright (c) 2015 Heidelberg Colaboratory for Image Processing
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
* Author Maximilian Diebold
*/
#include "components/comp_logical_and.h"

// 3. Implement virtual Process_() method
// ======================================

void DspAnd::Process_(DspSignalBus& inputs, DspSignalBus& outputs){
	// create local stack variables to hold input values

	vigra::MultiArray<2, UINT8> imageArray1;
	vigra::MultiArray<2, UINT8> imageArray2;
	inputs.GetValue(0, imageArray1);
	inputs.GetValue(1, imageArray2);

	std::cout << "Input Signal 1: " << imageArray1.shape() << std::endl;
	std::cout << "Input Signal 2: " << imageArray2.shape() << std::endl;


	// set output as the result of bool1 AND bool2
	outputs.SetValue(0, imageArray1); //OR outputs.SetValue("output", bool1 && bool2);
}