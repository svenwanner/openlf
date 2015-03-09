/* 
 * File:   test_lukas.hpp
 * Author: lukasdsauer
 *
 * Created on 6. März 2015, 14:04
 */

#ifndef TEST_LUKAS_HPP
#define	TEST_LUKAS_HPP

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
#include "OpenLF/lightfield/Lightfield_4D.hpp"

#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class test_lukas : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_lukas);

    CPPUNIT_TEST(test_exmp);

    CPPUNIT_TEST_SUITE_END();

public:
    test_lukas();
    virtual ~test_lukas();
    void setUp();
    void tearDown();

private:
    void test_exmp();
};

#endif	/* TEST_LUKAS_HPP */

