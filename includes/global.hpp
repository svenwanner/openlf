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

using namespace std;


//bool debug(int);
//void print(int,const char*);
//void print(int,const char*,const char*);



/*****************************************************************************
 *                     D E B U G   H E L P E R S
 *****************************************************************************/


static const int DEBUG_LEVEL = 3;

/// This method controls the debug level for console output
inline bool debug(int debug_level) {
    if(DEBUG_LEVEL >= debug_level) return true;
    else return false;
};

/// This method causes console output for specific debug level
inline void print(int debug_level, const char* text) {
    if(DEBUG_LEVEL >= debug_level) 
        cout << text << endl;
};

/// This method causes console output for specific debug level
inline void print(int debug_level, const char* text1, const char* text2) {
    if(DEBUG_LEVEL >= debug_level) 
        cout << text1 << " " << text2 << endl;
};

#endif	/* GLOBAL_HPP */

