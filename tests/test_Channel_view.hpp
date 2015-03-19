/*
 * File:   test_Channel_view.hpp 
 * Author: swanner
 *
 * Created on May 19, 2014, 9:32:18 AM
 */

#ifndef TEST_CHANNEL_VIEW_HPP 
#define	TEST_CHANNEL_VIEW_HPP 

#include <cppunit/extensions/HelperMacros.h>


class test_Channel_view : public CPPUNIT_NS::TestFixture { 
    CPPUNIT_TEST_SUITE(test_Channel_view); 

    CPPUNIT_TEST(testMethod); 

    CPPUNIT_TEST_SUITE_END();

public:
    test_Channel_view(); 
    virtual ~test_Channel_view(); 
    void setUp(); 
    void tearDown();

private:
    void testMethod(); 
};

#endif	/* TEST_CHANNEL_VIEW_HPP */ 

