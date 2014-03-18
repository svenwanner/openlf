/*
 * File:   test_image.cpp
 * Author: swanner
 *
 * Created on Mar 18, 2014, 3:30:24 PM
 */

#include "test_image.hpp"
#include "image/io.hpp"
#include "global.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(test_image);

test_image::test_image() {
}

test_image::~test_image() {
}

void test_image::setUp() {
}

void test_image::tearDown() {
}

void test_image::test_io() {
    map< string, vigra::MultiArray<2,float> > channels;
    channels["r"] = vigra::MultiArray<2,float>(vigra::Shape2(10,10));
    channels["g"] = vigra::MultiArray<2,float>(vigra::Shape2(10,10));
    channels["b"] = vigra::MultiArray<2,float>(vigra::Shape2(10,10));
    channels["bw"] = vigra::MultiArray<2,float>(vigra::Shape2(10,10));
    channels["x"] = vigra::MultiArray<2,float>(vigra::Shape2(10,10));
    channels["y"] = vigra::MultiArray<2,float>(vigra::Shape2(10,10));
    
    vector<string> keys {"a","c","d"};
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(test_result_dir+"test_save.jpg",channels));
}


