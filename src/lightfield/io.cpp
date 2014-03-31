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

#include "lightfield/io.hpp"





    
bool OpenLF::lightfield::io::load_4D_structure( vector<string> fname_list, 
                                                map< string, 
                                                vigra::MultiArray<2,float> > &channels, 
                                                Properties *properties )

/*TEST: via load_from_filesequence in test_lightfield::test_loading_from_imagefiles() */
{
    print(2,"lightfield::io::load_4D_structure(fname_list,channels,properties) called...");
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());
        
        // image size
        int width = info.width();
        int height = info.height();
        properties->set_field("width",width);
        properties->set_field("height",height);
        
        // camera grid info
        int cams_h;
        properties->get_field("cams_h",cams_h);
        int cams_v;
        properties->get_field("cams_v",cams_v);
        
        print(3,"Image info:");
        print(3,"width: ",info.width());
        print(3,"height: ",info.height());
        print(3,"numBands: ",info.numBands());
        print(3,"numExtraBands: ",info.numExtraBands());
        

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_4D_structure found grayscale image...");
            print(3,"create bw light field of size :");
            print(3,"width =",width);
            print(3,"height =",height);
            print(3,"cams_h =",cams_h);
            print(3,"cams_v =",cams_v);
            
            channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*width,cams_v*height));

            // loop over images
            for(int v=0; v<cams_v; v++) {
                for(int h=0; h<cams_h; h++) {
                    
                    try {
                        // load image infos from fname_list
                        vigra::ImageImportInfo info_bw(fname_list[v*cams_h+h].c_str());

                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::UInt8> in(width, height);

                        // import data
                        vigra::importImage(info_bw, vigra::destImage(in));
                      
                        // copy data into object and map to range [1,0]
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                channels["bw"](h*width+x,v*height+y) = ((float)in(x,y))/255.0;
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*width,cams_v*height)); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*width,cams_v*height)); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*width,cams_v*height)); 

            for(int v=0; v<cams_v; v++) {
                for(int h=0; h<cams_h; h++) {

                    try {
                        // load image infos from fname_list
                        vigra::ImageImportInfo info_rgb(fname_list[v*cams_h+h].c_str());
            
                        // uint rgb image to import data from file
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(vigra::Shape2(width,height));
                        
                        
                        // import data
                        if(info_rgb.numExtraBands()!=0) {
                            vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(width,height));
                            vigra::importImageAlpha(info_rgb, in, alpha);
                        }
                        else {
                            vigra::importImage(info_rgb, in);
                        }
                        
                        // copy data into lf container
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                channels["r"](h*width+x,v*height+y) = ((float)in(x,y)[0])/255.0f;
                                channels["g"](h*width+x,v*height+y) = ((float)in(x,y)[1])/255.0f;
                                channels["b"](h*width+x,v*height+y) = ((float)in(x,y)[2])/255.0f;
                            }
                        }
                    }
                    catch(int a) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    catch(int a) {
        return false;
        
        warning("Exception in lightfield::io::load_4D_structure...");
    }
}






bool OpenLF::lightfield::io::load_3DH_structure( vector<string> fname_list, 
                                                 map< string, vigra::MultiArray<2,float> > &channels, 
                                                 Properties *properties ) 
/*TEST: via load_from_filesequence in test_lightfield::test_loading_from_imagefiles() */
{
    print(2,"lightfield::io::load_3DH_structure(fname_list,channels,properties) called...");
     
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
        int width = info.width();
        int height = info.height();
        properties->set_field("width",width);
        properties->set_field("height",height);

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_3DH_structure found grayscale image...");
            channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*width,height));

            // loop over images
            for(int h=0; h<cams_h; h++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_bw(fname_list[h].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::UInt8> in(width, height);

                    // import data
                    vigra::importImage(info_bw, vigra::destImage(in));

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            channels["bw"](h*width+x,y) = ((float)in(x,y))/255.0;
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*width,height)); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*width,height)); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*width,height)); 


            for(int h=0; h<cams_h; h++) {

                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[h].c_str());

                    // uint rgb image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info_rgb.shape());

                    
                    // import data
                    if(info_rgb.numExtraBands()!=0) {
                        vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(width,height));
                        vigra::importImageAlpha(info_rgb, in, alpha);
                    }
                    else {
                        vigra::importImage(info_rgb, in);
                    }                 

                    // copy data into lf container
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            channels["r"](h*width+x,y) = ((float)in(x,y)[0])/255.0f;
                            channels["g"](h*width+x,y) = ((float)in(x,y)[1])/255.0f;
                            channels["b"](h*width+x,y) = ((float)in(x,y)[2])/255.0f;
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





bool OpenLF::lightfield::io::load_3DV_structure( vector<string> fname_list, 
                                                 map< string, vigra::MultiArray<2,float> > &channels, 
                                                 Properties *properties )

/*TEST: via load_from_filesequence in test_lightfield::test_loading_from_imagefiles() */
{
    print(2,"lightfield::io::load_3DV_structure(fname_list,channels,properties) called...");
     
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
        int width = info.width();
        int height = info.height();
        properties->set_field("width",width);
        properties->set_field("height",height);

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_3DV_structure found grayscale image...");
            channels["bw"] = vigra::MultiArray<2,float>(cams_v*height,width);
            //vigra::MultiArray<2,float> tmp(vigra::Shape2(cams_v*info.height(),info.width()));

            // loop over images
            for(int v=0; v<cams_v; v++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_bw(fname_list[v].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::UInt8> in(width, height);

                    // import data
                    vigra::importImage(info_bw, vigra::destImage(in));
                    
                    

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            channels["bw"](v*height+y,x) = ((float)in(x,y))/255.0;
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_v*height,width)); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_v*height,width)); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_v*height,width));
            
            for(int v=0; v<cams_v; v++) {

                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[v].c_str());

                    // uint rgb image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info_rgb.shape());

                    // import data
                    if(info_rgb.numExtraBands()!=0) {
                        vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(width,height));
                        vigra::importImageAlpha(info_rgb, in, alpha);
                    }
                    else {
                        vigra::importImage(info_rgb, in);
                    }                   

                    // copy data into lf container
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            channels["r"](v*height+y,x) = ((float)in(x,y)[0])/255.0f;
                            channels["g"](v*height+y,x) = ((float)in(x,y)[1])/255.0f;
                            channels["b"](v*height+y,x) = ((float)in(x,y)[2])/255.0f;
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





bool OpenLF::lightfield::io::load_cross_structure( vector<string> fname_list, 
                                                   map< string, vigra::MultiArray<2,float> > &channels, 
                                                   Properties *properties )

/*TEST: via load_from_filesequence in test_lightfield::test_loading_from_imagefiles() */
{
    print(2,"lightfield::io::load_cross_structure(fname_list,channels,properties) called...");
     
    // camera grid info
    int cams_h;
    properties->get_field("cams_h",cams_h);
    int cams_v;
    properties->get_field("cams_v",cams_v);
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());
      
        // image size
        int width = info.width();
        int height = info.height();
        properties->set_field("width",width);
        properties->set_field("height",height);
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
            channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(lf_width,lf_height));

            // loop over horizontal images
            for(int h=0; h<cams_h; h++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_bw(fname_list[h].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::UInt8> in(width, height);

                    // import data
                    vigra::importImage(info_bw, vigra::destImage(in));

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            channels["bw"](h*width+x,y) = ((float)in(x,y))/255.0;
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
                        vigra::MultiArray<2, vigra::UInt8> in(width, height);

                        // import data
                        vigra::importImage(info_bw, vigra::destImage(in));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                channels["bw"](v*height+y,height+x) = ((float)in(x,y))/255.0;
                            }
                        }
                    }
                    else {
                        vigra::ImageImportInfo info_bw(fname_list[image_index].c_str());
                        image_index++;
                        
                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::UInt8> in(width, height);

                        // import data
                        vigra::importImage(info_bw, vigra::destImage(in));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                channels["bw"](v*height+y,height+x) = ((float)in(x,y))/255.0;
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(lf_width,lf_height)); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(lf_width,lf_height)); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(lf_width,lf_height)); 
            
            // loop over horizontal images
            for(int h=0; h<cams_h; h++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[h].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(width, height);
                    
                    // import data
                    if(info_rgb.numExtraBands()!=0) {
                        vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(width,height));
                        vigra::importImageAlpha(info_rgb, in_rgb, alpha);
                    }
                    else {
                        vigra::importImage(info_rgb, in_rgb);
                    }
                    

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<height; y++) {
                        for(int x=0; x<width; x++) {
                            //channels["bw"](h*width+x,y) = ((float)in(x,y))/255.0;
                            channels["r"](h*width+x,y) = ((float)in_rgb(x,y)[0])/255.0;
                            channels["g"](h*width+x,y) = ((float)in_rgb(x,y)[1])/255.0;
                            channels["b"](h*width+x,y) = ((float)in_rgb(x,y)[2])/255.0;
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
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(width, height);

                        // import data
                        //vigra::importImage(info_rgb, vigra::destImage(in_rgb));
                        
                        // import data
                        if(info_rgb.numExtraBands()!=0) {
                            vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(width,height));
                            vigra::importImageAlpha(info_rgb, in_rgb, alpha);
                        }
                        else {
                            vigra::importImage(info_rgb, in_rgb);
                        }

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                //channels["bw"](v*height+y,height+x) = ((float)in(x,y))/255.0;
                                channels["r"](v*height+y,height+x) = ((float)in_rgb(x,y)[0])/255.0;
                                channels["g"](v*height+y,height+x) = ((float)in_rgb(x,y)[1])/255.0;
                                channels["b"](v*height+y,height+x) = ((float)in_rgb(x,y)[2])/255.0;
                            }
                        }
                    }
                    else {
                        vigra::ImageImportInfo info_rgb(fname_list[image_index].c_str());
                        image_index++;
                        
                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(width, height);

                        // import data
                       // vigra::importImage(info_rgb, vigra::destImage(in_rgb));
                        
                        // import data
                        if(info_rgb.numExtraBands()!=0) {
                            vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(width,height));
                            vigra::importImageAlpha(info_rgb, in_rgb, alpha);
                        }
                        else {
                            vigra::importImage(info_rgb, in_rgb);
                        }

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<height; y++) {
                            for(int x=0; x<width; x++) {
                                //channels["bw"](v*height+y,height+x) = ((float)in(x,y))/255.0;
                                channels["r"](v*height+y,height+x) = ((float)in_rgb(x,y)[0])/255.0;
                                channels["g"](v*height+y,height+x) = ((float)in_rgb(x,y)[1])/255.0;
                                channels["b"](v*height+y,height+x) = ((float)in_rgb(x,y)[2])/255.0;
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






bool OpenLF::lightfield::io::load_from_filesequence(string dir, map< string, 
                                                    vigra::MultiArray<2,float> > &channels, 
                                                    Properties *properties)

/*TEST: test_lightfield::test_loading_from_imagefiles() */
{
    print(1,"lightfield::io::load_from_filesequence(dir,channels,properties) called...");
     
    // get list of filenames
    vector<string> list;
    if(OpenLF::helpers::filenames_from_directory(dir, list)) {
        
        vector<string> fname_list;
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




bool OpenLF::lightfield::io::load_from_hdf5( string filename, 
                     map< string, vigra::MultiArray<2,float> > &channels,
                     Properties *properties ) 
{    
    print(2,"lightfield::io::load_from_hdf5(filename,channels,properties) called...");
    
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
            vector<string> ds_tree;
            ds_tree = file.ls();
            
            int itmp;
            float ftmp;
            
            // read the obligatory attributes
            try {
                // set the LF_TYPE
                int tmp_type;
                file.readAttribute("","LF_TYPE",tmp_type);               
                switch(tmp_type) {
                    case 1:
                        properties->set_lftype(LF_4D);
                        break;
                    case 2:
                        properties->set_lftype(LF_3DH);
                        break;
                    case 3:
                        properties->set_lftype(LF_3DV);
                        break;
                    case 4:
                        properties->set_lftype(LF_CROSS);
                        break;
                    default:
                        throw OpenLF_Exception("Loading light field from HDF5 failed, no LF_TYPE specified!");
                }
                
                file.readAttribute("","width",itmp);
                properties->set_field("width",itmp);
                
                file.readAttribute("","height",itmp);
                properties->set_field("height",itmp);
                
                file.readAttribute("","cams_h",itmp);
                properties->set_field("cams_h",itmp);
                
                file.readAttribute("","cams_v",itmp);
                properties->set_field("cams_v",itmp);
            }
            catch(int a) {
                throw OpenLF_Exception("Loading light field from HDF5 failed, couldn't find all necessary attributes!");
                return false;
            }
                
            try {
                file.readAttribute("","baseline_h",ftmp);
                properties->set_field("baseline_h",ftmp);
            } catch(int a) {
                warning("Found no property baseline!");
            }

            try {
                file.readAttribute("","baseline_v",ftmp);
                properties->set_field("baseline_v",ftmp);
            } catch(int a) {
                warning("Found no property baseline!");
            }

            try {
                file.readAttribute("","focal_length",ftmp);
                properties->set_field("focal_length",ftmp);
            } catch(int a) {
                warning("Found no property baseline!");
            }

            try {
                file.readAttribute("","DH",ftmp);
                properties->set_field("DH",ftmp);
            } catch(int a) {
                warning("Found no property baseline!");
            }

            try {
                file.readAttribute("","pixel_aspect_ratio",ftmp);
                properties->set_field("pixel_aspect_ratio",ftmp);
            } catch(int a) {
                warning("Found no property baseline!");
            }

            try {
                file.readAttribute("","aperture",ftmp);
                properties->set_field("aperture",ftmp);
            } catch(int a) {
                warning("Found no property baseline!");
            }

            try {
                file.readAttribute("","sensor_size_h",ftmp);
                properties->set_field("sensor_size_h",ftmp);
            } catch(int a) {
                warning("Found no property baseline!");
            }

            try {
                file.readAttribute("","sensor_size_v",ftmp);
                properties->set_field("sensor_size_v",ftmp);
            } catch(int a) {
                warning("Found no property baseline!");
            }
                
            
            // read the datasets
            for(unsigned int id=0; id<ds_tree.size(); id++ ) {
                // determine data set shape
                vigra::ArrayVector<int> ds_shape(2);
                ds_shape = file.getDatasetShape(ds_tree[id]);
                
                // allocate memory and read channels
                channels[ds_tree[id]] = vigra::MultiArray<2, float>(vigra::Shape2(ds_shape[0],ds_shape[1]));
                file.read(ds_tree[id], channels[ds_tree[id]]);
            }
            
        } else throw OpenLF_Exception("Loading light field from HDF5 failed, at least rgb or a bw channel is obligatory!");
    }
    catch(exception & e) {
        warning(e.what());
        return false;
    }
    
    return true;
}



bool OpenLF::lightfield::io::save_to_hdf5( string file_name, 
                   map< string, vigra::MultiArray<2,float> > &channels,
                   Properties *properties ) 
{
    print(2,"lightfield::io::save_to_hdf5(filename,channels,properties) called...");
    
    try {
        string dset_name;
        
        // open hdf5 file and define group name
        vigra::HDF5File file(file_name.c_str(),vigra::HDF5File::New);
        file.mkdir("LF");
        
        // loop over channels and save each using its key as dataset names
        for(map<string, vigra::MultiArray<2,float>>::iterator i = channels.begin(); i != channels.end(); ++i)
        {
            string key = i->first;
            dset_name = "/LF/"+key;
            file.write(dset_name.c_str(), channels[key]);
        }        
        
        int itmp;
        float ftmp;
        string stmp;
        vector<string> fields;
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
        for(int n=0; n<fields.size(); n++) {
            if(properties->get_field(fields[n],ftmp))
                file.writeAttribute("/LF/",fields[n],ftmp);
        }
        fields.clear();
        
        
        properties->get_str_field_keys(fields);
        for(int n=0; n<fields.size(); n++) {
            if(properties->get_field(fields[n],stmp))
                file.writeAttribute("/LF/",fields[n],stmp);
        }
        fields.clear();    
    }
    catch(exception & e) {
        warning(e.what());
        return false;
    }
    
    return true;
}