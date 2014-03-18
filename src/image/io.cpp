#include "image/io.hpp"



void OpenLF::image::io::reduce_channels(map<string,vigra::MultiArray<2,float>> &channels,vector<string> keys_to_keep) 
{
    if(keys_to_keep.size() == 0) return;
    
    int n=0;
    for(map<string, vigra::MultiArray<2,float>>::iterator i = channels.begin(); i != channels.end(); ++i)
    {
        string key = i->first;
        int key_found = 0;
        for(int c=0; c<keys_to_keep.size(); c++) {
            if(key==keys_to_keep[c]) {
                key_found++;
            }
        }

        if(key_found==0) {
            cout << "erase " << key << endl;
            channels.erase(key);
        }
        n++;
    }
}



void OpenLF::image::io::linear_range_mapping(vigra::MultiArray<2,float>& fimg, vigra::MultiArray<2, vigra::UInt8>& img) {
    print(1,"image::io::linear_range_mapping(fimg,img) called...");
    //functor to find range
    try {
        vigra::FindMinMax<vigra::FImage::PixelType> minmax; 
        //find original range
        vigra::inspectImage(vigra::srcImageRange(fimg), minmax);
        if(minmax.max<=minmax.min) throw OpenLF_Exception("image::io::linear_range_mapping failed, no distance in image to map!");
        
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


bool OpenLF::image::io::imread(string filename, map<string,vigra::MultiArray<2,float>> &channels) 
{
    print(1,"image::io::imread(string,map) called...");
    // import image info to get the image shape
    vigra::ImageImportInfo info(filename.c_str());

    // image size
    int width = info.width();
    int height = info.height();

    // load grayscale images
    if(info.isGrayscale()) {
        print(3,"image::io::imread(string,map) found grayscale image...");
        channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(info.width(),info.height()));

        try {

            // uint image to import data from file
            vigra::MultiArray<2, vigra::UInt8> in(width,height);

            // import data
            vigra::importImage(info, vigra::destImage(in));

            // copy data into object and map to range [1,0]
            for(int y=0; y<height; y++) {
                for(int x=0; x<width; x++) {
                    channels["bw"](x,y) = ((float)in(x,y))/255.0;
                }
            }
        } catch(exception & e) {
            cout << e.what() << endl;
        }
 
    }
    // load color images
    else if(info.isColor()) {
        print(3,"image::io::imread(string,map) found color image...");

        channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(width,height)); 
        channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(width,height)); 
        channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(width,height)); 

        try {
            // uint rgb image to import data from file
            vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info.shape());

            // import data
            vigra::importImage(info, in);                   

            // copy data into lf container
            for(int y=0; y<height; y++) {
                for(int x=0; x<width; x++) {
                    channels["r"](x,y) = ((float)in(x,y)[0])/255.0f;
                    channels["g"](x,y) = ((float)in(x,y)[1])/255.0f;
                    channels["b"](x,y) = ((float)in(x,y)[2])/255.0f;
                }
            }
        } catch(exception & e) {
            cout << e.what() << endl;
        }
    }
}


bool OpenLF::image::io::imsave(string filename, vigra::MultiArray<2,float> img) 
{
    string ftype = OpenLF::helpers::find_ftype(filename);
    
    // allocate memory to store range mapping results
    vigra::MultiArray<2,vigra::UInt8> tmp(vigra::Shape2(img.width(),img.height()));
    linear_range_mapping(img,tmp);

    if(ftype=="jpg")
        vigra::exportImage(tmp, vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
    else
        vigra::exportImage(tmp, filename.c_str());
}



bool OpenLF::image::io::imsave(string filename, map<string,vigra::MultiArray<2,float>> channels) 
{
    string ftype = OpenLF::helpers::find_ftype(filename);
    
    if ( channels.count("bw") != 0 ) {
        
        try {
            string msg = "save image as grayscale " + ftype +"..."; print(3,msg.c_str());

            // adapt filename to set the appendix
            string bw_filename = string(filename);
            int insert_pos = filename.length()-(ftype.length()+1);
            bw_filename.insert(insert_pos,"_bw");

            imsave(bw_filename,channels["bw"]);

            // delete bw channel
            channels.erase("bw");
            
        } catch(exception & e) {
            cout << e.what() << endl;
            return false;
        }
    }
    if ( channels.count("r") != 0 && channels.count("g") != 0  && channels.count("b") != 0 ) {
        
        try {
            string msg = "save image as color " + ftype +"...";  print(3,msg.c_str());

            // adapt filename to set the appendix
            string rgb_filename = string(filename);
            int insert_pos = filename.length()-(ftype.length()+1);
            rgb_filename.insert(insert_pos,"_rgb");

            // allocate output container
            vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > rgb(vigra::Shape2(channels["r"].width(),channels["r"].height()));

            // allocate memory to store range mapping results
            vigra::MultiArray<2,vigra::UInt8> tmp(vigra::Shape2(channels["r"].width(),channels["r"].height()));

            // range map data and copy to output image
            vector<string> channel_labels {"r","g","b"};
            for(int c=0; c<3; c++) {
                // map channel to [0,255]
                linear_range_mapping(channels[channel_labels[c]],tmp);

                // copy data into rgb container
                for(int y=0; y<channels[channel_labels[c]].height(); y++) {
                    for(int x=0; x<channels[channel_labels[c]].width(); x++) {
                        rgb(x,y)[c] = tmp(x,y);
                    }
                }

                // delete r,g and b channel
                channels.erase(channel_labels[c]);
            }

            if(ftype=="jpg")
                vigra::exportImage(rgb, vigra::ImageExportInfo(rgb_filename.c_str()).setCompression("JPEG QUALITY=75"));
            else
                vigra::exportImage(rgb, rgb_filename.c_str());
            
        } catch(exception & e) {
            cout << e.what() << endl;
        }
        
    }
    
    try {
        for(map<string, vigra::MultiArray<2,float>>::iterator i = channels.begin(); i != channels.end(); ++i)
        {
            string key = i->first;

            // adapt filename to set the appendix
            string tmp_filename = string(filename);
            int insert_pos = filename.length()-(ftype.length()+1);

            string appendix = "_"+key;
            tmp_filename.insert(insert_pos,appendix);

            imsave(tmp_filename,channels[key]);
            channels.erase(key);
        }
    } catch(exception & e) {
        cout << e.what() << endl;
    }
    
    
    return true;
}



bool OpenLF::image::io::imsave(string filename, map<string,vigra::MultiArray<2,float>> channels, vector<string> keys_to_save) 
{
    print(1,"image::io::imsave(filename, channels, keys_to_save) called...");
    
    try {
        reduce_channels(channels,keys_to_save);
    }
    catch(exception & e) {
        cout << e.what() << endl;
        return false;
    }
        
    return imsave(filename,channels);
}