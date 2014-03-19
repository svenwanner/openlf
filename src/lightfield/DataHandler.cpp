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

#include "lightfield/DataHandler.hpp"


OpenLF::lightfield::io::DataHandler::DataHandler() 
{
    print(1,"lightfield::io::DataHandler::DataHandler() called...");
}

OpenLF::lightfield::io::DataHandler::DataHandler(string, map<string,vigra::MultiArray<2,float> >& channels) 
{
    print(1,"lightfield::io::DataHandler::DataHandler(string,map) called...");
}

OpenLF::lightfield::io::DataHandler::DataHandler(const DataHandler& orig) 
{
    print(1,"lightfield::io::FileHandler::DataHandler(DataHandler&) called...");
}

OpenLF::lightfield::io::DataHandler::~DataHandler() 
{
    print(1,"lightfield::io::DataHandler::~DataHandler() called...");
}




bool OpenLF::lightfield::io::DataHandler::read(string source, map<string,vigra::MultiArray<2,float> >& channels) 
{
    print(1,"lightfield::io::DataHandler::read(string,map) called...");
    
    string source_check;
    source_check = OpenLF::helpers::find_ftype(source);
    
    if(source_check=="h5") {
        print(3,"lightfield::io::DataHandler::read(string,map) got an hdf5 file...");
        
        return true;
    }
    else if(boost::filesystem::is_directory(source_check)) {
        print(3,"lightfield::io::DataHandler::read(string,map) got a path...");

        return true;
    }
    else if(source_check=="png"  || source_check=="PNG" || source_check=="jpg" || 
            source_check=="JPEG" ||source_check=="JPG"  || source_check=="tif" || 
            source_check=="TIF"  || source_check=="bmp" || source_check=="BMP"  )
    {
        print(3,"lightfield::io::DataHandler::read(string,map) got an image file...");
        
        return true;
    }
    else {
        warning("Failed to identify input data source. Either hdf5 file is broken or path doesn't exist");
        return false;   
    }
}



bool OpenLF::lightfield::io::DataHandler::read(float* source, map<string,vigra::MultiArray<2,float> >& channels) 
{
    // TODO maybe later the camera data interface
    return true;
}
