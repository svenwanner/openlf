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

#pragma once
#ifndef WKF_STRUCTURETENSOR_HPP
#define WKF_STRUCTURETENSOR_HPP


#define DEMO_IN_PATH "bla"
#define DEMO_OUT_PATH "blub"

#include "openlf.hpp"

namespace openlf { 
    namespace components {

    class WKF_StructureTensor : public DspCircuit {
        private:
            DspCircuit *circ_structuretensor = std::nullptr_t();
            OP_LoadImage *img_in = std::nullptr_t();
            OP_SaveImage *img_out = std::nullptr_t();
            OP_Gauss *gauss = std::nullptr_t();
        public:
          WKF_StructureTensor() {
              
            // 1. Create a DspCircuit where we can route our components
            circ_structuretensor = new DspCircuit;
            img_in = new OP_LoadImage;
            img_out = new OP_SaveImage;
            gauss = new OP_Gauss;
                
            // 2. Create instances of the components needed for our circuit
            circ_structuretensor->AddComponent(img_in, "LoadImage");
            circ_structuretensor->AddComponent(img_out, "SaveImage");
            circ_structuretensor->AddComponent(gauss, "Gauss");
            
            img_in->SetParameter(0, DspParameter(DspParameter::FilePath, DEMO_IN_PATH))
            img_out->SetParameter(0, DspParameter(DspParameter::FilePath, DEMO_OUT_PATH))

            circ_structuretensor->ConnectOutToIn(img_in, 0, gauss, 0);
            circ_structuretensor->ConnectOutToIn(gauss, 0, img_out, 0);
          };
          
          ~circuit_demo() { 
            delete circ_structuretensor;
            delete img_in;
            delete img_out;
            delete gauss;
          };
          
        protected:
          virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
          
         
    };

}} //namespace openlf::components

#endif /* WKF_STRUCTURETENSOR_HPP */



/*

class circuit_demo

{
private:
	// 1. Create a DspCircuit 
	DspCircuit *circuit = std::nullptr_t();
	// 2. Create instances of the components
	SignalGenerator *signal1 = std::nullptr_t();
	SignalGenerator *signal2 = std::nullptr_t();
	SignalPrinter *boolPrinter = std::nullptr_t();
	DspAnd *logicAnd = std::nullptr_t();

public:
	
	// 2. Configure component IO buses
	// ===============================
	circuit_demo(){
		// 1. Create a DspCircuit where we can route our components
		circuit = new DspCircuit;
		signal1 = new SignalGenerator;
		signal2 = new SignalGenerator;
		boolPrinter = new SignalPrinter;
		logicAnd = new DspAnd;
		// 2. Create instances of the components needed for our circuit
		circuit->AddComponent(logicAnd, "Logic AND");
		circuit->AddComponent(signal1, "Input Signal1");
		circuit->AddComponent(signal2, "Input Signal2");
		circuit->AddComponent(boolPrinter, "Bool Printer");

		circuit->ConnectOutToIn(signal1, 0, logicAnd, 0);
		circuit->ConnectOutToIn(signal2, 0, logicAnd, 1);
		circuit->ConnectOutToIn(logicAnd, 0, boolPrinter, 0);
		//OR circuit.ConnectOutToIn("Logic AND", 0, "Bool Printer", 0);
		//OR circuit.ConnectOutToIn("Logic AND", "output", "Bool Printer", 0);

	};
	~circuit_demo(){ delete circuit;
		delete signal1;
		delete signal2;
		delete boolPrinter;
		delete logicAnd; };

	void run(){ 
		circuit->Tick(); 
		circuit->Reset(); 
	};

	void show(QtpMain &tool){
		tool.registerComponent(*logicAnd->getCompInfo("Logic AND"));
		tool.registerComponent(*signal1->getCompInfo("Input Signal1"));
		tool.registerComponent(*signal2->getCompInfo("Input Signal2"));
		tool.registerComponent(*boolPrinter->getCompInfo("Bool Printer"));
		tool.show();
	}

	void release(){
		delete circuit;
		delete signal1;
		delete signal2;
		delete boolPrinter;
		delete logicAnd;
	};

};


#endif // CIRCUIT_DEMO_H
 
 */