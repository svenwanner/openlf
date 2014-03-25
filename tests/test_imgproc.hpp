/*
 * File:   test_imgproc.hpp
 * Author: swanner
 *
 * Created on Mar 25, 2014, 11:06:07 AM
 */

#ifndef TEST_IMGPROC_HPP
#define	TEST_IMGPROC_HPP

#include <cppunit/extensions/HelperMacros.h>

#include "global.hpp"
#include "image/io.hpp"
#include "settings.hpp"
#include "image/imgproc.hpp"

class test_imgproc : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_imgproc);

    CPPUNIT_TEST(test_shape_check);
    CPPUNIT_TEST(test_difference);
    CPPUNIT_TEST(test_abs_difference);
    CPPUNIT_TEST(test_MSE);

    CPPUNIT_TEST_SUITE_END();

public:
    test_imgproc();
    virtual ~test_imgproc();
    void setUp();
    void tearDown();

private:
    void test_shape_check();
    void test_difference();
    void test_abs_difference();
    void test_MSE();
    
    map<string,string> imgnames;
    map<string,vigra::MultiArray<2,float> > lena_rgb;
    map<string,vigra::MultiArray<2,float> > lena_bw;
    map<string,vigra::MultiArray<2,float> > straw_rgb;
    map<string,vigra::MultiArray<2,float> > straw_bw;
};

#endif	/* TEST_IMGPROC_HPP */

