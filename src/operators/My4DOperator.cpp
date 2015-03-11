/*
* Copyright (c) 2014 Sven Wanner
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
*/

#include "OpenLF/operators/My4DOperator.hpp"

//My4DOperator::My4DOperator(const My4DOperator& orig) {
//}

OpenLF::operators::My4DOperator::~My4DOperator() 
{
    print(1,"My4DOperator::~My4DOperator() called...");
}

void OpenLF::operators::My4DOperator::allocate() 
{
    //==========================================
    // Here you need to allocate channels in the 
    // passed light field to store your results.
    //========================================== 
    
    
    // allocate a new channel to store your results
    lf->allocateChannel("myNewChannel");
}

void OpenLF::operators::My4DOperator::precompute() 
{
    //============================================
    // For pre-computation steps on the input data 
    // implement this method. Each operator has a
    // member variable called tmp_memory to keep
    // data temporarily during this process chain
    //============================================
    
    
    
    //**********************************************************************************
    //**************** this is the demo code which can be replaced ********************* 
    
    // allocate some memory to store stuff you may need in compute and post-compute but
    // only during computation. This map is deleted after the operator has finished.
    tmp_memory["aTmpStorage"] = OpenLF::image::ImageChannel(lf->width(),lf->height());
    
    // compute something of importance to use in compute and in postcompute
    if(lf->hasChannel("r") && lf->hasChannel("g") && lf->hasChannel("b")) {
        
        float* r_ptr = lf->channel_ptr("r");
        float* g_ptr = lf->channel_ptr("g");
        float* b_ptr = lf->channel_ptr("b");
        
        for(int n=0; n<lf->width()*lf->height(); n++) {
            tmp_memory["aTmpStorage"].data()[n] = 0.3*r_ptr[n]+0.59*g_ptr[n]+0.11*b_ptr[n];    
        }
    }
    else {
        for(int n=0; n<lf->width()*lf->height(); n++) {
            tmp_memory["aTmpStorage"].data()[n] = 1.0f;
        }
    }
    
    //**************** this is the demo code which can be replaced ********************* 
    //**********************************************************************************
}

void OpenLF::operators::My4DOperator::compute() 
{
    //============================================
    // This method is the main computation step to
    // compute your results and to store them in 
    // your allocated channels within your passed
    // light field class.
    //============================================
    

    
  
    //**********************************************************************************
    //**************** this is the demo code which can be replaced ********************* 
    
    // compute the most useful property ever if the input is a rgb light field
    // and store it in your new channel myNewChannel
    if(lf->hasChannel("r") && lf->hasChannel("g") && lf->hasChannel("b")) {
        
        float* r_ptr = lf->channel_ptr("r");
        float* g_ptr = lf->channel_ptr("g");
        float* b_ptr = lf->channel_ptr("b");
        float* nChannel = lf->channel_ptr("myNewChannel");
        
        for(int n=0; n<lf->width()*lf->height(); n++) {
            nChannel[n] = abs(tmp_memory["aTmpStorage"].data()[n]-r_ptr[n]);
            nChannel[n] += abs(tmp_memory["aTmpStorage"].data()[n]-g_ptr[n]);
            nChannel[n] += abs(tmp_memory["aTmpStorage"].data()[n]-b_ptr[n]);
            if(nChannel[n]<0.0f || nChannel[n]>1.0f)
                nChannel[n] = 0.0f;
        }
    }
    else {
        cout << "This operator does nothing to gray value light fields!" << endl;
    }
    
    //**************** this is the demo code which can be replaced ********************* 
    //**********************************************************************************
}

void OpenLF::operators::My4DOperator::postcompute() 
{
    //====================================================
    // This method can be used to do some pre-computations
    //====================================================
    
    
    
    //**********************************************************************************
    //**************** this is the demo code which can be replaced *********************
    
    // do a postprocessing using your data from precompute and from compute as well
    float* nChannel = lf->channel_ptr("myNewChannel");
    for(int n=0; n<lf->width()*lf->height(); n++) {
        if(nChannel[n] > tmp_memory["aTmpStorage"].data()[n])
            nChannel[n] = 1.0f;
        else
            nChannel[n] = 0.0;
    }
    
    //**************** this is the demo code which can be replaced ********************* 
    //**********************************************************************************
}
