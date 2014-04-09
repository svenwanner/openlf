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

#ifndef FILEHANDLER_HPP
#define	FILEHANDLER_HPP

#include "debug.hpp"
#include "global.hpp"
#include "image/io.hpp"
#include "lightfield/io.hpp"
#include "image/Channel.hpp"
#include "lightfield/Properties.hpp"
#include "lightfield/DataHandler.hpp"



namespace OpenLF { 
    namespace lightfield { 
        namespace io {
            

/*!
 * This class is derived from the pure virtual class DataHandler and implements 
 * the data reading from the harddrive. The passed configfile is parsed within
 * the DataHandler baseclass and if the source value in the configfile is not set
 * to "cam", the type is set to "disc". The FileHandler then checks the source 
 * variable if its a hdf5 file, an image file or a path to a filesequence and loads
 * the data respectively. The passed Properties instance is filled with all parameters 
 * from the configfile and the data are set when the readData method is called.
 */
class FileHandler : public DataHandler {
public:
    FileHandler();
    FileHandler(string config_filename, Properties *properties);
    FileHandler(const char* config_filename, Properties *properties);
    virtual ~FileHandler();   
    
    
    //! reads light field data from from the FileHandler
    /*!
     This method reads light field data from the FileHandler. The passed channels
     map is filled with data depending on the source value in the configfile.
     \param channels map object of string labels as keys and MultiArrays as data 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */ 
    bool readData(map<string,image::ImageChannel>& channels);
    
    
    
    
protected:
    string disc_source;         //!< is "cam" or the path to the data on the harddrive
    




    
    //! reads lightfield data from disc
    /*!
     \param channels map object of string labels as keys and MultiArrays as data 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */ 
    bool read_from_disc(map<string,image::ImageChannel>& channels);
};


}}}
#endif	/* FILEHANDLER_HPP */

