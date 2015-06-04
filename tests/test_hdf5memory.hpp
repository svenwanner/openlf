//
// Created by lukasdsauer on 01.06.15.
//

#ifndef TEST_HDF5MEMORY_HPP
#define TEST_HDF5MEMORY_HPP

#include <cppunit/extensions/HelperMacros.h>
#include "settings.hpp"

#include "OpenLF/operators/HDF5Memory.hpp"

class test_hdf5memory : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_hdf5memory);

    CPPUNIT_TEST(testBasic);

    CPPUNIT_TEST_SUITE_END();

public:
    test_hdf5memory();
    virtual ~test_hdf5memory();
    void setUp();
    void tearDown();

private:
    void testBasic();
};

#endif //TEST_HDF5MEMORY_HPP
