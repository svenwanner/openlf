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
        
 
class EpiOffset;
        
        
        
class Lightfield_base {
public:
    typedef std::map<std::string, image::ImageChannel> ChannelContainer;

protected:
    //friend class EpiIterator;
    Lightfield_base() {}
    Lightfield_base(Properties const & prop) : properties(prop) {}
    Lightfield_base(Properties const & prop, ChannelContainer const & chans) :
        channels(chans), properties(prop) {}

    //Lightfield(const Lightfield& orig);
    
public:
    
////////////////////////////////////////////////////////////////////////////////
//////                        I/O  M E T H O D S
////////////////////////////////////////////////////////////////////////////////
    
    //! save lightfields to hdf5 or config file
    /*!
     \param filename  
    */
    void save(std::string filename) {
        io::save_to_hdf5(filename,channels,&properties);
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
    bool hasChannel(std::string name);
    
    
    //! get list of available channels
    std::vector<std::string> getListOfChannelNames();
    
    
    //! check if a specific property exist
    /*!
     \param name of the property to check for existence
    */
    bool hasProperty(std::string name);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(std::string name, int &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(std::string name, float &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(std::string name, double &value);
    
    
    //! access a property by name
    /*!
     \param name of the property
     \param value reference to the value of the property 
    */
    bool getProperty(std::string name, std::string &value);
    
    
    //! get the LF_TYPE
    //LF_TYPE type();
    
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
    float* channel_ptr(std::string channel_name);
    
    
    //! get pointer to data channels
    /*!
     Returns a pointer to the channels map containing the data.
    */
    std::map<std::string,image::ImageChannel> * data();
    
    
    //! set pointer passed to address data channels
    /*!
     \param channels pointer to a channels map to get the address of the internal map
    */
    void data(std::map< std::string,image::ImageChannel> **channels);
    
    
    //! get pointer to specific channel
    /*!
     \param channel_name the name of the channel
    */
    image::ImageChannel *data(std::string channel_name);
    
    
    //! set pointer passed to the address of the channel specified
    /*!
     \param channel_name the name of the channel
     \param channel_data pointer to a MultiArray to get the address of the internal channel specified
    */
    void data(std::string channel_name, image::ImageChannel ** channel_data);
    
    
    //! Allocate a new channel
    /*!
     \param channel_name the name of the channel
    */
    void allocateChannel(std::string channel_name);
    
    
    //! merge internal properties with properties passed
    /*!
     \param properties instance
    */
    void appendProperties(Properties &properties);
    
    

    //EpiIterator* createEpiIterator(DIRECTION direction);
    
protected:
    std::map< std::string,image::ImageChannel> channels;  //!< map to store the light field channels
    Properties properties;          //!< properties instance to hold all parameters

    
};


template<LF_TYPE TypeTag>
class Lightfield : public Lightfield_base {
public:

    //friend class EpiIterator;
    Lightfield(Properties const & prop) : Lightfield_base(prop) {}
    Lightfield(Properties const & prop, ChannelContainer const & chans) :
        Lightfield_base(prop, chans) {}
    Lightfield(std::string const & filename);

    //! access a single intensity value of the channel specified
    /*!
     \param v vertical camera index
     \param h horizontal camera index
     \param x position index
     \param y position index
     \param channel_name name of the channel to access
    */
    float getLoxel(int h, int v, int x, int y, std::string const &channel_name);
    
    //! access a single intensity value of the channels specified
    /*!
     \param v vertical camera index
     \param h horizontal camera index
     \param x position index
     \param y position index
     \param channel_name name of the channel to access
     \param values reference to a float vector storing the results
    */
    void getLoxel(int h, int v, int x, int y,
            std::vector<std::string> const & channel_names,
            std::vector<float> &values);
    
    //! access a single image of a light field channel
    /*!
     \param h horizontal index
     \param v vertical index
     \param channel_name name of the channel
     \param img reference to MultiArrayView
    */
    void getImage(int h, int v, std::string const & channel_name,
            vigra::MultiArrayView<2,float> &img);
    
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
    void getHorizontalEpi(int y, int v, int focus,
            vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >& img);
    
    
    //! get a horizontal epi of either gray value or rgb if available
    /*!
     \param y fixed row image domain index
     \param v vertical camera index
     \param focus global shift parameter in pixel
     \param img vigra rgb image reference
    */
    void getVerticalEpi(int x, int h, int focus,
            vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >& img);
    
    
    const EpiOffset getEpiOffset(DIRECTION dir, size_t index, size_t focus=0);

    //! get a view to a horizontal epi of the channel specified
    /*!
     \param channel_name name of the channel to extract the epi from
     \param x fixed column image domain index
     \param h fixed horizontal camera index (default=0)
     \param focus global shift parameter in pixel (default=0)
    */
    vigra::MultiArrayView<2,float> getHorizontalEpiChannel(
            std::string const & channel_name, int y, int v=0, int focus=0);
    
    
    //! get a view to a vertical epi of the channel specified
    /*!
     \param channel_name name of the channel to extract the epi from
     \param x fixed column image domain index
     \param h fixed horizontal camera index (default=0)
     \param focus global shift paramter in pixel (default=0)
    */
    vigra::MultiArrayView<2,float> getVerticalEpiChannel(
            std::string const & channel_name, int x, int h=0, int focus=0);
    
    
protected:
    
    //! get a view to a horizontal epi of the channel specified for the 4D lightfield case
    /*!
     \param v fixed vertical camera index
     \param y fixed row image domain index
     \param channel_name name of the channel to extract the epi from
     \param focus global shift paramter in pixel
    */
    vigra::MultiArrayView<2,float> _getHorizontalEpiChannel_4D(int v, int y,
            std::string const & channel_name, int focus);
    
    
};

template<LF_TYPE TypeTag>
Lightfield<TypeTag>::Lightfield(std::string const & filename)
{
    print(1,"lightfield::LightfieldFactory(filename) called");

    std::string ftype;
    ftype = helpers::find_ftype(filename);

    bool success = false;
    if (ftype == "h5" || ftype == "lf" || ftype == "hdf5") {
        success = io::load_from_hdf5( filename, channels, properties );
    }
    else if (ftype == "cfg") {
        io::FileHandler dataHandler(filename, &properties);
        success = dataHandler.readData(channels);
    }
    else {
        throw OpenLF_Exception("Lightfield IO Error: Filetype not specified!");
    }
    if (!success) {
        throw OpenLF_Exception("Lightfield IO Error: cannot read data!");
    }
    LF_TYPE type;
    properties.get_lftype(type);
    if (TypeTag != type) {
        throw OpenLF_Exception("Lightfield IO Error: type not recognized!");
    }
}


/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<>
float Lightfield<LF_4D>::getLoxel(int h, int v, int x, int y,
        std::string const & channel_name);

template<>
float Lightfield<LF_3DV>::getLoxel(int h, int v, int x, int y,
        std::string const & channel_name);

template<>
float Lightfield<LF_3DH>::getLoxel(int h, int v, int x, int y,
        std::string const & channel_name);

template<>
float Lightfield<LF_CROSS>::getLoxel(int h, int v, int x, int y,
        std::string const & channel_name);

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<LF_TYPE TypeTag>
void Lightfield<TypeTag>::getLoxel(int h, int v, int x, int y,
        std::vector<std::string> const &channel_names,
        std::vector<float> &values)
{
    values.clear();
    
    for(auto itr = channel_names.begin(); itr != channel_names.end(); ++itr)
    {
        values.push_back(this->getLoxel(h, v, x, y, *itr));
    }
}

/*!
 This method returns a MultiArrayView to an image of the light field at position 
 (h,v). The exception cases of cross and 3D vertical light fields where images 
 are stored in a transposed manner are handled correctly, so the function will 
 return a view to the transposed version of the image channel.
 *
 If one would get images from a cross light field, the row is accessed by setting
 the parameter v=0, the column vice versa by setting h=0. So always one of the 
 camera dimension needs to be zero, otherwise an Exception is fired!
 *  
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<>
void Lightfield<LF_CROSS>::getImage(int h, int v,
        std::string const & channel_name,
        vigra::MultiArrayView<2,float> &img);

template<>
void Lightfield<LF_3DV>::getImage(int h, int v,
        std::string const & channel_name,
        vigra::MultiArrayView<2,float> &img);

template<>
void Lightfield<LF_3DH>::getImage(int h, int v,
        std::string const & channel_name,
        vigra::MultiArrayView<2,float> &img);


template<>
void Lightfield<LF_4D>::getImage(int h, int v,
        std::string const & channel_name,
        vigra::MultiArrayView<2,float> &img);

/*!
 This method returns a MultiArray of an image of the light field at position 
 (h,v). If a bw channel is present it returns this, if rgb data are present they
 are converted to an bw image.
 * 
 The exception cases of cross and 3D vertical light fields where images 
 are stored in a transposed manner are handled correctly, so the function will 
 return a view to the transposed version of the image channel.
 *
 If one would get images from a cross light field, the row is accessed by setting
 the parameter v=0, the column vice versa by setting h=0. So always one of the 
 camera dimension needs to be zero, otherwise an Exception is fired!
 *  
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<LF_TYPE TypeTag>
void Lightfield<TypeTag>::getImage(int h, int v,
        vigra::MultiArray<2,float> &img)
{
    if(hasRGB()) {
        vigra::MultiArrayView<2,float> img_r;
        getImage(h,v,"r",img_r);
        vigra::MultiArrayView<2,float> img_g;
        getImage(h,v,"g",img_g);
        vigra::MultiArrayView<2,float> img_b;
        getImage(h,v,"b",img_b);
        
        image::utils::mergeChannels(img_r,img_b,img_b,img);
    }
    else if(hasBW()) {
        vigra::MultiArrayView<2,float> img_bw;
        getImage(h,v,"bw",img_bw);
        img = vigra::MultiArray<2,float>(img_bw);       
    }
    else throw OpenLF_Exception("Lightfield::getImage -> no image data available!");
}


/*!
 This method returns a rgb MultiArray of an image of the light field at position 
 (h,v).
 * 
 The exception cases of cross and 3D vertical light fields where images 
 are stored in a transposed manner are handled correctly, so the function will 
 return a view to the transposed version of the image channel.
 *
 If one would get images from a cross light field, the row is accessed by setting
 the parameter v=0, the column vice versa by setting h=0. So always one of the 
 camera dimension needs to be zero, otherwise an Exception is fired!
 *  
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<LF_TYPE TypeTag>
void Lightfield<TypeTag>::getImage(int h, int v,
        vigra::MultiArray<2,vigra::RGBValue<float>> &img)
{
    if(!img.hasData())
    {
        img = vigra::MultiArray<2,vigra::RGBValue<float>>(shape(imgWidth(),imgHeight()));
    }
    else
    {
        if(img.width() != imgWidth() || img.height() != imgHeight())
            throw OpenLF_Exception("Lightfield::getImage -> shape mismatch!");
    }
    
    if(hasRGB()) {
        vigra::MultiArrayView<2,float> img_r;
        getImage(h,v,"r",img_r);
        vigra::MultiArrayView<2,float> img_g;
        getImage(h,v,"g",img_g);
        vigra::MultiArrayView<2,float> img_b;
        getImage(h,v,"b",img_b);
        
        image::utils::mergeChannels(img_r,img_g,img_b,img);
    }
    else if(hasBW())
    {
        vigra::MultiArrayView<2,float> img_bw;
        getImage(h,v,"bw",img_bw);
        
        for(int c=0; c<3; c++)
        {
            for(int y=0; y<imgHeight(); y++)
            {
                for(int x=0; x<imgWidth(); x++)
                {
                    img(x,y)[c] = img_bw(x,y);
                }
            }
        }
    }
    else throw OpenLF_Exception("Lightfield::getImage -> no rgb or bw image data available!");
}


/*!
 This method returns a rgb MultiArray of an image of the light field at position 
 (h,v).
 * 
 The exception cases of cross and 3D vertical light fields where images 
 are stored in a transposed manner are handled correctly, so the function will 
 return a view to the transposed version of the image channel.
 *
 If one would get images from a cross light field, the row is accessed by setting
 the parameter v=0, the column vice versa by setting h=0. So always one of the 
 camera dimension needs to be zero, otherwise an Exception is fired!
 *  
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<LF_TYPE TypeTag>
void Lightfield<TypeTag>::getImage(int h, int v,
        vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>> &img)
{
    if(!img.hasData())
    {
        img = vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>>(shape(imgWidth(),imgHeight()));
    }
    else
    {
        if(img.width() != imgWidth() || img.height() != imgHeight())
            throw OpenLF_Exception("Lightfield::getImage -> shape mismatch!");
    }
    
    if(hasRGB()) {
        vigra::MultiArrayView<2,float> img_r;
        getImage(h,v,"r",img_r);
        vigra::MultiArrayView<2,float> img_g;
        getImage(h,v,"g",img_g);
        vigra::MultiArrayView<2,float> img_b;
        getImage(h,v,"b",img_b);
        
        vigra::MultiArray<2,float> fimg_r = vigra::MultiArrayView<2,float>(img_r);
        vigra::MultiArray<2,float> fimg_g = vigra::MultiArrayView<2,float>(img_g);
        vigra::MultiArray<2,float> fimg_b = vigra::MultiArrayView<2,float>(img_b);
        
        image::io::linear_range_mapping(img_r,fimg_r);
        image::io::linear_range_mapping(img_g,fimg_g);
        image::io::linear_range_mapping(img_b,fimg_b);
        
        image::utils::mergeChannels(fimg_r,fimg_g,fimg_b,img);
    }
    else if(hasBW())
    {
        vigra::MultiArrayView<2,float> img_bw;
        getImage(h,v,"bw",img_bw);
        
        vigra::MultiArray<2,float> fimg_bw = vigra::MultiArrayView<2,float>(img_bw);
        image::io::linear_range_mapping(img_bw,fimg_bw);
        
        for(int c=0; c<3; c++)
        {
            for(int y=0; y<imgHeight(); y++)
            {
                for(int x=0; x<imgWidth(); x++)
                {
                    img(x,y)[c] = (vigra::UInt8)(fimg_bw(x,y));
                }
            }
        }
    }
    else throw OpenLF_Exception("Lightfield::getImage -> no rgb image data available!");
}


////////////////////////////////////////////////////////////////////////////////
//////             E P I   H A N D L I N G     M E T H O D S
////////////////////////////////////////////////////////////////////////////////

/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/

template<LF_TYPE TypeTag>
void Lightfield<TypeTag>::getHorizontalEpi(int y, int v, int focus,
        vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >& img)
{
    if(hasRGB()) {
        vigra::MultiArrayView<2,float> r = getHorizontalEpiChannel("r", y, v, focus);
        vigra::MultiArrayView<2,float> g = getHorizontalEpiChannel("g", y, v, focus);
        vigra::MultiArrayView<2,float> b = getHorizontalEpiChannel("b", y, v, focus);
        
        if(img.hasData()) {
            if(img.shape() != r.shape())
                throw OpenLF_Exception("Lightfield::getHorizontalEpi -> shape mismatch!");
        }
        else
            img = vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >(r.shape());
        
        for(int y=0; y<r.shape()[1]; y++) {
            for(int x=0; x<r.shape()[0]; x++) {
                img(x,y)[0] = (vigra::UInt8)(r(x,y)*255);
                img(x,y)[1] = (vigra::UInt8)(g(x,y)*255);
                img(x,y)[2] = (vigra::UInt8)(b(x,y)*255);
            }
        }
    }
    else if(hasBW()) {
        vigra::MultiArrayView<2,float> bw = getHorizontalEpiChannel("bw", y, v, focus);
        
        if(img.hasData()) 
        {
            if(img.shape() != bw.shape())
                throw OpenLF_Exception("Lightfield::getHorizontalEpi -> shape mismatch!");
        }
        else
            img = vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >(bw.shape());
        
        for(int y=0; y<bw.shape()[1]; y++) {
            for(int x=0; x<bw.shape()[0]; x++) {
                for(int c=0; c<3; c++)
                    img(x,y)[c] = (vigra::UInt8)(bw(x,y)*255);
            }
        }
    }
    else throw OpenLF_Exception("Lightfield::getHorizontalEpi -> no suitable channel available!");
}



/*!
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<LF_TYPE TypeTag>
void Lightfield<TypeTag>::getVerticalEpi(int x, int h, int focus,
        vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >& img)
{
    if(hasRGB()) {
        vigra::MultiArrayView<2,float> r = getVerticalEpiChannel("r", x, h, focus);
        vigra::MultiArrayView<2,float> g = getVerticalEpiChannel("g", x, h, focus);
        vigra::MultiArrayView<2,float> b = getVerticalEpiChannel("b", x, h, focus);
        
        if(img.hasData()) {
            if(img.shape() != r.shape())
                throw OpenLF_Exception("Lightfield::getHorizontalEpi -> shape mismatch!");
        }
        else
            img = vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >(r.shape());
        
        for(int y=0; y<r.shape()[1]; y++) {
            for(int x=0; x<r.shape()[0]; x++) {
                img(x,y)[0] = (vigra::UInt8)(r(x,y)*255);
                img(x,y)[1] = (vigra::UInt8)(g(x,y)*255);
                img(x,y)[2] = (vigra::UInt8)(b(x,y)*255);
            }
        }
    }
    else if(hasBW()) {
        vigra::MultiArrayView<2,float> bw = getHorizontalEpiChannel("bw", x, h, focus);
        
        if(img.hasData()) 
        {
            if(img.shape() != bw.shape())
                throw OpenLF_Exception("Lightfield::getHorizontalEpi -> shape mismatch!");
        }
        else
            img = vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> >(bw.shape());
        
        for(int y=0; y<bw.shape()[1]; y++) {
            for(int x=0; x<bw.shape()[0]; x++) {
                for(int c=0; c<3; c++)
                    img(x,y)[c] = (vigra::UInt8)(bw(x,y)*255);
            }
        }
    }
    else throw OpenLF_Exception("Lightfield::getHorizontalEpi -> no suitable channel available!");
}


template<>
vigra::MultiArrayView<2, float> Lightfield<LF_4D>::getHorizontalEpiChannel(
        std::string const & channel_name, int y, int v, int focus);
template<>
vigra::MultiArrayView<2, float> Lightfield<LF_3DV>::getHorizontalEpiChannel(
        std::string const & channel_name, int y, int v, int focus);
template<>
vigra::MultiArrayView<2, float> Lightfield<LF_3DH>::getHorizontalEpiChannel(
        std::string const & channel_name, int y, int v, int focus);
template<>
vigra::MultiArrayView<2, float> Lightfield<LF_CROSS>::getHorizontalEpiChannel(
        std::string const & channel_name, int y, int v, int focus);


/*!
This is the efficient variant of accessing epipolar plane images due to the concatenated memory access.
Accessing the vertical epipolar plane images using _getVerticalEpiChannel_4D is inefficient compared to this
due to the column accessing. To achieve the same efficiency for vertical access transpose the data and use
the horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<LF_TYPE TypeTag>
view_2D Lightfield<TypeTag>::_getHorizontalEpiChannel_4D(int v, int y,
        std::string const & channel_name, int focus)
{
    // if channel exist
    auto cur_channel = channels.find(channel_name);
    if (cur_channel == channels.end())
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_4D -> channel not available!");
        
    int offset = (cams_h()-1)*focus;
    vigra::MultiArrayView<1, float> row = cur_channel->second.viewToRow(
            v * imgHeight() + y);
    shape epi_shape = shape(imgWidth()-(cams_h()-1)*focus,cams_h());
    strideTag stride = strideTag(1, imgWidth() - focus);
    return view_2D(epi_shape, stride, row.data() + offset);
}


/*!
This is the inefficient variant of accessing epipolar plane images due to the unstrided memory access.
For optimal performance during computation transpose the whole lightfield and use horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<>
vigra::MultiArrayView<2,float> Lightfield<LF_4D>::getVerticalEpiChannel(
        std::string const & channel_name, int x, int h, int focus);

template<>
vigra::MultiArrayView<2,float> Lightfield<LF_3DH>::getVerticalEpiChannel(
        std::string const & channel_name, int x, int h, int focus);
/*!
This is the efficient variant of accessing epipolar plane images due to the concatenated memory access.
Accessing the vertical epipolar plane images using _getVerticalEpiChannel_4D is inefficient compared to this
due to the column accessing. To achieve the same efficiency for vertical access transpose the data and use
the horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<>
vigra::MultiArrayView<2,float> Lightfield<LF_3DV>::getVerticalEpiChannel(
        std::string const & channel_name, int x, int h, int focus);

/*!
This is the efficient variant of accessing epipolar plane images due to the concatenated memory access.
Accessing the vertical epipolar plane images using _getVerticalEpiChannel_4D is inefficient compared to this
due to the column accessing. To achieve the same efficiency for vertical access transpose the data and use
the horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
template<>
vigra::MultiArrayView<2,float> Lightfield<LF_CROSS>::getVerticalEpiChannel(
        std::string const & channel_name, int x, int h, int focus);


// FIXME: inherit from Shape2D to allow using the offset as an index directly?
// FIXME: (as in channel[*itr] to mean channel[*itr + Diff2D(0,0)]
//template <LF_TYPE TypeTag>
// FIXME: this is horizontal only
class EpiOffset
{
public:
    typedef vigra::Shape2 difference_type;
    typedef vigra::MultiArrayIndex difference_type_1;
    //typedef vigra::MultiArrayShape<2>::type size_t;

    EpiOffset(size_t index, size_t stride,
            size_t focus=0, size_t ncams=0) :
        m_offset(index, 0), m_stride(stride), m_focus(focus), m_ncams(ncams)
    {
        vigra_precondition( m_stride != 0,
                "stride cannot be 0 for EpiOffset construction" );
        vigra_precondition( focus ==0  || ncams > 0,
                "ncams must be > 0 if focus > 0");
    }

    EpiOffset(EpiOffset const & other) :
        m_offset(other.m_offset), m_stride(other.m_stride),
        m_focus(other.m_focus), m_ncams(other.m_ncams)
    {}

    EpiOffset(EpiOffset const & other, size_t focus) :
        m_offset(other.m_offset), m_stride(other.m_stride),
        m_focus(other.m_focus + focus), m_ncams(other.m_ncams)
    {}

    /*
    EpiOffset & operator=(EpiOffset const & other)
    {
    }
    */

    // refocus
    const EpiOffset operator()(size_t focus)
    {
        return EpiOffset(*this, focus);
    }

    const difference_type operator+(difference_type const & coord) const
    {
        // FIXME: only horizontal
        return m_offset + difference_type(0,
                (m_ncams/2 - coord[0])*m_focus + coord[0]*m_stride + coord[1]);
    }

private:
    const difference_type m_offset;
    const size_t m_stride;
    const size_t m_focus;
    const size_t m_ncams;
};

}} // namespace OpenLF::lightfield
#endif	/* LIGHTFIELD_HPP */

