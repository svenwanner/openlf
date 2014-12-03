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

#include "OpenLF/global.hpp"
#include "OpenLF/image/utils.hpp"
#include "OpenLF/lightfield/io.hpp"
#include "OpenLF/lightfield/Properties.hpp"
#include "OpenLF/lightfield/DataHandler.hpp"
#include "OpenLF/lightfield/FileHandler.hpp"


typedef vigra::Shape2 shape;
typedef vigra::Shape2 strideTag;
typedef vigra::MultiArrayView<2, float> view_2D;

namespace OpenLF { 
    namespace lightfield { 
        
 
        
class EpiIterator;
        
        

class Lightfield {
    
public:
    friend class EpiIterator;
    Lightfield();
    Lightfield(const std::string filename);
    //Lightfield(const Lightfield& orig);
    virtual ~Lightfield();

    
////////////////////////////////////////////////////////////////////////////////
//////                        I/O  M E T H O D S
////////////////////////////////////////////////////////////////////////////////
    
    //! open lightfields from  hdf5 or config file
    /*!
     \param filename of the .cfg, .h5,.hdf5 or .lf file 
    */
    bool open(const std::string filename);
    
    
    //! open lightfields from  hdf5 or config file
    /*!
     \param filename of the .cfg, .h5,.hdf5 or .lf file 
    */
    bool open(const char* filename);
    
    
    //! save lightfields to hdf5 or config file
    /*!
     \param filename  
    */
    void save(std::string filename) {
        OpenLF::lightfield::io::save_to_hdf5(filename,m_channels,&m_properties);
    }
    
        
    
    
    
 
    
    
////////////////////////////////////////////////////////////////////////////////
//////                        G E T    I N F O S 
////////////////////////////////////////////////////////////////////////////////
    
    //! check if rgb data are available
    bool hasRGB() const;
    
    
    //! check if bw data are available
    bool hasBW() const;
        
    
    //! check if a specific channel exist
    /*!
     \param name of the channel to check for existence
    */
    bool hasChannel(const std::string name) const;
    
    
    //! get list of available channels
    std::vector<std::string> getListOfChannelNames();
    
    
    //! check if a specific property exist
    /*!
     \param name of the property to check for existence
    */
    bool hasProperty(const std::string name);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(const std::string name, int &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(const std::string name, float &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(const std::string name, double &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(const std::string name, std::string &value);
    
    
    //! get the LF_TYPE
    LF_TYPE type();
    
    //! get width of a single image
    int imgWidth();
    
    //! get height of a single image
    int imgHeight();
    
    //! get width of the entire lf array
    int width();
    
    //! get height of the entire lf array
    int height();
    
    //! get horizontal number of cameras
    int cams_h();
    
    //! get vertical number of cameras
    int cams_v();
    
    
    
    
    
    
    
    
    
    
    
    
////////////////////////////////////////////////////////////////////////////////
//////                      A C C E S S    D A T A
//////////////////////////////////////////////////////////////////////////////// 
    
    //! access a single intensity value of the channel specified
    /*!
     \param v vertical camera index
     \param h horizontal camera index
     \param x position index
     \param y position index
     \param channel_name name of the channel to access
    */
    float getLoxel(int h, int v, int x, int y, const std::string channel_name);
    
    //! access a single intensity value of the channels specified
    /*!
     \param v vertical camera index
     \param h horizontal camera index
     \param x position index
     \param y position index
     \param channel_name name of the channel to access
     \param values reference to a float vector storing the results
    */
    void getLoxel(int h, int v, int x, int y, const std::vector<std::string> channel_names, std::vector<float> &values);
    
    
    //! get the data pointer of a specific channel 
    /*!
     \param channel_name the name of the channel
    */
    float* channel_ptr(const std::string channel_name);
    
    
    //! get pointer to data channels
    /*!
     Returns a pointer to the channels map containing the data.
    */
    std::map<std::string,OpenLF::image::ImageChannel> * data();
    
    
    //! set pointer passed to address data channels
    /*!
     \param channels pointer to a channels map to get the address of the internal map
    */
    void data(std::map< std::string,OpenLF::image::ImageChannel> **channels);
    
    
    //! get pointer to specific channel
    /*!
     \param channel_name the name of the channel
    */
    OpenLF::image::ImageChannel *data(const std::string channel_name);
    
    
    //! set pointer passed to the address of the channel specified
    /*!
     \param channel_name the name of the channel
     \param channel_data pointer to a MultiArray to get the address of the internal channel specified
    */
    void data(const std::string channel_name, OpenLF::image::ImageChannel ** channel_data);
    
    
    //! Allocate a new channel
    /*!
     \param channel_name the name of the channel
    */
    void allocateChannel(const std::string channel_name);
    
    
    //! merge internal properties with properties passed
    /*!
     \param properties instance
    */
    void appendProperties(Properties &properties);
    
    
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
    
    
    //! get a horizontal epi of either gray value or rgb if available
    /*!
     \param y fixed row image domain index
     \param v fixed vertical camera index
     \param focus global shift parameter in pixel
     \param img vigra rgb image reference
    */
    void getHorizontalEpi(int y, int v, int focus, vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >& img);
    
    
    //! get a horizontal epi of either gray value or rgb if available
    /*!
     \param y fixed row image domain index
     \param v vertical camera index
     \param focus global shift parameter in pixel
     \param img vigra rgb image reference
    */
    void getVerticalEpi(int x, int h, int focus, vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >& img);
    
    
    //! get a view to a horizontal epi of the channel specified
    /*!
     \param channel_name name of the channel to extract the epi from
     \param x fixed column image domain index
     \param h fixed horizontal camera index (default=0)
     \param focus global shift parameter in pixel (default=0)
    */
    view_2D getHorizontalEpiChannel(const std::string channel_name, int y, int v=0,  int focus=0);
    
    
    //! get a view to a vertical epi of the channel specified
    /*!
     \param channel_name name of the channel to extract the epi from
     \param x fixed column image domain index
     \param h fixed horizontal camera index (default=0)
     \param focus global shift paramter in pixel (default=0)
    */
    view_2D getVerticalEpiChannel(std::string channel_name, int x, int h=0, int focus=0);
    
    

    EpiIterator* createEpiIterator(DIRECTION direction);
    //std::shared_ptr<OpenLF::lightfield::EpiIterator> createEpiIterator(DIRECTION direction);
    
protected:
    std::map< std::string,OpenLF::image::ImageChannel> m_channels;  //!< map to store the light field channels
    std::unique_ptr<OpenLF::lightfield::io::DataHandler> m_dataHandler;   //!< instance of a dataHandler to read data
    OpenLF::lightfield::Properties m_properties;          //!< properties instance to hold all parameters

 
protected:
    
    //! get a view to a horizontal epi of the channel specified for the 4D lightfield case
    /*!
     \param v fixed vertical camera index
     \param y fixed row image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift parameter in pixel
    */
    view_2D _getHorizontalEpiChannel_4D(int v, int y, std::string channel_name, int focus);
    
    
    //! get a view to a vertical epi of the channel specified for the 3DV lightfield case
    /*!
     \param x fixed column image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift parameter in pixel
    */
    view_2D _getVerticalEpiChannel_3DV(int x, std::string channel_name, int focus);
    
    
    //! get a view to a vertical epi of the channel specified for the 3DV lightfield case
    /*!
     \param x fixed column image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift parameter in pixel
    */
    view_2D _getVerticalEpiChannel_Cross(int x, std::string channel_name, int focus);
    
    
    //! get a view to a vertical epi of the channel specified for the 4D lightfield case
    /*!
     \param h fixed horizontal camera index
     \param x fixed column image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift parameter in pixel
    */
    view_2D _getVerticalEpiChannel_4D(int h, int x, const std::string channel_name, int focus);
   
};












class EpiIterator {
    
    Lightfield *m_lf;
    DIRECTION m_direction;
    int m_camera_index;
    int m_epi_index;
    bool m_finished;
    
public:
    EpiIterator(Lightfield *lf, DIRECTION direction);
    //EpiIterator(const EpiIterator& orig);
    
    void first();
    void next();
    bool end();
    
    view_2D get(std::string channel_name, int focus);
    
    
    
    virtual ~EpiIterator();
    
};




}}
#endif	/* LIGHTFIELD_HPP */

