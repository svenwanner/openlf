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


}}
#endif	/* HELPERS_HPP */
