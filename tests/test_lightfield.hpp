/*
 * File:   test_lightfield.hpp
 * Author: swanner
 *
 * Created on Mar 14, 2014, 10:10:31 PM
 */

#ifndef TEST_LIGHTFIELD_HPP
#define	TEST_LIGHTFIELD_HPP

#include <cppunit/extensions/HelperMacros.h>

#include "utils/helpers.hpp"
#include "settings.hpp"

#include "global.hpp"
#include "image/io.hpp"
#include "lightfield/io.hpp"
#include "lightfield/FileHandler.hpp"

class test_lightfield : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_lightfield);

    CPPUNIT_TEST(test_hdf5_io);
    CPPUNIT_TEST(test_loading_from_imagefiles);
    CPPUNIT_TEST(test_FileHandler);
    

    CPPUNIT_TEST_SUITE_END();

public:
    test_lightfield();
    virtual ~test_lightfield();
    void setUp();
    void tearDown();

private:
    void test_hdf5_io();
    void test_loading_from_imagefiles();
    void test_FileHandler();
    
    
    
    string _lf_4D_hdf5_bw_path;
    string _lf_4D_hdf5_rgb_path;
    string _lf_4D_hdf5_bw_out_path;
    string _lf_4D_hdf5_rgb_out_path;
    string _lf_4D_path;
    string _lf_3DH_path;
    string _lf_3DV_path;
    string _lf_CROSS_path;
    string _lf_4D_bw_path;
    string _lf_3DH_bw_path;
    string _lf_3DV_bw_path;
    string _lf_CROSS_bw_path;
    string _lf_test_ftype;
    vector<string> _fnames;
};

#endif	/* TEST_LIGHTFIELD_HPP */

