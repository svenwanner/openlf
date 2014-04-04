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
}

void test_channel::setUp() {
    
    imgnames["lena_rgb"] = test_data_dir+"lena_rgb.jpg";
    imgnames["lena_bw"] = test_data_dir+"lena_bw.jpg";
    imgnames["straw_rgb"] = test_data_dir+"straw_rgb.jpg";
    imgnames["straw_bw"] = test_data_dir+"straw_bw.jpg";
    
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
    CPPUNIT_ASSERT(channels["r"].width()==1023);
    CPPUNIT_ASSERT(channels["r"].height()==774);
    
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["straw_bw"],channels));
    CPPUNIT_ASSERT(channels["bw"].width()==1023);
    CPPUNIT_ASSERT(channels["bw"].height()==774);
}


