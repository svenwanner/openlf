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
    Image();                     // default constructor
    virtual ~Image();            // destructor
    Image(int,int,int);          // empty image constructor (width,height,channels)
    Image(const char*);          // load from file constructor (filename)
    Image(const Image& orig);    // copy constructor
    
    int width() const;           // returns width
    int height() const;          // returns height
    int channels() const;        // returns number of channels
    string label() const;        // returns image label
    void set_label(string);      // set image label (label)
    
    void load(const char*);      // load image from file (filename)
    
    float* get_channel(int);
    void swap_channel(int,vigra::MultiArray<2,float>&);
    
    float acccess_pixel(int,int,int);
    float get_pixel(int,int,vector<float>&);
    
//    void get_channel(int,vigra::MultiArray<2,float>&);
    
//    float* get_data();
    
//    vigra::MultiArray<2,float>* get_channel(int);
//    void get_bw_channel(vigra::MultiArray<2,float>&);
//    void get_vec_channels(vigra::MultiArray<2,float>*,vigra::MultiArray<2,float>*);
//    void get_rgb_channels(vigra::MultiArray<2,float>*,vigra::MultiArray<2,float>*,vigra::MultiArray<2,float>*);
//    void get_rgb_compact(vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> >&);
    
protected:
    vector<vigra::MultiArray<2,float>* > _data;
    int _width,_height;
    string _label;
    
private:

};

}
#endif	/* IMAGE_HPP */

