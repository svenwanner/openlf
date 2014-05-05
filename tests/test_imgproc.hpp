/*
 * File:   test_imgproc.hpp
 * Author: swanner
 *
 * Created on Mar 25, 2014, 11:06:07 AM
 */

#ifndef TEST_IMGPROC_HPP
#define	TEST_IMGPROC_HPP

#include <cppunit/extensions/HelperMacros.h>


#include "settings.hpp"

#include "OpenLF/global.hpp"
#include "OpenLF/image/io.hpp"
#include "OpenLF/image/imgproc.hpp"
#include "OpenLF/image/Channel.hpp"

using namespace std;


class test_imgproc : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_imgproc);

    CPPUNIT_TEST(test_diff_abs_mse);
    CPPUNIT_TEST_SUITE_END();

public:
    test_imgproc();
    virtual ~test_imgproc();
    void setUp();
    void tearDown();

private:
    void test_diff_abs_mse();
    map<string,string> imgnames;
};

#endif	/* TEST_IMGPROC_HPP */

