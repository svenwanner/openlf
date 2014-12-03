/* 
 * File:   Lightfield3D.hpp
 * Author: kiryl
 *
 * Created on December 2, 2014, 11:53 AM
 */

#ifndef LIGHTFIELD3D_HPP
#define	LIGHTFIELD3D_HPP

#include "OpenLF/global.hpp"
#include "OpenLF/image/utils.hpp"
#include "OpenLF/lightfield/io.hpp"
#include "OpenLF/lightfield/Properties.hpp"
#include "OpenLF/lightfield/DataHandler.hpp"
#include "OpenLF/lightfield/FileHandler.hpp"
#include "OpenLF/lightfield/Lightfield.hpp"

namespace OpenLF { 
    namespace lightfield { 
        
class Lightfield_3D : public Lightfield {
public:
    friend class EpiIterator;
    Lightfield_3D();
    Lightfield_3D(const std::string filename);
    //Lightfield_3D(const Lightfield& orig);
    virtual ~Lightfield_3D();  
    
protected:
    //! get a view to a vertical epi of the channel specified for the 3DV lightfield case
    /*!
     \param x fixed column image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift parameter in pixel
    */
    vigra::MultiArrayView<2,float> _getVerticalEpiChannel_3DV(int x, std::string channel_name, int focus);
        
        };
    }
}

#endif	/* LIGHTFIELD3D_HPP */

