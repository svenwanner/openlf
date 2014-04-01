#include "debug.hpp"
#include "global.hpp"

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
