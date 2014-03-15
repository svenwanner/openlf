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

void OpenLF::lightfield::io::linearRangeMapping(vigra::MultiArray<2,float>& fimg, vigra::MultiArray<2, vigra::UInt8>& img) {
    print(3,"linearRangeMapping(MultiArray<2,float>&,MultiArray<2,UInt8>&) called...");
    //functor to find range
    try {
        vigra::FindMinMax<vigra::FImage::PixelType> minmax; 
        //find original range
        vigra::inspectImage(vigra::srcImageRange(fimg), minmax);
        if(minmax.max<=minmax.min) throw OpenLF_Exception("linearRangeMapping failed, no distance to map!");
        
        //transform to range 0...255
        int nmin, nmax;
        if(minmax.min>=0 && minmax.min<1 && minmax.max>0 && minmax.max<=1) {
            nmin = int(ceil(minmax.min*255));
            nmax = int(floor(minmax.max*255));
        }
        else {
            nmin = 0;
            nmax = 255;
        }
            
        vigra::transformImage(vigra::srcImageRange(fimg), vigra::destImage(img),
                              vigra::linearRangeMapping( minmax.min, minmax.max, nmin, nmax) );
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

void OpenLF::lightfield::io::save(string filename, map<string,vigra::MultiArray<2,float>> &img)  
{
    print(2,"lightfield::io::save(string, map) called...");
    
    string ftype = OpenLF::helpers::find_ftype(filename);
   
    if ( img.count("bw") != 0 ) {
        string msg = "save image as grayscale " + ftype +"..."; print(3,msg.c_str());
        
        // allocate memory to store range mapping results
        vigra::MultiArray<2,vigra::UInt8> tmp(vigra::Shape2(img["bw"].width(),img["bw"].height()));
        linearRangeMapping(img["bw"],tmp);
        
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
            linearRangeMapping(img[channel_labels[c]],tmp);

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


//bool OpenLF::lightfield::io::load_imagefile( string filename, 
//                                             map< string,vigra::MultiArray<2,float> > &channels) 
//{
//    map.clear();
//    
//    // load image infos
//    vigra::ImageImportInfo info(filename.c_str());
//    
//    if(info.isGrayscale()) {
//        try {
//            // uint image to import data from file
//            vigra::MultiArray<2, vigra::UInt8> in(info.width(), info.height());
//
//            // allocate memory
//            channels["bw"] = vigra::MultiArray<2,float>(info.width(), info.height());
//
//            // import data
//            vigra::importImage(info, vigra::destImage(in));
//
//            // copy data into object and map to range [1,0]
//            vigra::UInt8* data_ptr = in.data();
//            for(int n=0; n<info.width()*info.height(); n++) {
//                channels[0].data()[n] = ((float)data_ptr[n])/255.0;
//            }
//        }
//        catch(int a) {
//            return false;
//        }
//    }
//    else if(info.isColor()) {
//        try {
//            // uint rgb image to import data from file
//            vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info.shape());
//
//            // allocate memory
//            channels["r"] = vigra::MultiArray<2,float>(info.width(), info.height());
//            channels["g"] = vigra::MultiArray<2,float>(info.width(), info.height());
//            channels["b"] = vigra::MultiArray<2,float>(info.width(), info.height());
//
//            // import data
//            vigra::importImage(info, in);
//
//            // copy data into object and map to range [1,0]
//            int index;
//            for(int x=0; x<info.width(); x++) {
//                for(int y=0; y<info.height(); y++) {
//                    index = y*info.width()+x;
//                    channels["r"].data()[index] = in(x,y)[0]/255.0f;
//                    channels["g"].data()[index] = in(x,y)[1]/255.0f;
//                    channels["b"].data()[index] = in(x,y)[2]/255.0f;
//                }
//            }
//        }
//        catch(int a) {
//            return false;
//        }
//    }
//    return true;
//}


//bool OpenLF::lightfield::io::load_roi_from_imagefile( string filename, 
//                                                     map< string,vigra::MultiArray<2,float> > &channels, 
//                                                     int roi_start[2],
//                                                     int roi_end[2]) 
//{
//    // import image info from file
//    vigra::ImageImportInfo info(filename.c_str());
//
//    if(info.isGrayscale()) {
//
//        // uint image to import data from file
//        vigra::MultiArray<2, vigra::UInt8> in(info.width(), info.height());
//
//        // allocate memory
//        _data.push_back(new vigra::MultiArray<2,float>(info.width(), info.height()));
//
//        // import data
//        vigra::importImage(info, vigra::destImage(in));
//
//        // copy data into object and map to range [1,0]
//        vigra::UInt8* data_ptr = in.data();
//        for(int n=0; n<info.width()*info.height(); n++) {
//            _data[0]->data()[n] = ((float)data_ptr[n])/255.0;
//        }
//
//        // set properties
//        _width = info.width();
//        _height = info.height();
//        _label = "bw";
//        _num_of_channels = 1;
//
//    } else if(info.isColor()) {
//        print(2,"Image -> load rgb image...");
//
//        // uint rgb image to import data from file
//        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info.shape());
//
//        // allocate memory
//        for(int c=0; c<3; c++)
//            _data.push_back(new vigra::MultiArray<2,float>(info.width(), info.height()));
//
//        // import data
//        vigra::importImage(info, in);
//
//        // copy data into object and map to range [1,0]
//        int index;
//        for(int x=0; x<info.width(); x++) {
//            for(int y=0; y<info.height(); y++) {
//                index = y*info.width()+x;
//                _data[0]->data()[index] = in(x,y)[0]/255.0f;
//                _data[1]->data()[index] = in(x,y)[1]/255.0f;
//                _data[2]->data()[index] = in(x,y)[2]/255.0f;
//            }
//        }
//}
    
bool OpenLF::lightfield::io::load_4D_structure( vector<string> fname_list, 
                                                map< string, 
                                                vigra::MultiArray<2,float> > &channels, 
                                                int cams_h, 
                                                int cams_v ) 
{
    print(3,"lightfield::io::load_4D_structure called...");
    
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
    print(3,"lightfield::io::load_3DH_structure called...");
     
    if(cams_v!=1) {cout << "WARNING, You tried to load a horizontal light field but your parameter cams_v is not 1! This could be an error!?" << endl;}
    
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
                    cout << "WARNING: Loading bw image data failed while copying data into lf container!" << endl;
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
                    cout << "WARNING: Loading rgb image data failed while copying data into lf container!" << endl;
                    return false;
                }
            }
        }
        return true;
    }
    catch(int a) {
        cout << "WARNING: Loading image data failed while copying data into lf container!" << endl;
        return false;
    }
}

bool OpenLF::lightfield::io::load_3DV_structure( vector<string> fname_list, 
                                                 map< string, vigra::MultiArray<2,float> > &channels, 
                                                 int cams_h, 
                                                 int cams_v ) 
{
    print(3,"lightfield::io::load_3DV_structure called...");
     
    if(cams_h!=1) {cout << "WARNING, You tried to load a vertical light field but your parameter cams_h is not 1! This could be an error!?" << endl;}
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(fname_list[0].c_str());

        // image size
        int width = info.width();
        int height = info.height();

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"lightfield::io::load_3DV_structure found grayscale image...");
            //channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(info.width(),cams_h*info.height()));
            vigra::MultiArray<2,float> tmp(vigra::Shape2(cams_v*info.height(),info.width()));

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
                            tmp(v*height+y,x) = ((float)in(x,y))/255.0;
                        }
                    }
                }
                catch(int a) {
                    cout << "WARNING: Loading bw image data failed while copying data into lf container!" << endl;
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
                    cout << "WARNING: Loading rgb image data failed while copying data into lf container!" << endl;
                    return false;
                }
            }
        }
        
        
        return true;
    }
    catch(int a) {
        cout << "WARNING: Loading image data failed while copying data into lf container!" << endl;
        return false;
    }
}

bool OpenLF::lightfield::io::load_cross_structure( vector<string> fname_list, 
                                                   map< string, vigra::MultiArray<2,float> > &channels, 
                                                   int cams_h, 
                                                   int cams_v )  
{
    
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
                print(2,"lightfield::io load 4D structure...");
                return load_4D_structure(fname_list,channels,cams_h,cams_v);
            case LF_3DH:
                print(2,"lightfield::io load 3DH structure...");
                return load_3DH_structure(fname_list,channels,cams_h,cams_v);
            case LF_3DV:
                print(2,"lightfield::io load 3DV structure...");
                return load_3DV_structure(fname_list,channels,cams_h,cams_v);
            case LF_CROSS:
                print(2,"lightfield::io load CROSS structure...");
                return load_cross_structure(fname_list,channels,cams_h,cams_v);
            default:
                cout << "WARNING: Load_from_filesequence failed due to unknown LF_TYPE!" << endl;
                return false;
        }
    }
    cout << "WARNING: Load_from_filesequence failed when reading files from directory!" << endl;
    return false;
}