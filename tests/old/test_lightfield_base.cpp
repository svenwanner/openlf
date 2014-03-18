/*
 * File:   test_lightfield_base.cpp
 * Author: swanner
 *
 * Created on Mar 12, 2014, 2:36:07 PM
 */

#include "test_lightfield_base.hpp"
#include "lightfield/lightfield_base.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(test_lightfield_base);

test_lightfield_base::test_lightfield_base() {
}

test_lightfield_base::~test_lightfield_base() {
}

void test_lightfield_base::setUp() {
}

void test_lightfield_base::tearDown() {
}

void test_lightfield_base::testConstructor() {
    
    // test default constructor
    OpenLF::Lightfield_base* lf = new OpenLF::Lightfield_base();
    CPPUNIT_ASSERT(lf->width()==-1);
    CPPUNIT_ASSERT(lf->height()==-1);
    CPPUNIT_ASSERT(lf->cams_h()==-1);
    CPPUNIT_ASSERT(lf->cams_v()==-1);
    CPPUNIT_ASSERT(lf->channels()==0);
    CPPUNIT_ASSERT(lf->type()=="");
    CPPUNIT_ASSERT(lf->focal_length()==-1);
    CPPUNIT_ASSERT(lf->baseline_h()==-1);
    CPPUNIT_ASSERT(lf->baseline_v()==-1);
    CPPUNIT_ASSERT(lf->valid()==false);
    lf->~Lightfield_base();
    
    // test empty light field constructor 4D grayscale
    lf = new OpenLF::Lightfield_base(100, 200, 7, 5, 1, "4D");
    CPPUNIT_ASSERT(lf->width() == 100);
    CPPUNIT_ASSERT(lf->height() == 200);
    CPPUNIT_ASSERT(lf->cams_h() == 7);
    CPPUNIT_ASSERT(lf->cams_v() == 5);
    CPPUNIT_ASSERT(lf->channels() == 1);
    CPPUNIT_ASSERT(lf->type() == "4D");
    CPPUNIT_ASSERT(lf->focal_length() == -1);
    CPPUNIT_ASSERT(lf->baseline_h() == -1);
    CPPUNIT_ASSERT(lf->baseline_v() == -1);
    CPPUNIT_ASSERT(lf->valid() == true);
    
    // test MultiArray initialization
    vigra::Shape4 shape = lf->shape();
    cout << shape[0] << " " << shape[1] << " " << shape[2] << " " << shape[3] << endl;
    
    lf->~Lightfield_base();
    
    // test empty light field constructor 4D rgb
    lf = new OpenLF::Lightfield_base(200, 100, 5, 7, 3, "4D");
    CPPUNIT_ASSERT(lf->width() == 200);
    CPPUNIT_ASSERT(lf->height() == 100);
    CPPUNIT_ASSERT(lf->cams_h() == 5);
    CPPUNIT_ASSERT(lf->cams_v() == 7);
    CPPUNIT_ASSERT(lf->channels() == 3);
    CPPUNIT_ASSERT(lf->type() == "4D");
    CPPUNIT_ASSERT(lf->focal_length() == -1);
    CPPUNIT_ASSERT(lf->baseline_h() == -1);
    CPPUNIT_ASSERT(lf->baseline_v() == -1);
    CPPUNIT_ASSERT(lf->valid() == true);
    
    // test deleting channels via index
    lf->delete_channel(1);
    CPPUNIT_ASSERT(lf->channels() == 2);
    CPPUNIT_ASSERT(lf->get_label(0) == "r");
    CPPUNIT_ASSERT(lf->get_label(1) == "b");
    
    //test deleting channel via label
    lf->delete_channel("b");
    CPPUNIT_ASSERT(lf->channels() == 1);
    CPPUNIT_ASSERT(lf->get_label(0) == "r");
    lf->~Lightfield_base();
    
    // test empty light field constructor 4D grayscale
    lf = new OpenLF::Lightfield_base(100, 100, 7, 5, 1, "4D");
    
    CPPUNIT_ASSERT(lf->width() == 100);
    CPPUNIT_ASSERT(lf->height() == 100);
    CPPUNIT_ASSERT(lf->cams_h() == 7);
    CPPUNIT_ASSERT(lf->cams_v() == 5);
    CPPUNIT_ASSERT(lf->channels() == 1);
    CPPUNIT_ASSERT(lf->type() == "4D");
    CPPUNIT_ASSERT(lf->focal_length() == -1);
    CPPUNIT_ASSERT(lf->baseline_h() == -1);
    CPPUNIT_ASSERT(lf->baseline_v() == -1);
    CPPUNIT_ASSERT(lf->valid() == true);
    
    lf->~Lightfield_base();
    
    cout << "test finished" << endl;
    
    
}


