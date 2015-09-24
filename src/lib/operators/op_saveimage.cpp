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

#include "vigra/multi_array.hxx"
#include "operators.hpp"

#define OPENLF_OP_CONSTRUCT_PARAMS \
    AddParameter_("filename", DspParameter(DspParameter::ParamType::String, "")); \

OPENLF_OP_START(OP_SaveImage, 1, 0, 3, 3)   
        
    
    if (in[0]->shape()[2] == 1) {
        vigra::MultiArrayView<2, T> channel_in = in[0]->bindAt(2, 0);
        exportImage(channel_in, *op->GetParameter(0)->GetString());
    }
    else if (in[0]->shape()[2] == 3 || in[0]->shape()[2] == 4){
        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt16> > channel_in(in[0]->shape()[0], in[0]->shape()[1]);
        vigra::MultiArrayView<2, vigra::UInt16> r(channel_in.bindElementChannel(0));
        vigra::MultiArrayView<2, vigra::UInt16> g(channel_in.bindElementChannel(1));
        vigra::MultiArrayView<2, vigra::UInt16> b(channel_in.bindElementChannel(2));
        
        vigra::MultiArrayView<2, vigra::UInt16> r_in;
        r_in = in[0]->bindAt(2, 0);
        vigra::MultiArrayView<2, vigra::UInt16> g_in;
        g_in = in[0]->bindAt(2, 1);
        vigra::MultiArrayView<2, vigra::UInt16> b_in;
        b_in = in[0]->bindAt(2, 2);
        
        r = r_in;
        g = g_in;
        b = b_in;
//        std::cout << in[0]->shape()[0] << " " << in[0]->shape()[1] << " " << in[0]->shape()[2] << std::endl;
//        std::cout << channel_in.shape()[0] << " " << channel_in.shape()[1] << " " << channel_in.shape()[2] << std::endl;
//        int n=0;
//        for (int i=0; i<in[0]->shape()[0]; i++) {
//            for (int j=0; j<in[0]->shape()[1]; j++) {
//                r.data()[n] = in[0]->data()[n];
//                g.data()[n] = in[0]->data()[n];
//                b.data()[n] = in[0]->data()[n];
//                n++;
//            }
//        }
        exportImage(channel_in, *op->GetParameter(0)->GetString());
    }
    
OPENLF_OP_END(OP_SaveImage, 1, 0, 3, 3)