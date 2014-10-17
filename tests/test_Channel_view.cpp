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
    vigra::MultiArray<2,float> f_ma_2(vigra::Shape2(50,50),1.0f);
    vigra::MultiArray<2,float> ma_2(f_ma_2.shape(), f_ma_2.data());
    vigra::MultiArray<2,vigra::UInt8> int_ma_1 = vigra::MultiArray<2,vigra::UInt8>(vigra::Shape2(50,50),5);
    vigra::MultiArrayView<2,float> *ptr = &ma_2;
    vigra::MultiArrayView<2,float> **pixel = &ptr;
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
    
    CPPUNIT_ASSERT(int_ma_1.data()[0]==5);
    CPPUNIT_ASSERT_NO_THROW(ic_def4.init(50,50,int_ma_1.data()));
    CPPUNIT_ASSERT(ic_def4.externalData()==false);
    CPPUNIT_ASSERT(ic_def4.hasData()==true);
    float val = 5.0f/255.0f;
    CPPUNIT_ASSERT(ic_def4.data()[0]== val);
    
    CPPUNIT_ASSERT_NO_THROW(ic_def5.init(vigra::Shape2(50,50)));
    CPPUNIT_ASSERT(ic_def5.externalData()==false);
    CPPUNIT_ASSERT(ic_def5.hasData()==true);
    
    CPPUNIT_ASSERT_NO_THROW(ic_def6.init(vigra::Shape2(50,50),ma_1.data()));
    CPPUNIT_ASSERT(ic_def6.externalData()==true);
    CPPUNIT_ASSERT(ic_def6.hasData()==true);
    
    CPPUNIT_ASSERT_NO_THROW(ic_def7.init(vigra::Shape2(50,50),int_ma_1.data()));
    CPPUNIT_ASSERT(ic_def7.externalData()==false);
    CPPUNIT_ASSERT(ic_def7.hasData()==true);
    
    /**********************************************
     * the copy constructor 
     **********************************************/
    OpenLF::image::ImageChannel ic_copy(ic_def4);
    CPPUNIT_ASSERT(ic_copy.data()[0]==val);
    CPPUNIT_ASSERT(ic_copy.shape()==vigra::Shape2(50,50));
    CPPUNIT_ASSERT(ic_copy.hasData()==true);
    CPPUNIT_ASSERT(ic_copy.externalData()==false);
    CPPUNIT_ASSERT(ic_copy.image()->data()[0]==val);
    ic_copy.set(1.0f);
    CPPUNIT_ASSERT(ic_copy.data()[0]==1.0f);
    CPPUNIT_ASSERT(ic_def4.data()[0]==val);
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
    ic_def3.image(pixel);
    CPPUNIT_ASSERT((**pixel).data()[0]==5.0f);
    CPPUNIT_ASSERT(ic_def3.shape()==vigra::Shape2(50,50));
    float a = 5*50*50;
    CPPUNIT_ASSERT(ic_def3.sum()==a);
    CPPUNIT_ASSERT(ic_def3.width()==50);
    CPPUNIT_ASSERT(ic_def3.viewToColumn(2).shape()==vigra::Shape1(50));
    CPPUNIT_ASSERT(ic_def3.viewToColumn(2).data()[0]==5.0f);
    CPPUNIT_ASSERT(ic_def3.viewToRow(2).shape()==vigra::Shape1(50));
    CPPUNIT_ASSERT(ic_def3.viewToRow(2).data()[0]==5.0f);
    CPPUNIT_ASSERT(ic_def3.viewToROI(2,2,2,2).data()[0]==5.0f);
    CPPUNIT_ASSERT(ic_def3.viewToROI(2,2,2,2).shape()==vigra::Shape2(2,2));
    
    /**********************************************
     * operators
     **********************************************/
    //...
    
    /**********************************************
     * copy of a channel
     **********************************************/
    OpenLF::image::ImageChannel ic_setEqual = ic_def4;
    CPPUNIT_ASSERT(ic_setEqual == ic_def4);
    CPPUNIT_ASSERT(ic_setEqual.data()[0] == ic_def4.data()[0]);
    CPPUNIT_ASSERT(ic_setEqual.sum() == ic_def4.sum());
    CPPUNIT_ASSERT(ic_setEqual.hasData()==true);
    CPPUNIT_ASSERT(ic_setEqual.externalData()==false);
    ic_setEqual.set(3.0f);
    CPPUNIT_ASSERT(ic_def4.data()[0]==val);
    
    /**********************************************/
    
    OpenLF::image::ImageChannel ic_copy2;
    ic_copy2.deepcopy(ic_def3);
    CPPUNIT_ASSERT(ic_copy2.data()[0]==5.0f);
    CPPUNIT_ASSERT(ic_copy2.width()==50);
    CPPUNIT_ASSERT(ic_copy2.height()==50);
    ic_copy2.set(10.0f);
    CPPUNIT_ASSERT(ic_copy2.data()[0]==10.0f);
    CPPUNIT_ASSERT(ic_def3.data()[0]==5.0f);
    
    
    /**********************************************
     **********************************************
     ****** USE CASES
     **********************************************
     **********************************************/
    
    /* create a channel map */
    std::map<std::string,OpenLF::image::ImageChannel> img_channels;
    
    img_channels["r"] = OpenLF::image::ImageChannel();
    img_channels["r"].init(2,2,2.0f);
    img_channels["g"] = OpenLF::image::ImageChannel();
    img_channels["g"].init(2,2,3.0f);
    img_channels["b"] = OpenLF::image::ImageChannel();
    img_channels["b"].init(2,2,3.0f); 
    
    /* create imagechannel as a view */
    
    OpenLF::image::ImageChannel ic_1(img_channels["r"].shape(), img_channels["r"].data());
    
    vigra::MultiArray<2,float> MA(vigra::Shape2(10,10),4.0f);
    vigra::MultiArrayView<2,float> MAV = MA;
    OpenLF::image::ImageChannel fromMA(MA);
    OpenLF::image::ImageChannel fromMAV(MAV);
    CPPUNIT_ASSERT(fromMA.sum() == fromMAV.sum());
    
    /* create a deep copy */ 
    OpenLF::image::ImageChannel ic_copy10(ic_def3); //copy constructor
    
    OpenLF::image::ImageChannel ic_copy20; //default constructor first for Map handling
    ic_copy20.deepcopy(ic_def3);  
    CPPUNIT_ASSERT(ic_copy10.sum()==ic_copy20.sum());
    
    
}