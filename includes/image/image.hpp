/**
 * \class Image
 *
 * \brief Image container for grayscale, vector and rgb data
 *
 * This container acts as image object able to keep grayscale,
 * vector and rgb images. Labels for each type are set auto-
 * matically as bw(1), vec(2) or rgb(3) depending on the number 
 * of (channels) initialized. But individual labels can also be 
 * set manually as well as an arbitrary number of channels. 
 *
 * \note 
 *
 * \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 * 
 */

#ifndef IMAGE_HPP
#define	IMAGE_HPP

#include "global.hpp"
#include "image/image.hpp"


namespace OpenLF {

class Image {
public:
    //! Default constructor.
    /*!
      Initializes an empty image of size zero without a label. 
    */
    Image();                     
    virtual ~Image();            
    
    //! Empty image constructor.
    /*!
      Initializes an empty image. Size and number of channels needs to be
      specified by the user, 
    */
    Image(int x, int y, int channel);
    
    //! From file constructor.
    /*!
      Initializes image from file. Size, number of channels and [label] is
      specified automatically as 1[bw] or 3[rgb].
    */
    Image(const char* filename);          
    
    //! From file constructor.
    /*!
      Initializes image from file. Size, number of channels and [label] is 
      specified automatically as 1[bw] or 3[rgb].
    */
    Image(string filename);
    
    //! Copy constructor.
    /*!
      Copies only properties of the passed object and allocates memory for all
      channels. To copy the entire image use deepcopy(Image&).
    */
    Image(const Image& orig);    // copy constructor
    
    
    /*
     * GETTER SETTER METHODS
     */
    
    //! get width.
    int width() const;
    //! get height.
    int height() const;
    //! get number of channels.
    int channels() const;
    //! get label.
    string label() const;
    
    //! set label.
    void set_label(string label);
    
    
    
    /*
     * IO METHODS
     */
    
    //! load from file.
    /*!
     Load image data from file (.jpg,.png,.gif,.tif). Size, number of channels 
     and [label] is specified automatically as 1[bw] or 3[rgb]. 
    */
    void load(const char *filename);
    
    
    
    
    /*
     * ACCESS DATA METHODS
     */
    
    //! get data pointer of a specific channel.
    /*!
     Returns the pointer to the float data array of an existing channel. 
    */
    float* get_channel(int channel);
    
    //! fast channel copy to external MultiArray.
    /*!
     Copies the channel specified to passed MultiArray reference. 
    */
    void swap_channel(int channel, vigra::MultiArray<2,float>& array);
    
    //! pixel access.
    /*!
     Returns the value of the pixel (x,y) of channel specified. 
    */
    float access_pixel(int x, int y, int channel);
    
    //! pixel access.
    /*!
     Returns the value of the pixel (x,y) of all channels pushing them into the
     vector passed. 
    */
    void get_pixel(int x, int y, vector<float>& values);
    
//    void get_channel(int,vigra::MultiArray<2,float>&);
    
//    float* get_data();
    
//    vigra::MultiArray<2,float>* get_channel(int);
//    void get_bw_channel(vigra::MultiArray<2,float>&);
//    void get_vec_channels(vigra::MultiArray<2,float>*,vigra::MultiArray<2,float>*);
//    void get_rgb_channels(vigra::MultiArray<2,float>*,vigra::MultiArray<2,float>*,vigra::MultiArray<2,float>*);
//    void get_rgb_compact(vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> >&);
    
protected:
    vector<vigra::MultiArray<2,float>* > _data; //!< vector storing pointers to MultiArray channels
    int _width;  //!< image width
    int _height;  //!< image height
    string _label;   //!< image label "bw","vec","rgb" or specified by user
    
private:

};

}
#endif	/* IMAGE_HPP */

