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


#ifndef _OPENLF_OP_OPERATORS_H
#define _OPENLF_OP_OPERATORS_H

#include "clif/clif_vigra.hpp"
#include "clif/flexmav.hpp"
#include "dspatch/DspParameter.h"
#include "dspatch/DspComponent.h"

#include "operator_macro.hpp"

namespace openlf {
    namespace components {



  /*! \brief Simple vigra based gaussian smoothing operator
   * 
   * Dimension separated vigra based gaussian smoothing operator.
   * 
   * \param x blur <float> blur scale in x dimension
   * \param y blur <float> blur scale in y dimension
   */
  OPENLF_OP_CLASS_HEADER(OP_VigraGauss, 1, 1, 3, 3)

  /*! \brief Disc dilation operator
   *
   * Dimension separated vigra based disc dilation operator.
   *
   * \param radius <int> Radius of the disc used for dilation
   */
  OPENLF_OP_CLASS_HEADER(OP_DiscDilation, 1, 1, 3, 3)

  /*! \brief Disc erosion operator
   *
   * Dimension separated vigra based disc erosion operator.
   *
   * \param radius <int> Radius of the disc used for erosion
   */
  OPENLF_OP_CLASS_HEADER(OP_DiscErosion, 1, 1, 3, 3)

  /*! \brief Disc median operator
   *
   * Dimension separated vigra based median filter using a disc of given radius.
   * \param radius <int> Radius of the disc used for the filter.
   */
  OPENLF_OP_CLASS_HEADER(OP_DiscMedian, 1, 1, 3, 3)

  /*! \brief Gaussian sharpening operator
   *
   * Dimension separated vigra based gaussian sharpening filter.
   * \param sharpening_factor <double> Sharpening factor.
   * \param scale <double> Scale
   */
  OPENLF_OP_CLASS_HEADER(OP_GaussianSharpening, 1, 1, 3, 3)





 /*! \brief Simple vigra gradient magnitude operator
  *
  * Pre-bluring gradient magnitude operator.
  *
  * \param scale <float> pre-bluring scale
  */
  OPENLF_OP_SINGLE2D_CLASS_HEADER(OP_VigraGradientMagnitude)
  //============================================================================   
          
          
  /*! \brief Simple horizontal scharr gradient operator
   * 
   * Horizontal scharr gradient operator
   */
  OPENLF_OP_CLASS_HEADER(OP_ScharrX, 1, 1, 3, 3)
  //============================================================================

          
          
  /*! \brief Simple vertical scharr gradient operator
   * 
   * Vertical scharr gradient operator
   */
  OPENLF_OP_CLASS_HEADER(OP_ScharrY, 1, 1, 3, 3)
  //============================================================================
          
          
  /*! \brief Simple horizontal plus vertical scharr gradient operator
   * 
   * Horizontal (X outslot 0) and vertical (y outslot 1) scharr gradient operator
   */
  OPENLF_OP_CLASS_HEADER(OP_Scharr, 1, 2, 3, 3)
  //============================================================================
          
          
 /*! \brief Normalization operator
   * 
   * Normalizes input and converts to float
   */
  OPENLF_OP_CLASS_HEADER(OP_Normalize, 1, 1, 3, 3)
  //============================================================================
          
          
  /*! \brief Tensor operator
   * 
   * Operator builds a tensor from incoming channel slots (channel 0 called x, channel 1 called y)
   * Output are 3 channels [xx, xy, yy] 
   */
  OPENLF_OP_CLASS_HEADER(OP_Tensor2x2, 2, 3, 3, 3)
  //============================================================================
       
 
  /*! \brief merge tensor color components operator
   * 
   * If a incoming tensor has rgb tensor components, merge them to a single tensor component 
   * Output are 3 channels [xx, xy, yy] 
   */
  OPENLF_OP_CLASS_HEADER(OP_AverageChannels, 1, 1, 3, 3)
  //============================================================================
          
          
   /*! \brief Tensor operator
   * 
   * Operator builds a tensor from incoming channel slots (channel 0 called x, channel 1 called y)
   * Output are 3 channels [xx, xy, yy] 
   */
  OPENLF_OP_CLASS_HEADER(OP_Tensor2Orientation, 3, 2, 3, 3)
  //============================================================================
          
          
  /*! \brief Tensor operator
   * 
   * Operator builds a tensor from incoming channel slots (channel 0 called x, channel 1 called y)
   * Output are 3 channels [xx, xy, yy] 
   */
  //FIXME zero output count not working (MSVC)
  OPENLF_OP_CLASS_HEADER(OP_SaveImage, 1, 1, 3, 3)
  //============================================================================
  
  
  OPENLF_OP_CLASS_HEADER(OP_MergeDispByCoherence, 2, 2, 3, 3)
  
  OPENLF_OP_CLASS_HEADER(OP_Test, 1, 1, 3, 3)
  
}} //namespace openlf::components

#endif