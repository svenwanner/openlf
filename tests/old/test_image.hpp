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

/**
 *
 * \brief ...
 *
 * ...
 *
 * \note ...
 *
 * \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
 * 
 */

#ifndef IMAGE_TEST_HPP
#define	IMAGE_TEST_HPP

#include "settings.hpp"
#include "image/image.hpp"
#include <cppunit/extensions/HelperMacros.h>

const int NUMBER_OF_CHECKPOINTS = 6;
const unsigned int LENA_TEST_POS_X[NUMBER_OF_CHECKPOINTS] = {45,167,188,239,272,274};
const unsigned int LENA_TEST_POS_Y[NUMBER_OF_CHECKPOINTS] = {78,107,232,316,258,270};
const unsigned int LENA_TEST_COL_R[NUMBER_OF_CHECKPOINTS] = {176,175,87,236,86,216};
const unsigned int LENA_TEST_COL_G[NUMBER_OF_CHECKPOINTS] = {112,121,69,164,53,192};
const unsigned int LENA_TEST_COL_B[NUMBER_OF_CHECKPOINTS] = {102,83,83,142,60,205};
const unsigned int LENA_TEST_COL_BW[NUMBER_OF_CHECKPOINTS] = {125,128,74,178,61,198};

class image_test : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(image_test);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testCannelAcccess);
    CPPUNIT_TEST(addCannel);
    CPPUNIT_TEST(conversionOpenCV);

    CPPUNIT_TEST_SUITE_END();

public:
    image_test();
    virtual ~image_test();
    void setUp();
    void tearDown();

private:
    void testConstructor();
    void testCopyConstructor();
    void testCannelAcccess();
    void addCannel();
    void conversionOpenCV();
    
    string lena_rgb_path;
    string lena_bw_path;
    int lena_width,lena_height;
};

#endif	/* IMAGE_TEST_HPP */