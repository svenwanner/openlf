#include "image_test.hpp"
#include "image/image.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(image_test);

image_test::image_test() {
}

image_test::~image_test() {
}

void image_test::setUp() {
}

void image_test::tearDown() {
}

void image_test::testConstructor() {
    OpenLF::Image* img = new OpenLF::Image();
    
    CPPUNIT_ASSERT(img->width()==0);
    CPPUNIT_ASSERT(img->height()==0);
    CPPUNIT_ASSERT(img->channels()==0);
    CPPUNIT_ASSERT(img->shape()[0]==0);
    CPPUNIT_ASSERT(img->shape()[1]==0);
    CPPUNIT_ASSERT(img->name()=="");
    
    img = new OpenLF::Image(10,10,3);
    
    CPPUNIT_ASSERT(img->width()==10);
    CPPUNIT_ASSERT(img->height()==10);
    CPPUNIT_ASSERT(img->channels()==3);
    CPPUNIT_ASSERT(img->shape()[0]==10);
    CPPUNIT_ASSERT(img->shape()[1]==10);
    CPPUNIT_ASSERT(img->name()=="rgb");
    
    img = new OpenLF::Image(10,10,1);
    
    CPPUNIT_ASSERT(img->width()==10);
    CPPUNIT_ASSERT(img->height()==10);
    CPPUNIT_ASSERT(img->channels()==1);
    CPPUNIT_ASSERT(img->shape()[0]==10);
    CPPUNIT_ASSERT(img->shape()[1]==10);
    CPPUNIT_ASSERT(img->name()=="bw");
    
    img = new OpenLF::Image(10,10,2);
    
    CPPUNIT_ASSERT(img->width()==10);
    CPPUNIT_ASSERT(img->height()==10);
    CPPUNIT_ASSERT(img->channels()==2);
    CPPUNIT_ASSERT(img->shape()[0]==10);
    CPPUNIT_ASSERT(img->shape()[1]==10);
    CPPUNIT_ASSERT(img->name()=="vec");
    
    img = new OpenLF::Image(10,10,4);
    
    CPPUNIT_ASSERT(img->width()==10);
    CPPUNIT_ASSERT(img->height()==10);
    CPPUNIT_ASSERT(img->channels()==4);
    CPPUNIT_ASSERT(img->shape()[0]==10);
    CPPUNIT_ASSERT(img->shape()[1]==10);
    CPPUNIT_ASSERT(img->name()=="");
}


