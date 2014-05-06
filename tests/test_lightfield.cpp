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
    
    imgnames["4D_high_bw"] = test_lf_4D_high+"4D_high_bw.png";
    imgnames["4D_high_rgb"] = test_lf_4D_high+"4D_high_rgb.png";
    imgnames["4D_wide_bw"] = test_lf_4D_wide+"4D_wide_bw.png";
    imgnames["4D_wide_rgb"] = test_lf_4D_wide+"4D_wide_rgb.png";
    
    imgnames["4D_high_rgb_h5"] = test_lf_4D_high+"4D_high_rgb.lf";
    
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
    
    cfgnames["4D_high_rgb_h5"] = test_lf_4D_high+"4D_high_rgb_h5.cfg";
    
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



void test_lightfield::test_epi_access()
{
    string p = test_result_dir+"4D_wide_rgb_epi_h.png";
    
    OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield();
    // test open from hdf5
    CPPUNIT_ASSERT(lf->open(cfgnames["4D_wide_rgb"]));
    
    // get epi channel
    vigra::MultiArrayView<2,float> epi_h = lf->getHorizontalEpiChannel("r",24,2,1);
    OpenLF::image::io::imsave(p,epi_h);

    p = test_result_dir+"4D_wide_rgb_epi_v.png";
    
    vigra::MultiArrayView<2,float> epi_v = lf->getVerticalEpiChannel("r",32,3,1);
    OpenLF::image::io::imsave(p,epi_v);
    
    
    lf = new OpenLF::lightfield::Lightfield();
    // test open from hdf5
    CPPUNIT_ASSERT(lf->open(cfgnames["3DH_wide_rgb"]));
    
    lf = new OpenLF::lightfield::Lightfield();
    // test open from hdf5
    CPPUNIT_ASSERT(lf->open(cfgnames["3DV_wide_rgb"]));
    
    lf = new OpenLF::lightfield::Lightfield();
    // test open from hdf5
    CPPUNIT_ASSERT(lf->open(cfgnames["CROSS_wide_rgb"]));
}



void test_lightfield::test_loxel_access()
{
    // test instancing via the default constructor and open
    OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield();
    // test open from hdf5
    CPPUNIT_ASSERT(lf->open(imgnames["4D_high_rgb_h5"]));
    
    float val = 0.0f;
    val = 255*lf->getLoxel(2,3,24,32,"r");
    CPPUNIT_ASSERT(val==107);
    val = 255*lf->getLoxel(2,3,24,32,"g");
    CPPUNIT_ASSERT(val==78);
    val = 255*lf->getLoxel(2,3,24,32,"b");
    CPPUNIT_ASSERT(val==44);
    
    vector<string> names {"r","g","b"};
    vector<float> vals;
    lf->getLoxel(2,3,24,32, names, vals);
    
    CPPUNIT_ASSERT(255*vals[0]==107);
    CPPUNIT_ASSERT(255*vals[1]==78);
    CPPUNIT_ASSERT(255*vals[2]==44);
}


void test_lightfield::test_instantiate_Lightfield()
{
    // test instancing via the default constructor and open
    OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield();
    // test open from hdf5
    CPPUNIT_ASSERT(lf->open(imgnames["4D_high_rgb_h5"]));
    
    // test has property method
    CPPUNIT_ASSERT(lf->hasProperty("width"));
    CPPUNIT_ASSERT(!lf->hasProperty("notThere"));
    CPPUNIT_ASSERT(lf->type()==LF_4D);
    
    // test getting properties
    float tmp; int tmp2;
    CPPUNIT_ASSERT(lf->getProperty("aperture",tmp));
    CPPUNIT_ASSERT(tmp==2.8f);
    CPPUNIT_ASSERT(lf->getProperty("height",tmp2));
    CPPUNIT_ASSERT(tmp2==64);
    
    // create pointer to a map and a MultiArray to keep the addresses of the lf data
    map< string,OpenLF::image::ImageChannel> *test_channels = NULL;
    OpenLF::image::ImageChannel *test_image = NULL;
    
    // get the pointers to the lf data
    lf->data(&test_channels);
    lf->data("g",&test_image);
    
    CPPUNIT_ASSERT(test_channels!=NULL);
    CPPUNIT_ASSERT(test_image!=NULL);
    
    string p = test_result_dir+"4D_high_rgb_h5.png";
    OpenLF::image::io::imsave(p,*test_channels);
    p = test_result_dir+"4D_high_rgb_h5_g.png";
    OpenLF::image::io::imsave(p,*test_image);
    
    test_channels->clear();
    test_image = NULL;
    
    // test open new data set from config file
    CPPUNIT_ASSERT(lf->open(cfgnames["4D_wide_rgb"]));
    
    // get the pointers to the lf data
    lf->data(&test_channels);
    lf->data("g",&test_image);
    
    CPPUNIT_ASSERT(test_channels!=NULL);
    CPPUNIT_ASSERT(test_image!=NULL);
    
    p = test_result_dir+"4D_wide_rgb.png";
    OpenLF::image::io::imsave(p,*test_channels);
    p = test_result_dir+"4D_wide_rgb_g.png";
    OpenLF::image::io::imsave(p,*test_image);
}