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


#ifndef _OPENLF_OP_OPERATORS_H
#define _OPENLF_OP_OPERATORS_H

#include "openlf.hpp"
#include "clif/flexmav.hpp"

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
  OPENLF_OP_CLASS_HEADER(OP_VigraGauss)
  //============================================================================
          
          
   /*! \brief Simple vigra gradient magnitude operator
   * 
   * Pre-bluring gradient magnitude operator.
   * 
   * \param scale <float> pre-bluring scale
   */
  OPENLF_OP_CLASS_HEADER(OP_VigraGradientMagnitude)
  //============================================================================   
          
          
  /*! \brief Simple horizontal scharr gradient operator
   * 
   * Horizontal scharr gradient operator
   */
  OPENLF_OP_CLASS_HEADER(OP_ScharrX)
  //============================================================================
          
          
  /*! \brief Simple vertical scharr gradient operator
   * 
   * Vertical scharr gradient operator
   */
  OPENLF_OP_CLASS_HEADER(OP_ScharrY)
  //============================================================================
}} //namespace openlf::components

#endif