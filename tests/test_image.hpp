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
const unsigned int LENA_TEST_COL_BW[NUMBER_OF_CHECKPOINTS] = {125,130,75,177,63,200};

class image_test : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(image_test);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testCannelAcccess);

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
    string lena_rgb_path;
    string lena_bw_path;
};

#endif	/* IMAGE_TEST_HPP */