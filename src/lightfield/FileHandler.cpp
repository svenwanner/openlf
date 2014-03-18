/* 
 * File:   FileHandler.cpp
 * Author: swanner
 * 
 * Created on March 18, 2014, 9:12 AM
 */

#include "lightfield/FileHandler.hpp"

OpenLF::lightfield::io::FileHandler::FileHandler() 
{
    print(1,"lightfield::io::FileHandler::FileHandler() called...");
}

OpenLF::lightfield::io::FileHandler::FileHandler(string, map<string,vigra::MultiArray<2,float> >& channels) 
{
    print(1,"lightfield::io::FileHandler::FileHandler(string,map) called...");
}

OpenLF::lightfield::io::FileHandler::FileHandler(const FileHandler& orig) 
{
    print(1,"lightfield::io::FileHandler::FileHandler(FileHandler&) called...");
}

OpenLF::lightfield::io::FileHandler::~FileHandler() 
{
    print(1,"lightfield::io::FileHandler::~FileHandler() called...");
}

bool OpenLF::lightfield::io::FileHandler::read(string source, map<string,vigra::MultiArray<2,float> >& channels) 
{
    print(1,"lightfield::io::FileHandler::read(string,map) called...");
    
    return true;
}


