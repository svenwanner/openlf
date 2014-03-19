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
                                                Properties &properties )

/*TEST: via load_from_filesequence in test_lightfield::test_loading_from_imagefiles() */
{
    print(2,"lightfield::io::load_4D_structure(fname_list,channels,properties) called...");
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());

        // image size
        properties.width = info.width();
        properties.height = info.height();

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_4D_structure found grayscale image...");
            channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*info.width(),properties.cams_v*info.height()));

            // loop over images
            for(int v=0; v<properties.cams_v; v++) {
                for(int h=0; h<properties.cams_h; h++) {
                    
                    try {
                        // load image infos from fname_list
                        vigra::ImageImportInfo info_bw(fname_list[v*properties.cams_h+h].c_str());

                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::UInt8> in(properties.width, properties.height);

                        // import data
                        vigra::importImage(info_bw, vigra::destImage(in));
                      
                        // copy data into object and map to range [1,0]
                        for(int y=0; y<properties.height; y++) {
                            for(int x=0; x<properties.width; x++) {
                                channels["bw"](h*properties.width+x,v*properties.height+y) = ((float)in(x,y))/255.0;
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*info.width(),properties.cams_v*info.height())); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*info.width(),properties.cams_v*info.height())); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*info.width(),properties.cams_v*info.height())); 

            for(int v=0; v<properties.cams_v; v++) {
                for(int h=0; h<properties.cams_h; h++) {

                    try {
                        // load image infos from fname_list
                        vigra::ImageImportInfo info_rgb(fname_list[v*properties.cams_h+h].c_str());
                        
                        // uint rgb image to import data from file
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info_rgb.shape());
                        
                        // import data
                        vigra::importImage(info_rgb, in);                   
                        
                        // copy data into lf container
                        for(int y=0; y<info_rgb.height(); y++) {
                            for(int x=0; x<info_rgb.width(); x++) {
                                channels["r"](h*properties.width+x,v*properties.height+y) = ((float)in(x,y)[0])/255.0f;
                                channels["g"](h*properties.width+x,v*properties.height+y) = ((float)in(x,y)[1])/255.0f;
                                channels["b"](h*properties.width+x,v*properties.height+y) = ((float)in(x,y)[2])/255.0f;
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
                                                 Properties &properties ) 
/*TEST: via load_from_filesequence in test_lightfield::test_loading_from_imagefiles() */
{
    print(2,"lightfield::io::load_3DH_structure(fname_list,channels,properties) called...");
     
    if(properties.cams_v!=1) warning("You tried to load a horizontal light field but your parameter cams_v is not 1");
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());

        // image size
        properties.width = info.width();
        properties.height = info.height();

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_3DH_structure found grayscale image...");
            channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*properties.width,properties.height));

            // loop over images
            for(int h=0; h<properties.cams_h; h++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_bw(fname_list[h].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::UInt8> in(properties.width, properties.height);

                    // import data
                    vigra::importImage(info_bw, vigra::destImage(in));

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<properties.height; y++) {
                        for(int x=0; x<properties.width; x++) {
                            channels["bw"](h*properties.width+x,y) = ((float)in(x,y))/255.0;
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*properties.width,properties.height)); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*properties.width,properties.height)); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*properties.width,properties.height)); 


            for(int h=0; h<properties.cams_h; h++) {

                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[h].c_str());

                    // uint rgb image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info_rgb.shape());

                    // import data
                    vigra::importImage(info_rgb, in);                   

                    // copy data into lf container
                    for(int y=0; y<properties.height; y++) {
                        for(int x=0; x<properties.width; x++) {
                            channels["r"](h*properties.width+x,y) = ((float)in(x,y)[0])/255.0f;
                            channels["g"](h*properties.width+x,y) = ((float)in(x,y)[1])/255.0f;
                            channels["b"](h*properties.width+x,y) = ((float)in(x,y)[2])/255.0f;
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
                                                 Properties &properties )
/*TEST: via load_from_filesequence in test_lightfield::test_loading_from_imagefiles() */
{
    print(2,"lightfield::io::load_3DV_structure(fname_list,channels,properties) called...");
     
    if(properties.cams_h!=1) warning("You tried to load a vertical light field but your parameter cams_h is not 1");
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());

        // image size
        properties.width = info.width();
        properties.height = info.height();

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_3DV_structure found grayscale image...");
            channels["bw"] = vigra::MultiArray<2,float>(properties.cams_v*properties.height,properties.width);
            //vigra::MultiArray<2,float> tmp(vigra::Shape2(cams_v*info.height(),info.width()));

            // loop over images
            for(int v=0; v<properties.cams_v; v++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_bw(fname_list[v].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::UInt8> in(properties.width, properties.height);

                    // import data
                    vigra::importImage(info_bw, vigra::destImage(in));
                    
                    

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<properties.height; y++) {
                        for(int x=0; x<properties.width; x++) {
                            channels["bw"](v*properties.height+y,x) = ((float)in(x,y))/255.0;
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_v*properties.height,properties.width)); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_v*properties.height,properties.width)); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_v*properties.height,properties.width));
            
            for(int v=0; v<properties.cams_v; v++) {

                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[v].c_str());

                    // uint rgb image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info_rgb.shape());

                    // import data
                    vigra::importImage(info_rgb, in);                   

                    // copy data into lf container
                    for(int y=0; y<properties.height; y++) {
                        for(int x=0; x<properties.width; x++) {
                            channels["r"](v*properties.height+y,x) = ((float)in(x,y)[0])/255.0f;
                            channels["g"](v*properties.height+y,x) = ((float)in(x,y)[1])/255.0f;
                            channels["b"](v*properties.height+y,x) = ((float)in(x,y)[2])/255.0f;
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
                                                   Properties &properties )

/*TEST: via load_from_filesequence in test_lightfield::test_loading_from_imagefiles() */
{
    print(2,"lightfield::io::load_cross_structure(fname_list,channels,properties) called...");
     
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());
      
        // image size
        properties.width = info.width();
        properties.height = info.height();
        int cv_index = properties.cams_h/2;

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_CROSS_structure found grayscale image...");
            channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*properties.width,properties.height+properties.width));

            // loop over horizontal images
            for(int h=0; h<properties.cams_h; h++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_bw(fname_list[h].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::UInt8> in(properties.width, properties.height);

                    // import data
                    vigra::importImage(info_bw, vigra::destImage(in));

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<properties.height; y++) {
                        for(int x=0; x<properties.width; x++) {
                            channels["bw"](h*properties.width+x,y) = ((float)in(x,y))/255.0;
                        }
                    }
                }
                catch(int a) {
                    warning("Loading bw image data failed while copying data into lf container");
                    return false;
                }
            }
            
            // loop vertical over images
            int image_index=properties.cams_h;
            for(int v=0; v<properties.cams_v; v++) {
                
                try {
                            
                    // load image infos from fname_list
                    if(v==cv_index) {
                        vigra::ImageImportInfo info_bw(fname_list[cv_index].c_str());
                        
                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::UInt8> in(properties.width, properties.height);

                        // import data
                        vigra::importImage(info_bw, vigra::destImage(in));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<properties.height; y++) {
                            for(int x=0; x<properties.width; x++) {
                                channels["bw"](v*properties.height+y,properties.height+x) = ((float)in(x,y))/255.0;
                            }
                        }
                    }
                    else {
                        vigra::ImageImportInfo info_bw(fname_list[image_index].c_str());
                        image_index++;
                        
                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::UInt8> in(properties.width, properties.height);

                        // import data
                        vigra::importImage(info_bw, vigra::destImage(in));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<properties.height; y++) {
                            for(int x=0; x<properties.width; x++) {
                                channels["bw"](v*properties.height+y,properties.height+x) = ((float)in(x,y))/255.0;
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
            
            channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*properties.width,properties.height+properties.width)); 
            channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*properties.width,info.height()+properties.width)); 
            channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(properties.cams_h*properties.width,info.height()+properties.width)); 
            
            // loop over horizontal images
            for(int h=0; h<properties.cams_h; h++) {
                
                try {
                    // load image infos from fname_list
                    vigra::ImageImportInfo info_rgb(fname_list[h].c_str());

                    // uint image to import data from file
                    vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(properties.width, properties.height);

                    // import data
                    vigra::importImage(info_rgb, vigra::destImage(in_rgb));
                    

                    // copy data into object and map to range [1,0]
                    for(int y=0; y<properties.height; y++) {
                        for(int x=0; x<properties.width; x++) {
                            //channels["bw"](h*width+x,y) = ((float)in(x,y))/255.0;
                            channels["r"](h*properties.width+x,y) = ((float)in_rgb(x,y)[0])/255.0;
                            channels["g"](h*properties.width+x,y) = ((float)in_rgb(x,y)[1])/255.0;
                            channels["b"](h*properties.width+x,y) = ((float)in_rgb(x,y)[2])/255.0;
                        }
                    }
                }
                catch(int a) {
                    warning("Loading bw image data failed while copying data into lf container");
                    return false;
                }
            }
            
            // loop vertical over images
            int image_index=properties.cams_h;
            for(int v=0; v<properties.cams_v; v++) {
                
                try {
                            
                    // load image infos from fname_list
                    if(v==cv_index) {
                        vigra::ImageImportInfo info_rgb(fname_list[cv_index].c_str());
                        
                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(properties.width, properties.height);

                        // import data
                        vigra::importImage(info_rgb, vigra::destImage(in_rgb));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<properties.height; y++) {
                            for(int x=0; x<properties.width; x++) {
                                //channels["bw"](v*height+y,height+x) = ((float)in(x,y))/255.0;
                                channels["r"](v*properties.height+y,properties.height+x) = ((float)in_rgb(x,y)[0])/255.0;
                                channels["g"](v*properties.height+y,properties.height+x) = ((float)in_rgb(x,y)[1])/255.0;
                                channels["b"](v*properties.height+y,properties.height+x) = ((float)in_rgb(x,y)[2])/255.0;
                            }
                        }
                    }
                    else {
                        vigra::ImageImportInfo info_rgb(fname_list[image_index].c_str());
                        image_index++;
                        
                        // uint image to import data from file
                        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in_rgb(properties.width, properties.height);

                        // import data
                        vigra::importImage(info_rgb, vigra::destImage(in_rgb));

                        // copy data into object and map to range [1,0]
                        for(int y=0; y<properties.height; y++) {
                            for(int x=0; x<properties.width; x++) {
                                //channels["bw"](v*height+y,height+x) = ((float)in(x,y))/255.0;
                                channels["r"](v*properties.height+y,properties.height+x) = ((float)in_rgb(x,y)[0])/255.0;
                                channels["g"](v*properties.height+y,properties.height+x) = ((float)in_rgb(x,y)[1])/255.0;
                                channels["b"](v*properties.height+y,properties.height+x) = ((float)in_rgb(x,y)[2])/255.0;
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






bool OpenLF::lightfield::io::load_from_filesequence(string dir, map< string, vigra::MultiArray<2,float> > &channels, Properties &properties)
/*TEST: test_lightfield::test_loading_from_imagefiles() */
{
    print(1,"lightfield::io::load_from_filesequence(dir,channels,properties) called...");
     
    // get list of filenames
    vector<string> list;
    if(OpenLF::helpers::filenames_from_directory(dir, list)) {
        
        vector<string> fname_list;
        for(int i=0; i<list.size(); i++) {
            fname_list.push_back(dir+list[i]);
            print(3,fname_list[i].c_str());
        }
         
        // decide data structure depending on lf type
        switch(properties.type) {
            case LF_4D:
                return load_4D_structure(fname_list,channels,properties);
            case LF_3DH:
                return load_3DH_structure(fname_list,channels,properties);
            case LF_3DV:
                return load_3DV_structure(fname_list,channels,properties);
            case LF_CROSS:
                return load_cross_structure(fname_list,channels,properties);
            default:
                warning("Load_from_filesequence failed due to unknown LF_TYPE");
                return false;
        }
    }
    warning("Load_from_filesequence failed when reading files from directory");
    return false;
}




bool OpenLF::lightfield::io::load_from_hdf5( string filename, 
                     map< string, vigra::MultiArray<2,float> > &channels,
                     Properties &properties ) 

/* TEST: lightfield_test::test_hdf5_io() */
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
            
            // read the obligatory attributes
            try {
                // set the LF_TYPE
                int tmp_type;
                file.readAttribute("","LF_TYPE",tmp_type);               
                switch(tmp_type) {
                    case 1:
                        properties.type = LF_4D;
                        break;
                    case 2:
                        properties.type = LF_3DH;
                        break;
                    case 3:
                        properties.type = LF_3DV;
                        break;
                    case 4:
                        properties.type = LF_CROSS;
                        break;
                    default:
                        throw OpenLF_Exception("Loading light field from HDF5 failed, no LF_TYPE specified!");
                }
                
                file.readAttribute("","width",properties.width);
                file.readAttribute("","height",properties.height);
                file.readAttribute("","cams_h",properties.cams_h);
                file.readAttribute("","cams_v",properties.cams_v);
                file.readAttribute("","baseline_h",properties.baseline_h);
                file.readAttribute("","baseline_v",properties.baseline_v);
                file.readAttribute("","focal_length",properties.focal_length);
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
                   Properties &properties ) 

/* TEST: lightfield_test::test_hdf5_io() */
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
        
        // write attributes
        file.writeAttribute("/LF/","LF_TYPE",(int)properties.type);
        file.writeAttribute("/LF/","width",properties.width);
        file.writeAttribute("/LF/","height",properties.height);
        file.writeAttribute("/LF/","cams_h",properties.cams_h);
        file.writeAttribute("/LF/","cams_v",properties.cams_v);
        file.writeAttribute("/LF/","baseline_h",properties.baseline_h);
        file.writeAttribute("/LF/","baseline_v",properties.baseline_v);
        file.writeAttribute("/LF/","focal_length",properties.focal_length);
    }
    catch(exception & e) {
        cout << e.what() << endl;
        return false;
    }
    
    return true;
}