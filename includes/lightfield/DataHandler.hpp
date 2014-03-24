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

#ifndef DATAHANDLER_HPP
#define	DATAHANDLER_HPP

#include "debug.hpp"
#include "global.hpp"
#include "image/io.hpp"
#include "lightfield/io.hpp"
#include "utils/ConfigParser.hpp"
#include "lightfield/properties.hpp"



namespace OpenLF { 
    namespace lightfield { 
        namespace io {
            

class DataHandler {
public:
    DataHandler();
    DataHandler(string source);
    DataHandler(const char* source);
    DataHandler(const DataHandler& orig);
    virtual ~DataHandler();   
    
    
    
    
    //! set the source file
    /*!
     \param source filename of the configfile 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */ 
    void set_source(string source);
    
    //! set the source file
    /*!
     \param source filename of the configfile 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */ 
    void set_source(const char* source);
    
    //! reads light field data from from the DataHandler
    /*!
     This method reads light field data from the DataHandler. The passed channels
     map and the LF_Properties object are filled with data specified through the configfile
     \param channels map object of string labels as keys and MultiArrays as data 
     \param properties struct storing the important parameter 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */ 
    bool read(map<string,vigra::MultiArray<2,float> >& channels, LF_Properties &properties);
    
    
    
    
private:
    string type;
    string disc_source;
    float* buffer_source;
    LF_Properties properties;
    ConfigParser parser;





    
    //! reads lightfield data from disc
    /*!
     This method reads lightfield data from disc. As source can be passed a directory
     of image files, a hdf5 file or a single image file containing the 4D lightfield.
     The data are read and set into the passed channel reference. A property struct
     has to be passed, too.
     \param source full path of the lightfield image file, a directory or a hdf5 file
     \param channels map object of string labels as keys and MultiArrays as data 
     \param properties struct storing the important parameter 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */ 
    bool read_from_disc(string source, map<string,vigra::MultiArray<2,float> >& channels, LF_Properties &properties);
    
    //! camera data interface
    /*!
     \note not yet implemented but could serve as a later camera interface 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool read_from_buffer(float* source, map<string,vigra::MultiArray<2,float> >& channels, LF_Properties &properties);
    
    //! copies a LF_Property object
    /*!
     \param properties struct storing the important parameter  
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void copy_properties(LF_Properties &properties);
};


}}}
#endif	/* DATAHANDLER_HPP */

