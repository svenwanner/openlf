/* 
 * File:   Lightfield_CROSS.hpp
 * Author: kiryl
 *
 * Created on December 2, 2014, 11:53 AM
 */

#ifndef LIGHTFIELDCROSS_HPP
#define	LIGHTFIELDCROSS_HPP

#include "OpenLF/global.hpp"
#include "OpenLF/image/utils.hpp"
#include "OpenLF/lightfield/io.hpp"
#include "OpenLF/lightfield/Properties.hpp"
#include "OpenLF/lightfield/DataHandler.hpp"
#include "OpenLF/lightfield/FileHandler.hpp"
#include "OpenLF/lightfield/Lightfield.hpp"

namespace OpenLF { 
    namespace lightfield { 
 
class EpiIterator_CROSS;

class Lightfield_CROSS : public Lightfield{
public:
    friend class EpiIterator_CROSS;
    Lightfield_CROSS();
    Lightfield_CROSS(const std::string filename);
    //Lightfield_CROSS(const Lightfield_CROSS& orig);
    ~Lightfield_CROSS();

    //! open lightfield from  hdf5 or config file
    /*!
     \param filename of the .cfg, .h5,.hdf5 or .lf file
    */
    bool open(const std::string filename);
    
    //! access a single intensity value of the channel specified
    //! please note that the camera indeces are interpreted like 4D coordinates.
    /*!
     \param v vertical camera index
     \param h horizontal camera index
     \param x position index
     \param y position index
     \param channel_name name of the channel to access
    */
    float getLoxel(int h, int v, int x, int y, const std::string channel_name);
    
    
    
    //! access a single image of a light field channel
    //! please note that the camera indeces are interpreted like 4D coordinates.
    /*!
     \param h horizontal index
     \param v vertical index
     \param channel_name name of the channel
     \param img reference to MultiArrayView
    */
    void getImage(int h, int v, const std::string channel_name, vigra::MultiArrayView<2,float> &img);
    

public: 
    
    //! get a view to a horizontal epi of the channel specified
    /*!
     \param channel_name name of the channel to extract the epi from
     \param y fixed row image domain index
     \param v vertical camera index (default=0)
     \param focus global shift parameter in pixel (default=0)
    */
    vigra::MultiArrayView<2,float> getHorizontalEpiChannel(std::string channel_name, int y, int v, int focus);

    
    //! get a view to a vertical epi of the channel specified
    /*!
     \param channel_name name of the channel to extract the epi from
     \param x fixed column image domain index
     \param h fixed horizontal camera index (default=0)
     \param focus global shift paramter in pixel (default=0)
    */
    vigra::MultiArrayView<2,float> getVerticalEpiChannel(std::string channel_name, int x, int h, int focus);
    
    //! get a view to a vertical epi of the channel specified 
    /*!
     \param x fixed column image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift parameter in pixel
    */
    vigra::MultiArrayView<2,float> _getVerticalEpiChannel_CROSS(std::string channel_name, int x, int focus);

    // The intersec coordinates are the coordinates describing where the
    // vertical axis intersects the horizontal axis. So far, this is set to
    // the middle of both axises and we assume that both axises have an
    // odd number of pictures!
    int intersec_h();
    int intersec_v();

};


class EpiIterator_CROSS {
    Lightfield *m_lf;
    DIRECTION m_direction;
    int m_camera_index;
    int m_epi_index;
    bool m_finished;
    
public: 
    EpiIterator_CROSS(Lightfield *lf, DIRECTION direction);
    //EpiIterator_CROSS(const EpiIterator_CROSS& orig);
    
    void first();
    void next();
    bool end();
    view_2D get(std::string channel_name, int focus);
    ~EpiIterator_CROSS();
};
    }
}



#endif	/* LIGHTFIELDCROSS_HPP */

