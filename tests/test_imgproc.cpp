/*
* Copyright (c) 2014 Sven Wanner
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of 
* this software and associated documentation files (the "Software"), to deal in 
* the Software without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
* Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all 
* copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
    double mse = 0;
    vigra::MultiArray<2,float> tmp1(vigra::Shape2(3,3));
    vigra::MultiArray<2,float> tmp2(vigra::Shape2(3,3));
    vigra::MultiArray<2,float> tmp3(vigra::Shape2(3,3));
    
    for(int n=0; n<9; n++) {
        tmp1.data()[n] = n;
        tmp2.data()[n] = n;
        tmp3.data()[n] = n+0.1*n;
    }
    
    CPPUNIT_ASSERT(OpenLF::image::imgproc::MSE(tmp1,tmp2)==0.0);
    mse = OpenLF::image::imgproc::MSE(tmp1,tmp3);
    CPPUNIT_ASSERT((mse<0.226668 && mse>0.226666));
    
    map<string,double> mses;
    OpenLF::image::imgproc::MSE(lena_rgb,lena_rgb,mses);
    CPPUNIT_ASSERT(mses["r"]==0.0);
    CPPUNIT_ASSERT(mses["g"]==0.0);
    CPPUNIT_ASSERT(mses["b"]==0.0);
}