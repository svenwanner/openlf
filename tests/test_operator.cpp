/*
 * File:   test_operator.cpp
 * Author: swanner
 *
 * Created on May 19, 2014, 9:32:19 AM
 */

#include "test_operator.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(test_operator);

test_operator::test_operator() {
}

test_operator::~test_operator() {
}

void test_operator::setUp() {
}

void test_operator::tearDown() {
}

void test_operator::testMethod() {
    CPPUNIT_ASSERT(true);
}

void test_operator::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

