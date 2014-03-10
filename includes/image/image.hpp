#ifndef IMAGE_HPP
#define	IMAGE_HPP

#include "global.hpp"
#include "utils/helpers.hpp"
#include "image/image.hpp"


namespace OpenLF {
    

//!  Image container for grayscale, vector and rgb data. 
/*!
  This container acts as image object able to keep grayscale,
  vector and rgb images. Labels for each type are set auto-
  matically as bw(1), vec(2) or rgb(3) depending on the number 
  of (channels) initialized. But individual labels can also be 
  set manually as well as an arbitrary number of channels.
  
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/

class Image {
public:
    //! Default constructor.
    /*!
      Initializes an empty image of size zero without a label. 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    Image();                     
    virtual ~Image();            
    
    //! Empty image constructor.
    /*!
      Initializes an empty image. Size and number of channels needs to be
      specified by the user.
     \param x pixel coordinate
     \param y pixel coordinate 
     \param channel data channel
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    Image(int x, int y, int channel);
    
    //! From file constructor.
    /*!
      Initializes image from file. Size, number of channels and [label] is
      specified automatically as 1[bw] or 3[rgb].
     \param filename of image file
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    Image(const char* filename);          
    
    //! From file constructor.
    /*!
      Initializes image from file. Size, number of channels and [label] is 
      specified automatically as 1[bw] or 3[rgb].
     \param filename of image file
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    Image(string filename);
    
    //! Copy constructor.
    /*!
      Copies only properties of the passed object and allocates memory for all
      channels. To copy the entire image use deepcopy(Image&).
     \param orig instance to copy from
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
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
    
    //! set image label.
    /*!
     \param label image name
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void set_label(string label);
    
    //! fills channel of an passed image object with the value passed 
    /*!
     \param img instance of Image 
     \param channel to fill
     \param value to fill
     \param std standard deviation as randomness around value
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void fill_image_channel(int channel, float value, float std);
    
    //! adds empty channels to the image object
    /*!
     Adds an additional empty channel to the data container.
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void add_channel();
    
    //! adds channels to the image object
    /*!
     Copies a float array as an additional channel to the data container. It has to be
     ensured by the user that the shapes are consistent.
     \param data float pointer to data array 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void add_channel(float* data);
    
    //! adds channel to the image object
    /*!
     Adds a copy of a channel from the image object passed to the data container
     \param channel to be copied
     \param orig image instance from which the channel should be copied 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void add_channel(int channel, const OpenLF::Image& orig);
    
    //! copy data to the channel specified
    /*!
     Copies a float array into the channel specified. It has to be
     ensured by the user that the shapes are consistent.
     \param data float pointer to data array 
     \param channel to which data should be copied
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void set_channel(float* data, int channel);
    
    //! copies channel from image instance passed 
    /*!
     The channel specified is copied from the image instance passed. The label is
     set to bw, already existing channels are deleted.
     \param channel to be copied
     \param orig is the image instance the channel should be copied from
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void copy_channel(int channel, const Image& orig);
    
    
    
    /*
     * IO METHODS
     */
    
    //! load from file.
    /*!
     Load image data from file (.jpg, .png, .gif, .tif, .bmp, .exr). Size, 
     number of channels and [label] is specified automatically as 1[bw] or 3[rgb].
     \param filename of image file
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void load(const char *filename);
    
    //! save image to file.
    /*!
     Saves image data to file (.jpg, .png, .gif, .tif, .bmp, .exr).
     \param filename of image file
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void save(string filename);
    
    
    
    
    
    
    /*
     * ACCESS DATA METHODS
     */
    
    //! get data pointer of a specific channel.
    /*!
     Returns the pointer to the float data array of an existing channel.
     \param channel data channel
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de) 
    */
    float* get_channel(int channel) const;
    
    //! fast channel copy to external MultiArray.
    /*!
     Copies the channel specified to passed MultiArray reference. 
     \param channel to copy
     \param array vigra MultiArray to copy channel into 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void swap_channel(int channel, vigra::MultiArray<2,float>& array);
    
    //! pixel access.
    /*!
     Returns the value of the pixel (x,y) of channel specified.
     \param x pixel coordinate
     \param y pixel coordinate 
     \param channel image channel
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    float access_pixel(int x, int y, int channel);
    
    //! pixel access.
    /*!
     Returns the value of the pixel (x,y) of all channels pushing them into the
     vector passed. 
     \param x pixel coordinate
     \param y pixel coordinate 
     \vector<float>& value container
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void get_pixel(int x, int y, vector<float>& values);
    
    //! put data into vigra RGB image.
    /*!
     Passed vigra RGB image instance is filled with the first three data channels.
     If the image has more channel all above 3 are ignored. If there arre less than
     three channels available, the missing are set to zero.
     \param rgb_img a vigra RGB image container
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void get_rgb(vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> >& rgb_img);
    
    //! convert to OpenCV Mat 
    /*!
     Converts image data to OpenCV Mat object. 
     \param cv_mat reference to opencv container 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void get_opencv(cv::Mat& cv_mat);
    
    //! convert single channel to OpenCV Mat 
    /*!
     Converts data from a single channel to OpenCV Mat object. 
     \param channel to be copied
     \param cv_mat reference to opencv container 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void get_opencv(int channel, cv::Mat& cv_mat);
    
    
   
    
    
protected:
    vector<vigra::MultiArray<2,float>* > _data; //!< vector storing pointers to MultiArray channels
    int _width;                                 //!< image width
    int _height;                                //!< image height
    int _num_of_channels;                       //!< number of channels (size of vector _data)
    string _label;                              //!< image label "bw","vec","rgb" or specified by user
    
private:

};

}
#endif	/* IMAGE_HPP */

