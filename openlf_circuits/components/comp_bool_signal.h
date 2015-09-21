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

#ifndef COMP_BOOL_SIGNAL_H
#define COMP_BOOL_SIGNAL_H

#include "DSPatch.h"
#include <iostream>
#include "gui\includes\QtpComp.h"
#include <iostream>

// 1. Derive component class from DspComponent
// ===========================================

class SignalGenerator : public DspComponent
{
private:
	QtpComp::CompInfo *info;

public:
	// 2. Configure component IO buses
	// ===============================
	SignalGenerator(){
		AddOutput_("output");
	};

	QtpComp::CompInfo *getCompInfo(const char *name){
		info = new QtpComp::CompInfo;
		info->typeId = 3;
		info->typeName = QString(name);
		info->inPins;
		info->outPins << "output";
		return info;
	}

protected:
	// 3. Implement virtual Process_() method
	// ======================================
	virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs){
		// read image given as first command-line argument
		vigra::ImageImportInfo imageInfo("D:/LF-repos/openlf_gui/openlf_gui/gui/data/lenna.png");
		// print some information:
		std::cout << "Image information:\n";
		std::cout << "  file format: " << imageInfo.getFileType() << std::endl;
		std::cout << "  width:       " << imageInfo.width() << std::endl;
		std::cout << "  height:      " << imageInfo.height() << std::endl;
		std::cout << "  pixel type:  " << imageInfo.getPixelType() << std::endl;
		std::cout << "  color image: ";
		if (imageInfo.isColor())    std::cout << "yes (";
		else                        std::cout << "no  (";
		std::cout << "number of channels: " << imageInfo.numBands() << ")\n";

		vigra::MultiArray<2, UINT8> imageArray(imageInfo.shape());
		vigra::importImage(imageInfo, imageArray);

		//std::cout << "Input Pointer: " << &image << std::endl;
		outputs.SetValue(0, imageArray); //OR outputs.SetValue("output", bool1 && bool2);
	};

};

#endif // COMP_BOOL_SIGNAL_H