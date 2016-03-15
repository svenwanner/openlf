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
#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>
#include <vigra/transformimage.hxx>
#include <vigra/copyimage.hxx>
#include <vigra/multi_array.hxx>

#include <limits>

#include "openlf/operator_macro.hpp"

#define OPENLF_OP_CONSTRUCT_PARAMS \
    AddParameter_("filename", DspParameter(DspParameter::ParamType::String, ""));

OPENLF_VIGRA_OP_START(OP_Imwrite, 1, 1, 3, 3)
if(in[0].shape()[2] == 1) {
	vigra::MultiArrayView<2, T> out_im = in[0].bindAt(2, 0);
	exportImage(out_im, *op->GetParameter(0)->GetString());
}
else if (in[0].shape()[2] == 3 || in[0].shape()[2] == 4) {
    vigra::MultiArray<2, vigra::RGBValue<T> > out_im(in[0].shape()[0], in[0].shape()[1]);

    vigra::MultiArrayView<2, T> r(out_im.bindElementChannel(0));
    vigra::MultiArrayView<2, T> g(out_im.bindElementChannel(1));
    vigra::MultiArrayView<2, T> b(out_im.bindElementChannel(2));

    vigra::MultiArrayView<2, T> r_in;
    r_in = in[0].bindAt(2, 0);
    vigra::MultiArrayView<2, T> g_in;
    g_in = in[0].bindAt(2, 1);
    vigra::MultiArrayView<2, T> b_in;
    b_in = in[0].bindAt(2, 2);

    r = r_in;
    g = g_in;
    b = b_in;

	exportImage(out_im, *op->GetParameter(0)->GetString());
}
std::cout << "image saved!" <<std::endl;
out[0] = in[0];

OPENLF_OP_END

#undef OPENLF_OP_CONSTRUCT_PARAMS
