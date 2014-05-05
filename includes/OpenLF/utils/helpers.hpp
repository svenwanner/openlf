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


#include "OpenLF/debug.hpp"
#include "OpenLF/global.hpp"

#ifndef HELPERS_HPP
#define	HELPERS_HPP

namespace OpenLF { 
    namespace helpers {
 
        
//! find filetype.
/*!
 Checks filepath string for filetype and returns it 
 \param filepath 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
string find_ftype(string filepath);
    


//! find filenames in directory.
/*!
 Fills a passed vector reference with filenames of files in directory 
 \param dir directory to search for files
 \param list to store the filenames 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool filenames_from_directory(string dir, vector<string> &list);


//! removes spaces and tabs from a string
/*!
 \param input string
 \param result string without spaces and tabs
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void remove_leading_spaces_from_string(string input,string &result);


//! concats the dir of the passed filename and the relative part passed
/*!
 \param filename 
 \param relative_part to append to the dir of the filename param
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
string make_absolute_path(string filename, string relative_part); 


//! removes a element from a string vector by value
/*!
 \param list the vector to remove an item from 
 \param value the value to be removed
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool remove_by_value(vector<string> &list, string value);


void get_attribute_list(string filename, string GroupID, vector<string> &attrs, vector<bool> &isString);

}}
#endif	/* HELPERS_HPP */
