/*
 * File:   test_lightfield.hpp
 * Author: swanner
 *
 * Created on Mar 14, 2014, 10:10:31 PM
 */

#ifndef TEST_LIGHTFIELD_HPP
#define	TEST_LIGHTFIELD_HPP

#include <cppunit/extensions/HelperMacros.h>



#include "settings.hpp"

#include "debug.hpp"
#include "global.hpp"
#include "image/io.hpp"
#include "image/imgproc.hpp"
#include "utils/helpers.hpp"
#include "lightfield/io.hpp"
#include "image/Channel.hpp"
#include "lightfield/Properties.hpp"
#include "lightfield/FileHandler.hpp"
#include "lightfield/Lightfield.hpp"


class test_lightfield : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_lightfield);
    
    CPPUNIT_TEST(test_instantiate_Lightfield);

    CPPUNIT_TEST_SUITE_END();

public:
    test_lightfield();
    virtual ~test_lightfield();
    void setUp();
    void tearDown();

private:
    
    
    void test_instantiate_Lightfield();
    
    
    map<string,string> cfgnames;
    map<string,string> imgnames;
};

#endif	/* TEST_LIGHTFIELD_HPP */

