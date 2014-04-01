/*
 * File:   test_lightfield.cpp
 * Author: swanner
 *
 * Created on Mar 14, 2014, 10:10:32 PM
 */

#include "test_lightfield.hpp"
#include "image/imgproc.hpp"




CPPUNIT_TEST_SUITE_REGISTRATION(test_lightfield);

test_lightfield::test_lightfield() {
}

test_lightfield::~test_lightfield() {
}

void test_lightfield::setUp() {
    
    imgnames["4D_high_bw"] = test_lf_4D_high+"4D_high_bw.png";
    imgnames["4D_high_rgb"] = test_lf_4D_high+"4D_high_rgb.png";
    imgnames["4D_wide_bw"] = test_lf_4D_wide+"4D_wide_bw.png";
    imgnames["4D_wide_rgb"] = test_lf_4D_wide+"4D_wide_rgb.png";
    
    imgnames["3DH_high_bw"] = test_lf_3DH_high+"3DH_high_bw.png";
    imgnames["3DH_high_rgb"] = test_lf_3DH_high+"3DH_high_rgb.png";
    imgnames["3DH_wide_bw"] = test_lf_3DH_wide+"3DH_wide_bw.png";
    imgnames["3DH_wide_rgb"] = test_lf_3DH_wide+"3DH_wide_rgb.png";
    
    imgnames["3DV_high_bw"] = test_lf_3DV_high+"3DV_high_bw.png";
    imgnames["3DV_high_rgb"] = test_lf_3DV_high+"3DV_high_rgb.png";
    imgnames["3DV_wide_bw"] = test_lf_3DV_wide+"3DV_wide_bw.png";
    imgnames["3DV_wide_rgb"] = test_lf_3DV_wide+"3DV_wide_rgb.png";
    
    imgnames["CROSS_high_bw"] = test_lf_CROSS_high+"CROSS_high_bw.png";
    imgnames["CROSS_high_rgb"] = test_lf_CROSS_high+"CROSS_high_rgb.png";
    imgnames["CROSS_wide_bw"] = test_lf_CROSS_wide+"CROSS_wide_bw.png";
    imgnames["CROSS_wide_rgb"] = test_lf_CROSS_wide+"CROSS_wide_rgb.png";
    
     
    cfgnames["4D_high_bw"] = test_lf_4D_high+"bw.cfg";
    cfgnames["4D_wide_bw"] = test_lf_4D_wide+"bw.cfg";
    cfgnames["4D_high_rgb"] = test_lf_4D_high+"rgb.cfg";
    cfgnames["4D_wide_rgb"] = test_lf_4D_wide+"rgb.cfg";
    cfgnames["4D_high_bw_sf"] = test_lf_4D_high+"4D_high_bw.cfg";
    cfgnames["4D_wide_bw_sf"] = test_lf_4D_wide+"4D_wide_bw.cfg";
    cfgnames["4D_high_rgb_sf"] = test_lf_4D_high+"4D_high_rgb.cfg";
    cfgnames["4D_wide_rgb_sf"] = test_lf_4D_wide+"4D_wide_rgb.cfg";
    
    cfgnames["3DH_high_bw"] = test_lf_3DH_high+"bw.cfg";
    cfgnames["3DH_wide_bw"] = test_lf_3DH_wide+"bw.cfg";
    cfgnames["3DH_high_rgb"] = test_lf_3DH_high+"rgb.cfg";
    cfgnames["3DH_wide_rgb"] = test_lf_3DH_wide+"rgb.cfg";
    cfgnames["3DH_high_bw_sf"] = test_lf_3DH_high+"3DH_high_bw.cfg";
    cfgnames["3DH_wide_bw_sf"] = test_lf_3DH_wide+"3DH_wide_bw.cfg";
    cfgnames["3DH_high_rgb_sf"] = test_lf_3DH_high+"3DH_high_rgb.cfg";
    cfgnames["3DH_wide_rgb_sf"] = test_lf_3DH_wide+"3DH_wide_rgb.cfg";
     
    cfgnames["3DV_high_bw"] = test_lf_3DV_high+"bw.cfg";
    cfgnames["3DV_wide_bw"] = test_lf_3DV_wide+"bw.cfg";
    cfgnames["3DV_high_rgb"] = test_lf_3DV_high+"rgb.cfg";
    cfgnames["3DV_wide_rgb"] = test_lf_3DV_wide+"rgb.cfg"; 
    cfgnames["3DV_high_bw_sf"] = test_lf_3DV_high+"3DV_high_bw.cfg";
    cfgnames["3DV_wide_bw_sf"] = test_lf_3DV_wide+"3DV_wide_bw.cfg";
    cfgnames["3DV_high_rgb_sf"] = test_lf_3DV_high+"3DV_high_rgb.cfg";
    cfgnames["3DV_wide_rgb_sf"] = test_lf_3DV_wide+"3DV_wide_rgb.cfg";
    
    cfgnames["CROSS_high_bw"] = test_lf_CROSS_high+"bw.cfg";
    cfgnames["CROSS_wide_bw"] = test_lf_CROSS_wide+"bw.cfg";
    cfgnames["CROSS_high_rgb"] = test_lf_CROSS_high+"rgb.cfg";
    cfgnames["CROSS_wide_rgb"] = test_lf_CROSS_wide+"rgb.cfg";
    cfgnames["CROSS_high_bw_sf"] = test_lf_CROSS_high+"CROSS_high_bw.cfg";
    cfgnames["CROSS_wide_bw_sf"] = test_lf_CROSS_wide+"CROSS_wide_bw.cfg";
    cfgnames["CROSS_high_rgb_sf"] = test_lf_CROSS_high+"CROSS_high_rgb.cfg";
    cfgnames["CROSS_wide_rgb_sf"] = test_lf_CROSS_wide+"CROSS_wide_rgb.cfg";
}

void test_lightfield::tearDown() {
    cout << "\n\ntest suite runs through!" << endl;
}





void test_lightfield::test_instantiate_Lightfield()
{
    // instantiate a lightfield 
    OpenLF::lightfield::Lightfield lf(cfgnames["4D_high_rgb"]);
    
    // create pointer to a map and a MultiArray to keep the addresses of the lf data
    map< string, vigra::MultiArray<2,float> > *test_channels = NULL;
    vigra::MultiArray<2,float> *test_image = NULL;
    
    // get the pointers to the lf data
    lf.data(&test_channels);
    lf.data("b",&test_image);
    
    CPPUNIT_ASSERT(test_channels!=NULL);
    CPPUNIT_ASSERT(test_image!=NULL);
    
    string p = test_result_dir+"channels_from_lf.png";
    OpenLF::image::io::imsave(p,*test_channels);
    p = test_result_dir+"r_channel_from_lf.png";
    OpenLF::image::io::imsave(p,*test_image);
}