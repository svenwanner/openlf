/*
 * File:   test_lightfield_IO.hpp
 * Author: swanner
 *
 * Created on Apr 1, 2014, 4:15:12 PM
 */

#ifndef TEST_LIGHTFIELD_IO_HPP
#define	TEST_LIGHTFIELD_IO_HPP

#include "settings.hpp"

#include "debug.hpp"
#include "global.hpp"
#include "image/io.hpp"
#include "image/imgproc.hpp"
#include "utils/helpers.hpp"
#include "lightfield/io.hpp"
#include "lightfield/Properties.hpp"
#include "lightfield/FileHandler.hpp"
#include "lightfield/Lightfield.hpp"

#include <cppunit/extensions/HelperMacros.h>

class test_lightfield_IO : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_lightfield_IO);

    CPPUNIT_TEST(test_IO_Pipeline_4D);
    CPPUNIT_TEST(test_IO_Pipeline_3DH);
    CPPUNIT_TEST(test_IO_Pipeline_3DV);
    CPPUNIT_TEST(test_IO_Pipeline_CROSS);

    CPPUNIT_TEST_SUITE_END();

public:
    test_lightfield_IO();
    virtual ~test_lightfield_IO();
    void setUp();
    void tearDown();

private:
    void test_IO_Pipeline_4D();
    void test_IO_Pipeline_3DH();
    void test_IO_Pipeline_3DV();
    void test_IO_Pipeline_CROSS();
    
    map<string,string> cfgnames;
    map<string,string> imgnames;
};

#endif	/* TEST_LIGHTFIELD_IO_HPP */

