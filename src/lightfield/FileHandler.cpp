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

#include "OpenLF/lightfield/FileHandler.hpp"

namespace OpenLF {
namespace lightfield {
namespace io {


FileHandler::FileHandler() : DataHandler()
{
    print(1,"lightfield::io::FileHandler::FileHandler() called...");
    
    disc_source = "";
}

FileHandler::FileHandler(std::string config_filename, Properties *properties) : DataHandler(config_filename,properties)
{
    print(1,"lightfield::io::FileHandler::FileHandler(config_filename,*properties) called...");
    
    disc_source = "";
}

FileHandler::FileHandler(const char* config_filename, Properties *properties) : DataHandler(config_filename,properties)
{
    print(1,"lightfield::io::FileHandler::FileHandler(config_filename,*properties) called...");
    
    disc_source = "";
}

FileHandler::~FileHandler()
{
    print(1,"lightfield::io::FileHandler::~FileHandler() called...");
}



bool FileHandler::readData(std::map<std::string,image::ImageChannel>& channels)
{
    print(1,"lightfield::io:::FileHandler::readData(channels) called...");
    
    if(type=="") {
        throw OpenLF_Exception("lightfield::io::FileHandler, no source specified!");
        return false;
    }
    else if(type=="disc") {
        return __readFromDisc__(channels);
    }
    else return false;
}








/*##############################################################################
 *##############      P R I V A T E   M E T H O D S      #######################
 *##############################################################################*/

/*!
 * This method reads lightfield data from the hard drive. It first checks if the 
 * source variable specified in the configfile is a filename by detecting a filetype.
 * The result is stored in the variable source check and is either the type of the file
 * and if no filetype is found the source itself. It then tries to use the source_check
 * to decide how to load the data. Possibilities are from hdf5, image files or if no
 * filetype was found it interprets the source as a directory containing an image sequence.
 * If the source is not an absolute path the method tries to check if the path is a valid
 * path relative to the location of the configfile.
 */
bool FileHandler::__readFromDisc__(std::map<std::string,image::ImageChannel>& channels)
{
    print(1,"lightfield::io::FileHandler::read_from_disc(channels) called...");
    
    // set disc source type as specified in config file
    properties->get_field("source",disc_source);
    
    // check if source is path or filename by checking the filetype
    std::string source_check;
    source_check = helpers::find_ftype(disc_source);
    
    
    //##########################################################################
    //       if a file type was found and it's h5 read from hdf5 file
    //##########################################################################
    if(source_check=="h5" || source_check=="hdf5" || source_check=="lf") {
        print(2,"lightfield::io::FileHandler::read_from_disc(channels) got an hdf5 file...");
        
        // if the file exist read it
        if (boost::filesystem::exists( disc_source )) {
            print(2,"lightfield::io::FileHandler::read_from_disc(channels) got an absolute hdf5 path...");
                
            return load_from_hdf5(disc_source,channels,*properties);
        }
        // if not, check if path of configfile plus the value of source is a valid filename
        else {
            // make an absolute path from configfile name and the string relative path from configfile source variable
            std::string abs_path = helpers::make_absolute_path(config_filename,disc_source);
            
            // check if this is now a valid path
            if(boost::filesystem::exists(abs_path)) {
                print(2,"lightfield::io::FileHandler::read_from_disc(channels) got an relative image path...");
            
                return load_from_hdf5(abs_path,channels,*properties);
            }
            // if not there is nothing more to do
            else {
                std::string msg = "Failed to identify input data source: \n" + abs_path + "\n File broken or path doesn't exist";
                warning(msg);
                return false; 
            }
        }
    }
    
    //##########################################################################
    //         if the file type is an image type read an image file
    //##########################################################################
    else if(source_check=="png"  || source_check=="PNG" || source_check=="jpg" || 
            source_check=="JPEG" ||source_check=="JPG"  || source_check=="tif" || 
            source_check=="TIF"  || source_check=="bmp" || source_check=="BMP"  )
    {
        print(2,"lightfield::io::FileHandler::read_from_disc(channels) got an image file...");
        
        // if the file exist read it
        if (boost::filesystem::exists( disc_source )) {
            print(2,"lightfield::io::FileHandler::read_from_disc(channels) got an absolute image path...");
                
            return image::io::imread(disc_source,channels);
        }
        // if not, check if path of configfile plus the value of source is a valid filename
        else {
            // make an absolute path from configfile name and the string relative path from configfile source variable
            std::string abs_path = helpers::make_absolute_path(config_filename,disc_source);
            
            // check if this is now a valid path
            if(boost::filesystem::exists(abs_path)) {
                print(2,"lightfield::io::FileHandler::read_from_disc(channels) got an relative image path...");
            
                return image::io::imread(abs_path,channels);
            }
            // if not there is nothing more to do
            else {
                std::string msg = "Failed to identify input data source: \n" + abs_path + "\n File broken or path doesn't exist";
                warning(msg);
                return false; 
            }
        }
    }
    
    //##################################################################################
    // if the source_check is no file type check if it is an absolute or a relative path
    //##################################################################################
    else {
        // check if last character of path is a '/', if not append one
        if(source_check.back() != '/')
            source_check += "/";
        
        // if the source property in the configfile is a absolute path read from file sequence
        if(boost::filesystem::is_directory(source_check)) {
            print(2,"lightfield::io::FileHandler::read_from_disc(channels) got an absolute path...");
            return load_from_filesequence(source_check,channels,properties);
        }
        // if not, check if path of configfile plus the value of source is a valid path
        else {
            // make an absolute path from configfile name and the string relative path from configfile source variable
            std::string abs_path = helpers::make_absolute_path(config_filename,source_check);
            
            // check if this is now a valid path
            if(boost::filesystem::is_directory(abs_path)) {
                print(2,"lightfield::io::FileHandler::read_from_disc(channels) got an relative path...");
                return load_from_filesequence(abs_path,channels,properties);
            }
            // if not there is nothing more to do
            else {
                std::string msg = "Failed to identify input data source: \n" + disc_source + "\n File broken or path doesn't exist";
                warning(msg);
                return false;   
            }
        }     
    }
}

} // namespace io
} // namespace lightfield
} // namespace OpenLF

