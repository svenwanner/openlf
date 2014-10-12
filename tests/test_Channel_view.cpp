/*
 * File:   test_Channel_view.cpp 
 * Author: swanner
 *
 * Created on May 19, 2014, 9:32:19 AM
 */

#include "test_Channel_view.hpp" 
#include "iostream"
#include "OpenLF/image/Channel.hpp"
using namespace::std;


CPPUNIT_TEST_SUITE_REGISTRATION(test_Channel_view); 

test_Channel_view::test_Channel_view() {
}

test_Channel_view::~test_Channel_view() { 
}

void test_Channel_view::setUp() { 
    

}

void test_Channel_view::tearDown() { 
    cout << "\n\n all tests finished" << endl;
}

void test_Channel_view::testMethod() { 
    vigra::MultiArray<2,float> ma_1 = vigra::MultiArray<2,float>(vigra::Shape2(50,50),5.0f);
    vigra::MultiArray<2,float> int_ma_1 = vigra::MultiArray<2,vigra::UInt8>(vigra::Shape2(50,50),5);
    vigra::MultiArray<2,float> *ptr = &ma_1;
    vigra::MultiArray<2,float> **pixel = &ptr;
    float value = 1.0f;
    OpenLF::image::ImageChannel ic_def1;

    
    /**************************************
     * default constructor
     **************************************/
    
    CPPUNIT_ASSERT_THROW(ic_def1.image(),OpenLF_Exception); 
    CPPUNIT_ASSERT(ic_def1.externalData()==false);
    CPPUNIT_ASSERT(ic_def1.hasData()==false);
    CPPUNIT_ASSERT_THROW(ic_def1.data(),OpenLF_Exception); 
    CPPUNIT_ASSERT(ic_def1.externalData()==false);
    CPPUNIT_ASSERT(ic_def1.hasData()==false);
    CPPUNIT_ASSERT_THROW(ic_def1.get(1,1),OpenLF_Exception);
    CPPUNIT_ASSERT(ic_def1.externalData()==false);
    CPPUNIT_ASSERT(ic_def1.hasData()==false);
    CPPUNIT_ASSERT_THROW(ic_def1.get(1,1,value),OpenLF_Exception);
    CPPUNIT_ASSERT(ic_def1.externalData()==false);
    CPPUNIT_ASSERT(ic_def1.hasData()==false);
    CPPUNIT_ASSERT_THROW(ic_def1.image(pixel),OpenLF_Exception);
    CPPUNIT_ASSERT(ic_def1.externalData()==false);
    CPPUNIT_ASSERT(ic_def1.hasData()==false);
    CPPUNIT_ASSERT_THROW(ic_def1.set(5.0f),OpenLF_Exception);
    CPPUNIT_ASSERT(ic_def1.externalData()==false);
    CPPUNIT_ASSERT(ic_def1.hasData()==false);
    CPPUNIT_ASSERT_THROW(ic_def1.viewToColumn(5),OpenLF_Exception);
    CPPUNIT_ASSERT(ic_def1.externalData()==false);
    CPPUNIT_ASSERT(ic_def1.hasData()==false);
    CPPUNIT_ASSERT_THROW(ic_def1.viewToRow(5),OpenLF_Exception);
    CPPUNIT_ASSERT(ic_def1.externalData()==false);
    CPPUNIT_ASSERT(ic_def1.hasData()==false);
    CPPUNIT_ASSERT_THROW(ic_def1.viewToROI(1,1,2,2),OpenLF_Exception);
    CPPUNIT_ASSERT(ic_def1.externalData()==false);
    CPPUNIT_ASSERT(ic_def1.hasData()==false);
    
    /***************************************
     * initialization
     ***************************************/
    
    OpenLF::image::ImageChannel ic_def2, ic_def3, ic_def4, ic_def5, ic_def6, ic_def7;
    
    CPPUNIT_ASSERT_NO_THROW(ic_def2.init(50,50));
    CPPUNIT_ASSERT(ic_def2.externalData()==false);
    CPPUNIT_ASSERT(ic_def2.hasData()==true);
    
    CPPUNIT_ASSERT_NO_THROW(ic_def3.init(50,50, ma_1.data()));
    CPPUNIT_ASSERT(ic_def3.externalData()==true);
    CPPUNIT_ASSERT(ic_def3.hasData()==true);
    
    CPPUNIT_ASSERT_NO_THROW(ic_def4.init(50,50,int_ma_1.data()));
    CPPUNIT_ASSERT(ic_def4.externalData()==true);
    CPPUNIT_ASSERT(ic_def4.hasData()==true);
    
    CPPUNIT_ASSERT_NO_THROW(ic_def5.init(vigra::Shape2(50,50)));
    CPPUNIT_ASSERT(ic_def5.externalData()==false);
    CPPUNIT_ASSERT(ic_def5.hasData()==true);
    
    CPPUNIT_ASSERT_NO_THROW(ic_def6.init(vigra::Shape2(50,50),ma_1.data()));
    CPPUNIT_ASSERT(ic_def6.externalData()==true);
    CPPUNIT_ASSERT(ic_def6.hasData()==true);
    
    CPPUNIT_ASSERT_NO_THROW(ic_def7.init(vigra::Shape2(50,50),int_ma_1.data()));
    CPPUNIT_ASSERT(ic_def7.externalData()==true);
    CPPUNIT_ASSERT(ic_def7.hasData()==true);
    
    /**********************************************
     * the copy constructor 
     **********************************************/
    
    
    /**********************************************
     * test methods
     **********************************************/
    float *f_pointer;
    f_pointer = ic_def3.data();
    CPPUNIT_ASSERT(f_pointer[2]==5.0f);
    CPPUNIT_ASSERT(ic_def3.get(3,3)==5.0f);
    ic_def3.get(3,3,value);
    CPPUNIT_ASSERT(value==5.0f);
    CPPUNIT_ASSERT(ic_def3.height()==50);
    CPPUNIT_ASSERT(ic_def3.data()[0]==5.0f);
    /*ic_def3.image(pixel);
    CPPUNIT_ASSERT(pixel->);
    ic_def3.set()
    ic_def3.shape()
    ic_def3.sum()
    ic_def3.width()
    ic_def3.viewToColumn()
    ic_def3.viewToROI()
    ic_def3.viewToRow()*/
    /**********************************************
     * use cases
     **********************************************/
    
    /* build a channel map */
    
    /* use channel as view */
    
    /* create a copy */
    
    /* use channel as multiarray */
    OpenLF::image::ImageChannel ic_marray;
    ic_marray.deepcopy(ic_def3);
    CPPUNIT_ASSERT(ic_marray.data()[0]==5.0f);
    CPPUNIT_ASSERT(ic_marray.width()==50);
    CPPUNIT_ASSERT(ic_marray.height()==50);
    ic_marray.set(10.0f);
    CPPUNIT_ASSERT(ic_marray.data()[0]==10.0f);
    CPPUNIT_ASSERT(ic_def3.data()[0]==5.0f);
    
    /* create a copy */
    
    /*
    float t_2_pixel = ic_1.data()[0];
    float t_1_tmp = ic_1.image()->data()[0];
    
    float t_end = 15.0f;
    
    vigra::MultiArray<2,float> ma1= vigra::MultiArray<2,float>(vigra::Shape2(5,5));
    ma1.init(5.0f);
    vigra::MultiArrayView<2,float> mav1 = ma1;
    float f_mav1 = mav1.data()[1];
    float f_ma1 = ma1.data()[1];
    mav1 = 3.0f; 
    f_mav1 = mav1.data()[1];
    f_ma1 = ma1.data()[1];
    vigra::MultiArray<2,float> ma2 = vigra::MultiArray<2,float>(vigra::Shape2(5,5));
    ma2.init(6.0f);
    mav1 = ma2;
    f_mav1 = mav1.data()[1];
    f_ma1 = ma1.data()[1];
    vigra::MultiArray<2,float> ma3 = vigra::MultiArray<2,float>(vigra::Shape2(5,5));
    ma3.init(8.0f);
    vigra::MultiArrayView<2,float> mav3 = ma3;

    
    f_mav1 = mav1.data()[1];
    f_ma1 = ma1.data()[1];
    OpenLF::image::ImageChannel Channel1 = OpenLF::image::ImageChannel();
    CPPUNIT_ASSERT(Channel1.hasData()==false); //prone to error
    
    
    float f_end = 15.0f;
    
    //channel tests
    vigra::MultiArray<2,float> tarr(vigra::Shape2(3,3));

    //Kiryl: test ImageChannel as view
    OpenLF::image::ImageChannel ic_view;
    ic_view.init(3,3);
    CPPUNIT_ASSERT(ic_view.sum()==0.0f);
    
    
    //test init by width, height
    OpenLF::image::ImageChannel ic_wh;
    ic_wh.init(4,5);
    CPPUNIT_ASSERT(ic_wh.hasData());
    CPPUNIT_ASSERT(ic_wh.sum()==0.0f);
    CPPUNIT_ASSERT(ic_wh.width()==4);
    CPPUNIT_ASSERT(ic_wh.height()==5);
    CPPUNIT_ASSERT(ic_wh.shape()==vigra::Shape2(4,5));
    ic_wh.set(2.0f);
    CPPUNIT_ASSERT(ic_wh.sum()==40.0f);
    CPPUNIT_ASSERT(ic_wh.get(2,2)==2.0f);
    
    float test_float = 3.0f;
    ic_wh.get(2,2, test_float);
    CPPUNIT_ASSERT(test_float==2.0f);
    
    
    
    
    //test ROI
    
    OpenLF::image::ImageChannel ic_10;
    ic_10.init(10,10);

    ic_10 = 1.0f;
    CPPUNIT_ASSERT(ic_10.sum() == 100);
    
    for(int y=2; y<10; y++) {
        for(int x=2; x<10; x++) {
            ic_10(x,y) = 2.0f;   
        }
    } 
    CPPUNIT_ASSERT(ic_10.get(0,0) == 1.0f);
    CPPUNIT_ASSERT(ic_10.get(2,2) == 2.0f);
    
    OpenLF::image::ImageChannel ic_11 = OpenLF::image::ImageChannel(ic_10.viewToROI(0,0,4,4));
    CPPUNIT_ASSERT(ic_11.sum() == 20.0f);
    
    OpenLF::image::ImageChannel ic_12 = OpenLF::image::ImageChannel(ic_10.viewToROI(0,0,2,2));
    CPPUNIT_ASSERT(ic_12.sum() == 4.0f);
      
    OpenLF::image::ImageChannel ic_13 = OpenLF::image::ImageChannel(ic_10.viewToROI(2,2,2,2));
    CPPUNIT_ASSERT(ic_13.sum() == 8.0f);

    // test ViewToRow
   
    vigra::MultiArray<1,float>* tarr4_ptr = NULL;
    vigra::MultiArray<1,float>* tarr5_ptr = NULL;
    *tarr4_ptr = ic_10.viewToRow(1);
    *tarr5_ptr = ic_10.viewToRow(3);
    
    float sum4 = 0.0f;
    for(int n=0;n<10;n++) {
        sum4 += tarr4_ptr->data()[n];
    }
    float sum5 = 0.0f;
    for(int n=0;n<10;n++) {
        sum5 += tarr5_ptr->data()[n];
    }
    CPPUNIT_ASSERT(sum4 == 18.0f);
    CPPUNIT_ASSERT(sum5 == 20.0f);
    
    // test ViewToColumn
    vigra::MultiArray<1,float> *tarr6_ptr = NULL;
    vigra::MultiArray<1,float> *tarr7_ptr = NULL;
    *tarr6_ptr = ic_10.viewToRow(1);
    *tarr7_ptr = ic_10.viewToRow(3);
    tarr6_ptr = tarr4_ptr;
    tarr7_ptr = tarr5_ptr;
    float sum6 = 0.0f;
    for(int n=0;n<10;n++) {
        sum6 += tarr6_ptr->data()[n];
    }
    float sum7 = 0.0f;
    for(int n=0;n<10;n++) {
        sum7 += tarr7_ptr->data()[n];
    }
    CPPUNIT_ASSERT(sum6 == 18.0f);
    CPPUNIT_ASSERT(sum7 == 20.0f);   
    */
    
    
}  


