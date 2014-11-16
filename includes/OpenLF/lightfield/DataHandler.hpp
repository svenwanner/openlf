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

#include "OpenLF/global.hpp"
#include "OpenLF/image/Channel.hpp"
#include "OpenLF/lightfield/Properties.hpp"



namespace OpenLF { 
    namespace lightfield { 
        namespace io {
            
            
/*!
 * This class is a pure virtual class setting the name of the passed configfile
 * and does the parsing. It defines a virtual function readData(&channels) which
 * needs to be overwritten by a derived class aiming to take care of the data
 * handling and storing within the channels object. To handle any data reading 
 * derive from this class, which is a member of each LightField instance, and take
 * care of a correct sorting of your data and storing in the channel reference. 
 */
class DataHandler {
public:
    DataHandler();
    DataHandler(const std::string config_filename, Properties *properties);
    DataHandler(const char* config_filename, Properties *properties);
    virtual ~DataHandler();
    
    //! set the config file
    /*!
     \param config_filename is the filename of the configfile 
     \param properties an instance of a Properties instance to parse and hold the parameter
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */ 
    void setConfigfile(const std::string config_filename);
    
    //! set the config file
    /*!
     \param config_filename is the filename of the configfile 
     \param properties an instance of a Properties instance to parse and hold the parameter
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */ 
    void setConfigfile(const char* config_filename);
    
    virtual bool readData(std::map<std::string,OpenLF::image::ImageChannel>& channels) = 0;
    
protected:
    std::string m_type;            //!< type of input config_filename, disc or buffer
    std::string m_config_filename; //!< the passed config_filename string
    Properties *m_properties; //!< pointer to store the address of a properties instance

};

}}}
#endif	/* DATAHANDLER_HPP */

