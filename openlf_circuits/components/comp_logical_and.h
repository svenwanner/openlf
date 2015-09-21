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

#ifndef COMP_LOGICAL_AND_H
#define COMP_LOGICAL_AND_H


#include "vigra/imageinfo.hxx"
#include "vigra/multi_array.hxx"
#include <vigra/stdimage.hxx>
#include <vigra/impex.hxx>

#include "DSPatch.h"
#include <iostream>
#include "gui/includes/QtpComp.h"
#include <string>
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


// 1. Derive component class from DspComponent
// ===========================================
class DspAnd : public DspComponent
{
private:
	QtpComp::CompInfo *info;

public:
	
	// 2. Configure component IO buses
	// ===============================
	DspAnd(){
		// add 2 inputs
		AddInput_("input1");
		AddInput_("input2");
		// add 1 output
		AddOutput_("output");
	};
	QtpComp::CompInfo *getCompInfo(const char *name){
		info = new QtpComp::CompInfo;
		info->typeId = 2;
		info->typeName = QString(name);
		info->inPins << "input1" << "input2";
		info->outPins << "output";
		return info;
	}


protected:
	// 3. Implement virtual Process_() method in cpp
	// =============================================
	virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
};

#endif // COMP_LOGICAL_AND_H