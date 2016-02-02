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

#include <vigra/convolution.hxx>
#include <vigra/multi_convolution.hxx>

#include <opencv2/imgproc/imgproc.hpp>

#include "openlf/operator_macro.hpp"


using namespace cv;
using namespace vigra;

#define OPENLF_OP_CONSTRUCT_PARAMS

OPENLF_VIGRA_OP_START_OUTTYPE(OP_Scharr, 1, 2, 3, 3, float)
        
  /*Kernel1D<float> D;
  D.initExplicitly(-1,1) = -1.0/2.0, 0.0, 1.0/2.0;
  D.setBorderTreatment(BORDER_TREATMENT_REFLECT);
  Kernel1D<float> S;
  S.initExplicitly(-1,1) = 3.0/16.0, 10.0/16.0, 3.0/16.0;
  S.setBorderTreatment(BORDER_TREATMENT_REFLECT);
              
  convolveMultiArrayOneDimension(*in[0], *out[0], 1, D);
  convolveMultiArrayOneDimension(*out[0], *out[0], 0, S);
  
  convolveMultiArrayOneDimension(*in[0], *out[1], 0, D);
  convolveMultiArrayOneDimension(*out[1], *out[1], 1, S);*/
    
  //this is 21x times faster than above vigra code
  for (int i=0; i < in[0].shape()[2]; ++i) {
    vigra::MultiArrayView<2,T> ch_in = in[0].bindAt(2, i);
    //FIXME X should come first!
    vigra::MultiArrayView<2,float> ch_out_x = out[1].bindAt(2, i);
    vigra::MultiArrayView<2,float> ch_out_y = out[0].bindAt(2, i);
    cv::Mat cv_in(Size(ch_in.shape(0), ch_in.shape(1)), BaseType2CvDepth(in_mat[0]->type()), ch_in.data());
    cv::Mat cv_out_x(Size(ch_out_x.shape(0), ch_out_x.shape(1)), BaseType2CvDepth(out_mat[0]->type()), ch_out_x.data());
    cv::Mat cv_out_y(Size(ch_out_y.shape(0), ch_out_y.shape(1)), BaseType2CvDepth(out_mat[0]->type()), ch_out_y.data());
    /*cv::Mat mask;
    
    cv::dilate(cv_in, mask, cv::Mat());
    cv::threshold(mask, mask, 0, 1, cv::THRESH_BINARY_INV);
    mask.convertTo(mask, CV_8U);*/
    
    Scharr(cv_in, cv_out_x, CV_32F, 1, 0);
    //cv_out_x.setTo(0, mask);
    Scharr(cv_in, cv_out_y, CV_32F, 0, 1);
    //cv_out_y.setTo(0, mask);
  }
  //FIXME hack - need better treatment of the border between background and shifted epi
  for(int c=0;c<(*in_mat[0])[2];c++)
    for(int j=0;j<(*in_mat[0])[1];j++)
      for(int i=0;i<(*in_mat[0])[0];i++)
        if (in[0](i, j, c) == 0)
          for(int y=std::max(j-1,0);y<std::min(j+2, (*in_mat[0])[1]);y++)
            for(int x=std::max(i-1,0);x<std::min(i+2, (*in_mat[0])[0]);x++) {
              out[0](x, y, c) = 0;
              out[1](x, y, c) = 0;
            }
    
OPENLF_OP_END

#undef OPENLF_OP_CONSTRUCT_PARAMS
