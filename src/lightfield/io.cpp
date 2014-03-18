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



void OpenLF::lightfield::io::save(string filename, map<string,vigra::MultiArray<2,float>> &img)  
{    
    print(2,"lightfield::io::save(string, map) called...");
    
    string ftype = OpenLF::helpers::find_ftype(filename);
   
    if ( img.count("bw") != 0 ) {
        string msg = "save image as grayscale " + ftype +"..."; print(3,msg.c_str());
        
        // allocate memory to store range mapping results
        vigra::MultiArray<2,vigra::UInt8> tmp(vigra::Shape2(img["bw"].width(),img["bw"].height()));
        OpenLF::image::io::linear_range_mapping(img["bw"],tmp);
        
        if(ftype=="jpg")
            vigra::exportImage(tmp, vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
        else
            vigra::exportImage(tmp, filename.c_str());
    }
    if ( img.count("r") != 0 && img.count("g") != 0  && img.count("b") != 0 ) {
        string msg = "save image as color " + ftype +"..."; 
        print(3,msg.c_str());
        
        // allocate output container
        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > rgb(vigra::Shape2(img["r"].width(),img["r"].height()));
        
        // allocate memory to store range mapping results
        vigra::MultiArray<2,vigra::UInt8> tmp(vigra::Shape2(img["r"].width(),img["r"].height()));
        
        // range map data and copy to output image
        vector<string> channel_labels {"r","g","b"};
        for(int c=0; c<3; c++) {
            // map channel to [0,255]
            OpenLF::image::io::linear_range_mapping(img[channel_labels[c]],tmp);

            // copy data into rgb container
            for(int y=0; y<img[channel_labels[c]].height(); y++) {
                for(int x=0; x<img[channel_labels[c]].width(); x++) {
                    rgb(x,y)[c] = tmp(x,y);
                }
            }
        }
        
        if(ftype=="jpg")
            vigra::exportImage(rgb, vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
        else
            vigra::exportImage(rgb, filename.c_str());
    }
}





void OpenLF::lightfield::io::save(string filename, map<string,vigra::MultiArray<2,float>> &img, string key)  
{
    print(3,"lightfield::io::save(string, map, string) called...");
    string ftype = OpenLF::helpers::find_ftype(filename);
    
    string msg = "save channel " + key + " image as " + ftype +"..."; 
    print(3,msg.c_str());

    if ( img.count(key) != 0 ) {
        if(ftype=="jpg")
        vigra::exportImage(img[key], vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
        else
            vigra::exportImage(img[key], filename.c_str());
    }
}




    
bool OpenLF::lightfield::io::load_4D_structure( vector<string> fname_list, 
                                                map< string, 
                                                vigra::MultiArray<2,float> > &channels, 
                                                int cams_h, 
                                                int cams_v ) 
{
    print(2,"lightfield::io::load_4D_structure called...");
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());

        // image size
        int width = info.width();
        int height = info.height();

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_4D_structure found grayscale image...");
            channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),cams_v*info.height()));

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
                        for(int y=0; y<info_bw.height(); y++) {
                            for(int x=0; x<info_bw.width(); x++) {
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),cams_v*info.height())); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),cams_v*info.height())); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),cams_v*info.height())); 

            for(int v=0; v<cams_v; v++) {
                for(int h=0; h<cams_h; h++) {

                    try {
                        // load image infos from fname_list
                        vigra::ImageImportInfo info_rgb(fname_list[v*cams_h+h].c_str());
                        
                        // uint rgb image to import data from file
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info_rgb.shape());
                        
                        // import data
                        vigra::importImage(info_rgb, in);                   
                        
                        // copy data into lf container
                        for(int y=0; y<info_rgb.height(); y++) {
                            for(int x=0; x<info_rgb.width(); x++) {
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
    }
}






bool OpenLF::lightfield::io::load_3DH_structure( vector<string> fname_list, 
                                                 map< string, vigra::MultiArray<2,float> > &channels, 
                                                 int cams_h, 
                                                 int cams_v ) 
{
    print(2,"lightfield::io::load_3DH_structure called...");
     
    if(cams_v!=1) warning("You tried to load a horizontal light field but your parameter cams_v is not 1");
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());

        // image size
        int width = info.width();
        int height = info.height();

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_3DH_structure found grayscale image...");
            channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),info.height()));

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
                    for(int y=0; y<info_bw.height(); y++) {
                        for(int x=0; x<info_bw.width(); x++) {
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),info.height())); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),info.height())); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),info.height())); 


            for(int h=0; h<cams_h; h++) {

                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[h].c_str());

                    // uint rgb image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info_rgb.shape());

                    // import data
                    vigra::importImage(info_rgb, in);                   

                    // copy data into lf container
                    for(int y=0; y<info_rgb.height(); y++) {
                        for(int x=0; x<info_rgb.width(); x++) {
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
                                                 int cams_h, 
                                                 int cams_v ) 
{
    print(2,"lightfield::io::load_3DV_structure called...");
     
    if(cams_h!=1) warning("You tried to load a vertical light field but your parameter cams_h is not 1");
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());

        // image size
        int width = info.width();
        int height = info.height();

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_3DV_structure found grayscale image...");
            channels["bw"] = vigra::MultiArray<2,float>(cams_v*info.height(),info.width());
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
                    for(int y=0; y<info_bw.height(); y++) {
                        for(int x=0; x<info_bw.width(); x++) {
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_v*info.height(),info.width())); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_v*info.height(),info.width())); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_v*info.height(),info.width()));
            
            for(int v=0; v<cams_v; v++) {

                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[v].c_str());

                    // uint rgb image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info_rgb.shape());

                    // import data
                    vigra::importImage(info_rgb, in);                   

                    // copy data into lf container
                    for(int y=0; y<info_rgb.height(); y++) {
                        for(int x=0; x<info_rgb.width(); x++) {
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
                                                   int cams_h, 
                                                   int cams_v )  
{
    print(3,"lightfield::io::load_CROSSS_structure called...");
     
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());
      
        // image size
        int width = info.width();
        int height = info.height();
        int cv_index = cams_h/2;

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_CROSS_structure found grayscale image...");
            channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),info.height()+info.width()));

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
                    for(int y=0; y<info_bw.height(); y++) {
                        for(int x=0; x<info_bw.width(); x++) {
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
                        vigra::MultiArray<2, vigra::UInt8> in(info_bw.width(), info_bw.height());

                        // import data
                        vigra::importImage(info_bw, vigra::destImage(in));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<info_bw.height(); y++) {
                            for(int x=0; x<info_bw.width(); x++) {
                                channels["bw"](v*height+y,height+x) = ((float)in(x,y))/255.0;
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
                        for(int y=0; y<info_bw.height(); y++) {
                            for(int x=0; x<info_bw.width(); x++) {
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),info.height()+info.width())); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),info.height()+info.width())); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(cams_h*info.width(),info.height()+info.width())); 
            
            // loop over horizontal images
            for(int h=0; h<cams_h; h++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[h].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(info_rgb.width(), info_rgb.height());

                    // import data
                    vigra::importImage(info_rgb, vigra::destImage(in_rgb));
                    

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<info_rgb.height(); y++) {
                        for(int x=0; x<info_rgb.width(); x++) {
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
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(info_rgb.width(), info_rgb.height());

                        // import data
                        vigra::importImage(info_rgb, vigra::destImage(in_rgb));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<info_rgb.height(); y++) {
                            for(int x=0; x<info_rgb.width(); x++) {
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
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(info_rgb.width(), info_rgb.height());

                        // import data
                        vigra::importImage(info_rgb, vigra::destImage(in_rgb));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<info_rgb.height(); y++) {
                            for(int x=0; x<info_rgb.width(); x++) {
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






bool OpenLF::lightfield::io::load_from_filesequence(string dir, map< string, vigra::MultiArray<2,float> > &channels, LF_TYPE type, int cams_h, int cams_v) 
{
    print(2,"lightfield::io::load_from_filesequence called...");
     
    // get list of filenames
    vector<string> list;
    if(OpenLF::helpers::filenames_from_directory(dir, list)) {
        
        vector<string> fname_list;
        for(int i=0; i<list.size(); i++) {
            fname_list.push_back(dir+list[i]);
            print(3,fname_list[i].c_str());
        }
         
        // decide data structure depending on lf type
        switch(type) {
            case LF_4D:
                return load_4D_structure(fname_list,channels,cams_h,cams_v);
            case LF_3DH:
                return load_3DH_structure(fname_list,channels,cams_h,cams_v);
            case LF_3DV:
                return load_3DV_structure(fname_list,channels,cams_h,cams_v);
            case LF_CROSS:
                return load_cross_structure(fname_list,channels,cams_h,cams_v);
            default:
                warning("Load_from_filesequence failed due to unknown LF_TYPE");
                return false;
        }
    }
    warning("Load_from_filesequence failed when reading files from directory");
    return false;
}




bool OpenLF::lightfield::io::load_from_hdf5( string file_name, 
                     map< string, vigra::MultiArray<2,float> > &channels,
                     LF_TYPE &type,
                     int &width,
                     int &height,
                     int &cams_h,
                     int &cams_v,
                     float &baseline_h,
                     float &baseline_v,
                     float &focal_length ) 
/* TEST in lightfield_test::test_hdf5_io() */
{    
    print(2,"lightfield::io::load_from_hdf5 called...");
    
    // open hdf5 file
    vigra::HDF5File file(file_name.c_str(),vigra::HDF5File::OpenReadOnly);
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
            
            // read the obligatory attributes
            try {
                // set the LF_TYPE
                int tmp_type;
                file.readAttribute("","LF_TYPE",tmp_type);               
                switch(tmp_type) {
                    case 1:
                        type = LF_4D;
                        break;
                    case 2:
                        type = LF_3DH;
                        break;
                    case 3:
                        type = LF_3DV;
                        break;
                    case 4:
                        type = LF_CROSS;
                        break;
                    default:
                        throw OpenLF_Exception("Loading light field from HDF5 failed, no LF_TYPE specified!");
                }
                
                file.readAttribute("","width",width);
                file.readAttribute("","height",height);
                file.readAttribute("","cams_h",cams_h);
                file.readAttribute("","cams_v",cams_v);
                file.readAttribute("","baseline_h",baseline_h);
                file.readAttribute("","baseline_v",baseline_v);
                file.readAttribute("","focal_length",focal_length);
            }
            catch(int a) {
                throw OpenLF_Exception("Loading light field from HDF5 failed, didn't find all attributes!");
            }
            
            // read the datasets
            for(int id=0; id<ds_tree.size(); id++ ) {
                channels[ds_tree[id]] = vigra::MultiArray<2, float>(vigra::Shape2(480,400));
                file.read(ds_tree[id], channels[ds_tree[id]]);
            }
            
        } else throw OpenLF_Exception("Loading light field from HDF5 failed, at least rgb or a bw channel is obligatory!");
    }
    catch(exception & e) {
        cout << e.what() << endl;
        return false;
    }
    
    return true;
}



bool OpenLF::lightfield::io::save_to_hdf5( string file_name, 
                   map< string, vigra::MultiArray<2,float> > &channels,
                   LF_TYPE type,
                   int width,
                   int height,
                   int cams_h,
                   int cams_v,
                   float baseline_h,
                   float baseline_v,
                   float focal_length ) 

/* TEST in lightfield_test::test_hdf5_io() */
{
    print(2,"lightfield::io::save_to_hdf5 called...");
    
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
        
        // write attributes
        file.writeAttribute("/LF/","LF_TYPE",(int)type);
        file.writeAttribute("/LF/","width",width);
        file.writeAttribute("/LF/","height",height);
        file.writeAttribute("/LF/","cams_h",cams_h);
        file.writeAttribute("/LF/","cams_v",cams_v);
        file.writeAttribute("/LF/","baseline_h",baseline_h);
        file.writeAttribute("/LF/","baseline_v",baseline_v);
        file.writeAttribute("/LF/","focal_length",focal_length);
    }
    catch(exception & e) {
        cout << e.what() << endl;
        return false;
    }
    
    return true;
}