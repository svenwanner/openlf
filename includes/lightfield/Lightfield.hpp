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

#ifndef LIGHTFIELD_HPP
#define	LIGHTFIELD_HPP

#include "global.hpp"
#include "lightfield/io.hpp"
#include "lightfield/Properties.hpp"
#include "lightfield/DataHandler.hpp"
#include "lightfield/FileHandler.hpp"


namespace OpenLF { 
    namespace lightfield { 

class Lightfield {
public:
    Lightfield();
    Lightfield(string filename);
    Lightfield(const Lightfield& orig);
    virtual ~Lightfield();

    
    
    
    //! open lightfields from  hdf5 or config file
    /*!
     \param filename of the .cfg, .h5,.hdf5 or .lf file 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool open(string filename);
    
    
    //! open lightfields from  hdf5 or config file
    /*!
     \param filename of the .cfg, .h5,.hdf5 or .lf file 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool open(const char* filename);
    
    
    
    
    
    
    //! check if a specific property exist
    /*!
     \param name of the property to check for
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool has_property(string name);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool get_property(string name, int &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool get_property(string name, float &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool get_property(string name, double &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool get_property(string name, string &value);
    
    
    //! get the LF_TYPE
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    LF_TYPE type();
    
    
    
    
    
    
    //! get pointer to data channels
    /*!
     Returns a pointer to the channels map containing the data.
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    map< string,vigra::MultiArray<2,float> > * data();
    
    //! set pointer passed to address data channels
    /*!
     \param channels pointer to a channels map to get the address of the internal map
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void data(map< string,vigra::MultiArray<2,float> > **channels);
    
    //! get pointer to specific channel
    /*!
     Returns a pointer to the channel specified by the channel_name.
     If the channel key doesn't exist a NULL pointer is returned.
     \param channel_name the name of the channel
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    vigra::MultiArray<2,float> *data(string channel_name);
    
    //! set pointer passed to the address of the channel specified
    /*!
     Returns a pointer to the channel specified by the channel_name.
     If the channel key doesn't exist a NULL pointer is returned.
     \param channel_name the name of the channel
     \param channel_data pointer to a MultiArray to get the address of the internal channel specified
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void data(string channel_name, vigra::MultiArray<2,float> ** channel_data);
    
    
private:
    map< string,vigra::MultiArray<2,float> > channels; 
    OpenLF::lightfield::io::DataHandler *dataHandler;
    OpenLF::lightfield::Properties properties;
};

}}
#endif	/* LIGHTFIELD_HPP */

