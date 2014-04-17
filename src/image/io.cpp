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

#include "image/io.hpp"




void OpenLF::image::io::reduce_channels(map<string,OpenLF::image::ImageChannel> &channels,vector<string> keys_to_keep)
{
    print(1,"image::io::reduce_channels(channels,keys_to_keep) called...");
    
    // if no labels to keep passed return void
    if(keys_to_keep.size() == 0) return;

    // loop through map and erase channels not in keys_to_keep
    for(map<string, OpenLF::image::ImageChannel>::iterator i = channels.begin(); i != channels.end(); ++i)
    {
        // get key
        string key = i->first;
        
        // check if key is in keys_to_keep
        int key_found = 0;
        for(unsigned int c=0; c<keys_to_keep.size(); c++) {
            if(key==keys_to_keep[c]) {
                key_found++;
            }
        }

        // if not found erase channel
        if(key_found==0) {
            channels.erase(key);
        }
    }
}



void OpenLF::image::io::linear_range_mapping(vigra::MultiArray<2,float>& fimg, vigra::MultiArray<2, vigra::UInt8>& img) 
{
    print(1,"image::io::linear_range_mapping(fimg,img) called...");
    
    try {
        if(!img.hasData()) img = vigra::MultiArray<2, vigra::UInt8>(fimg.shape());
        
        // functor to find range
        vigra::FindMinMax<vigra::FImage::PixelType> minmax;
        
        // find original range
        vigra::inspectImage(vigra::srcImageRange(fimg), minmax);
        if(minmax.max<=minmax.min) throw OpenLF_Exception("image::io::linear_range_mapping failed, no distance in image to map!");
        
        
        int nmin, nmax;
        // if original range is btw [0,1] keep relative range by multiplying min/max with 255
        if(minmax.min>=0 && minmax.min<1 && minmax.max>0 && minmax.max<=1) {
            nmin = int(ceil(minmax.min*255));
            nmax = int(floor(minmax.max*255));
        }
        // else scale hard to [0,255]
        else {
            nmin = 0;
            nmax = 255;
        }
            
        // transform the range to min/max specified
        vigra::transformImage(vigra::srcImageRange(fimg), vigra::destImage(img),
                              vigra::linearRangeMapping( minmax.min, minmax.max, nmin, nmax) );
    } catch(exception & e) {
        warning(e.what());
    }
}


void OpenLF::image::io::linear_range_mapping(vigra::MultiArray<2,float>& fimg, vigra::MultiArray<2,float>& img) 
{
    print(1,"image::io::linear_range_mapping(fimg,img) called...");
    
    try {
        if(!img.hasData()) img = vigra::MultiArray<2,float>(fimg.shape());
        
        // functor to find range
        vigra::FindMinMax<vigra::FImage::PixelType> minmax;
        
        // find original range
        vigra::inspectImage(vigra::srcImageRange(fimg), minmax);
        if(minmax.max<=minmax.min) throw OpenLF_Exception("image::io::linear_range_mapping failed, no distance in image to map!");
        
        
        float nmin, nmax;
        // if original range is btw [0,1] keep relative range by multiplying min/max with 255
        if(minmax.min>=0 && minmax.min<1 && minmax.max>0 && minmax.max<=1) {
            nmin = minmax.min*255.0f;
            nmax = minmax.max*255.0f;
        }
        // else scale hard to [0,255]
        else {
            nmin = 0.0f;
            nmax = 255.0f;
        }
            
        // transform the range to min/max specified
        vigra::transformImage(vigra::srcImageRange(fimg), vigra::destImage(img),
                              vigra::linearRangeMapping( minmax.min, minmax.max, nmin, nmax) );
    } catch(exception & e) {
        warning(e.what());
    }
}


void OpenLF::image::io::linear_range_mapping(vigra::MultiArrayView<2,float>& fimg, vigra::MultiArray<2,float>& img) 
{
    print(1,"image::io::linear_range_mapping(fimg,img) called...");
    
    try {
        if(!img.hasData()) img = vigra::MultiArray<2,float>(fimg.shape());
        
        // functor to find range
        vigra::FindMinMax<vigra::FImage::PixelType> minmax;
        
        // find original range
        vigra::inspectImage(vigra::srcImageRange(fimg), minmax);
        if(minmax.max<=minmax.min) throw OpenLF_Exception("image::io::linear_range_mapping failed, no distance in image to map!");
        
        
        float nmin, nmax;
        // if original range is btw [0,1] keep relative range by multiplying min/max with 255
        if(minmax.min>=0 && minmax.min<1 && minmax.max>0 && minmax.max<=1) {
            nmin = minmax.min*255.0f;
            nmax = minmax.max*255.0f;
        }
        // else scale hard to [0,255]
        else {
            nmin = 0.0f;
            nmax = 255.0f;
        }
            
        // transform the range to min/max specified
        vigra::transformImage(vigra::srcImageRange(fimg), vigra::destImage(img),
                              vigra::linearRangeMapping( minmax.min, minmax.max, nmin, nmax) );
    } catch(exception & e) {
        warning(e.what());
    }
}


void OpenLF::image::io::linear_range_mapping(OpenLF::image::ImageChannel& img_channel, vigra::MultiArray<2, vigra::UInt8>& img) 
{
    print(1,"image::io::linear_range_mapping(img_channel,img) called...");
    
    try {
        // functor to find range
        vigra::FindMinMax<vigra::FImage::PixelType> minmax;
        
        // find original range
        vigra::MultiArray<2,float> *tmp;
        tmp = NULL;
        tmp = img_channel.image();
        
        if(tmp==NULL) throw OpenLF_Exception("image::io::linear_range_mapping failed, pointer NULL Exception!");
        
        vigra::inspectImage(vigra::srcImageRange(*tmp), minmax);
        if(minmax.max<=minmax.min) throw OpenLF_Exception("image::io::linear_range_mapping failed, no distance in image to map!");
        
        int nmin, nmax;
        // if original range is btw [0,1] keep relative range by multiplying min/max with 255
        if(minmax.min>=0 && minmax.min<1 && minmax.max>0 && minmax.max<=1) {
            nmin = int(ceil(minmax.min*255));
            nmax = int(floor(minmax.max*255));
        }
        // else scale hard to [0,255]
        else {
            nmin = 0;
            nmax = 255;
        }
            
        // transform the range to min/max specified
        vigra::transformImage(vigra::srcImageRange(*tmp), vigra::destImage(img),
                              vigra::linearRangeMapping( minmax.min, minmax.max, nmin, nmax) );
    } catch(exception & e) {
        warning(e.what());
    }
}



bool OpenLF::image::io::imread(string filename, map<string,OpenLF::image::ImageChannel> &img_channel)
{
    print(2,"image::io::imread(filename,channels) called...");
    
    try {
        // import image info to get the image shape
        vigra::ImageImportInfo info(filename.c_str());
    
        // image size
        int width = info.width();
        int height = info.height();

        // load grayscale images
        if(info.isGrayscale()) {
            print(3,"image::io::imread(string,map) found grayscale image...");
         
            // uint image to import data from file
            vigra::MultiArray<2, vigra::UInt8> in(width,height);

            // import data
            if(info.numExtraBands()!=0) {
                vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(info.width(),info.height()));
                vigra::importImageAlpha(info, in, alpha);
            }
            else {
                vigra::importImage(info, in);
            }  
            
            // create channel and copy data into object and map to range [1,0]
            img_channel["bw"] = OpenLF::image::ImageChannel();
            img_channel["bw"].init(info.width(),info.height(),in.data());
        }
        // load color images
        else if(info.isColor()) {
            print(3,"image::io::imread(string,map) found color image...");

            // create channels
            img_channel["r"] = OpenLF::image::ImageChannel(info.width(),info.height()); 
            img_channel["g"] = OpenLF::image::ImageChannel(info.width(),info.height()); 
            img_channel["b"] = OpenLF::image::ImageChannel(info.width(),info.height()); 

            // uint rgb image to import data from file
            vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info.shape());

            // import data
            if(info.numExtraBands()!=0) {
                vigra::MultiArray<2, vigra::UInt8 > alpha(vigra::Shape2(info.width(),info.height()));
                vigra::importImageAlpha(info, in, alpha);
            }
            else {
                vigra::importImage(info, in);
            }                      
            
            
            
            float* r_ptr = NULL;
            r_ptr = img_channel["r"].data();
            if(r_ptr==NULL) throw OpenLF_Exception("imread read channel error!");
            float* g_ptr = NULL;
            g_ptr = img_channel["g"].data();
            if(g_ptr==NULL) throw OpenLF_Exception("imread read channel error!");
            float* b_ptr = NULL;
            b_ptr = img_channel["b"].data();
            if(b_ptr==NULL) throw OpenLF_Exception("imread read channel error!");

            // copy data into lf container
            int n=0;
            for(int y=0; y<height; y++) {
                for(int x=0; x<width; x++) {
                    r_ptr[n] = ((float)in(x,y)[0])/255.0f;
                    g_ptr[n] = ((float)in(x,y)[1])/255.0f;
                    b_ptr[n] = ((float)in(x,y)[2])/255.0f;
                    n++;
                }
            }
        }
    }
    catch(exception &e) {
        warning(e.what());
        return false;
    }
    return true;
}



bool OpenLF::image::io::imsave(string filename, vigra::MultiArray<2,float> img)
{
    print(2,"image::io::imread(filename,img) called...");
    
    // get file type
    string ftype = OpenLF::helpers::find_ftype(filename);
    
    try {
        // allocate memory to store range mapping results
        vigra::MultiArray<2,vigra::UInt8> tmp(vigra::Shape2(img.width(),img.height()));
        linear_range_mapping(img,tmp);

        if(ftype=="jpg")
            vigra::exportImage(tmp, vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
        else
            vigra::exportImage(tmp, filename.c_str());
        
    } catch(exception & e) {
        warning(e.what());
        return false;
    }
    
    return true;
}


bool OpenLF::image::io::imsave(string filename, vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>> img)
{
    print(2,"image::io::imread(filename,img) called...");
    
    // get file type
    string ftype = OpenLF::helpers::find_ftype(filename);
    
    try {
        // allocate memory to store range mapping results
       // vigra::MultiArray<2,vigra::UInt8> tmp(vigra::Shape2(img.width(),img.height()));
       // linear_range_mapping(img,tmp);

        if(ftype=="jpg")
            vigra::exportImage(img, vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
        else
            vigra::exportImage(img, filename.c_str());
        
    } catch(exception & e) {
        warning(e.what());
        return false;
    }
    
    return true;
}


bool OpenLF::image::io::imsave(string filename, vigra::MultiArrayView<2,float> img)
{
    print(2,"image::io::imread(filename,img_view) called...");
    
    vigra::MultiArray<2,float> img_tmp = vigra::MultiArray<2,float>(img);
    return imsave(filename,img_tmp);
}



bool OpenLF::image::io::imsave(string filename, OpenLF::image::ImageChannel img_channel)
{
    print(2,"image::io::imread(filename,channel_img) called...");
    
    // get file type
    string ftype = OpenLF::helpers::find_ftype(filename);
    
    try {
        // allocate memory to store range mapping results
        vigra::MultiArray<2,vigra::UInt8> tmp(vigra::Shape2(img_channel.width(),img_channel.height()));
        linear_range_mapping(img_channel,tmp);

        if(ftype=="jpg")
            vigra::exportImage(tmp, vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
        else
            vigra::exportImage(tmp, filename.c_str());
        
    } catch(exception & e) {
        warning(e.what());
        return false;
    }
    
    return true;
}




bool OpenLF::image::io::imsave(string filename, map<string,OpenLF::image::ImageChannel> channels, string key)
/*TEST: test_image::test_io() */
{
    print(2,"image::io::save(filename,channels,key) called...");

    if ( channels.count(key) != 0 ) {
        return imsave(filename, channels[key]);
    }
    return false;
}




bool OpenLF::image::io::imsave(string filename, map<string,OpenLF::image::ImageChannel> channels)
{
    print(2,"image::io::imsave(filename, channels) called...");
  
    string ftype = OpenLF::helpers::find_ftype(filename);
       
    try {
        
        // if a grayscale channel exist save
        if ( channels.count("bw") != 0 ) {

            string msg = "save image as grayscale " + ftype +"..."; print(3,msg.c_str());

            // adapt filename to set the appendix
            string bw_filename = string(filename);
            int insert_pos = filename.length()-(ftype.length()+1);
            bw_filename.insert(insert_pos,"_bw");

            // save channel
            imsave(bw_filename,channels["bw"]);

            // delete bw channel
            channels.erase("bw");
        }
        
        // if r,g and b channels exist save
        if ( channels.count("r") != 0 && channels.count("g") != 0  && channels.count("b") != 0 ) {

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
            
            
        }

        // check for other channels and save them
        for(map<string, OpenLF::image::ImageChannel>::iterator i = channels.begin(); i != channels.end(); ++i)
        {
            // get key
            string key = i->first;

            // adapt filename to set the appendix
            string tmp_filename = string(filename);
            int insert_pos = filename.length()-(ftype.length()+1);

            string appendix = "_"+key;
            tmp_filename.insert(insert_pos,appendix);

            // save and delete channel
            imsave(tmp_filename,channels[key]);
            channels.erase(key);
        }
        
    } catch(exception & e) {
        warning(e.what());
        return false;
    }
    
    return true;
}




bool OpenLF::image::io::imsave(string filename, map<string,OpenLF::image::ImageChannel> channels, vector<string> keys_to_save)
{
    print(2,"image::io::imsave(filename, channels, keys_to_save) called...");
    
    try {
        // delete unnecessary channels and save
        reduce_channels(channels,keys_to_save);
        return imsave(filename,channels);
    }
    catch(exception & e) {
        warning(e.what());
        return false;
    }
}