/*
 * File:   test_image.hpp
 * Author: swanner
 *
 * Created on Mar 18, 2014, 3:30:24 PM
 */

#ifndef TEST_IMAGE_HPP
#define	TEST_IMAGE_HPP

#include <cppunit/extensions/HelperMacros.h>

#include "global.hpp"
#include "settings.hpp"
#include "image/io.hpp"
#include "image/Channel.hpp"

class test_image : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_image);

    CPPUNIT_TEST(test_io);

    CPPUNIT_TEST_SUITE_END();

public:
    test_image();
    virtual ~test_image();
    void setUp();
    void tearDown();

    void test_io();
    
private:
    string _lena_rgb_dir;
    string _lena_bw_dir;
};

#endif	/* TEST_IMAGE_HPP */

