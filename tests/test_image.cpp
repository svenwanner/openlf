/*
 * File:   test_image.cpp
 * Author: swanner
 *
 * Created on Mar 18, 2014, 3:30:24 PM
 */

#include "test_image.hpp"



CPPUNIT_TEST_SUITE_REGISTRATION(test_image);

test_image::test_image() {
}

test_image::~test_image() {
}

void test_image::setUp() {
    _lena_rgb_dir = test_data_dir+"lena_rgb.jpg";
    _lena_bw_dir = test_data_dir+"lena_bw.jpg";
}

void test_image::tearDown() {
    cout << "test suite runs through!" << endl;
}

void test_image::test_io() {
    map< string,OpenLF::image::ImageChannel> channels;
    
    // test loading an bw image and save it again
    CPPUNIT_ASSERT(OpenLF::image::io::imread(_lena_bw_dir,channels));
    CPPUNIT_ASSERT(channels["bw"].width() == 512);
    CPPUNIT_ASSERT(channels["bw"].height() == 576);
    CPPUNIT_ASSERT(channels.size()==1);
       
    // test loading an rgb image
    CPPUNIT_ASSERT(OpenLF::image::io::imread(_lena_rgb_dir,channels));
    
    CPPUNIT_ASSERT(channels["r"].width() == 512);
    CPPUNIT_ASSERT(channels["r"].height() == 576);
    CPPUNIT_ASSERT(channels["g"].width() == 512);
    CPPUNIT_ASSERT(channels["g"].height() == 576);
    CPPUNIT_ASSERT(channels["b"].width() == 512);
    CPPUNIT_ASSERT(channels["b"].height() == 576);
    CPPUNIT_ASSERT(channels.size()==4);
    
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_img.jpg",channels));
    
    // test single channel save
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_single.jpg",channels,"g"));
    
    // add some channels with other labels and set some values
    channels["x"] = OpenLF::image::ImageChannel(vigra::Shape2(512,576));
    channels["y"] = OpenLF::image::ImageChannel(vigra::Shape2(512,576));
    
    for(int y=0; y<576; y++) {
        for(int x=0; x<512; x++) {
            channels["x"](x,y) = 1.0/576*y;
            channels["y"](x,y) = 1.0/576*y;
            if(y%2==0 && x%2!=0) {  
                channels["x"](x,y) = channels["g"](x,y);
                channels["y"](x,y) = channels["b"](x,y);
            }
            else if(y%2!=0 && x%2==0) {
                channels["x"](x,y) = 1.0/576*y;
                channels["y"](x,y) = 1.0/576*y;
            }
        }
    }

    // test saving all channels
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_all_channels.jpg",channels));
    
    // test saving only some channels
    vector<string> keys {"x","y","bw"};
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_channel_selection.jpg",channels));
    
    // test if still all channels are present
    CPPUNIT_ASSERT(channels.size()==6);
    CPPUNIT_ASSERT(channels["r"].width() == 512);
    CPPUNIT_ASSERT(channels["r"].height() == 576);
    CPPUNIT_ASSERT(channels["g"].width() == 512);
    CPPUNIT_ASSERT(channels["g"].height() == 576);
    CPPUNIT_ASSERT(channels["b"].width() == 512);
    CPPUNIT_ASSERT(channels["b"].height() == 576);
    CPPUNIT_ASSERT(channels["x"].width() == 512);
    CPPUNIT_ASSERT(channels["x"].height() == 576);
    CPPUNIT_ASSERT(channels["y"].width() == 512);
    CPPUNIT_ASSERT(channels["y"].height() == 576);
}


void test_image::test_roi_io() {

    map< string,OpenLF::image::ImageChannel> channels;
   
    OpenLF::ROI roi;
    roi.pos_x = 235;
    roi.pos_y = 235;
    roi.width = 78;
    roi.height = 64;
    
    CPPUNIT_ASSERT(OpenLF::image::io::imread(_lena_bw_dir,roi,channels));
    CPPUNIT_ASSERT(channels["bw"].width() == 78);
    CPPUNIT_ASSERT(channels["bw"].height() == 64);
    CPPUNIT_ASSERT(channels.size()==1);
    
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_img_roi.jpg",channels));
    channels.clear();
       
    // test loading an rgb image
    CPPUNIT_ASSERT(OpenLF::image::io::imread(_lena_rgb_dir,roi,channels));
    
    CPPUNIT_ASSERT(channels["r"].width() == 78);
    CPPUNIT_ASSERT(channels["r"].height() == 64);
    CPPUNIT_ASSERT(channels["g"].width() == 78);
    CPPUNIT_ASSERT(channels["g"].height() == 64);
    CPPUNIT_ASSERT(channels["b"].width() == 78);
    CPPUNIT_ASSERT(channels["b"].height() == 64);
    CPPUNIT_ASSERT(channels.size()==3);
    
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_img_roi.jpg",channels));
    channels.clear();
}