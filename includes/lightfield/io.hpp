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


#ifndef IO_LIGHTFIELD_HPP
#define	IO_LIGHTFIELD_HPP

#include "global.hpp"
#include "image/io.hpp"
#include "utils/helpers.hpp"


namespace OpenLF { 
    namespace lightfield { 
        namespace io {
            
   

//! load a 4D light field from filenames in directory
/*!
 Loads all files in passed directory and creates 4D light field channels depending 
 on color mode into the passed map container using channel names as keys (bw,r,g,b). 
 \param channels map container storing the channels
 \param cams_h number of horizontal cameras
 \param cams_v number of vertical cameras 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_4D_structure( vector<string> fname_list,
                        map< string, vigra::MultiArray<2,float> > &channels,
                        int cams_h,
                        int cams_v );


//! load horizontal 3D light field data from filenames in directory
/*!
 Loads all files in passed directory and creates 3DH light field channels depending 
 on color mode into the passed map container using channel names as keys (bw,r,g,b). 
 \param channels map container storing the channels
 \param cams_h number of horizontal cameras
 \param cams_v number of vertical cameras 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_3DH_structure( vector<string> fname_list,
                         map< string, vigra::MultiArray<2,float> > &channels,
                         int cams_h,
                         int cams_v );


//! load vertical 3D light field data from filenames in directory
/*!
 Loads all files in passed directory and creates 3DV light field channels depending 
 on color mode into the passed map container using channel names as keys (bw,r,g,b). 
 \param channels map container storing the channels
 \param cams_h number of horizontal cameras
 \param cams_v number of vertical cameras 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_3DV_structure( vector<string> fname_list,
                         map< string, vigra::MultiArray<2,float> > &channels,
                         int cams_h,
                         int cams_v );


//! load cross light field data from filenames in directory
/*!
 Loads all files in passed directory and creates cross light field channels depending 
 on color mode into the passed map container using channel names as keys (bw,r,g,b). 
 \param channels map container storing the channels
 \param cams_h number of horizontal cameras
 \param cams_v number of vertical cameras 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_cross_structure( vector<string> fname_list,
                           map< string, vigra::MultiArray<2,float> > &channels,
                           int cams_h,
                           int cams_v );
            

//! load light field data from filenames in directory
/*!
 Loads all files in passed directory and creates light field channels depending 
 on color mode into the passed map container using channel names as keys (bw,r,g,b).
 Ensure that the images contain no alpha alpha channel, handling them is not yet supported.
 \image html resources/LF_TYPES.jpg   
 \param dir directory to search for files
 \param channels map container storing the channels
 \param type of light field to load (4D,3DH,3DV,CROSS)
 \param cams_h number of horizontal cameras
 \param cams_v number of vertical cameras 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_from_filesequence( string dir, 
                             map< string, vigra::MultiArray<2,float> > &channels,
                             LF_TYPE type,
                             int cams_h,
                             int cams_v );





//! load MultiArray map data from hdf5 file
/*!
 Loads all channels from a hdf5 file and sets all available properties   
 \param file_name full path of the hdf5 file
 \param channels map container storing the channels
 \param type reference of light field type to load (4D,3DH,3DV,CROSS)
 \param width reference to set the image width
 \param height reference to set the image height 
 \param cams_h reference to set number of horizontal cameras
 \param cams_v reference to set number of vertical cameras 
 \param baseline_h reference to set horizontal camera baseline
 \param baseline_v reference to set vertical camera baseline
 \param focal_length reference to set camera focal length
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_from_hdf5( string file_name, 
                     map< string, vigra::MultiArray<2,float> > &channels,
                     LF_TYPE &type,
                     int &width,
                     int &height,
                     int &cams_h,
                     int &cams_v,
                     float &baseline_h,
                     float &baseline_v,
                     float &focal_length );



//! save MultiArray map to hdf5 file
/*!
 Saves all channels in form of a MultiArray map to datasets in a hdf5 file, as  
 well as the passed arguments as properties.   
 \param file_name full path of the hdf5 file
 \param channels map container storing the channels
 \param type reference of light field type to load (4D,3DH,3DV,CROSS)
 \param width reference to set the image width
 \param height reference to set the image height 
 \param cams_h reference to set number of horizontal cameras
 \param cams_v reference to set number of vertical cameras 
 \param baseline_h reference to set horizontal camera baseline
 \param baseline_v reference to set vertical camera baseline
 \param focal_length reference to set camera focal length
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool save_to_hdf5( string file_name, 
                   map< string, vigra::MultiArray<2,float> > &channels,
                   LF_TYPE type,
                   int width,
                   int height,
                   int cams_h,
                   int cams_v,
                   float baseline_h,
                   float baseline_v,
                   float focal_length );


}}}
#endif	/* IO_LIGHTFIELD_HPP */

