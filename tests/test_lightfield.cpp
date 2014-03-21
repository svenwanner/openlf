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
    _lf_4D_hdf5_rgb_out_path = test_result_dir+"test_lf4D_rgb_toH5.h5";
    _lf_4D_hdf5_bw_out_path = test_result_dir+"test_lf4D_bw_toH5.h5";
    _lf_4D_path = test_lf_dir+"4D/rgb/";
    _lf_3DH_path = test_lf_dir+"3DH/rgb/";
    _lf_3DV_path = test_lf_dir+"3DV/rgb/";
    _lf_CROSS_path = test_lf_dir+"CROSS/rgb/";
    _lf_4D_bw_path = test_lf_dir+"4D/bw/";
    _lf_3DH_bw_path = test_lf_dir+"3DH/bw/";
    _lf_3DV_bw_path = test_lf_dir+"3DV/bw/";
    _lf_CROSS_bw_path = test_lf_dir+"CROSS/bw/";
    _lf_4D_gt_path = test_lf_dir+"test_lf_4D_gt.png";
    _lf_test_ftype = ".png";
}

void test_lightfield::tearDown() {
    cout << "test suite runs through!" << endl;
}

void test_lightfield::test_hdf5_io() {
    map< string, vigra::MultiArray<2,float> > channels;
    Properties props_4D; 
    
    CPPUNIT_ASSERT( OpenLF::lightfield::io::load_from_hdf5( _lf_4D_hdf5_rgb_path,channels,props_4D ));
    
    CPPUNIT_ASSERT(props_4D.type == LF_4D);
    CPPUNIT_ASSERT(props_4D.width == 480);
    CPPUNIT_ASSERT(props_4D.height == 400);
    CPPUNIT_ASSERT(props_4D.cams_h == 5);
    CPPUNIT_ASSERT(props_4D.cams_v == 5);
    CPPUNIT_ASSERT(props_4D.baseline_h == 0.3f);
    CPPUNIT_ASSERT(props_4D.baseline_v == 0.3f);
    CPPUNIT_ASSERT(props_4D.focal_length = 10.0f);
    CPPUNIT_ASSERT(channels.size()==3);
    
    OpenLF::image::io::imsave(test_result_dir+"test_4D_rgb_fromH5.jpg",channels);
    CPPUNIT_ASSERT( OpenLF::lightfield::io::save_to_hdf5(_lf_4D_hdf5_rgb_out_path,channels,props_4D) );
    channels.clear();
    
    CPPUNIT_ASSERT( OpenLF::lightfield::io::load_from_hdf5( _lf_4D_hdf5_bw_path,channels,props_4D ));
    
    CPPUNIT_ASSERT(props_4D.type == LF_4D);
    CPPUNIT_ASSERT(props_4D.width == 480);
    CPPUNIT_ASSERT(props_4D.height == 400);
    CPPUNIT_ASSERT(props_4D.cams_h == 5);
    CPPUNIT_ASSERT(props_4D.cams_v == 5);
    CPPUNIT_ASSERT(props_4D.baseline_h == 0.3f);
    CPPUNIT_ASSERT(props_4D.baseline_v == 0.3f);
    CPPUNIT_ASSERT(props_4D.focal_length = 10.5f);
    CPPUNIT_ASSERT(channels.size()==1);
    
    OpenLF::image::io::imsave(test_result_dir+"test_4D_bw_fromH5.jpg",channels);
    CPPUNIT_ASSERT( OpenLF::lightfield::io::save_to_hdf5(_lf_4D_hdf5_bw_out_path,channels,props_4D) );
    channels.clear();
}




void test_lightfield::test_loading_from_imagefiles() {
    map< string, vigra::MultiArray<2,float> > channels;
    Properties props_4D; 
    props_4D.cams_h = 5;
    props_4D.cams_v = 5;
    props_4D.type = LF_4D;
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_4D_path,channels,props_4D));
    OpenLF::image::io::imsave(test_result_dir+"test_4D_rgb.jpg",channels);
    CPPUNIT_ASSERT(channels.size()==3);
    CPPUNIT_ASSERT(channels["r"].width()==480);
    CPPUNIT_ASSERT(channels["r"].height()==400);
    CPPUNIT_ASSERT(channels["g"].width()==480);
    CPPUNIT_ASSERT(channels["g"].height()==400);
    CPPUNIT_ASSERT(channels["b"].width()==480);
    CPPUNIT_ASSERT(channels["b"].height()==400);
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_4D_bw_path,channels,props_4D));
    OpenLF::image::io::imsave(test_result_dir+"test_4D_bw.jpg",channels);
    CPPUNIT_ASSERT(channels.size()==1);
    CPPUNIT_ASSERT(channels["bw"].width()==480);
    CPPUNIT_ASSERT(channels["bw"].height()==400);
    channels.clear();
    
    
    Properties props_3DH; 
    props_3DH.cams_h = 5;
    props_3DH.cams_v = 1;
    props_3DH.type = LF_3DH;
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DH_path,channels,props_3DH));
    OpenLF::image::io::imsave(test_result_dir+"test_3DH.jpg",channels);
    CPPUNIT_ASSERT(channels.size()==3);
    CPPUNIT_ASSERT(channels["r"].width()==480);
    CPPUNIT_ASSERT(channels["r"].height()==80);
    CPPUNIT_ASSERT(channels["g"].width()==480);
    CPPUNIT_ASSERT(channels["g"].height()==80);
    CPPUNIT_ASSERT(channels["b"].width()==480);
    CPPUNIT_ASSERT(channels["b"].height()==80);
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DH_bw_path,channels,props_3DH));
    OpenLF::image::io::imsave(test_result_dir+"test_3DH_bw.jpg",channels);
    CPPUNIT_ASSERT(channels.size()==1);
    CPPUNIT_ASSERT(channels["bw"].width()==480);
    CPPUNIT_ASSERT(channels["bw"].height()==80);
    channels.clear();
    
    
    Properties props_3DV; 
    props_3DV.cams_h = 1;
    props_3DV.cams_v = 5;
    props_3DV.type = LF_3DV;
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DV_path,channels,props_3DV));
    OpenLF::image::io::imsave(test_result_dir+"test_3DV.jpg",channels);
    CPPUNIT_ASSERT(channels.size()==3);
    CPPUNIT_ASSERT(channels["r"].width()==400);
    CPPUNIT_ASSERT(channels["r"].height()==96);
    CPPUNIT_ASSERT(channels["g"].width()==400);
    CPPUNIT_ASSERT(channels["g"].height()==96);
    CPPUNIT_ASSERT(channels["b"].width()==400);
    CPPUNIT_ASSERT(channels["b"].height()==96);
    channels.clear();

    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_3DV_bw_path,channels,props_3DV));
    OpenLF::image::io::imsave(test_result_dir+"test_3DV_bw.jpg",channels);
    CPPUNIT_ASSERT(channels.size()==1);
    CPPUNIT_ASSERT(channels["bw"].width()==400);
    CPPUNIT_ASSERT(channels["bw"].height()==96);
    channels.clear();
    
    
    Properties props_CROSS; 
    props_CROSS.cams_h = 5;
    props_CROSS.cams_v = 5;
    props_CROSS.type = LF_CROSS;
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_CROSS_path,channels,props_CROSS));
    OpenLF::image::io::imsave(test_result_dir+"test_CROSS.jpg",channels);
    CPPUNIT_ASSERT(channels.size()==3);
    CPPUNIT_ASSERT(channels["r"].width()==480);
    CPPUNIT_ASSERT(channels["r"].height()==176);
    CPPUNIT_ASSERT(channels["g"].width()==480);
    CPPUNIT_ASSERT(channels["g"].height()==176);
    CPPUNIT_ASSERT(channels["b"].width()==480);
    CPPUNIT_ASSERT(channels["b"].height()==176);
    channels.clear();
    
    CPPUNIT_ASSERT(OpenLF::lightfield::io::load_from_filesequence(_lf_CROSS_bw_path,channels,props_CROSS));
    OpenLF::image::io::imsave(test_result_dir+"test_CROSS_bw.jpg",channels);
    CPPUNIT_ASSERT(channels.size()==1);
    CPPUNIT_ASSERT(channels["bw"].width()==480);
    CPPUNIT_ASSERT(channels["bw"].height()==176);
    channels.clear();
}




void test_lightfield::test_DataHandler() {
    
    // test reading from filesequence 
    map< string, vigra::MultiArray<2,float> > channels;
    Properties props_4D; 
    props_4D.cams_h = 5;
    props_4D.cams_v = 5;
    props_4D.type = LF_4D;
    
    // init a DataHandler with a string source 
    OpenLF::lightfield::io::DataHandler dataHandler(_lf_4D_path);
   
    // read the data
    CPPUNIT_ASSERT(dataHandler.read(channels,props_4D) == true );
    CPPUNIT_ASSERT(props_4D.type == LF_4D);
    CPPUNIT_ASSERT(props_4D.width == 96);
    CPPUNIT_ASSERT(props_4D.height == 80);
    CPPUNIT_ASSERT(props_4D.cams_h == 5);
    CPPUNIT_ASSERT(props_4D.cams_v == 5);
    CPPUNIT_ASSERT(channels.size()==3);
    CPPUNIT_ASSERT(channels["r"].width()==480);
    CPPUNIT_ASSERT(channels["r"].height()==400);
    CPPUNIT_ASSERT(channels["g"].width()==480);
    CPPUNIT_ASSERT(channels["g"].height()==400);
    CPPUNIT_ASSERT(channels["b"].width()==480);
    CPPUNIT_ASSERT(channels["b"].height()==400);
    channels.clear();
    
//    // test reading from hdf5
//    CPPUNIT_ASSERT(dataHandler.read(_lf_4D_hdf5_rgb_path,channels) == true );
//    channels.clear();
//    
//    // test if failed mode works
//    CPPUNIT_ASSERT(dataHandler.read("/dummy/path/that/hopefully/may/not/exist/",channels) == false );
//    channels.clear();
//    
//    CPPUNIT_ASSERT(dataHandler.read(_lf_4D_gt_path,channels) == true);
//    channels.clear();
}



void test_lightfield::test_tmp() {
    vector<string> cfgnames {
    test_lf_4D_wide+"rgb.cfg",
    test_lf_4D_high+"rgb.cfg",
    test_lf_3DH_wide+"rgb.cfg",
    test_lf_3DH_high+"rgb.cfg",
    test_lf_3DV_wide+"rgb.cfg",
    test_lf_3DV_high+"rgb.cfg",
    test_lf_CROSS_wide+"rgb.cfg",
    test_lf_CROSS_high+"rgb.cfg"};
    
    string path = "";
    int width = 0;
    float baseline_h = 0.0;
    double focal_length = 0.0;
    
    OpenLF::ConfigParser cfg;
    
    for(int n=0; n<cfgnames.size(); n++) {
        cout << "try to parse " << cfgnames[n] << endl;
        cfg.parse(cfgnames[n]);
        
        CPPUNIT_ASSERT(cfg.get_field("home",path));
        CPPUNIT_ASSERT(cfg.get_field("width",width));
        CPPUNIT_ASSERT(cfg.get_field("baseline_h",baseline_h));
        CPPUNIT_ASSERT(cfg.get_field("focal_length",focal_length));
        
        cout << path << " " << width << " " << baseline_h << " " << focal_length << " " << endl;
    }
    
    
    
    
    
    
    
}