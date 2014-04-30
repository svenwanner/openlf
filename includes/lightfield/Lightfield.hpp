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
#include "image/utils.hpp"
#include "lightfield/io.hpp"
#include "lightfield/Properties.hpp"
#include "lightfield/DataHandler.hpp"
#include "lightfield/FileHandler.hpp"


typedef vigra::Shape2 shape;
typedef vigra::Shape2 strideTag;

namespace OpenLF { 
    namespace lightfield { 

class Lightfield {
    
public:
    Lightfield();
    Lightfield(string filename);
    Lightfield(const Lightfield& orig);
    virtual ~Lightfield();

    
////////////////////////////////////////////////////////////////////////////////
//////                        I/O  M E T H O D S
////////////////////////////////////////////////////////////////////////////////
    
    //! open lightfields from  hdf5 or config file
    /*!
     \param filename of the .cfg, .h5,.hdf5 or .lf file 
    */
    bool open(string filename);
    
    
    //! open lightfields from  hdf5 or config file
    /*!
     \param filename of the .cfg, .h5,.hdf5 or .lf file 
    */
    bool open(const char* filename);
    
    
    //! save lightfields to hdf5 or config file
    /*!
     \param filename  
    */
    void save(string filename) {
        OpenLF::lightfield::io::save_to_hdf5(filename,channels,&properties);
    }
    
        
    
    
    
 
    
    
////////////////////////////////////////////////////////////////////////////////
//////                        G E T    I N F O S 
////////////////////////////////////////////////////////////////////////////////
    
    //! check if rgb data are available
    bool hasRGB();
    
    
    //! check if bw data are available
    bool hasBW();
        
    
    //! check if a specific channel exist
    /*!
     \param name of the channel to check for existence
    */
    bool hasChannel(string name);
    
    
    //! check if a specific property exist
    /*!
     \param name of the property to check for existence
    */
    bool hasProperty(string name);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(string name, int &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(string name, float &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(string name, double &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(string name, string &value);
    
    
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
    
    //! get the data pointer of a specific channel 
    /*!
     \param channel_name the name of the channel
    */
    float* channel_ptr(string channel_name);
    
    
    //! get pointer to data channels
    /*!
     Returns a pointer to the channels map containing the data.
    */
    map<string,OpenLF::image::ImageChannel> * data();
    
    
    //! set pointer passed to address data channels
    /*!
     \param channels pointer to a channels map to get the address of the internal map
    */
    void data(map< string,OpenLF::image::ImageChannel> **channels);
    
    
    //! get pointer to specific channel
    /*!
     \param channel_name the name of the channel
    */
    OpenLF::image::ImageChannel *data(string channel_name);
    
    
    //! set pointer passed to the address of the channel specified
    /*!
     \param channel_name the name of the channel
     \param channel_data pointer to a MultiArray to get the address of the internal channel specified
    */
    void data(string channel_name, OpenLF::image::ImageChannel ** channel_data);
    
    
    //! Allocate a new channel
    /*!
     \param channel_name the name of the channel
    */
    void allocateChannel(string channel_name);
    
    
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
    void getImage(int h, int v,  string channel_name, vigra::MultiArrayView<2,float> &img);
    
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
    void getImage(int h, int v, vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>> &img);
    
    
    //! get a view to a horizontal epi of the channel specified
    /*!
     \param v fixed vertical camera index
     \param y fixed row image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift paramter in pixel
    */
    vigra::MultiArrayView<2,float> getHorizontalEpiChannel(int v, int y, string channel_name, int focus=0);
    
    
    //! get a view to a vertical epi of the channel specified
    /*!
     \param h fixed horizontal camera index
     \param x fixed column image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift paramter in pixel
    */
    vigra::MultiArrayView<2,float> getVerticalEpiChannel(int h, int x, string channel_name, int focus=0);
    
    
//    void getVerticalEpiChannel(int h, int x, string channel_name, vigra::MultiArrayView<2,float> &img);
//    
//    void getHorizontalEpi(int v, int y, int focus, vigra::MultiArray<2,float> &img);
//    
//    void getVerticalEpi(int h, int x, vigra::MultiArray<2,float> &img);
    
protected:
    map< string,OpenLF::image::ImageChannel> channels;  //!< map to store the light field channels
    OpenLF::lightfield::io::DataHandler *dataHandler;   //!< instance of a dataHandler to read data
    OpenLF::lightfield::Properties properties;          //!< properties instance to hold all parameters

    
protected:
    
    //! get a view to a horizontal epi of the channel specified for the 4D lightfield case
    /*!
     \param v fixed vertical camera index
     \param y fixed row image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift paramter in pixel
    */
    vigra::MultiArrayView<2,float> _getHorizontalEpiChannel_4D(int v, int y, string channel_name, int focus);
    
    //! get a view to a vertical epi of the channel specified for the 4D lightfield case
    /*!
     \param h fixed horizontal camera index
     \param x fixed column image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift paramter in pixel
    */
    vigra::MultiArrayView<2,float> _getVerticalEpiChannel_4D(int h, int x, string channel_name, int focus);
    
};

}}
#endif	/* LIGHTFIELD_HPP */

