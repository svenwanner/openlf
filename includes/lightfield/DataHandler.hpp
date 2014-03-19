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

#include "global.hpp"
#include "image/io.hpp"
#include "lightfield/io.hpp"
#include "lightfield/properties.hpp"



namespace OpenLF { 
    namespace lightfield { 
        namespace io {
            

class DataHandler {
public:
    DataHandler();
    DataHandler(string, map<string,vigra::MultiArray<2,float> >& channels);
    DataHandler(const DataHandler& orig);
    virtual ~DataHandler();
    
    //! reads lightfield data from disc
    /*!
     This method reads lightfield data from disc. As source can be passed a directory
     of image files, a hdf5 file or a single image file containing the 4D lightfield.
     The data are read and set into the passed channel reference.
     \param source full path of the lightfield image file, a directory or a hdf5 file
     \param channels map object of string labels as keys and MultiArrays as data 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */ 
    bool read(string source, map<string,vigra::MultiArray<2,float> >& channels);
    
    //! camera data interface
    /*!
     \note not yet implemented but could serve as a later camera interface 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool read(float* source, map<string,vigra::MultiArray<2,float> >& channels);
    
private:

};


}}}
#endif	/* DATAHANDLER_HPP */

