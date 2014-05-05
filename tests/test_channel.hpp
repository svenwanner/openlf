/*
 * File:   test_channel.hpp
 * Author: swanner
 *
 * Created on Apr 3, 2014, 12:09:21 PM
 */

#ifndef TEST_CHANNEL_HPP
#define	TEST_CHANNEL_HPP

#include "OpenLF/global.hpp"
#include "settings.hpp"
#include "OpenLF/image/Channel.hpp" 

#include <cppunit/extensions/HelperMacros.h>

using namespace std;


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
};

#endif	/* TEST_CHANNEL_HPP */

