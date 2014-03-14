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



/**
 * \class Lightfield_base
 *
 * \brief ...
 *
 * ...
 *
 * \note ...
 *
 * \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 * 
 */

#ifndef LIGHTFIELD_BASE_HPP
#define	LIGHTFIELD_BASE_HPP

#include "global.hpp"

namespace OpenLF {

class Lightfield_base {
public:
    
    //! Default constructor
    /*!
      Initializes an empty lightfield of size zero without a type. 
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    Lightfield_base();
    virtual ~Lightfield_base();
  
    //! release data
    /*!
     Deletes all channels and labels
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void release();
    
    
    //! Empty lightfield constructor
    /*!
      Initializes an empty lightfield whose channels are filled with zeros. 
      Size, number of cameras, number of channels and the type must be specified.
     \param width of the images
     \param height of the images 
     \param cams_h number of horizontal cameras
     \param cams_v number of vertical cameras 
     \param channels to be initialized
     \param type light field type (3DH,3DV,4D,CROSS)
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    Lightfield_base(int width,int height,int cams_h,int cams_v,int channels,string type);
    
    //! Empty lightfield constructor
    /*!
      Initializes an empty lightfield whose channels are filled with zeros. 
      Size, number of cameras, number of channels, baselines, focal length and 
      the type must be specified.
     \param width of the images
     \param height of the images 
     \param cams_h number of horizontal cameras
     \param cams_v number of vertical cameras 
     \param channels to be initialized
     \param baseline_h horizontal distance between cameras 
     \param baseline_v vertical distance between cameras
     \param focal_length of the cameras
     \param type light field type (3DH,3DV,4D,CROSS)
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    Lightfield_base(int width,int height,int cams_h,int cams_v,int channels,float baseline_h,float baseline_v,float focal_length,string type);

    
    //! Copy constructor
    /*!
      Copies only properties of the passed object and allocates memory for all
      channels. To copy the entire lightfield use deepcopy(LightField&).
     \param orig instance to copy from
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    Lightfield_base(const Lightfield_base& orig);
    
    
    /*
     * GETTER SETTER METHODS
     */
    
    //! get number of cams vertical
    int cams_v() const;
    //! get number of cams horizontal
    int cams_h() const;
    //! get width.
    int width() const;
    //! get height.
    int height() const;
    //! get number of channels
    int channels() const;
    //! get focal length
    float focal_length() const;
    //! get vertical baseline
    float baseline_v() const;
    //! get vertical baseline
    float baseline_h() const;
    //! get label
    string type() const;
    //! check if container is valid
    bool valid() const;
    
    //! get channel by index
    void get_channel(int index, vigra::MultiArray<4,float>&);
    //! get channel by label
    void get_channel(string label, vigra::MultiArray<4,float>&);
    //! get channel name
    string get_label(int index);
    //! get vigra array shape of the data
    vigra::Shape4 shape();
    
    
    
    
    /*
     * CHANGE CONTENT METHODS
     */
    
    //! delete channel and corresponding label by index
    void delete_channel(int index);
    
    //! delete channel and corresponding label by label
    void delete_channel(string label);
    
    
    
protected: 
   
    int _width;                                  //!< image width
    int _height;                                 //!< image height
    int _num_of_cams_v;                          //!< number of cameras in vertical direction
    int _num_of_cams_h;                          //!< number of cameras in horizontal direction
    int _focal_length;                           //!< focal length of cameras
    int _baseline_v;                             //!< vertical distance between cameras
    int _baseline_h;                             //!< horizontal distance between cameras
    string _type;                                //!< lightfield type (3DH,3DV,4D,CROSS)
    bool _valid;                                 //!< true if all important data are available
    
    vector< vigra::MultiArray<4,float> > _data;  //!< data container holding the channels
    vector< string > _labels;                    //!< label container holding the channel names

protected:
    /*
     * PROTECTED HELPER METHODS
     */
    
    //! init lightfield properties.
    /*!
      Sets all necessary properties. Depending in the constructor the baselines
      and the focal length has to be set manually later. 
      If type is not 3DH,3DV,4D or CROSS, an exception will be thrown. 
      If channels are not zeros empty 4D MultiArrays for each channel specified through
      the parameters are initialized. Depending of the number of channels specified 
      labels are given like (bw) for a single channel, (r,g,b) if 3 channels are 
      set and as the channel index otherwise.
     \param width of the images
     \param height of the images 
     \param cams_h number of horizontal cameras
     \param cams_v number of vertical cameras 
     \param channels to be initialized
     \param baseline_h horizontal distance between cameras 
     \param baseline_v vertical distance between cameras
     \param focal_length of the cameras
     \param type light field type (3DH,3DV,4D,CROSS)
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void init_properties(int width, int height, int cams_h, int cams_v, int channels, float baseline_h, float baseline_v, float focal_length, string type);
    
    //! computes the index of the channel depending on the label.
    /*!
     \param label name of the channel
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    int get_data_index(string label);
};

}
#endif	/* LIGHTFIELD_BASE_HPP */

