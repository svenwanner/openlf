/*
 * File:   test_channel.cpp
 * Author: swanner
 *
 * Created on Apr 3, 2014, 12:09:21 PM
 */

#include "test_channel.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(test_channel);

test_channel::test_channel() {
}

test_channel::~test_channel() {
    cout << "tests run through!" << endl;
}

void test_channel::setUp() {
    
    imgnames["lena_rgb"] = test_data_dir+"lena_rgb.jpg";
    imgnames["lena_bw"] = test_data_dir+"lena_bw.jpg";
    imgnames["straw_rgb"] = test_data_dir+"straw_rgb.jpg";
    imgnames["straw_bw"] = test_data_dir+"straw_bw.jpg";
                
    cout <<  imgnames["lena_rgb"] << " " << imgnames["lena_bw"] << endl;
    
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["lena_rgb"],lena_rgb));
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["lena_bw"],lena_bw));
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["straw_rgb"],straw_rgb));
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["straw_bw"],straw_bw));
}

void test_channel::tearDown() {
}

void test_channel::test_initialization() {
    OpenLF::image::ImageChannel channel;
    map<string,OpenLF::image::ImageChannel> channels;
  
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["straw_rgb"],channels));
    
    CPPUNIT_ASSERT(channels["r"].width()==1032);
    CPPUNIT_ASSERT(channels["r"].height()==774);
    CPPUNIT_ASSERT(channels["g"].width()==1032);
    CPPUNIT_ASSERT(channels["g"].height()==774);
    CPPUNIT_ASSERT(channels["b"].width()==1032);
    CPPUNIT_ASSERT(channels["b"].height()==774);
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_single_channels_r.jpg",channels["r"]));
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_single_channels_g.jpg",channels["g"]));
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_single_channels_b.jpg",channels["b"]));
            
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_single_key.jpg", channels, "b"));
    
    vector<string> keys_to_save {"g","b"};
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_key_selection.jpg", channels, keys_to_save));
    
    float* arr = new float[1032*774];
    float m=0.0;
    for(int n=0; n<1032*774; n++) {
        arr[n] = m;
        if(n%1032==0) {
            m+=1.0/773.0;
        }
    }
    OpenLF::image::ImageChannel additional_channel(1032,774,arr);
    channels["x"] = additional_channel;
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save_entire_channel_map.jpg", channels));
    
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["straw_bw"],channels));
    CPPUNIT_ASSERT(channels["bw"].width()==1032);
    CPPUNIT_ASSERT(channels["bw"].height()==774);
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_single_channels_bw.jpg",channels["bw"]));
    
    channels.clear();
}


