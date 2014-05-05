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

#include "OpenLF/debug.hpp"
#include "OpenLF/global.hpp"
#include "OpenLF/image/io.hpp"
#include "OpenLF/utils/helpers.hpp"
#include "OpenLF/image/Channel.hpp"
#include "OpenLF/lightfield/Properties.hpp"


namespace OpenLF { 
    namespace lightfield { 
        namespace io {
            
   

//! load a 4D light field from filenames in directory
/*!
 Loads all files in passed directory and creates 4D light field channels depending 
 on color mode into the passed map container using channel names as keys (bw,r,g,b). 
 If in properties a region of interest is set (mandatory is width and height of the roi
 and the values roi_pos_x and roi_pos_y) the channels are only filled with the roi. 
 \note Mandatory for this method is that cams_v and cams_h are set in Property struct
 * 
 \param fname_list list of filenames to load
 \param channels map container storing the channels
 \param properties struct storing the important parameter 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_4D_structure( std::vector<std::string> fname_list,
                        std::map< std::string,image::ImageChannel> &channels,
                        Properties *properties );



//! load horizontal 3D light field data from filenames in directory
/*!
 Loads all files in passed directory and creates 3DH light field channels depending 
 on color mode into the passed map container using channel names as keys (bw,r,g,b).
 If in properties a region of interest is set (mandatory is width and height of the roi
 and the values roi_pos_x and roi_pos_y) the channels are only filled with the roi. 
 \note Mandatory for this method is that cams_v and cams_h are set in Property struct 
 \param channels map container storing the channels
 \param properties struct storing the important parameter 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_3DH_structure( std::vector<std::string> fname_list,
                         std::map< std::string,image::ImageChannel> &channels,
                         Properties *properties );


//! load vertical 3D light field data from filenames in directory
/*!
 Loads all files in passed directory and creates 3DV light field channels depending 
 on color mode into the passed map container using channel names as keys (bw,r,g,b). 
 If in properties a region of interest is set (mandatory is width and height of the roi
 and the values roi_pos_x and roi_pos_y) the channels are only filled with the roi. 
 \note Mandatory for this method is that cams_v and cams_h are set in Property struct
 \param channels map container storing the channels
 \param properties struct storing the important parameter 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_3DV_structure( std::vector<std::string> fname_list,
                         std::map< std::string,image::ImageChannel> &channels,
                         Properties *properties );


//! load cross light field data from filenames in directory
/*!
 Loads all files in passed directory and creates cross light field channels depending 
 on color mode into the passed map container using channel names as keys (bw,r,g,b). 
 If in properties a region of interest is set (mandatory is width and height of the roi
 and the values roi_pos_x and roi_pos_y) the channels are only filled with the roi. 
 \note Mandatory for this method is that cams_v and cams_h are set in Property struct
 \param channels map container storing the channels
 \param properties struct storing the important parameter 
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_cross_structure( std::vector<std::string> fname_list,
                           std::map< std::string,image::ImageChannel> &channels,
                           Properties *properties );
            

//! load light field data from filenames in directory
/*!
 Loads all files in passed directory and creates light field channels depending 
 on color mode into the passed map container using channel names as keys (bw,r,g,b).
 \note Mandatory for this method is that "type", "cams_v" and "cams_h" are set in 
 the Property struct. Ensure to specifiy those via an configfile or during runtime 
 before calling the method.
 \image html resources/LF_TYPES.jpg   
 \param dir directory to search for files
 \param channels map container storing the channels
 \param properties struct storing the important parameter
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_from_filesequence( std::string dir, 
                             std::map< std::string,image::ImageChannel> &channels,
                             Properties *properties);





//! load MultiArray map data from hdf5 file
/*!
 Loads all channels from a hdf5 file and sets all available properties   
 \param file_name full path of the hdf5 file
 \param channels map container storing the channels
 \param properties struct storing the important parameter
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool load_from_hdf5( std::string file_name, 
                     std::map< std::string,image::ImageChannel> &channels,
                     Properties *properties);



//! save MultiArray map to hdf5 file
/*!
 Saves all channels in form of a MultiArray map to datasets in a hdf5 file, as  
 well as the passed arguments as properties.   
 \param file_name full path of the hdf5 file
 \param channels map container storing the channels
 \param properties struct storing the important parameter
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
bool save_to_hdf5( std::string file_name, 
                   std::map< std::string,image::ImageChannel> &channels,
                   Properties *properties);


}}}
#endif	/* IO_LIGHTFIELD_HPP */

