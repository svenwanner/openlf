/* 
 * File:   Lightfield_3D.hpp
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
 
class EpiIterator_3D;

class Lightfield_3D : public Lightfield{
public:
    friend class EpiIterator_3D;
    Lightfield_3D();
    Lightfield_3D(const std::string filename);
    //Lightfield_3D(const Lightfield& orig);
    ~Lightfield_3D();
    
    //! access a single intensity value of the channel specified
    /*!
     \param v vertical camera index
     \param h horizontal camera index
     \param x position index
     \param y position index
     \param channel_name name of the channel to access
    */
    float getLoxel(int h, int v, int x, int y, const std::string channel_name);
    
    //! access a single intensity value of the channel specified
    /*!
     \param n camera index, will be interpreted either as a vertical or a horizontal index, depending on wether the LF is 3DV or 3DH
     \param x position index
     \param y position index
     \param channel_name name of the channel to access
     */
    float getLoxel(int n, int x, int y, const std::string channel_name);
    
    
    //! access a single image of a light field channel
    /*!
     \param h horizontal index
     \param v vertical index
     \param channel_name name of the channel
     \param img reference to MultiArrayView
    */
    void getImage(int h, int v, const std::string channel_name, vigra::MultiArrayView<2,float> &img);

    //! access a single image of a light field channel
    /*!
     \param h horizontal index
     \param v vertical index
     \param img reference to bw MultiArray
    */
    void getImage(int h, int v, vigra::MultiArray<2,float> &img);

    //! access a single rgb image of a light field
    /*!
     \param h horizontal index
     \param v vertical index
     \param img reference to a rgb float MultiArray
    */
    void getImage(int h, int v, vigra::MultiArray<2,vigra::RGBValue<float>> &img);

    //! access a single rgb image of a light field
    /*!
     \param h horizontal index
     \param v vertical index
     \param img reference to a rgb uint8 MultiArray
    */
    void getImage(int h, int v, vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> > &img);


public: //change!
    
    //! get a view to a horizontal epi of the channel specified
    /*!
     \param channel_name name of the channel to extract the epi from
     \param y fixed row image domain index
     \param v vertical camera index (default=0)
     \param focus global shift parameter in pixel (default=0)
    */
    vigra::MultiArrayView<2,float> getHorizontalEpiChannel(std::string channel_name, int y, int v, int focus);

    vigra::MultiArrayView<2,float> getHorizontalEpiChannel(std::string channel_name, int y, int v);
    
    
    //! get a view to a vertical epi of the channel specified
    /*!
     \param channel_name name of the channel to extract the epi from
     \param x fixed column image domain index
     \param h fixed horizontal camera index (default=0)
     \param focus global shift paramter in pixel (default=0)
    */
    vigra::MultiArrayView<2,float> getVerticalEpiChannel(std::string channel_name, int x, int h, int focus);

    vigra::MultiArrayView<2,float> getVerticalEpiChannel(std::string channel_name, int x, int h);
    
    vigra::MultiArrayView<2,float> _getVerticalEpiChannel_3D(std::string channel_name, int x, int focus);

    vigra::MultiArrayView<2,float> _getVerticalEpiChannel_3D(std::string channel_name, int x);
    
    
    
};

class EpiIterator_3D {
    Lightfield *m_lf;
    DIRECTION m_direction;
    int m_camera_index;
    int m_epi_index;
    bool m_finished;
    
public: 
    EpiIterator_3D(Lightfield *lf, DIRECTION direction);
    //EpiIterator_3D(const EpiIterator_3D& orig);
    
    void first();
    void next();
    bool end();
    view_2D get(std::string channel_name, int focus);
    ~EpiIterator_3D();
};
    }
}



#endif	/* LIGHTFIELD3D_HPP */

