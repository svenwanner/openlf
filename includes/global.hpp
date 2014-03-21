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



#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <math.h>
#include <list>
#include <map>

#include <H5Cpp.h>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/lexical_cast.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>

#include <vigra/stdimagefunctions.hxx>
#include <vigra/multi_convolution.hxx>
#include <vigra/transformimage.hxx>
#include <vigra/flatmorphology.hxx>
#include <vigra/inspectimage.hxx>
#include <vigra/convolution.hxx>
#include <vigra/resizeimage.hxx>
#include <vigra/multi_impex.hxx>
#include <vigra/multi_array.hxx>
#include <vigra/tv_filter.hxx>
#include <vigra/hdf5impex.hxx>
#include <vigra/stdimage.hxx>
#include <vigra/impex.hxx>





using namespace std;




/*****************************************************************************
 *                     D E B U G   H E L P E R S
 *****************************************************************************/

struct OpenLF_Exception : public exception
{
   string s;
   OpenLF_Exception(string ss) : s(ss) {}
   ~OpenLF_Exception() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};


const int DEBUG_LEVEL = 3;

#define RED          "\033[22;31m" 

const vector<const char*> DEBUGCOLOR = {"\033[0;40;37m","\033[1;40;32m","\033[1;40;35m","\033[1;40;36m","\033[1;40;33m","\033[1;40;31m"};


/// This method controls the debug level for console output
inline bool debug(int debug_level) {
    if(DEBUG_LEVEL >= debug_level) return true;
    else return false;
};

/// This method causes console output for specific debug level
inline void print(int debug_level, const char* text) {
    if(DEBUG_LEVEL >= debug_level && debug_level>0) {
        string space = "";
        for(int i=0; i<debug_level; i++)
            space.append("-");
        space.append("> ");
        cout << DEBUGCOLOR[debug_level] << space.c_str() << text << DEBUGCOLOR[0] << endl;
    }
};

/// This method causes console output for specific debug level
inline void print(int debug_level, const char* text1, const char* text2) {
    if(DEBUG_LEVEL >= debug_level && debug_level>0) {
        string space = "";
        for(int i=0; i<debug_level; i++)
            space.append("-");
        space.append("> ");
        cout << DEBUGCOLOR[debug_level] << space.c_str() << text1 << " " << text2 << DEBUGCOLOR[0] << endl;
    }
};

inline void warning(const char* text) 
{
    cout << RED << "WARNING: " << text << "!" << DEBUGCOLOR[0] << endl; 
};

inline void msg(const char* text) 
{
    cout << DEBUGCOLOR[0] << "# msg: " << text << DEBUGCOLOR[0] << endl; 
};

inline void msg(string text) 
{
    cout << DEBUGCOLOR[0] << "# msg: " << text << DEBUGCOLOR[0] << endl; 
};

inline void msg(const char* text, int num) 
{
    cout << DEBUGCOLOR[0] << "# msg: " << text << " : " << num << DEBUGCOLOR[0] << endl; 
};

inline void msg(string text, float num) 
{
    cout << DEBUGCOLOR[0] << "# msg: " << text << " : " << num << DEBUGCOLOR[0] << endl; 
};

#endif	/* GLOBAL_HPP */

