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
    //OpenLF::image::io::imsave(filename20, myOpEpi->get_horizontal_epi(0));
    //view_2D refocused = myOpEpi->refocus(2, myOpEpi->get_horizontal_epi(0));
    //OpenLF::image::io::imsave(filename19, refocused);

    //********************************************************
    //** test Gaussian smoothing
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


    //********************************************************
    //** test load epis vertical
    //********************************************************
    
    vigra::MultiArray<2,float> image = *(lfa->data()->find("r")->second.image());

    vigra::MultiArray<1,float> column = image.bind<0>(30);
    shape epi_shape = shape(64,7);
    vigra::MultiArray<2,float> epi_vertical(epi_shape,column.data()); 
    std::string filename_epi_vertical = test_data2_dir+"epi_vertical_00_"+std::to_string(1)+"_img width:"+std::to_string(lfa->imgWidth())+"_img height:"+std::to_string(lfa->imgHeight())+"_lf width:"+std::to_string(lfa->width())+".jpg";
    OpenLF::image::io::imsave_HQ_float(filename_epi_vertical, epi_vertical);


    //********************************************************
    //** test refocus_uncut horizontal 
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

    array_2D EPI_originalv2 = ST2->m_vertical_epis["r"][0];
    std::string filename26bv = test_data2_dir+"1epi_original_26v2.jpg";
    OpenLF::image::io::imsave_HQ_float(filename26bv, EPI_originalv2);

    OpenLF::operators::epi epi_original;
    
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
    //** test refocus_uncut vertical
    //********************************************************

    std::string filename26b = test_data2_dir+"1epi_original_26v.jpg";
    std::string filename27b = test_data2_dir+"2epi_uncut_26v.jpg";
    std::string filename28b = test_data2_dir+"3epi_backfocus_26v.jpg";
    std::string filename29b = test_data2_dir+"4epi_uncut_26_2v.jpg";
    std::string filename30b = test_data2_dir+"5epi_backfocus_26_2v.jpg";

    OpenLF::lightfield::Lightfield_4D *lf1b = new OpenLF::lightfield::Lightfield_4D();
    lf1b->open(cfgnames["4D_high_rgb"]);
    OpenLF::operators::Structure_Tensor * ST2b = new OpenLF::operators::Structure_Tensor(inslots,outslots);
    ST2b->set(lf1b);
    ST2b->load_epi_containers("r");

    std::string filename11111 = test_data2_dir+"image_image.jpg";
    CPPUNIT_ASSERT(OpenLF::image::io::imsave_HQ_float(filename11111, *(lf1b->data()->find("r")->second.image())));

    array_2D EPI_originalb = ST2b->m_vertical_epis["r"][30];

    CPPUNIT_ASSERT(OpenLF::image::io::imsave_HQ_float(filename26b, EPI_originalb));

    OpenLF::operators::epi epi_originalb;
    
    epi_originalb.EPI = EPI_originalb;
    epi_originalb.focus = 0;


    OpenLF::operators::epi epi_refocusedb;
    epi_refocusedb = ST2b->refocus_uncut(2,epi_originalb);
    CPPUNIT_ASSERT(epi_refocusedb.focus==2);

    CPPUNIT_ASSERT(OpenLF::image::io::imsave_HQ_float(filename27b, epi_refocusedb.EPI));

    OpenLF::operators::epi epi_backfocusb;
    epi_backfocusb = ST2b->refocus_uncut(0,epi_refocusedb);
    
    CPPUNIT_ASSERT(epi_backfocusb.focus==0);
    
    
    OpenLF::operators::epi epi_refocus2b;
    epi_refocus2b = ST2b->refocus_uncut(-2,epi_backfocusb);
    
    OpenLF::operators::epi epi_backfocus2b;
    epi_backfocus2b = ST2b->refocus_uncut(0,epi_refocus2b);
    
    
    CPPUNIT_ASSERT(OpenLF::image::io::imsave_HQ_float(filename28b, epi_backfocusb.EPI));
    OpenLF::image::io::imsave_HQ_float(filename29b, epi_refocus2b.EPI);
    OpenLF::image::io::imsave_HQ_float(filename30b, epi_backfocus2b.EPI);


    //****************************************************************************************************************
    //** SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX *****
    //****************************************************************************************************************
    //**            PARAMETERS TO PLAY WITH                           ************************************************
    //****************************************************************************************************************
    //****************************************************************************************************************

    std::string method = "focused_scharr5x5"; // "vigra" or "focused_vigra" / "scharr5x5" / "focused_scharr5x5"
    OpenLF::operators::orientation orientation;
    OpenLF::operators::focuses f = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; // for focused ST
    //DIRECTION direction = HORIZONTAL; // or VERTICAL
    std::string coherence = "Yes"; // or "None"
    int focus = 0; // different single focuses not for focused STs
    double inner_scale = 1.0;
    double outer_scale = 0.5;
    double smoothing_scale = outer_scale;
    double max_slope = 1.0;
    double coh_threshold = 0.8;








    //********************************************************
    //** test focused orientation
    //********************************************************

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

/*    // output to txt
    const int size = st.coherence.size();
    float a[size];
    int j = 0;
    for(auto it = epi_original.EPI.begin(); it != epi_original.EPI.end(); it++) {
        a[j] = *it;
        j++;
    }
    ofstream fout(test_data2_dir+"epi_original.txt"); 
    if(fout.is_open()) {
        for(int i = 0; a[i] != '\0'; i++)
        {
            fout << std::to_string(a[i]) + "\n"; 
        }
    }
*/

    //********************************************************
    //** a.2) test vigra structure tensor focus = 0
    //********************************************************
    

    OpenLF::operators::ST st001 = ST2->vigra_structure_tensor("r", 0, 0, HORIZONTAL, inner_scale, outer_scale, smoothing_scale);
    std::string filename33a = test_data2_dir+"stxx_vigra_focus_0.jpg";
    std::string filename34b = test_data2_dir+"stxy_vigra_focus_0.jpg";
    std::string filename35c = test_data2_dir+"styy_vigra_focus_0.jpg";
    std::string filename36d = test_data2_dir+"stcoherence_vigra_focus_0.jpg";
    OpenLF::image::io::imsave_HQ_float(filename33a, st001.xx);
    OpenLF::image::io::imsave_HQ_float(filename34b, st001.xy);
    OpenLF::image::io::imsave_HQ_float(filename35c, st001.yy);
    OpenLF::image::io::imsave_HQ_float(filename36d, st001.coherence);

    //********************************************************
    //** a.2) test scharr5x5 structure tensor focus = 0
    //********************************************************

    OpenLF::operators::ST st001s0 = ST2->Scharr5x5_structure_tensor("r", 0, 0, HORIZONTAL, smoothing_scale);
    std::string filename33as0 = test_data2_dir+"stxx_scharr_focus_0.jpg";
    std::string filename34bs0 = test_data2_dir+"stxy_scharr_focus_0.jpg";
    std::string filename35cs0 = test_data2_dir+"styy_scharr_focus_0.jpg";
    std::string filename36ds0 = test_data2_dir+"stcoherence_scharr_focus_0.jpg";
    OpenLF::image::io::imsave_HQ_float(filename33as0, st001s0.xx);
    OpenLF::image::io::imsave_HQ_float(filename34bs0, st001s0.xy);
    OpenLF::image::io::imsave_HQ_float(filename35cs0, st001s0.yy);
    OpenLF::image::io::imsave_HQ_float(filename36ds0, st001s0.coherence);

    //********************************************************
    //** a.2) test scharr5x5 structure tensor focus != 0
    //********************************************************

    OpenLF::operators::ST st001s3 = ST2->Scharr5x5_structure_tensor("r", 0, 3, HORIZONTAL, smoothing_scale);
    std::string filename33as3 = test_data2_dir+"stxx_scharr_focus_3.jpg";
    std::string filename34bs3 = test_data2_dir+"stxy_scharr_focus_3.jpg";
    std::string filename35cs3 = test_data2_dir+"styy_scharr_focus_3.jpg";
    std::string filename36ds3 = test_data2_dir+"stcoherence_scharr_focus_3.jpg";
    OpenLF::image::io::imsave_HQ_float(filename33as3, st001s3.xx);
    OpenLF::image::io::imsave_HQ_float(filename34bs3, st001s3.xy);
    OpenLF::image::io::imsave_HQ_float(filename35cs3, st001s3.yy);
    OpenLF::image::io::imsave_HQ_float(filename36ds3, st001s3.coherence);

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
    std::string filename33a1 = test_data2_dir+"stxx_vigra_focus_3.jpg";
    std::string filename34b1 = test_data2_dir+"stxy_vigra_focus_3.jpg";
    std::string filename35c1 = test_data2_dir+"styy_vigra_focus_3.jpg";
    std::string filename36d1 = test_data2_dir+"stcoherence_vigra_focus_3.jpg";
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
    //** test focused orientation complete 
    //********************************************************

    std::string st_type = "vigra";
    orientation = ST2->focused_orientation(epi_original.EPI, f, smoothing_scale, inner_scale, outer_scale, max_slope, coh_threshold, st_type);
    std::string filename31 = test_data2_dir+"6orientation.jpg";
    std::string filename32 = test_data2_dir+"7coherence.jpg";
    OpenLF::image::io::imsave_HQ_float(filename31, orientation.ori);
    OpenLF::image::io::imsave_HQ_float(filename32, orientation.coh);

    
    //********************************************************
    //** test images_from_epis horizontal (test fct.)
    //********************************************************

    std::vector<array_2D> vector = ST2->images_from_epis("r");
    std::string filename40 = test_data2_dir+"reconstruct_image.jpg";
    OpenLF::image::io::imsave_HQ_float(filename40, vector[34]);
    CPPUNIT_ASSERT(vector.size() == 35);

    //********************************************************
    //** test images_from_epis vertical
    //********************************************************

    std::vector<array_2D> vectorv = ST2->images_from_epis("r", VERTICAL);
    std::string filename40v = test_data2_dir+"reconstruct_image_v.jpg";
    OpenLF::image::io::imsave_HQ_float(filename40v, vectorv[34]);
    CPPUNIT_ASSERT(vectorv.size() == 35);


    //********************************************************
    //** test reconstruct vigra depth
    //********************************************************

    /*********************************************************************
     *                     Test from woods    
     *********************************************************************/

    lf1 = new OpenLF::lightfield::Lightfield_4D();
    lf1->open(cfgnames["4D_high_rgb"]);
    OpenLF::operators::Structure_Tensor * ST3 = new OpenLF::operators::Structure_Tensor(inslots,outslots);
    ST3->set(lf1);
    ST3->load_epi_containers("r");

//horizontal

    std::vector<array_2D> h = ST3->reconstruct_depth("r", method ,coherence, focus, HORIZONTAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    array_2D overlay_h(shape(48,64),0.0);

    CPPUNIT_ASSERT(h.size() == 35);
    for(int i=0;i<35;i++) {
        std::string filename_woods_h = test_data2_dir+method+"_orientation_image_h_"+std::to_string(i)+".jpg";
        OpenLF::image::io::imsave_HQ_float(filename_woods_h, h[i]);
        overlay_h += h[i];
    }
    std::string filename_woods_overlay_h = test_data2_dir+method+"_orientation_image_overlay_h.jpg";
    OpenLF::image::io::imsave_HQ_float(filename_woods_overlay_h, overlay_h);

//vertical

    std::vector<array_2D> v = ST3->reconstruct_depth("r", method ,coherence, focus, VERTICAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    array_2D overlay_v(shape(64,48),0.0);

    CPPUNIT_ASSERT(v.size() == 35);

    for(int i=0;i<35;i++) {
        std::string filename_woods_v = test_data2_dir+method+"_orientation_image_v"+std::to_string(i)+".jpg";
        OpenLF::image::io::imsave_HQ_float(filename_woods_v, v[i]);
        overlay_v += v[i];
    }

    std::string filename_woods_overlay_v = test_data2_dir+method+"_orientation_image_overlay_v.jpg";
    OpenLF::image::io::imsave_HQ_float(filename_woods_overlay_v, overlay_v);

    array_2D rotated_overlay_v(48,64);
    vigra::rotateImage(overlay_v,rotated_overlay_v,-90);

    std::string filename_woods_overlay_v_rotated = test_data2_dir+method+"_orientation_image_overlay_v_rotated.jpg";
    OpenLF::image::io::imsave_HQ_float(filename_woods_overlay_v_rotated, rotated_overlay_v);
    
    rotated_overlay_v += overlay_h;
    CPPUNIT_ASSERT(rotated_overlay_v.shape() == shape(48,64));
    std::string filename_woods_overlay = test_data2_dir+method+"_orientation_image_overlay_woods.jpg";
    OpenLF::image::io::imsave_HQ_float(filename_woods_overlay, rotated_overlay_v);

    
    array_2D depth = ST3->get_depth_image("r", method ,coherence, focus, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);
    std::string filename_woods_depth = test_data2_dir+method+"_depth_woods.jpg";
    OpenLF::image::io::imsave_HQ_float(filename_woods_depth, depth);

    /*********************************************************************
     *                     Test from buddha 4D     
     *********************************************************************/

    /*********************************************************************
     *                     1) load from images  
     *********************************************************************/
/* 
    string fname = test_lf_buddha+"buddha_4D.cfg";
    string p = test_lf_buddha+"buddha_4D.png";
    
    map< string,OpenLF::image::ImageChannel> channels;
    OpenLF::lightfield::Properties *properties = new OpenLF::lightfield::Properties();
    
    OpenLF::lightfield::io::DataHandler *dataHandler;

    dataHandler = new OpenLF::lightfield::io::FileHandler(fname,properties);
    
    CPPUNIT_ASSERT(dataHandler->readData(channels));
    OpenLF::image::io::imsave(p,channels);
    channels.clear();
*/

    /*********************************************************************
     *                     2) load lightfield and perform calculations
     *********************************************************************/
/*  //UNCOMMENT  
    std::string buddha_method = "focused_scharr5x5";

    OpenLF::lightfield::Lightfield_4D * lf_buddha = new OpenLF::lightfield::Lightfield_4D();
    lf_buddha->open(test_lf_buddha+"buddha_4D.cfg");
    OpenLF::operators::Structure_Tensor * ST_buddha = new OpenLF::operators::Structure_Tensor(inslots,outslots);
    ST_buddha->set(lf_buddha);
    ST_buddha->load_epi_containers("r");
    array_2D depth_buddha = ST_buddha->get_depth_image("r", buddha_method ,coherence, focus, inner_scale, outer_scale, smoothing_scale, 0.95, max_slope, f);

    std::string filename_buddha = test_lf_buddha+"buddha_depth_"+buddha_method+"_focus=0, channel=red.jpg";
    OpenLF::image::io::imsave_HQ_float(filename_buddha, depth_buddha);
    
*/ //UNCOMMENT  





/*
    std::vector<array_2D> v_buddha = ST_buddha->reconstruct_depth("r", method ,coherence, focus, direction, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    for(int i=0;i<81;i++) {
        std::string filename_buddha = test_lf_buddha+method+"_00"+std::to_string(i)+".jpg";
        OpenLF::image::io::imsave_HQ_float(filename_buddha, v_buddha[i]);
    }
*/
}
void test_operator::testFailedMethod() {

}

