/*
 * File:   test_lightfield_IO.hpp
 * Author: swanner
 *
 * Created on Apr 1, 2014, 4:15:12 PM
 */

#ifndef TEST_LIGHTFIELD_IO_HPP
#define	TEST_LIGHTFIELD_IO_HPP

#include "settings.hpp"

#include "OpenLF/debug.hpp"
#include "OpenLF/global.hpp"
#include "OpenLF/image/io.hpp"
#include "OpenLF/image/imgproc.hpp"
#include "OpenLF/utils/helpers.hpp"
#include "OpenLF/lightfield/io.hpp"
#include "OpenLF/image/Channel.hpp"
#include "OpenLF/lightfield/Properties.hpp"
#include "OpenLF/lightfield/FileHandler.hpp"
#include "OpenLF/lightfield/Lightfield.hpp"

#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class test_lightfield_IO : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_lightfield_IO);

    CPPUNIT_TEST(test_ROI_IO_Pipeline_4D);
    CPPUNIT_TEST(test_IO_Pipeline_4D);
    CPPUNIT_TEST(test_IO_Pipeline_3DH);
    CPPUNIT_TEST(test_IO_Pipeline_3DV);
    CPPUNIT_TEST(test_IO_Pipeline_CROSS);
    CPPUNIT_TEST(test_Properties_methods);

    CPPUNIT_TEST_SUITE_END();
    
    
public:
    test_lightfield_IO();
    virtual ~test_lightfield_IO();
    void setUp();
    void tearDown();

private:
    void test_ROI_IO_Pipeline_4D();
    void test_IO_Pipeline_4D();
    void test_IO_Pipeline_3DH();
    void test_IO_Pipeline_3DV();
    void test_IO_Pipeline_CROSS();
    void test_Properties_methods();
    
    map<string,string> cfgnames;
    map<string,string> imgnames;
};

#endif	/* TEST_LIGHTFIELD_IO_HPP */

