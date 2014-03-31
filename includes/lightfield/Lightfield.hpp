/* 
 * File:   Lightfield.hpp
 * Author: swanner
 *
 * Created on March 31, 2014, 1:07 PM
 */

#ifndef LIGHTFIELD_HPP
#define	LIGHTFIELD_HPP

#include "global.hpp"
//#include "lightfield/io.hpp"
#include "lightfield/Properties.hpp"
#include "lightfield/DataHandler.hpp"
#include "lightfield/FileHandler.hpp"


namespace OpenLF { 
    namespace lightfield { 

class Lightfield {
public:
    Lightfield(string filename);
    Lightfield(const Lightfield& orig);
    virtual ~Lightfield();
    
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

