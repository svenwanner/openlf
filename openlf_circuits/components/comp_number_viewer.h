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
#pragma once

#ifndef COMP_NUMBER_VIEWER_H
#define COMP_NUMBER_VIEWER_H


#include "DSPatch.h"
#include <iostream>
#include "gui\includes\QtpComp.h"

class SignalPrinter : public DspComponent
{
private:
	QtpComp::CompInfo *info;

public:
	// 2. Configure component IO buses
	// ===============================
	SignalPrinter(){
		AddInput_("input");
	};

	QtpComp::CompInfo *getCompInfo(const char *name){
		info = new QtpComp::CompInfo;
		info->typeId = 1;
		info->typeName = QString(name);
		info->inPins << "input";
		info->outPins;
		return info;
	}

protected:
	// 3. Implement virtual Process_() method
	// ======================================
	virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs){
		vigra::MultiArray<2, UINT8> imageArray1;
		inputs.GetValue(0, imageArray1);
		std::cout << "Output Signal: " << imageArray1.shape() << std::endl;
	};

};


#endif // COMP_NUMBER_VIEWER_H