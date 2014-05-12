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

#include "OpenLF/lightfield/io.hpp"





    
bool OpenLF::lightfield::io::load_4D_structure( std::vector<std::string> fname_list, 
                                                std::map< std::string,OpenLF::image::ImageChannel> &channels, 
                                                Properties *properties )
{
    print(2,"lightfield::io::load_4D_structure(fname_list,channels,properties) called...");
    
    try {
        // create roi if needed
        OpenLF::image::ROI roi;
        roi.height = 0;
        roi.width = 0;
        roi.pos_x = 0;
        roi.pos_y = 0;
        bool use_roi = false;
                
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());
        
        // image size
        int width = 0;
        int height = 0;
        if(properties->has_field("width"))
        {
            properties->get_field("width",width);
        }
        else
        {
            width = info.width();
            properties->set_field("width",width);
        }
        if(properties->has_field("height"))
        {
            properties->get_field("height",height);
        }
        else
        {
            height = info.height();
            properties->set_field("height",height);
        }
        
        // camera grid info
        int cams_h;
        properties->get_field("cams_h",cams_h);
        int cams_v;
        properties->get_field("cams_v",cams_v);
        
        // init the roi if available
        bool roi_x_available = properties->has_field("roi_pos_x");
        bool roi_y_available = properties->has_field("roi_pos_y");
        if(roi_x_available && roi_y_available)
        {
            int roi_pos = 0;
            properties->get_field("roi_pos_x",roi_pos);
            if(roi_pos < 0 || roi_pos >= info.width())
                throw OpenLF_Exception("region of interest out of bounce!");
            roi.pos_x = roi_pos;
            properties->get_field("roi_pos_y",roi_pos);
            if(roi_pos < 0 || roi_pos >= info.height())
                throw OpenLF_Exception("region of interest out of bounce!");
            roi.pos_y = roi_pos;
            roi.width = width;
            roi.height = height;
            use_roi = true;
        }
        

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_4D_structure found grayscale image...");
            print(3,"create bw light field of size :");
            print(3,"width =",width);
            print(3,"height =",height);
            print(3,"cams_h =",cams_h);
            print(3,"cams_v =",cams_v);
            
            channels["bw"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_h*width,cams_v*height));
            
            // loop over images
            for(int v=0; v<cams_v; v++) {
                for(int h=0; h<cams_h; h++) {
                    
                    try {
                        // load image infos from fname_list
                        vigra::ImageImportInfo info_bw(fname_list[v*cams_h+h].c_str());

                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::UInt8> in(info_bw.width(), info_bw.height());

                        // import data
                        vigra::importImage(info_bw, vigra::destImage(in));
                      
                        // copy data into object and map to range [1,0]
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                if(use_roi)
                                {
                                    channels["bw"](h*width+x,v*height+y) = ((float)in(roi.pos_x+x,roi.pos_y+y))/255.0;
                                }
                                else {
                                    channels["bw"](h*width+x,v*height+y) = ((float)in(x,y))/255.0;
                                }
                            }
                        }
                    }
                    catch(int a) {
                        return false;
                    }
                }
            }
        } 
        
        // load color images
        else if(info.isColor()) {
            print(3,"lightfield::io::load_4D_structure found color image...");
            print(3,"create rgb light field of size :");
            print(3,"width =",width);
            print(3,"height =",height);
            print(3,"cams_h =",cams_h);
            print(3,"cams_v =",cams_v);
            
            channels["r"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_h*width,cams_v*height)); 
            channels["g"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_h*width,cams_v*height)); 
            channels["b"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_h*width,cams_v*height)); 

            for(int v=0; v<cams_v; v++) {
                for(int h=0; h<cams_h; h++) {

                    try {
                        // load image infos from fname_list
                        vigra::ImageImportInfo info_rgb(fname_list[v*cams_h+h].c_str());
            
                        // uint rgb image to import data from file
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(vigra::Shape2(info_rgb.width(),info_rgb.height()));
                        
                        
                        // import data
                        if(info_rgb.numExtraBands()!=0) {
                            vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(info_rgb.width(),info_rgb.height()));
                            vigra::importImageAlpha(info_rgb, in, alpha);
                        }
                        else {
                            vigra::importImage(info_rgb, in);
                        }
                        
                        // copy data into lf container
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                
                                if(use_roi)
                                {
                                    channels["r"](h*width+x,v*height+y) = ((float)in(roi.pos_x+x,roi.pos_y+y)[0])/255.0f;
                                    channels["g"](h*width+x,v*height+y) = ((float)in(roi.pos_x+x,roi.pos_y+y)[1])/255.0f;
                                    channels["b"](h*width+x,v*height+y) = ((float)in(roi.pos_x+x,roi.pos_y+y)[2])/255.0f;
                                }
                                else 
                                {
                                    channels["r"](h*width+x,v*height+y) = ((float)in(x,y)[0])/255.0f;
                                    channels["g"](h*width+x,v*height+y) = ((float)in(x,y)[1])/255.0f;
                                    channels["b"](h*width+x,v*height+y) = ((float)in(x,y)[2])/255.0f;   
                                }
                            }
                        }
                    }
                    catch(int a) {
                        return false;
                    }
                }
            }
        }
    }
    catch(int a) {
        return false;
        
        warning("Exception in lightfield::io::load_4D_structure...");
    }
    
    return true;
}



bool OpenLF::lightfield::io::load_3DH_structure( std::vector<std::string> fname_list, 
                                                 std::map< std::string,OpenLF::image::ImageChannel> &channels, 
                                                 Properties *properties ) 
{
    print(2,"lightfield::io::load_3DH_structure(fname_list,channels,properties) called...");
     
    // create roi if needed
    OpenLF::image::ROI roi;
    roi.height = 0;
    roi.width = 0;
    roi.pos_x = 0;
    roi.pos_y = 0;
    bool use_roi = false;
    
    // camera grid info
    int cams_h;
    properties->get_field("cams_h",cams_h);
    int cams_v;
    properties->get_field("cams_v",cams_v);
    
    if(cams_v!=1) warning("You tried to load a horizontal light field but your parameter cams_v is not 1");
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());
        
        // image size
        int width = 0;
        int height = 0;
        if(properties->has_field("width"))
        {
            properties->get_field("width",width);
        }
        else
        {
            width = info.width();
            properties->set_field("width",width);
        }
        if(properties->has_field("height"))
        {
            properties->get_field("height",height);
        }
        else
        {
            height = info.height();
            properties->set_field("height",height);
        }
        
        
        // init the roi if available
        bool roi_x_available = properties->has_field("roi_pos_x");
        bool roi_y_available = properties->has_field("roi_pos_y");
        if(roi_x_available && roi_y_available)
        {
            int roi_pos = 0;
            properties->get_field("roi_pos_x",roi_pos);
            if(roi_pos < 0 || roi_pos >= info.width())
                throw OpenLF_Exception("region of interest out of bounce!");
            roi.pos_x = roi_pos;
            properties->get_field("roi_pos_y",roi_pos);
            if(roi_pos < 0 || roi_pos >= info.height())
                throw OpenLF_Exception("region of interest out of bounce!");
            roi.pos_y = roi_pos;
            roi.width = width;
            roi.height = height;
            use_roi = true;
        }
        

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_3DH_structure found grayscale image...");
            channels["bw"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_h*width,height));

            // loop over images
            for(int h=0; h<cams_h; h++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_bw(fname_list[h].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::UInt8> in(info_bw.width(), info_bw.height());

                    // import data
                    vigra::importImage(info_bw, vigra::destImage(in));

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            
                            if(use_roi)
                            {
                                channels["bw"](h*width+x,y) = ((float)in(roi.pos_x+x,roi.pos_y+y))/255.0;
                            }
                            else {
                                channels["bw"](h*width+x,y) = ((float)in(x,y))/255.0;
                            }
                        }
                    }
                }
                catch(int a) {
                    warning("Loading bw image data failed while copying data into lf container");
                    return false;
                }
            }
        } 
       
        // load color images
        else if(info.isColor()) {
            print(3,"lightfield::io::load_3DH_structure found color image...");
            
            channels["r"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_h*width,height)); 
            channels["g"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_h*width,height)); 
            channels["b"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_h*width,height)); 


            for(int h=0; h<cams_h; h++) {

                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[h].c_str());

                    // uint rgb image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info_rgb.shape());

                    
                    // import data
                    if(info_rgb.numExtraBands()!=0) {
                        vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(info_rgb.width(),info_rgb.height()));
                        vigra::importImageAlpha(info_rgb, in, alpha);
                    }
                    else {
                        vigra::importImage(info_rgb, in);
                    }                 

                    // copy data into lf container
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            
                            if(use_roi)
                            {
                                channels["r"](h*width+x,y) = ((float)in(roi.pos_x+x,roi.pos_y+y)[0])/255.0f;
                                channels["g"](h*width+x,y) = ((float)in(roi.pos_x+x,roi.pos_y+y)[1])/255.0f;
                                channels["b"](h*width+x,y) = ((float)in(roi.pos_x+x,roi.pos_y+y)[2])/255.0f;
                            }
                            else {
                                channels["r"](h*width+x,y) = ((float)in(x,y)[0])/255.0f;
                                channels["g"](h*width+x,y) = ((float)in(x,y)[1])/255.0f;
                                channels["b"](h*width+x,y) = ((float)in(x,y)[2])/255.0f;
                            }                            
                        }
                    }
                }
                catch(int a) {
                    warning("Loading rgb image data failed while copying data into lf container");
                    return false;
                }
            }
        }
        return true;
    }
    catch(int a) {
        warning("Loading image data failed while copying data into lf container");
        return false;
    }
}





bool OpenLF::lightfield::io::load_3DV_structure( std::vector<std::string> fname_list, 
                                                 std::map< std::string,OpenLF::image::ImageChannel> &channels, 
                                                 Properties *properties )

{
    print(2,"lightfield::io::load_3DV_structure(fname_list,channels,properties) called...");
 
    // create roi if needed
    OpenLF::image::ROI roi;
    roi.height = 0;
    roi.width = 0;
    roi.pos_x = 0;
    roi.pos_y = 0;
    bool use_roi = false;
    
    // camera grid info
    int cams_h;
    properties->get_field("cams_h",cams_h);
    int cams_v;
    properties->get_field("cams_v",cams_v);
    
    if(cams_h!=1) warning("You tried to load a vertical light field but your parameter cams_h is not 1");
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());

        // image size
        int width = 0;
        int height = 0;
        if(properties->has_field("width"))
        {
            properties->get_field("width",width);
        }
        else
        {
            width = info.width();
            properties->set_field("width",width);
        }
        if(properties->has_field("height"))
        {
            properties->get_field("height",height);
        }
        else
        {
            height = info.height();
            properties->set_field("height",height);
        }
        
        
        // init the roi if available
        bool roi_x_available = properties->has_field("roi_pos_x");
        bool roi_y_available = properties->has_field("roi_pos_y");
        if(roi_x_available && roi_y_available)
        {
            int roi_pos = 0;
            properties->get_field("roi_pos_x",roi_pos);
            if(roi_pos < 0 || roi_pos >= info.width())
                throw OpenLF_Exception("region of interest out of bounce!");
            roi.pos_x = roi_pos;
            properties->get_field("roi_pos_y",roi_pos);
            if(roi_pos < 0 || roi_pos >= info.height())
                throw OpenLF_Exception("region of interest out of bounce!");
            roi.pos_y = roi_pos;
            roi.width = width;
            roi.height = height;
            use_roi = true;
        }

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_3DV_structure found grayscale image...");
            channels["bw"] = OpenLF::image::ImageChannel(cams_v*height,width);
            //vigra::MultiArray<2,float> tmp(vigra::Shape2(cams_v*info.height(),info.width()));

            // loop over images
            for(int v=0; v<cams_v; v++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_bw(fname_list[v].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::UInt8> in(info_bw.width(), info_bw.height());

                    // import data
                    vigra::importImage(info_bw, vigra::destImage(in));
                    
                    

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            if(use_roi)
                            {
                                channels["bw"](v*height+y,x) = ((float)in(roi.pos_x+x,roi.pos_y+y))/255.0;
                            }
                            else {
                                channels["bw"](v*height+y,x) = ((float)in(x,y))/255.0;
                            }
                        }
                    }
                }
                catch(int a) {
                    warning("Loading bw image data failed while copying data into lf container");
                    return false;
                }
            }
            
        } 
       
        // load color images
        else if(info.isColor()) {
            print(3,"lightfield::io::load_3DV_structure found color image...");
            
            channels["r"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_v*height,width)); 
            channels["g"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_v*height,width)); 
            channels["b"] = OpenLF::image::ImageChannel(vigra::Shape2(cams_v*height,width));
            
            for(int v=0; v<cams_v; v++) {

                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[v].c_str());

                    // uint rgb image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info_rgb.shape());

                    // import data
                    if(info_rgb.numExtraBands()!=0) {
                        vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(info_rgb.width(),info_rgb.height()));
                        vigra::importImageAlpha(info_rgb, in, alpha);
                    }
                    else {
                        vigra::importImage(info_rgb, in);
                    }                   

                    // copy data into lf container
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            
                            
                            if(use_roi)
                            {
                                channels["r"](v*height+y,x) = ((float)in(roi.pos_x+x,roi.pos_y+y)[0])/255.0f;
                                channels["g"](v*height+y,x) = ((float)in(roi.pos_x+x,roi.pos_y+y)[1])/255.0f;
                                channels["b"](v*height+y,x) = ((float)in(roi.pos_x+x,roi.pos_y+y)[2])/255.0f;
                            }
                            else {
                                channels["r"](v*height+y,x) = ((float)in(x,y)[0])/255.0f;
                                channels["g"](v*height+y,x) = ((float)in(x,y)[1])/255.0f;
                                channels["b"](v*height+y,x) = ((float)in(x,y)[2])/255.0f;
                            }
                        }
                    }
                }
                catch(int a) {
                    warning("Loading rgb image data failed while copying data into lf container");
                    return false;
                }
            }
        }
        
        
        return true;
    }
    catch(int a) {
        warning("Loading image data failed while copying data into lf container");
        return false;
    }
}





bool OpenLF::lightfield::io::load_cross_structure( std::vector<std::string> fname_list, 
                                                   std::map< std::string,OpenLF::image::ImageChannel> &channels, 
                                                   Properties *properties )
{
    print(2,"lightfield::io::load_cross_structure(fname_list,channels,properties) called...");
    
    // create roi if needed
    OpenLF::image::ROI roi;
    roi.height = 0;
    roi.width = 0;
    roi.pos_x = 0;
    roi.pos_y = 0;
    bool use_roi = false;
     
    // camera grid info
    int cams_h;
    properties->get_field("cams_h",cams_h);
    int cams_v;
    properties->get_field("cams_v",cams_v);
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());
      
        // image size
        int width = 0;
        int height = 0;
        if(properties->has_field("width"))
        {
            properties->get_field("width",width);
        }
        else
        {
            width = info.width();
            properties->set_field("width",width);
        }
        if(properties->has_field("height"))
        {
            properties->get_field("height",height);
        }
        else
        {
            height = info.height();
            properties->set_field("height",height);
        }
        
        int cv_index = cams_h/2;
        
        int lf_width=0;
        int lf_height=0;
        int tmp = cams_h*width;
        
        // find width of lf image by checking possible dimensions
        if(tmp > cams_v*height) {
            lf_width = tmp;
            lf_height = width+height;
        }
        else {
            lf_width = cams_v*height;
            lf_height = width+height;
        }
        

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_CROSS_structure found grayscale image...");
            channels["bw"] = OpenLF::image::ImageChannel(vigra::Shape2(lf_width,lf_height));

            // loop over horizontal images
            for(int h=0; h<cams_h; h++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_bw(fname_list[h].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::UInt8> in(info_bw.width(), info_bw.height());

                    // import data
                    vigra::importImage(info_bw, vigra::destImage(in));

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            if(use_roi)
                            {
                                channels["bw"](h*width+x,y) = ((float)in(roi.pos_x+x,roi.pos_y+y))/255.0;
                            }
                            else {
                                channels["bw"](h*width+x,y) = ((float)in(x,y))/255.0;
                            }
                        }
                    }
                }
                catch(int a) {
                    warning("Loading bw image data failed while copying data into lf container");
                    return false;
                }
            }
            
            // loop vertical over images
            int image_index=cams_h;
            for(int v=0; v<cams_v; v++) {
                
                try {
                            
                    // load image infos from fname_list
                    if(v==cv_index) {
                        vigra::ImageImportInfo info_bw(fname_list[cv_index].c_str());
                        
                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::UInt8> in(info_bw.width(), info_bw.height());

                        // import data
                        vigra::importImage(info_bw, vigra::destImage(in));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                if(use_roi)
                                {
                                    channels["bw"](v*height+y,height+x) = ((float)in(roi.pos_x+x,roi.pos_y+y))/255.0;
                                }
                                else {
                                    channels["bw"](v*height+y,height+x) = ((float)in(x,y))/255.0;
                                }
                            }
                        }
                    }
                    else {
                        vigra::ImageImportInfo info_bw(fname_list[image_index].c_str());
                        image_index++;
                        
                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::UInt8> in(info_bw.width(), info_bw.height());

                        // import data
                        vigra::importImage(info_bw, vigra::destImage(in));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                if(use_roi)
                                {
                                    channels["bw"](v*height+y,height+x) = ((float)in(roi.pos_x+x,roi.pos_y+y))/255.0;
                                }
                                else {
                                    channels["bw"](v*height+y,height+x) = ((float)in(x,y))/255.0;
                                }
                                
                            }
                        }
                    }

                    
                }
                catch(int a) {
                    warning("Loading bw image data failed while copying data into lf container");
                    return false;
                }
            }
            
        } 
       
        // load color images
        else if(info.isColor()) {
            print(3,"lightfield::io::load_CROSS_structure found color image...");
            
            channels["r"] = OpenLF::image::ImageChannel(vigra::Shape2(lf_width,lf_height)); 
            channels["g"] = OpenLF::image::ImageChannel(vigra::Shape2(lf_width,lf_height)); 
            channels["b"] = OpenLF::image::ImageChannel(vigra::Shape2(lf_width,lf_height)); 
            
            // loop over horizontal images
            for(int h=0; h<cams_h; h++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[h].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(info_rgb.width(), info_rgb.height());
                    
                    // import data
                    if(info_rgb.numExtraBands()!=0) {
                        vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(info_rgb.width(),info_rgb.height()));
                        vigra::importImageAlpha(info_rgb, in_rgb, alpha);
                    }
                    else {
                        vigra::importImage(info_rgb, in_rgb);
                    }
                    

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            if(use_roi)
                            {
                                channels["r"](h*width+x,y) = ((float)in_rgb(roi.pos_x+x,roi.pos_y+y)[0])/255.0;
                                channels["g"](h*width+x,y) = ((float)in_rgb(roi.pos_x+x,roi.pos_y+y)[1])/255.0;
                                channels["b"](h*width+x,y) = ((float)in_rgb(roi.pos_x+x,roi.pos_y+y)[2])/255.0;
                            }
                            else {
                                channels["r"](h*width+x,y) = ((float)in_rgb(x,y)[0])/255.0;
                                channels["g"](h*width+x,y) = ((float)in_rgb(x,y)[1])/255.0;
                                channels["b"](h*width+x,y) = ((float)in_rgb(x,y)[2])/255.0;
                            }
                        }
                    }
                }
                catch(int a) {
                    warning("Loading bw image data failed while copying data into lf container");
                    return false;
                }
            }
            
            // loop vertical over images
            int image_index=cams_h;
            for(int v=0; v<cams_v; v++) {
                
                try {
                            
                    // load image infos from fname_list
                    if(v==cv_index) {
                        vigra::ImageImportInfo info_rgb(fname_list[cv_index].c_str());
                        
                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(info_rgb.width(), info_rgb.height());

                        // import data
                        //vigra::importImage(info_rgb, vigra::destImage(in_rgb));
                        
                        // import data
                        if(info_rgb.numExtraBands()!=0) {
                            vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(info_rgb.width(),info_rgb.height()));
                            vigra::importImageAlpha(info_rgb, in_rgb, alpha);
                        }
                        else {
                            vigra::importImage(info_rgb, in_rgb);
                        }

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                if(use_roi)
                                {
                                    channels["r"](v*height+y,height+x) = ((float)in_rgb(roi.pos_x+x,roi.pos_y+y)[0])/255.0;
                                    channels["g"](v*height+y,height+x) = ((float)in_rgb(roi.pos_x+x,roi.pos_y+y)[1])/255.0;
                                    channels["b"](v*height+y,height+x) = ((float)in_rgb(roi.pos_x+x,roi.pos_y+y)[2])/255.0;
                                }
                                else {
                                    channels["r"](v*height+y,height+x) = ((float)in_rgb(x,y)[0])/255.0;
                                    channels["g"](v*height+y,height+x) = ((float)in_rgb(x,y)[1])/255.0;
                                    channels["b"](v*height+y,height+x) = ((float)in_rgb(x,y)[2])/255.0;
                                }
                            }
                        }
                    }
                    else {
                        vigra::ImageImportInfo info_rgb(fname_list[image_index].c_str());
                        image_index++;
                        
                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(info_rgb.width(), info_rgb.height());

                        // import data
                        if(info_rgb.numExtraBands()!=0) {
                            vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(info_rgb.width(),info_rgb.height()));
                            vigra::importImageAlpha(info_rgb, in_rgb, alpha);
                        }
                        else {
                            vigra::importImage(info_rgb, in_rgb);
                        }

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                if(use_roi)
                                {
                                    channels["r"](v*height+y,height+x) = ((float)in_rgb(roi.pos_x+x,roi.pos_y+y)[0])/255.0;
                                    channels["g"](v*height+y,height+x) = ((float)in_rgb(roi.pos_x+x,roi.pos_y+y)[1])/255.0;
                                    channels["b"](v*height+y,height+x) = ((float)in_rgb(roi.pos_x+x,roi.pos_y+y)[2])/255.0;
                                }
                                else {
                                    channels["r"](v*height+y,height+x) = ((float)in_rgb(x,y)[0])/255.0;
                                    channels["g"](v*height+y,height+x) = ((float)in_rgb(x,y)[1])/255.0;
                                    channels["b"](v*height+y,height+x) = ((float)in_rgb(x,y)[2])/255.0;
                                }                                
                            }
                        }
                    }

                    
                }
                catch(int a) {
                    warning("Loading bw image data failed while copying data into lf container");
                    return false;
                }
            }
        }
        return true;
    }
    catch(int a) {
        warning("Loading image data failed while copying data into lf container");
        return false;
    }
}






bool OpenLF::lightfield::io::load_from_filesequence(std::string dir, 
                                                    std::map< std::string,OpenLF::image::ImageChannel> &channels, 
                                                    Properties *properties)

/*TEST: test_lightfield::test_loading_from_imagefiles() */
{
    print(1,"lightfield::io::load_from_filesequence(dir,channels,properties) called...");
     
    // get list of filenames
    std::vector<std::string> list;
    if(OpenLF::helpers::filenames_from_directory(dir, list)) {
        
        std::vector<std::string> fname_list;
        for(unsigned int i=0; i<list.size(); i++) {
            fname_list.push_back(dir+list[i]);
            print(3,fname_list[i].c_str());
        }
         
        // decide data structure depending on lf type
        LF_TYPE type;
        properties->get_lftype(type);
        if(!properties->get_lftype(type))
            throw OpenLF_Exception("Unknown LF_TYPE in lightfield::io::load_from_filesequence, check your Properties instance or your ConfigFile!");
        switch(type) {
            case LF_4D:
                return load_4D_structure(fname_list,channels,properties);
            case LF_3DH:
                return load_3DH_structure(fname_list,channels,properties);
            case LF_3DV:
                return load_3DV_structure(fname_list,channels,properties);
            case LF_CROSS:
                return load_cross_structure(fname_list,channels,properties);
            default:
                throw OpenLF_Exception("Unknown LF_TYPE in lightfield::io::load_from_filesequence, check your Properties instance or your ConfigFile!");
                return false;
        }
    }
    return false;
}




bool OpenLF::lightfield::io::load_from_hdf5( std::string filename, 
                     std::map< std::string,OpenLF::image::ImageChannel> &channels,
                     Properties *properties ) 
{    
    print(2,"lightfield::io::load_from_hdf5(filename,channels,properties) called...");
    
    
    // read all attribute names 
    std::vector<std::string> attrs;
    std::vector<bool> isStr;
    OpenLF::helpers::get_attribute_list(filename,"LF",attrs,isStr);
    if(attrs.size()==0) throw OpenLF_Exception("No attributes found while loading from hdf5!");
    
    // open hdf5 file
    vigra::HDF5File file(filename.c_str(),vigra::HDF5File::OpenReadOnly);
    // ensure you're in root dir
    file.root();
    
    try {
        // navigate to group LF
        file.cd_mk("LF");
       
        
        // if no bw or rgb channels available throw exception
        if((file.existsDataset("r") && file.existsDataset("g") && file.existsDataset("b")) || file.existsDataset("bw")) {
            
            // read the dataset names
            std::vector<std::string> ds_tree;
            ds_tree = file.ls();
            
            while(true) {
                if(isStr.size()==0 || attrs.size()==0) break;
                
                std::string name = attrs.back();
                bool str = isStr.back();
                float num_fval = 0.0;
                int num_ival = 0.0;
                std::string str_val = "";
                
                if(str) {
                    file.readAttribute("",name,str_val);
                    properties->set_field(name,str_val);
                    properties->get_field(name,str_val); 
                }
                else {
                    if(name=="LF_TYPE") {
                        // set the LF_TYPE
                        file.readAttribute("","LF_TYPE",num_ival);
                        properties->set_field("type",num_ival);
                    }
                    if(name=="width" || name=="height" || name=="cams_v" || name=="cams_h") {
                        file.readAttribute("",name,num_ival);
                        properties->set_field(name,num_ival);
                        
                        properties->get_field(name,num_ival);
                    }
                    else {
                        file.readAttribute("",name,num_fval);
                        properties->set_field(name,num_fval);
                        properties->get_field(name,num_fval);
                    }
                }
                
                attrs.pop_back();
                isStr.pop_back();
            }
            
            // read the datasets
            for(unsigned int id=0; id<ds_tree.size(); id++ ) {
                // determine data set shape
                vigra::ArrayVector<int> ds_shape(2);
                ds_shape = file.getDatasetShape(ds_tree[id]);
                
                // allocate memory and read channels
                channels[ds_tree[id]] = OpenLF::image::ImageChannel(ds_shape[0],ds_shape[1]);
                vigra::MultiArray<2,float> *tmp;
                channels[ds_tree[id]].image(&tmp);
                file.read(ds_tree[id], *tmp);
            }
            
        } else throw OpenLF_Exception("Loading light field from HDF5 failed, at least rgb or a bw channel is obligatory!");
    }
    catch(std::exception & e) {
        warning(e.what());
        return false;
    }
    
    return true;
}



bool OpenLF::lightfield::io::save_to_hdf5( std::string file_name, 
                   std::map< std::string,OpenLF::image::ImageChannel> &channels,
                   Properties *properties ) 
{
    print(2,"lightfield::io::save_to_hdf5(filename,channels,properties) called...");
    
    try {
        std::string dset_name;
        
        // open hdf5 file and define group name
        vigra::HDF5File file(file_name.c_str(),vigra::HDF5File::New);
        file.mkdir("LF");
        
        // loop over channels and save each using its key as dataset names
        for(std::map<std::string, OpenLF::image::ImageChannel>::iterator i = channels.begin(); i != channels.end(); ++i)
        {
            std::string key = i->first;
            dset_name = "/LF/"+key;
            vigra::MultiArray<2,float> *tmp;
            channels[key].image(&tmp);
            file.write(dset_name.c_str(), *tmp);
        }        
        
        int itmp;
        float ftmp;
        std::string stmp;
        std::vector<std::string> fields;
        properties->get_num_field_keys(fields);
        
        
        // write obligatory attributes
        if(properties->get_field("type",itmp)) {
            if(OpenLF::helpers::remove_by_value(fields, "type"))
                file.writeAttribute("/LF/","LF_TYPE",itmp);
            else warning("Missing obligatory property (LF_TYPE) while saving to hdf5!");
        }
        
        if(properties->get_field("width",itmp)) {
            if(OpenLF::helpers::remove_by_value(fields, "width"))
                file.writeAttribute("/LF/","width",itmp);
            else warning("Missing obligatory property (width) while saving to hdf5!");
        }
        if(properties->get_field("height",itmp)) {
            if(OpenLF::helpers::remove_by_value(fields, "height"))
                file.writeAttribute("/LF/","height",itmp);
            else warning("Missing obligatory property (height) while saving to hdf5!");
        }
        
        if(properties->get_field("cams_h",itmp)) {
            if(OpenLF::helpers::remove_by_value(fields, "cams_h"))
                file.writeAttribute("/LF/","cams_h",itmp);
            else warning("Missing obligatory property (cams_h) while saving to hdf5!");
        }
        
        if(properties->get_field("cams_v",itmp)) {
            if(OpenLF::helpers::remove_by_value(fields, "cams_v"))
                file.writeAttribute("/LF/","cams_v",itmp);
            else warning("Missing obligatory property (cams_v) while saving to hdf5!");
        }
        
        // write all attributes left as float or string
        for(unsigned int n=0; n<fields.size(); n++) {
            if(properties->get_field(fields[n],ftmp))
                file.writeAttribute("/LF/",fields[n],ftmp);
        }
        fields.clear();
        
        
        properties->get_str_field_keys(fields);
        for(unsigned int n=0; n<fields.size(); n++) {
            if(properties->get_field(fields[n],stmp))
                file.writeAttribute("/LF/",fields[n],stmp);
        }
        fields.clear();    
    }
    catch(std::exception & e) {
        warning(e.what());
        return false;
    }
    
    return true;
}