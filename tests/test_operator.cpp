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
    
    //delete myOp;

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
/*
    std::string filename19 = test_data2_dir+"MyEpiOperator_refocused.jpg";
    std::string filename20 = test_data2_dir+"MyEpiOperator_epi_original.jpg";

    myOpEpi = new OpenLF::operators::MyEpiOperator(inslots,outslots);

    myOpEpi->set(lf);
    myOpEpi->load_epi_containers("r");
    myOpEpi->process();
    OpenLF::image::io::imsave(filename20, myOpEpi->get_horizontal_epi(0));
    view_2D refocused = myOpEpi->refocus(2, myOpEpi->get_horizontal_epi(0));
    OpenLF::image::io::imsave(filename19, refocused);
*/
    //********************************************************
    //** test Structure_Tensor
    //********************************************************


    std::string filename21 = test_data2_dir+"Channel_r_original.jpg";
    std::string filename22 = test_data2_dir+"Channel_r_smoothed.jpg";
    std::string filename23 = test_data2_dir+"Channel_r_smoothed2.jpg";
    std::string filename24 = test_data2_dir+"Channel_r_smoothed3.jpg";
    std::string filename25 = test_data2_dir+"Channel_r_smoothed4.jpg";

    OpenLF::operators::Structure_Tensor * ST = new OpenLF::operators::Structure_Tensor(inslots,outslots);
    OpenLF::lightfield::Lightfield_4D *lfa = new OpenLF::lightfield::Lightfield_4D();
    lfa->open(cfgnames["4D_high_rgb"]); 
    ST->set(lfa);
    
    vigra::MultiArray<2, float> smoothed1 = ST->gaussian_smoothing(ST->lf_channel("r"),0.9);
    OpenLF::image::io::imsave(filename21, ST->lf_channel("r"));
    OpenLF::image::io::imsave(filename22, smoothed1);

    array_2D smoothed2 = ST->gaussian_smoothing(ST->lf_channel("r"),1.0);
    OpenLF::image::io::imsave(filename23, smoothed2);
    //delete ST;
    //ST = nullptr;

    //********************************************************
    //** test refocus_uncut
    //********************************************************

    std::string filename26 = test_data2_dir+"1epi_original_26.jpg";
    std::string filename27 = test_data2_dir+"2epi_uncut_26.jpg";
    std::string filename28 = test_data2_dir+"3epi_backfocus_26.jpg";
    std::string filename29 = test_data2_dir+"4epi_uncut_26_2.jpg";
    std::string filename30 = test_data2_dir+"5epi_backfocus_26_2.jpg";

    OpenLF::lightfield::Lightfield_4D *lf1 = new OpenLF::lightfield::Lightfield_4D();
    lf1->open(cfgnames["4D_high_rgb"]);
    OpenLF::operators::Structure_Tensor * ST2 = new OpenLF::operators::Structure_Tensor(inslots,outslots);
    ST2->set(lf1);
    ST2->load_epi_containers("r");
    array_2D EPI_original = ST2->m_horizontal_epis["r"][0];

    OpenLF::operators::epi epi_original;
    //array_2D EPI_original = ST2->horizontal_epis_ptr("r")->at(0);
    
    epi_original.EPI = EPI_original;
    epi_original.focus = 0;

    CPPUNIT_ASSERT(OpenLF::image::io::imsave_HQ_float(filename26, EPI_original));


    OpenLF::operators::epi epi_refocused;
    epi_refocused = ST2->refocus_uncut(2,epi_original);
    CPPUNIT_ASSERT(epi_refocused.focus==2);

    CPPUNIT_ASSERT(OpenLF::image::io::imsave_HQ_float(filename27, epi_refocused.EPI));

    OpenLF::operators::epi epi_backfocus;
    epi_backfocus = ST2->refocus_uncut(0,epi_refocused);
    
    CPPUNIT_ASSERT(epi_backfocus.focus==0);
    CPPUNIT_ASSERT(epi_backfocus.EPI.width()==48);
    CPPUNIT_ASSERT(epi_backfocus.EPI.height()==5);
    
    
    OpenLF::operators::epi epi_refocus2;
    epi_refocus2 = ST2->refocus_uncut(-2,epi_backfocus);
    
    OpenLF::operators::epi epi_backfocus2;
    epi_backfocus2 = ST2->refocus_uncut(0,epi_refocus2);
    
    
    
    
    
    CPPUNIT_ASSERT(OpenLF::image::io::imsave_HQ_float(filename28, epi_backfocus.EPI));
    OpenLF::image::io::imsave_HQ_float(filename29, epi_refocus2.EPI);
    OpenLF::image::io::imsave_HQ_float(filename30, epi_backfocus2.EPI);

    //********************************************************
    //** test focused orientation
    //********************************************************

    OpenLF::operators::orientation orientation;
    OpenLF::operators::focuses f = {0,1,2,3};

    double inner_scale = 1.0;
    double outer_scale = 1.0;
    double smoothing_scale = outer_scale;
    double max_slope = 1.0;
    double coh_threshold = 0.99;

    //********************************************************
    //** a.1) test vigra structure tensor from source
    //********************************************************

    OpenLF::operators::ST st;
    st = ST2->vigra_structure_tensor_from_source(epi_original.EPI, inner_scale, outer_scale, smoothing_scale);
    
    std::string filename33 = test_data2_dir+"stxx.jpg";
    std::string filename34 = test_data2_dir+"stxy.jpg";
    std::string filename35 = test_data2_dir+"styy.jpg";
    std::string filename36 = test_data2_dir+"stcoherence.jpg";
    OpenLF::image::io::imsave_HQ_float(filename33, st.xx);
    OpenLF::image::io::imsave_HQ_float(filename34, st.xy);
    OpenLF::image::io::imsave_HQ_float(filename35, st.yy);
    OpenLF::image::io::imsave_HQ_float(filename36, st.coherence);

    //********************************************************
    //** a.2) test vigra structure tensor focus = 0
    //********************************************************
    

    OpenLF::operators::ST st001 = ST2->vigra_structure_tensor("r", 0, 0, HORIZONTAL, inner_scale, outer_scale, smoothing_scale);
    std::string filename33a = test_data2_dir+"stxx02.jpg";
    std::string filename34b = test_data2_dir+"stxy02.jpg";
    std::string filename35c = test_data2_dir+"styy02.jpg";
    std::string filename36d = test_data2_dir+"stcoherence02.jpg";
    OpenLF::image::io::imsave_HQ_float(filename33a, st001.xx);
    OpenLF::image::io::imsave_HQ_float(filename34b, st001.xy);
    OpenLF::image::io::imsave_HQ_float(filename35c, st001.yy);
    OpenLF::image::io::imsave_HQ_float(filename36d, st001.coherence);

    //********************************************************
    //** a.2) test refocus(channel) 
    //********************************************************

    ST2->refocus(2, "r");
    std::string filename33a3 = test_data2_dir+"refocused_channel.jpg";
    std::string filename33a32 = test_data2_dir+"refocused_channel2.jpg";
    OpenLF::image::io::imsave_HQ_float(filename33a3, ST2->m_horizontal_epis["r"][0]);
    OpenLF::image::io::imsave_HQ_float(filename33a32, ST2->m_horizontal_epis["r"][1]);


    //********************************************************
    //** a.3) test vigra structure tensor focus != 0 
    //********************************************************
    
    st = ST2->vigra_structure_tensor("r", 0, 3, HORIZONTAL, inner_scale, outer_scale, smoothing_scale);
    std::string filename33a1 = test_data2_dir+"stxx03.jpg";
    std::string filename34b1 = test_data2_dir+"stxy03.jpg";
    std::string filename35c1 = test_data2_dir+"styy03.jpg";
    std::string filename36d1 = test_data2_dir+"stcoherence03.jpg";
    OpenLF::image::io::imsave_HQ_float(filename33a1, st.xx);
    OpenLF::image::io::imsave_HQ_float(filename34b1, st.xy);
    OpenLF::image::io::imsave_HQ_float(filename35c1, st.yy);
    OpenLF::image::io::imsave_HQ_float(filename36d1, st.coherence);
    
    //********************************************************
    //** b) test orientation
    //********************************************************

    array_2D ori_array = ST2->orientation(st, "None", coh_threshold, max_slope);

    std::string filename37 = test_data2_dir+"7orientation.jpg";
    OpenLF::image::io::imsave_HQ_float(filename37, ori_array);

    //********************************************************
    //** test focused orientation complete - error!!
    //********************************************************
    /*
    std::string st_type = "vigra";
    orientation = ST2->focused_orientation(epi_original.EPI, f, smoothing_scale, inner_scale, outer_scale, max_slope, coh_threshold, st_type);
    std::string filename31 = test_data2_dir+"6orientation.jpg";
    std::string filename32 = test_data2_dir+"7coherence.jpg";
    OpenLF::image::io::imsave_HQ_float(filename31, orientation.ori);
    OpenLF::image::io::imsave_HQ_float(filename32, orientation.coh);
    */
    
    //********************************************************
    //** test images_from_epis
    //********************************************************

    std::vector<array_2D> vector = ST2->images_from_epis("r");
    std::string filename40 = test_data2_dir+"reconstruct_image.jpg";
    OpenLF::image::io::imsave_HQ_float(filename40, vector[34]);
    CPPUNIT_ASSERT(vector.size() == 35);

    //********************************************************
    //** test reconstruct vigra depth
    //********************************************************
    
    lf1 = new OpenLF::lightfield::Lightfield_4D();
    lf1->open(cfgnames["4D_high_rgb"]);
    OpenLF::operators::Structure_Tensor * ST3 = new OpenLF::operators::Structure_Tensor(inslots,outslots);
    ST3->set(lf1);
    ST3->load_epi_containers("r");

    std::vector<array_2D> v = ST3->reconstruct_depth("r");
    std::string filename41 = test_data2_dir+"vigra_orientation_image.jpg";
    
    OpenLF::image::io::imsave_HQ_float(filename41, v[0]);
    CPPUNIT_ASSERT(v.size() == 35);
    std::string filename42 = test_data2_dir+"vigra_orientation_image1.jpg";
    std::string filename43 = test_data2_dir+"vigra_orientation_image2.jpg";
    std::string filename44 = test_data2_dir+"vigra_orientation_image3.jpg";
    std::string filename45 = test_data2_dir+"vigra_orientation_image4.jpg";
    std::string filename46 = test_data2_dir+"vigra_orientation_image5.jpg";
    std::string filename47 = test_data2_dir+"vigra_orientation_image6.jpg";
    std::string filename48 = test_data2_dir+"vigra_orientation_image7.jpg";
    std::string filename49 = test_data2_dir+"vigra_orientation_image8.jpg";
    std::string filename50 = test_data2_dir+"vigra_orientation_image9.jpg";
    std::string filename51 = test_data2_dir+"vigra_orientation_image10.jpg";
    std::string filename52 = test_data2_dir+"vigra_orientation_image11.jpg";
    std::string filename53 = test_data2_dir+"vigra_orientation_image12.jpg";
    std::string filename54 = test_data2_dir+"vigra_orientation_image13.jpg";
    std::string filename55 = test_data2_dir+"vigra_orientation_image14.jpg";
    std::string filename56 = test_data2_dir+"vigra_orientation_image15.jpg";
    std::string filename57 = test_data2_dir+"vigra_orientation_image16.jpg";
    std::string filename58 = test_data2_dir+"vigra_orientation_image17.jpg";
    std::string filename59 = test_data2_dir+"vigra_orientation_image18.jpg";
    std::string filename60 = test_data2_dir+"vigra_orientation_image19.jpg";
    std::string filename61 = test_data2_dir+"vigra_orientation_image20.jpg";
    std::string filename62 = test_data2_dir+"vigra_orientation_image21.jpg";
    std::string filename63 = test_data2_dir+"vigra_orientation_image22.jpg";
    std::string filename64 = test_data2_dir+"vigra_orientation_image23.jpg";
    std::string filename65 = test_data2_dir+"vigra_orientation_image24.jpg";
    std::string filename66 = test_data2_dir+"vigra_orientation_image25.jpg";
    std::string filename67 = test_data2_dir+"vigra_orientation_image26.jpg";
    std::string filename68 = test_data2_dir+"vigra_orientation_image27.jpg";
    std::string filename69 = test_data2_dir+"vigra_orientation_image28.jpg";
    std::string filename70 = test_data2_dir+"vigra_orientation_image29.jpg";
    std::string filename71 = test_data2_dir+"vigra_orientation_image30.jpg";
    std::string filename72 = test_data2_dir+"vigra_orientation_image31.jpg";
    std::string filename73 = test_data2_dir+"vigra_orientation_image32.jpg";
    std::string filename74 = test_data2_dir+"vigra_orientation_image33.jpg";
    std::string filename75 = test_data2_dir+"vigra_orientation_image34.jpg";
    std::string filename76 = test_data2_dir+"vigra_orientation_image35.jpg";

    OpenLF::image::io::imsave_HQ_float(filename42, v[0]);
    OpenLF::image::io::imsave_HQ_float(filename43, v[1]);
    OpenLF::image::io::imsave_HQ_float(filename44, v[2]);
    OpenLF::image::io::imsave_HQ_float(filename45, v[3]);
    OpenLF::image::io::imsave_HQ_float(filename46, v[4]);
    OpenLF::image::io::imsave_HQ_float(filename47, v[5]);
    OpenLF::image::io::imsave_HQ_float(filename48, v[6]);
    OpenLF::image::io::imsave_HQ_float(filename49, v[7]);
    OpenLF::image::io::imsave_HQ_float(filename50, v[8]);
    OpenLF::image::io::imsave_HQ_float(filename51, v[9]);
    OpenLF::image::io::imsave_HQ_float(filename52, v[10]);
    OpenLF::image::io::imsave_HQ_float(filename53, v[11]);
    OpenLF::image::io::imsave_HQ_float(filename54, v[12]);
    OpenLF::image::io::imsave_HQ_float(filename55, v[13]);
    OpenLF::image::io::imsave_HQ_float(filename56, v[14]);
    OpenLF::image::io::imsave_HQ_float(filename57, v[15]);
    OpenLF::image::io::imsave_HQ_float(filename58, v[16]);
    OpenLF::image::io::imsave_HQ_float(filename59, v[17]);
    OpenLF::image::io::imsave_HQ_float(filename60, v[18]);
    OpenLF::image::io::imsave_HQ_float(filename61, v[19]);
    OpenLF::image::io::imsave_HQ_float(filename62, v[20]);
    OpenLF::image::io::imsave_HQ_float(filename63, v[21]);
    OpenLF::image::io::imsave_HQ_float(filename64, v[22]);
    OpenLF::image::io::imsave_HQ_float(filename65, v[23]);
    OpenLF::image::io::imsave_HQ_float(filename66, v[24]);
    OpenLF::image::io::imsave_HQ_float(filename67, v[25]);
    OpenLF::image::io::imsave_HQ_float(filename68, v[26]);
    OpenLF::image::io::imsave_HQ_float(filename69, v[27]);
    OpenLF::image::io::imsave_HQ_float(filename70, v[28]);
    OpenLF::image::io::imsave_HQ_float(filename71, v[29]);
    OpenLF::image::io::imsave_HQ_float(filename72, v[30]);
    OpenLF::image::io::imsave_HQ_float(filename73, v[31]);
    OpenLF::image::io::imsave_HQ_float(filename74, v[32]);
    OpenLF::image::io::imsave_HQ_float(filename75, v[33]);
    OpenLF::image::io::imsave_HQ_float(filename76, v[34]);
/*
    OpenLF::image::io::imsave_HQ_float(filename42, ST3->orientations["r"][0]);
    OpenLF::image::io::imsave_HQ_float(filename43, ST3->orientations["r"][1]);
    OpenLF::image::io::imsave_HQ_float(filename44, ST3->orientations["r"][2]);
    OpenLF::image::io::imsave_HQ_float(filename45, ST3->orientations["r"][3]);
    OpenLF::image::io::imsave_HQ_float(filename46, ST3->orientations["r"][4]);
    OpenLF::image::io::imsave_HQ_float(filename47, ST3->orientations["r"][5]);
    OpenLF::image::io::imsave_HQ_float(filename48, ST3->orientations["r"][6]);
    OpenLF::image::io::imsave_HQ_float(filename49, ST3->orientations["r"][7]);
    OpenLF::image::io::imsave_HQ_float(filename50, ST3->orientations["r"][8]);
    OpenLF::image::io::imsave_HQ_float(filename51, ST3->orientations["r"][9]);
    OpenLF::image::io::imsave_HQ_float(filename52, ST3->orientations["r"][10]);
    OpenLF::image::io::imsave_HQ_float(filename53, ST3->orientations["r"][11]);
    OpenLF::image::io::imsave_HQ_float(filename54, ST3->orientations["r"][12]);
    OpenLF::image::io::imsave_HQ_float(filename55, ST3->orientations["r"][13]);
    OpenLF::image::io::imsave_HQ_float(filename56, ST3->orientations["r"][14]);
    OpenLF::image::io::imsave_HQ_float(filename57, ST3->orientations["r"][15]);
    OpenLF::image::io::imsave_HQ_float(filename58, ST3->orientations["r"][16]);
    OpenLF::image::io::imsave_HQ_float(filename59, ST3->orientations["r"][17]);
    OpenLF::image::io::imsave_HQ_float(filename60, ST3->orientations["r"][18]);
    OpenLF::image::io::imsave_HQ_float(filename61, ST3->orientations["r"][19]);
    OpenLF::image::io::imsave_HQ_float(filename62, ST3->orientations["r"][20]);
    OpenLF::image::io::imsave_HQ_float(filename63, ST3->orientations["r"][21]);
    OpenLF::image::io::imsave_HQ_float(filename64, ST3->orientations["r"][22]);
    OpenLF::image::io::imsave_HQ_float(filename65, ST3->orientations["r"][23]);
    OpenLF::image::io::imsave_HQ_float(filename66, ST3->orientations["r"][24]);
    OpenLF::image::io::imsave_HQ_float(filename67, ST3->orientations["r"][25]);
    OpenLF::image::io::imsave_HQ_float(filename68, ST3->orientations["r"][26]);
    OpenLF::image::io::imsave_HQ_float(filename69, ST3->orientations["r"][27]);
    OpenLF::image::io::imsave_HQ_float(filename70, ST3->orientations["r"][28]);
    OpenLF::image::io::imsave_HQ_float(filename71, ST3->orientations["r"][29]);
    OpenLF::image::io::imsave_HQ_float(filename72, ST3->orientations["r"][30]);
    OpenLF::image::io::imsave_HQ_float(filename73, ST3->orientations["r"][31]);
    OpenLF::image::io::imsave_HQ_float(filename74, ST3->orientations["r"][32]);
    OpenLF::image::io::imsave_HQ_float(filename75, ST3->orientations["r"][33]);
    OpenLF::image::io::imsave_HQ_float(filename76, ST3->orientations["r"][34]);
*/

}

void test_operator::testFailedMethod() {

}

