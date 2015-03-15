/*
 * File:   test_operator.cpp
 * Author: swanner
 *
 * Created on May 19, 2014, 9:32:19 AM
 */

#include "test_operator.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(test_operator);

test_operator::test_operator() {
}

test_operator::~test_operator() {
}

void test_operator::setUp() {



    imgnames["4D_high_bw"] = test_lf_4D_high+"4D_high_bw.png";
    imgnames["4D_high_rgb"] = test_lf_4D_high+"4D_high_rgb.png";
    cfgnames["4D_high_bw"] = test_lf_4D_high+"bw.cfg";
    cfgnames["4D_high_rgb"] = test_lf_4D_high+"bw.cfg";

    
}

void test_operator::tearDown() {
}

void test_operator::testMethod() {

    OpenLF::lightfield::Lightfield *lf = new OpenLF::lightfield::Lightfield_4D();
    lf->open(cfgnames["4D_high_rgb"]);

    vigra::MultiArrayView<2,float> img_bw;
    vigra::MultiArrayView<2,float> img_rgb;

    lf->getImage(4,4,"bw",img_bw);
    lf->getImage(4,4,"r",img_rgb);

    //std::string filename13 = "/home/kiryl/Documents/openlf/openlf/tests/data_2/LF4DOperator_bw.jpg";
    std::string filename14 = "/home/kiryl/Documents/openlf/openlf/tests/data_2/LF4DOperator_r.jpg";
    

    //OpenLF::image::io::imsave(filename13,img_bw);
    OpenLF::image::io::imsave(filename14,img_rgb);   
 
    std::vector<std::string> inslots;
    std::vector<std::string> outslots; 
    inslots.push_back("a");
    outslots.push_back("b");
    OpenLF::operators::My4DOperator myOp(inslots,outslots);
    myOp.set(lf);
    myOp.process();
    
    //OpenLF::image::ImageChannel *test_image_bw = NULL;
    OpenLF::image::ImageChannel *test_image_r = NULL;
    
    // get the pointers to the lf data
    lf->data("r",&test_image_r);
    
    std::string filename15 = "/home/kiryl/Documents/openlf/openlf/tests/data_2/LF4DOperator_r_processed.jpg";
    //std::string filename16 = "/home/kiryl/Documents/openlf/openlf/tests/data_2/LF4DOperator_bw_processed.jpg";
    std::string filename17 = "/home/kiryl/Documents/openlf/openlf/tests/data_2/LF4DOperator_r_image_processed.jpg";

    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename15, *test_image_r));
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename17, img_rgb));
}

void test_operator::testFailedMethod() {

}

