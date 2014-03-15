/*
 * File:   test_lightfield.cpp
 * Author: swanner
 *
 * Created on Mar 14, 2014, 10:10:32 PM
 */

#include "test_lightfield.hpp"




CPPUNIT_TEST_SUITE_REGISTRATION(test_lightfield);

test_lightfield::test_lightfield() {
}

test_lightfield::~test_lightfield() {
}

void test_lightfield::setUp() {
    _lf_4D_path = test_lf_dir+"4D/rgb/";
    _lf_3DH_path = test_lf_dir+"3DH/rgb/";
    _lf_3DV_path = test_lf_dir+"3DV/rgb/";
    _lf_CROSS_path = test_lf_dir+"CROSS/rgb/";
    _lf_4D_bw_path = test_lf_dir+"4D/bw/";
    _lf_3DH_bw_path = test_lf_dir+"3DH/bw/";
    _lf_3DV_bw_path = test_lf_dir+"3DV/bw/";
    _lf_CROSS_bw_path = test_lf_dir+"CROSS/bw/";
    _lf_test_ftype = ".png";
}

void test_lightfield::tearDown() {
}

void test_lightfield::test_loading_from_imagefiles() {
    map< string, vigra::MultiArray<2,float> > channels;

    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_4D_path,channels,LF_4D,5,5));
    OpenLF::lightfield::io::save("/home/swanner/Desktop/test_4D_rgb.jpg",channels);
    channels.clear();
    
    cout << _lf_4D_bw_path << endl;
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_4D_bw_path,channels,LF_4D,5,5));
    OpenLF::lightfield::io::save("/home/swanner/Desktop/test_4D_bw.jpg",channels);
    channels.clear();
    
    cout << "\n_lf_3DH_path " << _lf_3DH_path << endl;
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DH_path,channels,LF_3DH,5,1));
    OpenLF::lightfield::io::save("/home/swanner/Desktop/test_3DH.jpg",channels);
    channels.clear();
    
    cout << "\n_lf_3DH_bw_path " << _lf_3DH_bw_path << endl;
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DH_bw_path,channels,LF_3DH,5,1));
    OpenLF::lightfield::io::save("/home/swanner/Desktop/test_3DH_bw.jpg",channels);
    channels.clear();
    
    cout << "\n_lf_3DV_path " << _lf_3DV_path << endl;
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DV_path,channels,LF_3DV,1,5));
    OpenLF::lightfield::io::save("/home/swanner/Desktop/test_3DV.jpg",channels);
    channels.clear();
    
    cout << "\n_lf_3DV_bw_path " << _lf_3DV_bw_path << endl;
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DV_bw_path,channels,LF_3DV,1,5));
    OpenLF::lightfield::io::save("/home/swanner/Desktop/test_3DV_bw.jpg",channels);
    channels.clear();
}
