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
    OpenLF::image::Channel ch;
    
    vigra::MultiArray<2,float> *tmp;
  
    ch.init(straw_bw["bw"].width(),straw_bw["bw"].height(),straw_bw["bw"].data());
    
    CPPUNIT_ASSERT(ch.width()==straw_bw["bw"].width());
    CPPUNIT_ASSERT(ch.height()==straw_bw["bw"].height());
    
    ch.data(&tmp);
    
    OpenLF::image::io::imsave("/home/swanner/Desktop/test.jpg",*tmp);
}


