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

#include <cppunit/extensions/HelperMacros.h>

class image_test : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(image_test);

    CPPUNIT_TEST(testConstructor);

    CPPUNIT_TEST_SUITE_END();

public:
    image_test();
    virtual ~image_test();
    void setUp();
    void tearDown();

private:
    void testConstructor();

};

#endif	/* IMAGE_TEST_HPP */