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
    _lf_4D_hdf5_rgb_path = test_lf_dir+"4D/"+"test_lf4D_rgb.h5";
    _lf_4D_hdf5_bw_path = test_lf_dir+"4D/"+"test_lf4D_bw.h5";
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
    string outputpath;
    int width = 0;
    int height = 0;
    int cams_v = 0;
    int cams_h = 0;
    float baseline_v = 0;
    float baseline_h = 0;
    float focal_length = 0;
    LF_TYPE type = NONE;
    
    CPPUNIT_ASSERT( load_from_hdf5( _lf_4D_hdf5_rgb_path,channels,type,width,height,cams_h,cams_v,baseline_h,baseline_v,focal_length ));
    
    CPPUNIT_ASSERT(type == LF_4D);
    CPPUNIT_ASSERT(width == 480);
    CPPUNIT_ASSERT(height == 400);
    CPPUNIT_ASSERT(cams_h == 5);
    CPPUNIT_ASSERT(cams_v == 5);
    CPPUNIT_ASSERT(baseline_h == 0.3f);
    CPPUNIT_ASSERT(baseline_v == 0.3f);
    CPPUNIT_ASSERT(focal_length = 10.0f);
    CPPUNIT_ASSERT(channels.size()==3);
    
    OpenLF::lightfield::io::save(test_result_dir+"test_4D_rgb_fromH5.jpg",channels);
    channels.clear();
    
    CPPUNIT_ASSERT( load_from_hdf5( _lf_4D_hdf5_bw_path,channels,type,width,height,cams_h,cams_v,baseline_h,baseline_v,focal_length ));
    
    CPPUNIT_ASSERT(type == LF_4D);
    CPPUNIT_ASSERT(width == 480);
    CPPUNIT_ASSERT(height == 400);
    CPPUNIT_ASSERT(cams_h == 5);
    CPPUNIT_ASSERT(cams_v == 5);
    CPPUNIT_ASSERT(baseline_h == 0.3f);
    CPPUNIT_ASSERT(baseline_v == 0.3f);
    CPPUNIT_ASSERT(focal_length = 10.5f);
    CPPUNIT_ASSERT(channels.size()==1);
    
    OpenLF::lightfield::io::save(test_result_dir+"test_4D_bw_fromH5.jpg",channels);
    channels.clear();

    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_4D_path,channels,LF_4D,5,5));
    OpenLF::lightfield::io::save(test_result_dir+"test_4D_rgb.jpg",channels);
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_4D_bw_path,channels,LF_4D,5,5));
    OpenLF::lightfield::io::save(test_result_dir+"test_4D_bw.jpg",channels);
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DH_path,channels,LF_3DH,5,1));
    OpenLF::lightfield::io::save(test_result_dir+"test_3DH.jpg",channels);
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DH_bw_path,channels,LF_3DH,5,1));
    OpenLF::lightfield::io::save(test_result_dir+"test_3DH_bw.jpg",channels);
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DV_path,channels,LF_3DV,1,5));
    OpenLF::lightfield::io::save(test_result_dir+"test_3DV.jpg",channels);
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DV_bw_path,channels,LF_3DV,1,5));
    OpenLF::lightfield::io::save(test_result_dir+"test_3DV_bw.jpg",channels);
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_CROSS_path,channels,LF_CROSS,5,5));
    OpenLF::lightfield::io::save(test_result_dir+"test_CROSS.jpg",channels);
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_CROSS_bw_path,channels,LF_CROSS,5,5));
    OpenLF::lightfield::io::save(test_result_dir+"test_CROSS_bw.jpg",channels);
    channels.clear();
}
