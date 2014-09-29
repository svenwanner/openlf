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
}

void test_imgproc::tearDown() {
    cout << "\n\nall tests finished" << endl;
}


void test_imgproc::test_diff_abs_mse()
{   
    map<string,OpenLF::image::ImageChannel> channels;
    OpenLF::image::io::imread(imgnames["lena_rgb"],channels);
    OpenLF::image::ImageChannel ic_r = channels["r"];
    OpenLF::image::ImageChannel ic_g = channels["g"];
    OpenLF::image::ImageChannel ic_b = channels["b"];
    
    OpenLF::image::ImageChannel ic_res_1 = OpenLF::image::ImageChannel(channels["b"].shape());
    OpenLF::image::ImageChannel ic_res_2 = OpenLF::image::ImageChannel(channels["b"].shape());
    
    // test difference 
    ic_res_1 = 1.0f;
    ic_res_2 = 1.0f; 
    
    OpenLF::image::imgproc::difference(ic_b,ic_r,ic_res_1);
    OpenLF::image::imgproc::difference(ic_r,ic_r,ic_res_2);
    
        

    CPPUNIT_ASSERT(ic_res_1.sum()>-70000 && ic_res_1.sum()<-68000);
    CPPUNIT_ASSERT(ic_res_2.sum()==0.0f);
    
    
    // test abs_difference 
    ic_res_1.set(1.0f);
    ic_res_2.set(1.0f);
    
    OpenLF::image::imgproc::abs_difference(ic_r,ic_b,ic_res_1);
    OpenLF::image::imgproc::abs_difference(ic_r,ic_r,ic_res_2);
    
    CPPUNIT_ASSERT(ic_res_1.sum()<70000 && ic_res_1.sum()>68000);
    CPPUNIT_ASSERT(ic_res_2.sum()==0.0f);
    
    // test mse 
    double mse = 0;
    OpenLF::image::ImageChannel ic_tmp_1(3,3);
    OpenLF::image::ImageChannel ic_tmp_2(3,3);
    OpenLF::image::ImageChannel ic_tmp_3(3,3);
    
    int n=0;
    for(int y=0; y<3; y++) {
        for(int x=0; x<3; x++) {
            ic_tmp_1(x,y)=n;
            ic_tmp_2(x,y)=n;
            ic_tmp_3(x,y)=n+0.1*n;
            n++;
        }
    }
    
    CPPUNIT_ASSERT(OpenLF::image::imgproc::MSE(ic_tmp_1,ic_tmp_2)==0.0);
    mse = OpenLF::image::imgproc::MSE(ic_tmp_1,ic_tmp_3);
    
    CPPUNIT_ASSERT((mse<0.2267 && mse>0.2266));
    
    map<string,double> mses;
    OpenLF::image::imgproc::MSE(channels,channels,mses);
    CPPUNIT_ASSERT(mses["r"]==0.0);
    CPPUNIT_ASSERT(mses["g"]==0.0);
    CPPUNIT_ASSERT(mses["b"]==0.0);
}
