/*
 * File:   test_channel.cpp
 * Author: swanner
 *
 * Created on Apr 3, 2014, 12:09:21 PM
 */

#include "test_channel.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(test_channel);

test_channel::test_channel() {
    imgnames["lena_rgb"] = test_data_dir+"lena_rgb.jpg";
    imgnames["lena_bw"] = test_data_dir+"lena_bw.jpg";
    imgnames["straw_rgb"] = test_data_dir+"straw_rgb.jpg";
    imgnames["straw_bw"] = test_data_dir+"straw_bw.jpg";
                   
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["lena_rgb"],lena_rgb));
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["lena_bw"],lena_bw));
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["straw_rgb"],straw_rgb));
    CPPUNIT_ASSERT(OpenLF::image::io::imread(imgnames["straw_bw"],straw_bw));
}

test_channel::~test_channel() {   
}

void test_channel::setUp() {
}

void test_channel::tearDown() {   
    cout << "\ntest finished" << endl;
}

void test_channel::test_initialization() {

    // init vigra arrays for testing
    vigra::MultiArray<2,float> tarr(vigra::Shape2(3,3));
    vigra::MultiArray<2,vigra::UInt8> tarr_ui8(vigra::Shape2(3,3));
    for(int y=0; y<3; y++) {
        for(int x=0; x<3; x++) {
            tarr(x,y) = (float)(x+1.0f);
            tarr_ui8(x,y) = 255;
        }
    }   
    CPPUNIT_ASSERT(tarr.sum<float>()==18.0f);
    CPPUNIT_ASSERT(tarr_ui8.sum<int>()==9*255);
    
    
    
    // get data pointer for testing
    float *tarr_ptr = tarr.data();
    vigra::UInt8 *tarr_ui8_ptr = tarr_ui8.data();
    
    // test init default
    OpenLF::image::ImageChannel ic_def;
    CPPUNIT_ASSERT(!ic_def.hasData());
    ic_def.init(3,3);
    CPPUNIT_ASSERT(ic_def.hasData());
    CPPUNIT_ASSERT(ic_def.sum()==0.0f);
    CPPUNIT_ASSERT(ic_def.width()==3);
    CPPUNIT_ASSERT(ic_def.height()==3);
    CPPUNIT_ASSERT(ic_def.shape()==vigra::Shape2(3,3));
    
    // test init by shape
    OpenLF::image::ImageChannel ic_sh(vigra::Shape2(3,3));
    CPPUNIT_ASSERT(ic_sh.hasData());
    CPPUNIT_ASSERT(ic_sh.sum()==0.0f);
    
    // test set value
    ic_sh.set(1.0f);
    CPPUNIT_ASSERT(ic_sh.sum()==9.0f);
    
    // test init using pointer 
    OpenLF::image::ImageChannel ic_ptr_f(3,3,tarr_ptr);
    OpenLF::image::ImageChannel ic_ptr_ui8(3,3,tarr_ui8_ptr);
    CPPUNIT_ASSERT(ic_ptr_f.sum()==18.0f);
    CPPUNIT_ASSERT(ic_ptr_ui8.sum()==9.0f);
    
    // test init using a vigra MultiArray
    OpenLF::image::ImageChannel ic_tarr(tarr);
    CPPUNIT_ASSERT(ic_tarr.sum()==18.0f);
    OpenLF::image::ImageChannel ic_tarr_ui8(tarr_ui8);
    CPPUNIT_ASSERT(ic_tarr_ui8.sum()==9.0f);
    
    // test get image and data
    vigra::MultiArray<2,float> *img_ptr_1 = NULL;
    vigra::MultiArray<2,float> *img_ptr_2 = NULL;
    float* data_ptr = NULL;
    
    ic_tarr.set(1.234);
    img_ptr_1 = ic_tarr.image();
    ic_tarr.image(&img_ptr_2);
    data_ptr = ic_tarr.data();
    
    int n=0;
    for(int y=0; y<3; y++) {
        for(int x=0; x<3; x++) {
            CPPUNIT_ASSERT(ic_tarr(x,y)==1.234f);
            CPPUNIT_ASSERT(ic_tarr(x,y)==1.234f);
            CPPUNIT_ASSERT(img_ptr_1->data()[n]==1.234f);
            CPPUNIT_ASSERT(img_ptr_2->data()[n]==1.234f);
            CPPUNIT_ASSERT(data_ptr[n]==1.234f);
            data_ptr[n] = 1.0f;
            CPPUNIT_ASSERT(ic_tarr.get(x,y)==1.0f);
            float tmp = 0.0f;
            ic_tarr.get(x,y,tmp);
            CPPUNIT_ASSERT(tmp==1.0f);
            n++;
        }
    }   
}



void test_channel::test_operator_overload()
{
    map<string,OpenLF::image::ImageChannel> channels;
    OpenLF::image::ImageChannel ic_res_1(3,3);
    OpenLF::image::ImageChannel ic_res_2(3,3);
    OpenLF::image::ImageChannel ic_res_3(4,4);
    
    // test '==' operator
    CPPUNIT_ASSERT(ic_res_1==ic_res_2);
    CPPUNIT_ASSERT(ic_res_1!=ic_res_3);
    
    // test '=' operator
    ic_res_1 = 0.0f;
    ic_res_2 = 0.0f;
    CPPUNIT_ASSERT(ic_res_1.sum()==0.0f);
    CPPUNIT_ASSERT(ic_res_2.sum()==0.0f);
    ic_res_1 = 1.0f;
    CPPUNIT_ASSERT(ic_res_1.sum()==(float)(ic_res_1.width()*ic_res_1.height()));
        
    // test '+' operator
    ic_res_1 = 0.0f;
    ic_res_1 = ic_res_1 + 1.0f;
    CPPUNIT_ASSERT(ic_res_1.sum()==(float)(ic_res_1.width()*ic_res_1.height()));
    
    // test '-' operator
    ic_res_1 = ic_res_1 - 1.0f;
    CPPUNIT_ASSERT(ic_res_1.sum()==0.0f);
    
    // test '+=' and '-=' operator
    ic_res_1 += 1.0f;
    CPPUNIT_ASSERT(ic_res_1.sum()==(float)(ic_res_1.width()*ic_res_1.height()));
    ic_res_1 -= 1.0f;
    CPPUNIT_ASSERT(ic_res_1.sum()==0.0f);
    
    ic_res_1 = 0.0f;
    for(int y=0; y<3; y++)
        for(int x=0; x<3; x++) 
            ic_res_2(x,y)=x;
    
    CPPUNIT_ASSERT(ic_res_1.sum()==0.0f);
    CPPUNIT_ASSERT(ic_res_2.sum()==9.0f);
    
    // test '+=' and '-=' pixelwise operator
    ic_res_1 += ic_res_2;
    CPPUNIT_ASSERT(ic_res_1.sum()==9.0f);
    
    ic_res_1 -= ic_res_2;
    CPPUNIT_ASSERT(ic_res_1.sum()==0.0f);
    
    ic_res_1 += 1.0f;
    CPPUNIT_ASSERT(ic_res_1.sum()==9.0f);
    
    // test '*=' and '/=' operator
    ic_res_1 *= 2.0f;
    CPPUNIT_ASSERT(ic_res_1.sum()==18.0f);
    
    ic_res_1 /= 2.0f;
    CPPUNIT_ASSERT(ic_res_1.sum()==9.0f);
    
    // test '*=' and '/=' pixelwise and () operator
    ic_res_1 = 1.0f;
    ic_res_1 *= ic_res_2;
    for(int y=0; y<3; y++)
        for(int x=0; x<3; x++) 
            CPPUNIT_ASSERT(ic_res_1(x,y)==x);
    
    ic_res_1 = 0.0f;
    ic_res_2 = 0.0f;
    for(int y=0; y<3; y++) {
        for(int x=0; x<3; x++) {
            ic_res_1(x,y)=x+1;
            ic_res_2(x,y)=x+1;
        }
    }
    
    ic_res_1 /= ic_res_2;
    for(int y=0; y<3; y++)
        for(int x=0; x<3; x++) 
            CPPUNIT_ASSERT(ic_res_1(x,y)==1.0f);
}

