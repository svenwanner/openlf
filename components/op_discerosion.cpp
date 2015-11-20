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
* Author Sven Wanner, Maximilian Diebold, Hendrik Siedelmann 
*
*/
//#include <vigra/flatmorphology.hxx>
//#include "openlf/operator_macro.hpp"

//#define OPENLF_OP_CONSTRUCT_PARAMS \
//    AddParameter_("radius", DspParameter(DspParameter::ParamType::Int, 0)); \

//OPENLF_OLDAPI_OP_START(OP_DiscErosion, 1, 1, 3, 3)

// TODO Vigra discErosion() is only compatible with integer data ranging from 0..255. So this is incompatible with the FlexMAV, which supports other data types as well.


//  int radius = *op->GetParameter(0)->GetInt();
//    for (int i=0; i < in[0]->shape()[2]; ++i){
//        vigra::MultiArrayView<2, T> channel_in = in[0]->bindAt(2, i);
//        vigra::MultiArrayView<2, T> channel_out = out[0]->bindAt(2, i);
//        vigra::discErosion(channel_in,channel_out, radius);
//    }

//OPENLF_OLDAPI_OP_END(OP_DiscErosion, 1, 1, 3, 3)

//
//#undef OPENLF_OP_CONSTRUCT_PARAMS
