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
    
    type = "";
    disc_source = "";
    buffer_source = NULL;
}

OpenLF::lightfield::io::DataHandler::DataHandler(string source) 
{
    print(1,"lightfield::io::DataHandler::DataHandler(string source) called...");
    
    type = "";
    disc_source = "";
    buffer_source = NULL;
    
    set_source(source);
}

OpenLF::lightfield::io::DataHandler::DataHandler(const char* source) 
{
    print(1,"lightfield::io::DataHandler::DataHandler(string source) called...");
    
    type = "";
    disc_source = "";
    buffer_source = NULL;
    
    set_source(source);
}

//OpenLF::lightfield::io::DataHandler::DataHandler(const DataHandler& orig) 
//{
//    print(1,"lightfield::io::DataHandler::DataHandler(DataHandler&) called...");
//}

OpenLF::lightfield::io::DataHandler::~DataHandler() 
{
    print(1,"lightfield::io::DataHandler::~DataHandler() called...");
}








void OpenLF::lightfield::io::DataHandler::set_source(string source)
{
    print(1,"lightfield::io:::DataHandler::set_source(source) called...");
    
    string ftype = OpenLF::helpers::find_ftype(source);
    
    if(ftype=="cfg") {
        parser.parse(source);
        
        // read properties from parsed configfile 
        int lft;
        parser.get_field("type",lft);
        switch(lft) {
            case 1: properties.type = LF_4D; break;
            case 2: properties.type = LF_3DH; break;
            case 3: properties.type = LF_3DV; break;
            case 4: properties.type = LF_CROSS; break;
            default: properties.type = NONE;
        }
        parser.get_field("width",properties.width);
        parser.get_field("height",properties.height);
        parser.get_field("cams_h",properties.cams_h);
        parser.get_field("cams_v",properties.cams_v);
        parser.get_field("baseline_h",properties.baseline_h);
        parser.get_field("baseline_v",properties.baseline_v);
        parser.get_field("focal_length",properties.baseline_v);
        parser.get_field("horopter",properties.horopter);
        
        string source_type;
        parser.get_field("source",source_type);
        
        // check if source is hardware device or configfile
        if(source_type == "cam") {
            //TODO: Here later camera data should be handled
            //TODO: via the source type different types of cameras can be managed
            type = "buffer";
        }
        else {
            
            type = "disc"; // set data reading type 
            disc_source = source_type; // set disc source type as specified in config file
        }
    }
}
 
void OpenLF::lightfield::io::DataHandler::set_source(const char* source)
{
    print(1,"lightfield::io:::DataHandler::set_source(source) called...");
    
    string str_source(source);
    set_source(str_source);
}



bool OpenLF::lightfield::io::DataHandler::read(map<string,vigra::MultiArray<2,float> >& channels, 
                                               LF_Properties &properties) 
/* Test: */
{
    print(1,"lightfield::io:::DataHandler::read(channels,properties) called...");
    
    if(type=="") {
        throw OpenLF_Exception("lightfield::io::DataHandler, no source specified!");
        return false;
    }
    else if(type=="disc") {
        bool status = read_from_disc(disc_source, channels, this->properties);
        copy_properties(properties);
        return status;
    }
    else if(type=="buffer") {
//        return read_from_buffer(buffer_source, channels, this->properties);
        return false;
    }
    else return false;
}








/*##############################################################################
 *##############      P R I V A T E   M E T H O D S      #######################
 *##############################################################################*/

bool OpenLF::lightfield::io::DataHandler::read_from_disc(string source, 
                                               map<string,vigra::MultiArray<2,float> >& channels,
                                               LF_Properties &properties) 
/* Test: */
{
    print(1,"lightfield::io::DataHandler::read_from_disc(source,channels,properties) called...");
    
    string source_check;
    source_check = OpenLF::helpers::find_ftype(source);
    
    cout << "source " << source << endl;
    cout << "source check " << source_check << endl;
    
    if(source_check=="h5") {
        print(3,"lightfield::io::DataHandler::read(string,map) got an hdf5 file...");
        
        return OpenLF::lightfield::io::load_from_hdf5(disc_source,channels,properties);
    }
    else if(boost::filesystem::is_directory(source_check)) {
        print(3,"lightfield::io::DataHandler::read(string,map) got a path...");

        return OpenLF::lightfield::io::load_from_filesequence(disc_source,channels,properties);
    }
    else if(source_check=="png"  || source_check=="PNG" || source_check=="jpg" || 
            source_check=="JPEG" ||source_check=="JPG"  || source_check=="tif" || 
            source_check=="TIF"  || source_check=="bmp" || source_check=="BMP"  )
    {
        print(3,"lightfield::io::DataHandler::read(string,map) got an image file...");
        
        return OpenLF::image::io::imread(source,channels);
    }
    else {
        warning("Failed to identify input data source. Either hdf5 file is broken or path doesn't exist");
        return false;   
    }
}



//bool OpenLF::lightfield::io::DataHandler::read_from_buffer(float* source, 
//                                                           map<string,vigra::MultiArray<2,float> >& channels,
//                                                           LF_Properties &properties) 
///* Test: */
//{
//    // TODO maybe later the camera data interface
//    source = NULL;
//    return true;
//}


void OpenLF::lightfield::io::DataHandler::copy_properties(LF_Properties &properties) 
{
    properties.type = this->properties.type;
    properties.width = this->properties.width;
    properties.height = this->properties.height;
    properties.cams_h = this->properties.cams_h;
    properties.cams_v = this->properties.cams_v;
    properties.horopter = this->properties.horopter;
    properties.baseline_h = this->properties.baseline_h;
    properties.baseline_v = this->properties.baseline_v;
    properties.focal_length = this->properties.focal_length;
}