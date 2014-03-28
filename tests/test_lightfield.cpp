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
//    _lf_4D_hdf5_rgb_path = test_lf_dir+"4D/"+"test_lf4D_rgb.h5";
//    _lf_4D_hdf5_bw_path = test_lf_dir+"4D/"+"test_lf4D_bw.h5";
//    _lf_4D_hdf5_rgb_out_path = test_result_dir+"test_lf4D_rgb_toH5.h5";
//    _lf_4D_hdf5_bw_out_path = test_result_dir+"test_lf4D_bw_toH5.h5";
//    _lf_4D_path = test_lf_dir+"4D/rgb/";
//    _lf_3DH_path = test_lf_dir+"3DH/rgb/";
//    _lf_3DV_path = test_lf_dir+"3DV/rgb/";
//    _lf_CROSS_path = test_lf_dir+"CROSS/rgb/";
//    _lf_4D_bw_path = test_lf_dir+"4D/bw/";
//    _lf_3DH_bw_path = test_lf_dir+"3DH/bw/";
//    _lf_3DV_bw_path = test_lf_dir+"3DV/bw/";
//    _lf_CROSS_bw_path = test_lf_dir+"CROSS/bw/";
//    _lf_4D_gt_path = test_lf_dir+"test_lf_4D_gt.png";
//    _lf_test_ftype = ".png";
    
    
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


void test_lightfield::test_IO_Pipeline_4D()
{
    string p;
    
    map< string, vigra::MultiArray<2,float> > channels;
    map< string, vigra::MultiArray<2,float> > channels_gt;
    OpenLF::lightfield::Properties properties;
    
    // result gt container
    vigra::MultiArray<2,float> result_4D_wide(vigra::Shape2(448,240));
    vigra::MultiArray<2,float> result_4D_high(vigra::Shape2(240,448));
    
    // pointer storing the FileHandler instance
    OpenLF::lightfield::io::DataHandler *dataHandler;

    LF_TYPE type;
    int width,height,cams_v,cams_h;
    float baseline_h,baseline_v,focal_length,DH,pixel_aspect_ratio,aperture,sensor_size_v,sensor_size_h;
    
    /*********************************************************************
     *                     Test from sequence 4D high     
     *********************************************************************/
    // init FileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["4D_high_rgb"],&properties);
    //dataHandler = fileHandler;
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"4D_high.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // test if config parser works
    CPPUNIT_ASSERT(properties.get_lftype(type));
    CPPUNIT_ASSERT(properties.get_field("width",width));
    CPPUNIT_ASSERT(properties.get_field("height",height));
    CPPUNIT_ASSERT(properties.get_field("cams_v",cams_v));
    CPPUNIT_ASSERT(properties.get_field("cams_h",cams_h));
    CPPUNIT_ASSERT(properties.get_field("baseline_h",baseline_h));
    CPPUNIT_ASSERT(properties.get_field("baseline_v",baseline_v));
    CPPUNIT_ASSERT(properties.get_field("focal_length",focal_length));
    CPPUNIT_ASSERT(properties.get_field("aperture",aperture));
    CPPUNIT_ASSERT(properties.get_field("pixel_aspect_ratio",pixel_aspect_ratio));
    CPPUNIT_ASSERT(properties.get_field("sensor_size_v",sensor_size_v));
    CPPUNIT_ASSERT(properties.get_field("sensor_size_h",sensor_size_h));
    
    CPPUNIT_ASSERT(type==LF_4D);
    CPPUNIT_ASSERT(width==48);
    CPPUNIT_ASSERT(height==64);
    CPPUNIT_ASSERT(cams_v==7);
    CPPUNIT_ASSERT(cams_h==5);
    CPPUNIT_ASSERT(baseline_h==0.1f);
    CPPUNIT_ASSERT(baseline_v==0.1f);
    CPPUNIT_ASSERT(focal_length==0.020f);
    CPPUNIT_ASSERT(aperture==2.8f);
    CPPUNIT_ASSERT(pixel_aspect_ratio==1.0f);
    CPPUNIT_ASSERT(sensor_size_v==0.002f);
    CPPUNIT_ASSERT(sensor_size_h==0.0025f);
    
    // make ground truth check of read data
    result_4D_high = 1;
    OpenLF::image::io::imread(imgnames["4D_high_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_4D_high);
    
    CPPUNIT_ASSERT(result_4D_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
  
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["4D_high_bw"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"4D_high.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_4D_high = 1;
    OpenLF::image::io::imread(imgnames["4D_high_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_4D_high);
    
    CPPUNIT_ASSERT(result_4D_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                   Test from sequence 4D wide     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["4D_wide_rgb"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"4D_wide.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_4D_wide = 1;
    OpenLF::image::io::imread(imgnames["4D_wide_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_4D_wide);
    
    CPPUNIT_ASSERT(result_4D_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["4D_wide_bw"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"4D_wide.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_4D_wide = 1;
    OpenLF::image::io::imread(imgnames["4D_wide_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_4D_wide);
    
    CPPUNIT_ASSERT(result_4D_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                       Test from 4D image high    
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["4D_high_rgb_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"4D_high_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_4D_high = 1;
    OpenLF::image::io::imread(imgnames["4D_high_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_4D_high);
    
    CPPUNIT_ASSERT(result_4D_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["4D_high_bw_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"4D_high_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_4D_high = 1;
    OpenLF::image::io::imread(imgnames["4D_high_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_4D_high);
    
    CPPUNIT_ASSERT(result_4D_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    /*********************************************************************
     *                       Test from 4D image wide     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["4D_wide_rgb_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"4D_wide_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_4D_wide = 1;
    OpenLF::image::io::imread(imgnames["4D_wide_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_4D_wide);
    
    CPPUNIT_ASSERT(result_4D_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["4D_wide_bw_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"4D_wide_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_4D_wide = 1;
    OpenLF::image::io::imread(imgnames["4D_wide_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_4D_wide);
    
    CPPUNIT_ASSERT(result_4D_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
}

void test_lightfield::test_IO_Pipeline_3DH() 
{
    string p;
    
    map< string, vigra::MultiArray<2,float> > channels;
    map< string, vigra::MultiArray<2,float> > channels_gt;
    OpenLF::lightfield::Properties properties;
    
    // result gt container
    vigra::MultiArray<2,float> result_3DH_wide(vigra::Shape2(448,48));
    vigra::MultiArray<2,float> result_3DH_high(vigra::Shape2(240,64));
    
    // pointer storing the FileHandler instance
    OpenLF::lightfield::io::DataHandler *dataHandler;

    
    
    /*********************************************************************
     *                       Test from 3DH image high     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DH_high_rgb_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DH_high_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DH_high = 1;
    OpenLF::image::io::imread(imgnames["3DH_high_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DH_high);
    
    CPPUNIT_ASSERT(result_3DH_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DH_high_bw_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DH_high_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DH_high = 1;
    OpenLF::image::io::imread(imgnames["3DH_high_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DH_high);
    
    CPPUNIT_ASSERT(result_3DH_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                       Test from 3DH sequence wide     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DH_wide_rgb"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DH_wide.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DH_wide = 1;
    OpenLF::image::io::imread(imgnames["3DH_wide_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DH_wide);
    
    CPPUNIT_ASSERT(result_3DH_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DH_wide_bw"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DH_wide.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DH_wide = 1;
    OpenLF::image::io::imread(imgnames["3DH_wide_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DH_wide);
    
    CPPUNIT_ASSERT(result_3DH_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                       Test from 3DH image high     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DH_high_rgb"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DH_high.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DH_high = 1;
    OpenLF::image::io::imread(imgnames["3DH_high_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DH_high);
    
    CPPUNIT_ASSERT(result_3DH_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DH_high_bw"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DH_high.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DH_high = 1;
    OpenLF::image::io::imread(imgnames["3DH_high_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DH_high);
    
    CPPUNIT_ASSERT(result_3DH_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                       Test from 3DH image wide     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DH_wide_rgb_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DH_wide_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DH_wide = 1;
    OpenLF::image::io::imread(imgnames["3DH_wide_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DH_wide);
    
    CPPUNIT_ASSERT(result_3DH_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DH_wide_bw_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DH_wide_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DH_wide = 1;
    OpenLF::image::io::imread(imgnames["3DH_wide_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DH_wide);
    
    CPPUNIT_ASSERT(result_3DH_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
}

void test_lightfield::test_IO_Pipeline_3DV() 
{
    string p;
    
    map< string, vigra::MultiArray<2,float> > channels;
    map< string, vigra::MultiArray<2,float> > channels_gt;
    OpenLF::lightfield::Properties properties;
    
    // result gt container
    vigra::MultiArray<2,float> result_3DV_wide(vigra::Shape2(240,64));
    vigra::MultiArray<2,float> result_3DV_high(vigra::Shape2(448,48));
    
    // pointer storing the FileHandler instance
    OpenLF::lightfield::io::DataHandler *dataHandler;

    
    
    /*********************************************************************
     *                       Test from 3DV image high     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DV_high_rgb_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DV_high_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DV_high = 1;
    OpenLF::image::io::imread(imgnames["3DV_high_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DV_high);
    
    CPPUNIT_ASSERT(result_3DV_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DV_high_bw_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DV_high_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DV_high = 1;
    OpenLF::image::io::imread(imgnames["3DV_high_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DV_high);
    
    CPPUNIT_ASSERT(result_3DV_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                       Test from 3DV sequence wide     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DV_wide_rgb"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DV_wide.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DV_wide = 1;
    OpenLF::image::io::imread(imgnames["3DV_wide_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DV_wide);
    
    CPPUNIT_ASSERT(result_3DV_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DV_wide_bw"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DV_wide.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DV_wide = 1;
    OpenLF::image::io::imread(imgnames["3DV_wide_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DV_wide);
    
    CPPUNIT_ASSERT(result_3DV_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                       Test from 3DV image high     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DV_high_rgb"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DV_high.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DV_high = 1;
    OpenLF::image::io::imread(imgnames["3DV_high_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DV_high);
    
    CPPUNIT_ASSERT(result_3DV_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DV_high_bw"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DV_high.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DV_high = 1;
    OpenLF::image::io::imread(imgnames["3DV_high_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DV_high);
    
    CPPUNIT_ASSERT(result_3DV_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                       Test from 3DV image wide     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DV_wide_rgb_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DV_wide_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DV_wide = 1;
    OpenLF::image::io::imread(imgnames["3DV_wide_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DV_wide);
    
    CPPUNIT_ASSERT(result_3DV_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["3DV_wide_bw_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"3DV_wide_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_3DV_wide = 1;
    OpenLF::image::io::imread(imgnames["3DV_wide_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_3DV_wide);
    
    CPPUNIT_ASSERT(result_3DV_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
}

void test_lightfield::test_IO_Pipeline_CROSS() 
{
    string p;
    
    map< string, vigra::MultiArray<2,float> > channels;
    map< string, vigra::MultiArray<2,float> > channels_gt;
    OpenLF::lightfield::Properties properties;
    
    // result gt container
    vigra::MultiArray<2,float> result_CROSS_wide(vigra::Shape2(448,112));
    vigra::MultiArray<2,float> result_CROSS_high(vigra::Shape2(448,112));
    
    // pointer storing the FileHandler instance
    OpenLF::lightfield::io::DataHandler *dataHandler;

    

    /*********************************************************************
     *                       Test from CROSS image high     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["CROSS_high_rgb_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"CROSS_high_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_CROSS_high = 1;
    OpenLF::image::io::imread(imgnames["CROSS_high_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_CROSS_high);
    
    CPPUNIT_ASSERT(result_CROSS_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["CROSS_high_bw_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"CROSS_high_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_CROSS_high = 1;
    OpenLF::image::io::imread(imgnames["CROSS_high_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_CROSS_high);
    
    CPPUNIT_ASSERT(result_CROSS_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                       Test from 3DV sequence wide     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["CROSS_wide_rgb"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"CROSS_wide.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_CROSS_wide = 1;
    OpenLF::image::io::imread(imgnames["CROSS_wide_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_CROSS_wide);
    
    CPPUNIT_ASSERT(result_CROSS_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["CROSS_wide_bw"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"CROSS_wide.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_CROSS_wide = 1;
    OpenLF::image::io::imread(imgnames["CROSS_wide_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_CROSS_wide);
    
    CPPUNIT_ASSERT(result_CROSS_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                       Test from 3DV image high     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["CROSS_high_rgb"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"CROSS_high.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_CROSS_high = 1;
    OpenLF::image::io::imread(imgnames["CROSS_high_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_CROSS_high);
    
    CPPUNIT_ASSERT(result_CROSS_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["CROSS_high_bw"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"CROSS_high.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_CROSS_high = 1;
    OpenLF::image::io::imread(imgnames["CROSS_high_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_CROSS_high);
    
    CPPUNIT_ASSERT(result_CROSS_high.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    /*********************************************************************
     *                       Test from 3DV image wide     
     *********************************************************************/
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["CROSS_wide_rgb_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"CROSS_wide_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_CROSS_wide = 1;
    OpenLF::image::io::imread(imgnames["CROSS_wide_rgb"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_CROSS_wide);
    
    CPPUNIT_ASSERT(result_CROSS_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    // init fileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["CROSS_wide_bw_sf"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
//    p = test_result_dir+"CROSS_wide_sf.png";
//    OpenLF::image::io::imsave(p,channels);
    
    // make ground truth check of read data
    result_CROSS_wide = 1;
    OpenLF::image::io::imread(imgnames["CROSS_wide_bw"],channels_gt);
    OpenLF::image::imgproc::abs_difference(channels,channels_gt,result_CROSS_wide);
    
    CPPUNIT_ASSERT(result_CROSS_wide.sum<int>()==0);
    channels.clear();
    channels_gt.clear();
    
    
    
    
    delete dataHandler;
}