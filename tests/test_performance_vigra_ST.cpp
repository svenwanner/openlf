/*
 * File:   test_operator.cpp
 * Author: swanner
 *
 * Created on May 19, 2014, 9:32:19 AM
 */

#include "test_performance_vigra_ST.hpp"


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

    //****************************************************************************************************************
    //** SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX SANDBOX *****
    //****************************************************************************************************************
    //**            PARAMETERS TO PLAY WITH                           ************************************************
    //****************************************************************************************************************
    //****************************************************************************************************************

     /*********************************************************************
     *                     Test from woods    
     *********************************************************************/
    std::vector<std::string> inslots;
    std::vector<std::string> outslots; 

    std::string method = "focused_vigra";// "vigra" or "focused_vigra" or "scharr5x5" or "focused_scharr5x5"
    OpenLF::operators::orientation orientation;
    OpenLF::operators::focuses f = {0,1,2,3,4,5,6,7,8,9,10}; // for focused ST
    //DIRECTION direction = HORIZONTAL; // or VERTICAL
    std::string coherence = "Yes"; // or "None"
    //int focus = 0; // different single focuses not for focused STs
    double inner_scale = 1.0;
    double outer_scale = 0.3;
    double smoothing_scale = outer_scale;
    double max_slope = 1.0;
    double coh_threshold = 0.95;

    OpenLF::lightfield::Lightfield_4D * lf = new OpenLF::lightfield::Lightfield_4D();
    lf->open(cfgnames["4D_high_rgb"]);
    OpenLF::operators::Structure_Tensor * ST = new OpenLF::operators::Structure_Tensor(inslots,outslots);
    ST->set(lf);

    array_2D epi_v = lf->getVerticalEpiChannel("r", 0, 0);
    std::string filename_epi_v = test_data2_dir+"epi_v.jpg";
    OpenLF::image::io::imsave_HQ_float(filename_epi_v, epi_v);

    array_2D epi_h = lf->getHorizontalEpiChannel("r", 0, 0);
    std::string filename_epi_h = test_data2_dir+"epi_h.jpg";
    OpenLF::image::io::imsave_HQ_float(filename_epi_h, epi_h);

    //ST->load_epi_containers("r");
/*
    array_2D depth = ST->get_depth_image_lightweight("r", method ,coherence, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);
    std::string filename_woods_depth = test_data2_dir+method+"_depth_woods.jpg";
    OpenLF::image::io::imsave_HQ_float(filename_woods_depth, depth);
*/

//horizontal
/*
    std::vector<array_2D> h = ST->reconstruct_depth_lightweight("r", method ,coherence, HORIZONTAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);


    CPPUNIT_ASSERT(h.size() == 35);
    for(int i=0;i<35;i++) {
        std::string filename_woods_h = test_data2_dir+method+"_orientation_image_h_"+std::to_string(i)+".jpg";
        OpenLF::image::io::imsave_HQ_float(filename_woods_h, h[i]);

    }

//vertical

    std::vector<array_2D> v = ST->reconstruct_depth_lightweight("r", method ,coherence, VERTICAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    CPPUNIT_ASSERT(v.size() == 35);

    for(int i=0;i<35;i++) {
   	 array_2D overlay_v_rotated(h[0].shape());
   	 vigra::rotateImage(v[i],overlay_v_rotated,90);
	 array_2D overlay_v_reflected(overlay_v_rotated.shape());
 	 vigra::reflectImage(overlay_v_rotated,overlay_v_reflected,vigra::horizontal);
  	 //overlay_v_reflected += h[0];

        std::string filename_woods_v = test_data2_dir+method+"_orientation_image_v"+std::to_string(i)+".jpg";
        //OpenLF::image::io::imsave_HQ_float(filename_woods_v, v[i]);
        OpenLF::image::io::imsave_HQ_float(filename_woods_v, overlay_v_reflected);
    }
*/




    /*********************************************************************
     *                     Test from buddha 4D     
     *********************************************************************/

    //std::string buddha_method = "vigra";

    OpenLF::lightfield::Lightfield_4D * lf_buddha = new OpenLF::lightfield::Lightfield_4D();
    lf_buddha->open(test_lf_buddha+"buddha_4D.cfg");
    OpenLF::operators::Structure_Tensor * ST_buddha = new OpenLF::operators::Structure_Tensor(inslots,outslots);
    ST_buddha->set(lf_buddha);
    //ST_buddha->load_epi_containers("r");

/*
    array_2D depth_buddha = ST_buddha->get_depth_image_lightweight("r", method ,coherence, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    std::string filename_buddha = test_lf_buddha+"buddha_depth_"+method+"channel=red.jpg";
    OpenLF::image::io::imsave_HQ_float(filename_buddha, depth_buddha);
*/
    


 std::vector<array_2D> h_buddha = ST_buddha->reconstruct_depth_lightweight("r", method ,coherence, HORIZONTAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    for(int i=0;i<81;i++) {
        std::string filename_buddha = test_lf_buddha+method+"_00"+std::to_string(i)+"_h.jpg";
        OpenLF::image::io::imsave_HQ_float(filename_buddha, h_buddha[i]);
    }
/*
    std::vector<array_2D> v_buddha = ST_buddha->reconstruct_depth_lightweight("r", method ,coherence, VERTICAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    for(int i=0;i<81;i++) {
         array_2D overlay_v_rotated(h_buddha[0].shape());
   	 vigra::rotateImage(v_buddha[i],overlay_v_rotated,90);
	 array_2D overlay_v_reflected(overlay_v_rotated.shape());
 	 vigra::reflectImage(overlay_v_rotated,overlay_v_reflected,vigra::horizontal);
        std::string filename_buddha = test_lf_buddha+method+"_00"+std::to_string(i)+"_v.jpg";
        OpenLF::image::io::imsave_HQ_float(filename_buddha, overlay_v_reflected);
        //OpenLF::image::io::imsave_HQ_float(filename_buddha, v_buddha[i]);
    }
*/
}
void test_operator::testFailedMethod() {

}
