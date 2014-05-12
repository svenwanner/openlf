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

using namespace std;

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

