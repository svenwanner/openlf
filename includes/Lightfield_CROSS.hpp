/* 
 * File:   Lightfield_CROSS.hpp
 * Author: kiryl
 *
 * Created on December 2, 2014, 11:57 AM
 */

#ifndef LIGHTFIELD_CROSS_HPP
#define	LIGHTFIELD_CROSS_HPP

#include "OpenLF/global.hpp"
#include "OpenLF/image/utils.hpp"
#include "OpenLF/lightfield/io.hpp"
#include "OpenLF/lightfield/Properties.hpp"
#include "OpenLF/lightfield/DataHandler.hpp"
#include "OpenLF/lightfield/FileHandler.hpp"
#include "OpenLF/lightfield/Lightfield.hpp"

namespace OpenLF { 
    namespace lightfield { 
        
class Lightfield_CROSS : public Lightfield {
public:
    friend class EpiIterator;
    Lightfield_CROSS();
    Lightfield_CROSS(const std::string filename);
    //Lightfield_CROSS(const Lightfield& orig);
    virtual ~Lightfield_CROSS();  
    
protected:
    //! get a view to a vertical epi of the channel specified for the 3DV lightfield case
    /*!
     \param x fixed column image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift parameter in pixel
    */
    vigra::MultiArrayView<2,float> _getVerticalEpiChannel_Cross(int x, std::string channel_name, int focus);
       
        };
    }
}

#endif	/* LIGHTFIELD_CROSS_HPP */

