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
    
    string source_check;
    source_check = OpenLF::helpers::find_ftype(source);
    
    if(source_check=="h5") {
        print(3,"lightfield::io::FileHandler::read(string,map) got an hdf5 file...");
        
        return true;
    }
    else if(source_check=="png"  || source_check=="PNG" || source_check=="jpg" || 
            source_check=="JPEG" ||source_check=="JPG"  || source_check=="tif" || 
            source_check=="TIF"  || source_check=="bmp" || source_check=="BMP"  )
    {
        
        return true;
    }
    else if(boost::filesystem::is_directory(source_check)) {
        print(3,"lightfield::io::FileHandler::read(string,map) got a path...");

        return true;
    }
    else {
        warning("Failed to identify input data source. Either hdf5 file is broken or path doesn't exist");
        return false;   
    }
}


