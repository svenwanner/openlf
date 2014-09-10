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

#include "OpenLF/lightfield/DataHandler.hpp"


namespace OpenLF {
namespace lightfield {
namespace io {

DataHandler::DataHandler()
{
    print(1,"lightfield::io::DataHandler::DataHandler() called...");
    
    type = "";
}

DataHandler::DataHandler(std::string config_filename, Properties *properties)
{
    print(1,"lightfield::io::DataHandler::DataHandler(config_filename,*properties) called...");
    
    type = "";
    
    this->properties = properties;
    setConfigfile(config_filename);
}

DataHandler::DataHandler(const char* config_filename, Properties *properties)
{
    print(1,"lightfield::io::DataHandler::DataHandler(config_filename,*properties) called...");
    
    type = "";
   
    this->properties = properties;
    setConfigfile(config_filename);
}

DataHandler::~DataHandler()
{
    print(1,"lightfield::io::DataHandler::~DataHandler() called...");
    
}





/*!
* This method is the entry point for data initialization. The passed string is thought
* to be a path to a configfile. If not see the comment later in the else section. The
* passed Properties instance is in fact a configparser parsing the configfile and storing
* all the parameter. Pipe this thing through wherever you need the properties. After parsing the 
* configfile this method checks the important source parameter in the configfile. If this
* is the string "cam" it later should handle the data from a buffer if not this function 
* set the type of data handling to "disc" which means the source parameter is automatically
* interpreted as a filename of a single image file containing the light field, a hdf5 file
* or a path storing the images as single image files. 
*/
void DataHandler::setConfigfile(std::string config_filename)
{
    print(1,"lightfield::io:::DataHandler::set_configfile(config_filename,&properties) called...");
    
    this->config_filename = config_filename;
    
    std::string ftype = helpers::find_ftype(config_filename);
    
    
    if(ftype=="cfg") {
        
        // parse configfile
        try {
            properties->parse(config_filename);
        } catch(std::exception &e) {
            warning(e.what());
        }
        
        std::string source_type;
        properties->get_field("source",source_type);
        
        // check if source is a camera then handle data from buffer else handle from disc
        if(source_type == "cam") {
            type = "buffer"; // set data reading type buffer
        }
        else { 
            type = "disc"; // set data reading type to disc
        }
    }
    else {
        warning("lightfield::io::DataHandler::set_configfile(config_filename) expects a  configfile as input!");
        throw OpenLF_Exception("Missing Configfile!");
    }
}
 
void DataHandler::setConfigfile(const char* config_filename)
{
    print(1,"lightfield::io:::DataHandler::set_configfile(config_filename) called...");
    
    std::string tmp(config_filename);
    setConfigfile(tmp);
}

} // namespace io
} // namespace lightfield
} // namespace OpenLF
