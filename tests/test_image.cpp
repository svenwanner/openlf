#include "test_image.hpp"
#include "image/image.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(image_test);

image_test::image_test() {
}

image_test::~image_test() {
}

void image_test::setUp() {
    lena_rgb_path = test_data_dir+"lena_rgb.jpg";
    lena_bw_path = test_data_dir+"lena_bw.jpg";
}

void image_test::tearDown() {
}

void image_test::testConstructor() {
    OpenLF::Image* img = new OpenLF::Image();
    
    CPPUNIT_ASSERT(img->width()==0);
    CPPUNIT_ASSERT(img->height()==0);
    CPPUNIT_ASSERT(img->channels()==0);
    CPPUNIT_ASSERT(img->label()=="");
    img->~Image();
    
    img = new OpenLF::Image(10,10,3);
    
    CPPUNIT_ASSERT(img->width()==10);
    CPPUNIT_ASSERT(img->height()==10);
    CPPUNIT_ASSERT(img->channels()==3);
    CPPUNIT_ASSERT(img->label()=="rgb");
    img->~Image();
    
    img = new OpenLF::Image(10,10,1);
    
    CPPUNIT_ASSERT(img->width()==10);
    CPPUNIT_ASSERT(img->height()==10);
    CPPUNIT_ASSERT(img->channels()==1);
    CPPUNIT_ASSERT(img->label()=="bw");
    img->~Image();
    
    img = new OpenLF::Image(10,10,2);
    
    CPPUNIT_ASSERT(img->width()==10);
    CPPUNIT_ASSERT(img->height()==10);
    CPPUNIT_ASSERT(img->channels()==2);
    CPPUNIT_ASSERT(img->label()=="vec");
    img->~Image();
    
    img = new OpenLF::Image(10,10,4);
    
    CPPUNIT_ASSERT(img->width()==10);
    CPPUNIT_ASSERT(img->height()==10);
    CPPUNIT_ASSERT(img->channels()==4);
    CPPUNIT_ASSERT(img->label()=="");
    img->~Image();
    
    
    // test gray image loading from file
    vector<float> px;
    float total_diff = 0.0f;
    
    img = new OpenLF::Image(lena_bw_path);
    
    CPPUNIT_ASSERT(img->width()==512);
    CPPUNIT_ASSERT(img->height()==512);
    CPPUNIT_ASSERT(img->channels()==1);
    CPPUNIT_ASSERT(img->label()=="bw");
    
    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
        img->get_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i],px);
        total_diff = total_diff + abs(LENA_TEST_COL_BW[i]/255.0f-px[0]);
    }
    CPPUNIT_ASSERT(total_diff<1e-9);
    img->~Image();
    
    // test rgb image loading from file
    total_diff = 0.0f;
    img = new OpenLF::Image(lena_rgb_path);
    
    CPPUNIT_ASSERT(img->width()==512);
    CPPUNIT_ASSERT(img->height()==512);
    CPPUNIT_ASSERT(img->channels()==3);
    CPPUNIT_ASSERT(img->label()=="rgb");
    
    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
        img->get_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i],px);
        total_diff = total_diff + abs(LENA_TEST_COL_R[i]/255.0f-px[0]);
        total_diff = total_diff + abs(LENA_TEST_COL_G[i]/255.0f-px[1]);
        total_diff = total_diff + abs(LENA_TEST_COL_B[i]/255.0f-px[2]);
    }
    CPPUNIT_ASSERT(total_diff<1e-9);
    img->~Image();
        
    //delete img;
}
