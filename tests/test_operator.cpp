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
    cfgnames["4D_high_rgb"] = test_lf_4D_high+"rgb.cfg";

    
}

void test_operator::tearDown() {
}

void test_operator::testMethod() {

    OpenLF::lightfield::Lightfield_4D *lf = new OpenLF::lightfield::Lightfield_4D();
    lf->open(cfgnames["4D_high_rgb"]);

    vigra::MultiArrayView<2,float> img_rgb;

    lf->getImage(1,1,"r",img_rgb);

    std::string filename14 = test_data2_dir+"LF4DOperator_r.jpg";
 
    OpenLF::image::io::imsave(filename14,img_rgb);   
 
    std::vector<std::string> inslots;
    std::vector<std::string> outslots; 
    inslots.push_back("a");
    outslots.push_back("b");
    OpenLF::operators::Operator * myOp = new OpenLF::operators::My4DOperator(inslots,outslots);
    
    myOp->set(lf);
    myOp->process();
    
    OpenLF::image::ImageChannel *test_image_result = NULL;
    vigra::MultiArrayView<2,float> img_result;
    lf->getImage(1,1,"myNewChannel",img_result); //change to internal lf

    // get the pointers to the lf data
    lf->data("myNewChannel",&test_image_result);
    
    std::string filename15 = test_data2_dir+"LF4DOperator_processed.jpg";
    std::string filename16 = test_data2_dir+"LF4DOperator_image_processed.jpg";

    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename15, *test_image_result));
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename16, img_result));

    //********************************************************
    //** test Epi Operator
    //********************************************************

    std::string filename17 = test_data2_dir+"Epi_Operator_processed.jpg";
    std::string filename18 = test_data2_dir+"Epi_Operator_image_original.jpg";

    OpenLF::operators::Operator_EPI * myOpEpi = new OpenLF::operators::MyEpiOperator(inslots,outslots);

    myOpEpi->set(lf);
    vigra::MultiArrayView<2,float> channel_r = *(lf->data("r")->image());
    //OpenLF::image::io::imsave(filename17, myOpEpi->getTransposed("r"));
    OpenLF::image::io::imsave(filename18, channel_r);

    //********************************************************
    //** test MyEpiOperator
    //********************************************************

    std::string filename19 = test_data2_dir+"MyEpiOperator_refocused.jpg";
    std::string filename20 = test_data2_dir+"MyEpiOperator_epi_original.jpg";

    myOpEpi = new OpenLF::operators::MyEpiOperator(inslots,outslots);

    myOpEpi->set(lf);
    myOpEpi->load_epi_containers("r");
    myOpEpi->process();
    OpenLF::image::io::imsave(filename20, myOpEpi->get_horizontal_epi(0));
    view_2D refocused = myOpEpi->refocus(2, myOpEpi->get_horizontal_epi(0));
    OpenLF::image::io::imsave(filename19, refocused);
}

void test_operator::testFailedMethod() {

}

