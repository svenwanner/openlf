/*
 * File:   test_operator.hpp
 * Author: swanner
 *
 * Created on May 19, 2014, 9:32:18 AM
 */

#ifndef TEST_OPERATOR_HPP
#define	TEST_OPERATOR_HPP

#include <cppunit/extensions/HelperMacros.h>

class test_operator : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_operator);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    test_operator();
    virtual ~test_operator();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif	/* TEST_OPERATOR_HPP */

