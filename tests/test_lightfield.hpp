/*
* Copyright (c) 2014 Sven Wanner
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of 
* this software and associated documentation files (the "Software"), to deal in 
* the Software without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
* Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all 
* copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
#include "OpenLF/lightfield/Lightfield.hpp"
#include "OpenLF/lightfield/Properties.hpp"
#include "OpenLF/lightfield/FileHandler.hpp"

using namespace std;

class test_lightfield : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_lightfield);
    
    CPPUNIT_TEST(test_epi_iterator);
    CPPUNIT_TEST(test_epi_access);
    CPPUNIT_TEST(test_loxel_access);
    CPPUNIT_TEST(test_instantiate_Lightfield);

    CPPUNIT_TEST_SUITE_END();

public:
    test_lightfield();
    virtual ~test_lightfield();
    void setUp();
    void tearDown();

private:
    void test_epi_iterator();
    void test_epi_access();
    void test_loxel_access();
    void test_instantiate_Lightfield();
    
    
    map<string,string> cfgnames;
    map<string,string> imgnames;
    map<string,string> fnames;
};

#endif	/* TEST_LIGHTFIELD_HPP */

