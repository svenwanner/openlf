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

/**
 * \brief ...
 *
 * ...
 *
 * \note ...
 *
 * \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 * 
 */

#ifndef GLOBAL_HPP
#define	GLOBAL_HPP

#include <cctype>

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <limits> 
#include <vector>
#include <string>
#include <math.h>
#include <list>
#include <map>




#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/lexical_cast.hpp>

//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/contrib/contrib.hpp>
//#include <opencv2/core/core.hpp>

#include <vigra/stdimagefunctions.hxx>
#include <vigra/multi_convolution.hxx>
#include <vigra/transformimage.hxx>
#include <vigra/flatmorphology.hxx>
#include <vigra/inspectimage.hxx>
#include <vigra/convolution.hxx>
#include <vigra/resizeimage.hxx>
#include <vigra/multi_impex.hxx>
#include <vigra/multi_array.hxx>
#include <vigra/impexalpha.hxx>
#include <vigra/tv_filter.hxx>
#include <vigra/hdf5impex.hxx>
#include <vigra/stdimage.hxx>
#include <vigra/impex.hxx>

#include <H5Cpp.h>

//using namespace std;


typedef enum {NONE,LF_4D,LF_3DH,LF_3DV,LF_CROSS} LF_TYPE;
typedef enum {HORIZONTAL,VERTICAL} DIRECTION;

struct OpenLF_Exception : public std::exception
{
   std::string s;
   OpenLF_Exception(std::string ss) : s(ss) {}
   ~OpenLF_Exception() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};

#endif	/* GLOBAL_HPP */

