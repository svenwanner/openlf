
#ifndef LIGHTFIELD_4D_HPP
#define	LIGHTFIELD_4D_HPP

#include "OpenLF/global.hpp"
#include "OpenLF/image/utils.hpp"
#include "OpenLF/lightfield/io.hpp"
#include "OpenLF/lightfield/Properties.hpp"
#include "OpenLF/lightfield/DataHandler.hpp"
#include "OpenLF/lightfield/FileHandler.hpp"
#include "OpenLF/lightfield/Lightfield.hpp"

namespace OpenLF { 
    namespace lightfield { 
        
class Lightfield_4D : public Lightfield {
public:
    friend class EpiIterator;
    Lightfield_4D();
    Lightfield_4D(const std::string filename);
    //Lightfield_3D(const Lightfield& orig);
    virtual ~Lightfield_4D();  
 
protected:
    //! get a view to a horizontal epi of the channel specified for the 4D lightfield case
    /*!
     \param v fixed vertical camera index
     \param y fixed row image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift parameter in pixel
    */
    vigra::MultiArrayView<2,float> _getHorizontalEpiChannel_4D(int v, int y, std::string channel_name, int focus);
     
    //! get a view to a vertical epi of the channel specified for the 4D lightfield case
    /*!
     \param h fixed horizontal camera index
     \param x fixed column image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift parameter in pixel
    */
    vigra::MultiArrayView<2,float> _getVerticalEpiChannel_4D(int h, int x, const std::string channel_name, int focus);
        
        };
    }
}


#endif	/* LIGHTFIELD_4D_HPP */

