/*
 * File:   test_imgproc.cpp
 * Author: swanner
 *
 * Created on Mar 25, 2014, 11:06:07 AM
 */

#include "test_imgproc.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(test_imgproc);

test_imgproc::test_imgproc() {
}

test_imgproc::~test_imgproc() {
}

void test_imgproc::setUp() {
    imgnames["lena_rgb"] = test_data_dir+"lena_rgb.jpg";
    imgnames["lena_bw"] = test_data_dir+"lena_bw.jpg";
    imgnames["straw_rgb"] = test_data_dir+"straw_rgb.jpg";
    imgnames["straw_bw"] = test_data_dir+"straw_bw.jpg";
    
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["lena_rgb"],lena_rgb));
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["lena_bw"],lena_bw));
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["straw_rgb"],straw_rgb));
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["straw_bw"],straw_bw));
}

void test_imgproc::tearDown() {
}

void test_imgproc::test_shape_check() {
    CPPUNIT_ASSERT(OpenLF::image::imgproc::shape_check(lena_rgb["r"].shape(),lena_bw["bw"].shape()) == true);
    CPPUNIT_ASSERT(OpenLF::image::imgproc::shape_check(lena_rgb["r"].shape(),straw_bw["bw"].shape()) == false);
}

void test_imgproc::test_difference()
{
    vigra::MultiArray<2,float> tmp1(vigra::Shape2(lena_bw["bw"].width(),lena_bw["bw"].height()));
    tmp1 = lena_bw["bw"];
    vigra::MultiArray<2,float> tmp2(vigra::Shape2(lena_bw["bw"].width(),lena_bw["bw"].height()));
    tmp2 = lena_bw["bw"];
    vigra::MultiArray<2,float> tmp3(vigra::Shape2(lena_rgb["r"].width(),lena_rgb["r"].height()));
    tmp3 = lena_rgb["r"];
    
    vigra::MultiArray<2,float> res1(vigra::Shape2(lena_bw["bw"].width(),lena_bw["bw"].height()));
    OpenLF::image::imgproc::difference(tmp1,tmp2,res1);
    vigra::MultiArray<2,float> res2(vigra::Shape2(lena_bw["bw"].width(),lena_bw["bw"].height()));
    OpenLF::image::imgproc::difference(tmp1,tmp3,res2);
    
//    OpenLF::image::io::imsave(test_result_dir+"tmp1.png",tmp1);
//    OpenLF::image::io::imsave(test_result_dir+"tmp2.png",tmp2);
//    OpenLF::image::io::imsave(test_result_dir+"tmp3.png",tmp3);
//    OpenLF::image::io::imsave(test_result_dir+"res1.png",res1);
//    OpenLF::image::io::imsave(test_result_dir+"res2.png",res2);
    
    CPPUNIT_ASSERT(res1.sum<float>()==0.0);
    CPPUNIT_ASSERT(res2.sum<float>()<-44400.0);
    
    res1 = 0;
    res2 = 0;
    OpenLF::image::imgproc::difference(lena_bw,lena_bw,res1);
    OpenLF::image::imgproc::difference(lena_rgb,lena_rgb,res2);
    CPPUNIT_ASSERT(res1.sum<float>()==0.0);
    CPPUNIT_ASSERT(res2.sum<float>()==0.0);
}

void test_imgproc::test_abs_difference() 
{
    vigra::MultiArray<2,float> tmp1(vigra::Shape2(lena_bw["bw"].width(),lena_bw["bw"].height()));
    tmp1 = lena_bw["bw"];
    vigra::MultiArray<2,float> tmp2(vigra::Shape2(lena_bw["bw"].width(),lena_bw["bw"].height()));
    tmp2 = lena_bw["bw"];
    vigra::MultiArray<2,float> tmp3(vigra::Shape2(lena_rgb["r"].width(),lena_rgb["r"].height()));
    tmp3 = lena_rgb["r"];
    
    vigra::MultiArray<2,float> res1(vigra::Shape2(lena_bw["bw"].width(),lena_bw["bw"].height()));
    OpenLF::image::imgproc::abs_difference(tmp1,tmp2,res1);
    vigra::MultiArray<2,float> res2(vigra::Shape2(lena_bw["bw"].width(),lena_bw["bw"].height()));
    OpenLF::image::imgproc::abs_difference(tmp1,tmp3,res2);
    
//    OpenLF::image::io::imsave(test_result_dir+"tmp1.png",tmp1);
//    OpenLF::image::io::imsave(test_result_dir+"tmp2.png",tmp2);
//    OpenLF::image::io::imsave(test_result_dir+"tmp3.png",tmp3);
//    OpenLF::image::io::imsave(test_result_dir+"res1.png",res1);
//    OpenLF::image::io::imsave(test_result_dir+"res2.png",res2);
    
    
    CPPUNIT_ASSERT(res1.sum<float>()==0.0);
    CPPUNIT_ASSERT(res2.sum<float>()>46600.0);
    
    res1 = 0;
    res2 = 0;
    OpenLF::image::imgproc::abs_difference(lena_bw,lena_bw,res1);
    OpenLF::image::imgproc::abs_difference(lena_rgb,lena_rgb,res2);
    CPPUNIT_ASSERT(res1.sum<float>()==0.0);
    CPPUNIT_ASSERT(res2.sum<float>()==0.0);
}

void test_imgproc::test_MSE()
{
    
}