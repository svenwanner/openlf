/*
 * File:   test_channel.hpp
 * Author: swanner
 *
 * Created on Apr 3, 2014, 12:09:21 PM
 */

#ifndef TEST_CHANNEL_HPP
#define	TEST_CHANNEL_HPP

#include "settings.hpp"

#include "debug.hpp"
#include "global.hpp"
#include "image/io.hpp"
#include "image/imgproc.hpp"
#include "image/Channel.hpp" 
#include "utils/helpers.hpp"
#include "lightfield/io.hpp"
#include "lightfield/Properties.hpp"
#include "lightfield/FileHandler.hpp"
#include "lightfield/Lightfield.hpp"

#include <cppunit/extensions/HelperMacros.h>



class test_channel : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_channel);

    CPPUNIT_TEST(test_initialization);
    CPPUNIT_TEST(test_operator_overload);

    CPPUNIT_TEST_SUITE_END();

public:
    test_channel();
    virtual ~test_channel();
    void setUp();
    void tearDown();

private:
    void test_initialization();
    void test_operator_overload();
    
    
    map<string,string> imgnames;
    map<string,vigra::MultiArray<2,float> > lena_rgb;
    map<string,vigra::MultiArray<2,float> > lena_bw;
    map<string,vigra::MultiArray<2,float> > straw_rgb;
    map<string,vigra::MultiArray<2,float> > straw_bw;
};

#endif	/* TEST_CHANNEL_HPP */

