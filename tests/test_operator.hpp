/*
 * File:   test_operator.hpp
 * Author: swanner
 *
 * Created on May 19, 2014, 9:32:18 AM
 */

#ifndef TEST_OPERATOR_HPP
#define	TEST_OPERATOR_HPP

#include <cppunit/extensions/HelperMacros.h>
#include "settings.hpp"

#include "OpenLF/global.hpp"
/*
#include "OpenLF/debug.hpp"
#include "OpenLF/global.hpp"
*/
#include "OpenLF/image/io.hpp"

//#include "OpenLF/image/imgproc.hpp"
//#include "OpenLF/utils/helpers.hpp"

#include "OpenLF/lightfield/io.hpp"

#include "OpenLF/image/Channel.hpp"
#include "OpenLF/lightfield/Lightfield.hpp"
#include "OpenLF/lightfield/Lightfield_3D.hpp"
#include "OpenLF/lightfield/Lightfield_4D.hpp"
#include "OpenLF/lightfield/Lightfield_CROSS.hpp"
#include "OpenLF/lightfield/Properties.hpp"
#include "OpenLF/lightfield/FileHandler.hpp"
#include "OpenLF/operators/My4DOperator.hpp"
#include "OpenLF/operators/MyEpiOperator.hpp"
#include "OpenLF/operators/Structure_Tensor.hpp"

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

    map<string,string> cfgnames;
    map<string,string> imgnames;
    map<string,string> fnames;
};

#endif	/* TEST_OPERATOR_HPP */

