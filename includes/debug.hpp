/* 
 * File:   debug.hpp
 * Author: swanner
 *
 * Created on March 24, 2014, 9:56 AM
 */

#ifndef DEBUG_HPP
#define	DEBUG_HPP

#include "global.hpp"



/*****************************************************************************
 *                     D E B U G   H E L P E R S
 *****************************************************************************/

const int DEBUG_LEVEL = 0;

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

/// This method causes console output for specific debug level
inline void print(int debug_level, const char* text1, int text2) {
    if(DEBUG_LEVEL >= debug_level && debug_level>0) {
        string space = "";
        for(int i=0; i<debug_level; i++)
            space.append("-");
        space.append("> ");
        cout << DEBUGCOLOR[debug_level] << space.c_str() << text1 << " " << text2 << DEBUGCOLOR[0] << endl;
    }
};

/// This method causes console output for specific debug level
inline void print(int debug_level, const char* text1, float text2) {
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

#endif	/* DEBUG_HPP */

