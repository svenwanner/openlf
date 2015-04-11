/*
* Copyright (c) 2014 Sven Wanner
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of 
* this software and associated documentation files (the "Software"), to deal in 
* the Software without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
* Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all 
* copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "test_lightfield.hpp"




CPPUNIT_TEST_SUITE_REGISTRATION(test_lightfield);

test_lightfield::test_lightfield() {
}

test_lightfield::~test_lightfield() {
}

void test_lightfield::setUp() {
    
    imgnames["4D_high_bw"] = test_lf_4D_high+"4D_high_bw.png";
    imgnames["4D_high_rgb"] = test_lf_4D_high+"4D_high_rgb.png";
    imgnames["4D_wide_bw"] = test_lf_4D_wide+"4D_wide_bw.png";
    imgnames["4D_wide_rgb"] = test_lf_4D_wide+"4D_wide_rgb.png";
    
    imgnames["4D_high_rgb_h5"] = test_lf_4D_high+"4D_high_rgb.lf";
    
    imgnames["3DH_high_bw"] = test_lf_3DH_high+"3DH_high_bw.png";
    imgnames["3DH_high_rgb"] = test_lf_3DH_high+"3DH_high_rgb.png";
    imgnames["3DH_wide_bw"] = test_lf_3DH_wide+"3DH_wide_bw.png";
    imgnames["3DH_wide_rgb"] = test_lf_3DH_wide+"3DH_wide_rgb.png";
    
    imgnames["3DV_high_bw"] = test_lf_3DV_high+"3DV_high_bw.png";
    imgnames["3DV_high_rgb"] = test_lf_3DV_high+"3DV_high_rgb.png";
    imgnames["3DV_wide_bw"] = test_lf_3DV_wide+"3DV_wide_bw.png";
    imgnames["3DV_wide_rgb"] = test_lf_3DV_wide+"3DV_wide_rgb.png";
    
    imgnames["CROSS_high_bw"] = test_lf_CROSS_high+"CROSS_high_bw.png";
    imgnames["CROSS_high_rgb"] = test_lf_CROSS_high+"CROSS_high_rgb.png";
    imgnames["CROSS_wide_bw"] = test_lf_CROSS_wide+"CROSS_wide_bw.png";
    imgnames["CROSS_wide_rgb"] = test_lf_CROSS_wide+"CROSS_wide_rgb.png";
    
     
    cfgnames["4D_high_bw"] = test_lf_4D_high+"bw.cfg";
    cfgnames["4D_wide_bw"] = test_lf_4D_wide+"bw.cfg";
    cfgnames["4D_high_rgb"] = test_lf_4D_high+"rgb.cfg";
    cfgnames["4D_wide_rgb"] = test_lf_4D_wide+"rgb.cfg";
    cfgnames["4D_high_bw_sf"] = test_lf_4D_high+"4D_high_bw.cfg";
    cfgnames["4D_wide_bw_sf"] = test_lf_4D_wide+"4D_wide_bw.cfg";
    cfgnames["4D_high_rgb_sf"] = test_lf_4D_high+"4D_high_rgb.cfg";
    cfgnames["4D_wide_rgb_sf"] = test_lf_4D_wide+"4D_wide_rgb.cfg";
    
    cfgnames["4D_high_rgb_h5"] = test_lf_4D_high+"4D_high_rgb_h5.cfg";
    
    cfgnames["4D_diversity"] = test_data_dir+"OpenLF_testLF/4D/h4_v3_h60_w80/rgb.cfg";
    cfgnames["4D_diversity_roi"] = test_data_dir+"OpenLF_testLF/4D/h4_v3_h60_w80/rgb_roi.cfg";
    
    cfgnames["3DH_high_bw"] = test_lf_3DH_high+"bw.cfg";
    cfgnames["3DH_wide_bw"] = test_lf_3DH_wide+"bw.cfg";
    cfgnames["3DH_high_rgb"] = test_lf_3DH_high+"rgb.cfg";
    cfgnames["3DH_wide_rgb"] = test_lf_3DH_wide+"rgb.cfg";
    cfgnames["3DH_high_bw_sf"] = test_lf_3DH_high+"3DH_high_bw.cfg";
    cfgnames["3DH_wide_bw_sf"] = test_lf_3DH_wide+"3DH_wide_bw.cfg";
    cfgnames["3DH_high_rgb_sf"] = test_lf_3DH_high+"3DH_high_rgb.cfg";
    cfgnames["3DH_wide_rgb_sf"] = test_lf_3DH_wide+"3DH_wide_rgb.cfg";
     
    cfgnames["3DV_high_bw"] = test_lf_3DV_high+"bw.cfg";
    cfgnames["3DV_wide_bw"] = test_lf_3DV_wide+"bw.cfg";
    cfgnames["3DV_high_rgb"] = test_lf_3DV_high+"rgb.cfg";
    cfgnames["3DV_wide_rgb"] = test_lf_3DV_wide+"rgb.cfg"; 
    cfgnames["3DV_high_bw_sf"] = test_lf_3DV_high+"3DV_high_bw.cfg";
    cfgnames["3DV_wide_bw_sf"] = test_lf_3DV_wide+"3DV_wide_bw.cfg";
    cfgnames["3DV_high_rgb_sf"] = test_lf_3DV_high+"3DV_high_rgb.cfg";
    cfgnames["3DV_wide_rgb_sf"] = test_lf_3DV_wide+"3DV_wide_rgb.cfg";
    
    cfgnames["CROSS_high_bw"] = test_lf_CROSS_high+"bw.cfg";
    cfgnames["CROSS_wide_bw"] = test_lf_CROSS_wide+"bw.cfg";
    cfgnames["CROSS_high_rgb"] = test_lf_CROSS_high+"rgb.cfg";
    cfgnames["CROSS_wide_rgb"] = test_lf_CROSS_wide+"rgb.cfg";
    cfgnames["CROSS_high_bw_sf"] = test_lf_CROSS_high+"CROSS_high_bw.cfg";
    cfgnames["CROSS_wide_bw_sf"] = test_lf_CROSS_wide+"CROSS_wide_bw.cfg";
    cfgnames["CROSS_high_rgb_sf"] = test_lf_CROSS_high+"CROSS_high_rgb.cfg";
    cfgnames["CROSS_wide_rgb_sf"] = test_lf_CROSS_wide+"CROSS_wide_rgb.cfg";
    
    
    imgnames["4D_wide_r_epi_h0"] = test_lf_4D_wide+"epi_h0.png";
    imgnames["4D_wide_r_epi_h1"] = test_lf_4D_wide+"epi_h1.png";
    imgnames["4D_wide_r_epi_v0"] = test_lf_4D_wide+"epi_v0.png";
    imgnames["4D_wide_r_epi_v1"] = test_lf_4D_wide+"epi_v1.png";
    imgnames["4D_wide_rgb_epi_h1"] = test_lf_4D_wide+"rgb_epi_h1.png";
    imgnames["4D_wide_rgb_epi_v1"] = test_lf_4D_wide+"rgb_epi_v1.png";
    imgnames["4D_wide_bw_epi_h1"] = test_lf_4D_wide+"bw_epi_h1.png";
    imgnames["4D_wide_bw_epi_v1"] = test_lf_4D_wide+"bw_epi_v1.png";
    
    fnames["Horizontal_EpiIterTest_4D"] = test_lf_4D_wide+"horizontal_epiIterTest.txt";
    fnames["Vertical_EpiIterTest_4D"] = test_lf_4D_wide+"vertical_epiIterTest.txt";
    fnames["Horizontal_EpiIterTest_3DH"] = test_lf_3DH_wide+"horizontal_epiIterTest.txt";
    fnames["Vertical_EpiIterTest_3DV"] = test_lf_3DV_wide+"vertical_epiIterTest.txt";
    fnames["Horizontal_EpiIterTest_CROSS"] = test_lf_CROSS_wide+"horizontal_epiIterTest.txt";
    fnames["Vertical_EpiIterTest_CROSS"] = test_lf_CROSS_wide+"vertical_epiIterTest.txt";
}

void test_lightfield::tearDown() {
    cout << "\n\ntest suite runs through!" << endl;
}





void test_lightfield::test_epi_iterator()
{
    
    //==========================================================================
    // test 4D 
    //==========================================================================

    OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield_4D();
    CPPUNIT_ASSERT(lf->open(cfgnames["4D_wide_rgb"]));
    
    
    string line;
    ifstream gt_h;
    ifstream gt_v;
    gt_h.open (fnames["Horizontal_EpiIterTest_4D"], ios::in);
    gt_v.open (fnames["Vertical_EpiIterTest_4D"], ios::in);
    
    if (gt_h.is_open()) { 
        EpiIterator_4D *iter_h = lf->createEpiIterator<EpiIterator_4D>(HORIZONTAL);
        
        //#pragma omp parallel for
        for(iter_h->first(); !iter_h->end(); iter_h->next())
        //for(iter_h->first(); !iter_h->end(); iter_h->next())
        {
            getline (gt_h,line);
            vigra::MultiArrayView<2,float> epi = iter_h->get("r",1); 
            stringstream ss;
            ss << 255*epi(0,0);
            CPPUNIT_ASSERT(line==ss.str());
        }
        delete iter_h;
    }
    gt_h.close();
    
    if (gt_v.is_open()) {
        EpiIterator_4D *iter_v = lf->createEpiIterator<EpiIterator_4D>(VERTICAL);

        //#pragma omp parallel for
        for(iter_v->first(); !iter_v->end(); iter_v->next())
        {
            getline (gt_v,line);
            vigra::MultiArrayView<2,float> epi = iter_v->get("r",1);  
            stringstream ss;
            ss << 255*epi(0,0);
            CPPUNIT_ASSERT(line==ss.str());
        }
        delete iter_v;
    }
    gt_v.close();
    
    
    
    
    
    //==========================================================================
    // test 3DH
    //==========================================================================
    
    lf = new OpenLF::lightfield::Lightfield_3D();
    CPPUNIT_ASSERT(lf->open(cfgnames["3DH_wide_rgb"]));
    
    gt_h.open (fnames["Horizontal_EpiIterTest_3DH"], ios::in);
    
    if (gt_h.is_open()) { 
        EpiIterator_3D *iter_h = lf->createEpiIterator<EpiIterator_3D>(HORIZONTAL);

        //#pragma omp parallel for
        //for(int n = iter_h->first(); n <= iter_h->end(); n = iter_h->next())
        //for(int n = 0; n <= iter_h->end(); n = iter_h->next())
        //for(it = iter_h->first(); it <= iter_h->end(); it++)
        for(iter_h->first(); !iter_h->end(); iter_h->next())
        {   
            

            getline (gt_h,line);
            vigra::MultiArrayView<2,float> epi = iter_h->get("r",1);
            
            stringstream ss;
            ss << 255*epi(0,0);
            CPPUNIT_ASSERT(line==ss.str());
        }
        delete iter_h;
    }
    gt_h.close();
    
    
    
    //==========================================================================
    // test 3DV
    //==========================================================================
    
    lf = new OpenLF::lightfield::Lightfield_3D();
    CPPUNIT_ASSERT(lf->open(cfgnames["3DV_wide_rgb"]));
    
    gt_v.open (fnames["Vertical_EpiIterTest_3DV"], ios::in);
    
    if (gt_h.is_open()) { 
        EpiIterator_3D *iter_h = lf->createEpiIterator<EpiIterator_3D>(VERTICAL);
        
        //#pragma omp parallel for
        for(iter_h->first(); !iter_h->end(); iter_h->next())
        {
            getline (gt_h,line);
            vigra::MultiArrayView<2,float> epi = iter_h->get("r",1);  
            
            stringstream ss;
            ss << 255*epi(0,0);
            CPPUNIT_ASSERT(line==ss.str());
        }
        delete iter_h;
    }
    gt_v.close();
    
    
    
    
    //==========================================================================
    // test CROSS
    //==========================================================================
    
    
    lf = new OpenLF::lightfield::Lightfield_CROSS();
    CPPUNIT_ASSERT(lf->open(cfgnames["CROSS_wide_rgb"]));

    gt_h.open (fnames["Horizontal_EpiIterTest_CROSS"], ios::in);
    gt_v.open (fnames["Vertical_EpiIterTest_CROSS"], ios::in);
    
    if (gt_h.is_open()) { 
        EpiIterator_CROSS *iter_h = lf->createEpiIterator<EpiIterator_CROSS>(HORIZONTAL);

        //#pragma omp parallel for
        for(iter_h->first(); !iter_h->end(); iter_h->next())
        {
            getline (gt_h,line);
            vigra::MultiArrayView<2,float> epi = iter_h->get("r",1);  

            stringstream ss;
            ss << 255*epi(0,0);
            CPPUNIT_ASSERT(line==ss.str());
        }
        delete iter_h;
    }
    gt_h.close();

     
    if (gt_v.is_open()) {
        EpiIterator_CROSS *iter_v = lf->createEpiIterator<EpiIterator_CROSS>(VERTICAL);

        //#pragma omp parallel for
        for(iter_v->first(); !iter_v->end(); iter_v->next())
        {
            getline (gt_v,line);
            vigra::MultiArrayView<2,float> epi = iter_v->get("r",1);  

            stringstream ss;
            ss << 255*epi(0,0);
            CPPUNIT_ASSERT(line==ss.str());
        }
        delete iter_v;
    }
    gt_v.close();
}





void test_lightfield::test_epi_access()
{
    // get ground truth epis
    map<string,OpenLF::image::ImageChannel> epi_r_h0;
    OpenLF::image::io::imread(imgnames["4D_wide_r_epi_h0"],epi_r_h0);
    map<string,OpenLF::image::ImageChannel> epi_r_h1;
    OpenLF::image::io::imread(imgnames["4D_wide_r_epi_h1"],epi_r_h1);
    map<string,OpenLF::image::ImageChannel> epi_r_v0;
    OpenLF::image::io::imread(imgnames["4D_wide_r_epi_v0"],epi_r_v0);
    map<string,OpenLF::image::ImageChannel> epi_r_v1;
    OpenLF::image::io::imread(imgnames["4D_wide_r_epi_v1"],epi_r_v1);
    
    map<string,OpenLF::image::ImageChannel> rgb_epi_h1;
    OpenLF::image::io::imread(imgnames["4D_wide_rgb_epi_h1"],rgb_epi_h1);
    map<string,OpenLF::image::ImageChannel> rgb_epi_v1;
    OpenLF::image::io::imread(imgnames["4D_wide_rgb_epi_v1"],rgb_epi_v1);
    map<string,OpenLF::image::ImageChannel> bw_epi_h1;
    OpenLF::image::io::imread(imgnames["4D_wide_bw_epi_h1"],bw_epi_h1);
    map<string,OpenLF::image::ImageChannel> bw_epi_v1;
    OpenLF::image::io::imread(imgnames["4D_wide_bw_epi_v1"],bw_epi_v1);
    
    
    //==========================================================================
    // test 4D epi access
    //==========================================================================
    OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield_4D();
    CPPUNIT_ASSERT(lf->open(cfgnames["4D_wide_rgb"]));
    
     //get epi channel
    vigra::MultiArrayView<2,float> epi_h0 = lf->getHorizontalEpiChannel("r",24,2,0);
    vigra::MultiArrayView<2,float> epi_h1 = lf->getHorizontalEpiChannel("r",24,2,1);
    vigra::MultiArrayView<2,float> epi_v0 = lf->getVerticalEpiChannel("r",32,3,0);
    vigra::MultiArrayView<2,float> epi_v1 = lf->getVerticalEpiChannel("r",32,3,1);
    
    float sum_h0,sum_h1,sum_v0,sum_v1;
    sum_h0=0; sum_h1=0; sum_v0=0; sum_v1=0;
    
    for( int i=0; i<5; i++)
    {
        for( int j=0; j<15; j++)
        {
            sum_h0 += abs(epi_h0(j,i)-epi_r_h0["bw"](j,i));
            sum_h1 += abs(epi_h1(j,i)-epi_r_h1["bw"](j,i));
            sum_v0 += abs(epi_v0(j,i)-epi_r_v0["bw"](j,i));
            sum_v1 += abs(epi_v1(j,i)-epi_r_v1["bw"](j,i));
        }   
    }
    
    CPPUNIT_ASSERT(sum_h0<0.00000001);
    CPPUNIT_ASSERT(sum_h1<0.00000001);
    CPPUNIT_ASSERT(sum_v0<0.00000001);
    CPPUNIT_ASSERT(sum_v1<0.00000001);
    
    sum_h0=0; sum_h1=0; sum_v0=0; sum_v1=0;
    
    
    vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> > epi_h;
    lf->getHorizontalEpi(24, 2, 1, epi_h);
    
    vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> > epi_v;
    lf->getHorizontalEpi(32, 3, 1, epi_v);
    
    for( int i=0; i<5; i++)
    {
        for( int j=0; j<15; j++)
        {
            sum_h1 += abs(epi_h(j,i)[0]-255*rgb_epi_h1["r"](j,i));
            sum_v1 += abs(epi_v(j,i)[0]-255*rgb_epi_v1["r"](j,i));
        }   
    }
    
    CPPUNIT_ASSERT(sum_h1<0.00000001);
    CPPUNIT_ASSERT(sum_v1<0.00000001);
    
    sum_h1=0; sum_v1=0;
    
    lf = new OpenLF::lightfield::Lightfield_4D();
    CPPUNIT_ASSERT(lf->open(cfgnames["4D_wide_bw"]));
    lf->getHorizontalEpi(24, 2, 1, epi_h);
    
    lf->getHorizontalEpi(32, 3, 1, epi_v);
    
    for( int i=0; i<5; i++)
    {
        for( int j=0; j<15; j++)
        {
            sum_h1 += abs(epi_h(j,i)[0]-255*bw_epi_h1["r"](j,i));
            sum_v1 += abs(epi_v(j,i)[0]-255*bw_epi_v1["r"](j,i));
        }   
    }
    
    CPPUNIT_ASSERT(sum_h1<0.00000001);
    CPPUNIT_ASSERT(sum_v1<0.00000001);
    
    sum_h1=0; sum_v1=0;
    
    
    
    
    //==========================================================================
    // test 3DH epi access
    //==========================================================================
    lf = new OpenLF::lightfield::Lightfield_3D();
    CPPUNIT_ASSERT(lf->open(cfgnames["3DH_wide_rgb"]));
    
    vigra::MultiArrayView<2,float> epi_3DH_h0 = lf->getHorizontalEpiChannel("r",24,0,0);
    vigra::MultiArrayView<2,float> epi_3DH_h1 = lf->getHorizontalEpiChannel("r",24,0,1);
    
    for( int i=0; i<5; i++)
    {
        for( int j=0; j<15; j++)
        {
            //sum_h0 += abs(epi_r_h0["bw"](j,i));
            sum_h0 += abs(epi_3DH_h0(j,i)-epi_r_h0["bw"](j,i));
            sum_h1 += abs(epi_3DH_h1(j,i)-epi_r_h1["bw"](j,i));
        }   
    }
    
    CPPUNIT_ASSERT(sum_h0<0.00000001);
    CPPUNIT_ASSERT(sum_h1<0.00000001);
    
    sum_h0=0; sum_h1=0;
    
    
    //==========================================================================
    // test 3DV epi access
    //==========================================================================
    lf = new OpenLF::lightfield::Lightfield_3D();
    CPPUNIT_ASSERT(lf->open(cfgnames["3DV_wide_rgb"]));
    
    vigra::MultiArrayView<2,float> epi_3DV_v0 = lf->getVerticalEpiChannel("r",32,0,0);
    vigra::MultiArrayView<2,float> epi_3DV_v1 = lf->getVerticalEpiChannel("r",32,0,1);
    
    for( int i=0; i<15; i++)
    {
        for( int j=0; j<5; j++)
        {
            sum_v0 += abs(epi_3DV_v0(i,j)-epi_r_v0["bw"](i,j));
            sum_v1 += abs(epi_3DV_v1(i,j)-epi_r_v1["bw"](i,j));
        }   
    }
    
    CPPUNIT_ASSERT(sum_v0<0.00000001);
    CPPUNIT_ASSERT(sum_v1<0.00000001);
    
    sum_v0=0; sum_v1=0;
    
    //==========================================================================
    // test CROSS epi access
    //==========================================================================
    lf = new OpenLF::lightfield::Lightfield_CROSS();
    CPPUNIT_ASSERT(lf->open(cfgnames["CROSS_wide_rgb"]));
       
     //get epi channel
    /*vigra::MultiArrayView<2,float> epi_Cross_h0 = lf->getHorizontalEpiChannel("r",24,2,0);
    vigra::MultiArrayView<2,float> epi_Cross_h1 = lf->getHorizontalEpiChannel("r",24,2,1);
    vigra::MultiArrayView<2,float> epi_Cross_v0 = lf->getVerticalEpiChannel("r",32,3,0);
    vigra::MultiArrayView<2,float> epi_Cross_v1 = lf->getVerticalEpiChannel("r",32,3,1);
    */ 

    vigra::MultiArrayView<2,float> epi_Cross_h0 = lf->getHorizontalEpiChannel("r",24,0,0);
    vigra::MultiArrayView<2,float> epi_Cross_h1 = lf->getHorizontalEpiChannel("r",24,0,1);
    vigra::MultiArrayView<2,float> epi_Cross_v0 = lf->getVerticalEpiChannel("r",32,0,0);
    vigra::MultiArrayView<2,float> epi_Cross_v1 = lf->getVerticalEpiChannel("r",32,0,1);
    for( int i=0; i<5; i++)
    {
        for( int j=0; j<15; j++)
        {
            sum_h0 += abs(epi_Cross_h0(j,i)-epi_r_h0["bw"](j,i));
            sum_h1 += abs(epi_Cross_h1(j,i)-epi_r_h1["bw"](j,i));
            sum_v0 += abs(epi_Cross_v0(j,i)-epi_r_v0["bw"](j,i));
            sum_v1 += abs(epi_Cross_v1(j,i)-epi_r_v1["bw"](j,i));
        }   
    }
    
    CPPUNIT_ASSERT(sum_h0<0.00000001);
    CPPUNIT_ASSERT(sum_h1<0.00000001);
    CPPUNIT_ASSERT(sum_v0<0.00000001);
    CPPUNIT_ASSERT(sum_v1<0.00000001);
}





void test_lightfield::test_loxel_access()
{
    OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield_4D();
    CPPUNIT_ASSERT(lf->open(cfgnames["4D_wide_rgb"]));
    
    float r,g,b;
    
    r = lf->getLoxel(3,2,9,7,"r");
    g = lf->getLoxel(3,2,9,7,"g");
    b = lf->getLoxel(3,2,9,7,"b");
    
    CPPUNIT_ASSERT(r*255==62);
    CPPUNIT_ASSERT(g*255==74);
    CPPUNIT_ASSERT(b*255==26);
    
    r = lf->getLoxel(3,2,31,36,"r");
    g = lf->getLoxel(3,2,31,36,"g");
    b = lf->getLoxel(3,2,31,36,"b");
    
    CPPUNIT_ASSERT(r*255==49);
    CPPUNIT_ASSERT(g*255==30);
    CPPUNIT_ASSERT(b*255==11);
    
    vector<float> rgb;
    vector<string> chls {"r","b"};
    
    lf->getLoxel(3,2,9,7,chls,rgb);
    CPPUNIT_ASSERT(rgb[0]*255==62);
    CPPUNIT_ASSERT(rgb[1]*255==26);
    
    lf->getLoxel(3,2,31,36,chls,rgb);
    CPPUNIT_ASSERT(rgb[0]*255==49);
    CPPUNIT_ASSERT(rgb[1]*255==11);
    
    
    //Testing 3D_horizontal
    OpenLF::lightfield::Lightfield_3D* lf3D = new OpenLF::lightfield::Lightfield_3D();
    CPPUNIT_ASSERT(lf3D->open(cfgnames["3DH_wide_rgb"]));
    CPPUNIT_ASSERT(lf3D->type()==LF_3DH);
    
    //4 arguments
    r = lf3D->getLoxel(5,0,21,25,"r");
    g = lf3D->getLoxel(5,0,21,25,"g");
    b = lf3D->getLoxel(5,0,21,25,"b");
                        
    CPPUNIT_ASSERT(r*255==93);
    CPPUNIT_ASSERT(g*255==56);
    CPPUNIT_ASSERT(b*255==25);
    
    //3 arguments
    r = lf3D->getLoxel(5,21,25,"r");
    g = lf3D->getLoxel(5,21,25,"g");
    b = lf3D->getLoxel(5,21,25,"b");
                        
    CPPUNIT_ASSERT(r*255==93);
    CPPUNIT_ASSERT(g*255==56);
    CPPUNIT_ASSERT(b*255==25);
    
    
    // Testing 3D_vertical
    OpenLF::lightfield::Lightfield_3D* lf3DV =new OpenLF::lightfield::Lightfield_3D();
    CPPUNIT_ASSERT(lf3DV->open(cfgnames["3DV_high_rgb"]));
    CPPUNIT_ASSERT(lf3DV->type()==LF_3DV);
    

    // 4 arguments
    r = lf3DV->getLoxel(0,3,0,0,"r");
    g = lf3DV->getLoxel(0,3,0,0,"g");
    b = lf3DV->getLoxel(0,3,0,0,"b");

    CPPUNIT_ASSERT(r*255==47);
    CPPUNIT_ASSERT(g*255==56);
    CPPUNIT_ASSERT(b*255==20);
    
    //3 arguments
    r = lf3DV->getLoxel(6,23,27,"r");
    g = lf3DV->getLoxel(6,23,27,"g");
    b = lf3DV->getLoxel(6,23,27,"b");
    
    CPPUNIT_ASSERT(r*255==114);
    CPPUNIT_ASSERT(g*255==89);
    CPPUNIT_ASSERT(b*255==56);
    
    //Testing CROSS
    OpenLF::lightfield::Lightfield* lfc = new OpenLF::lightfield::Lightfield_CROSS();
    CPPUNIT_ASSERT(lfc->open(cfgnames["CROSS_wide_rgb"]));
    CPPUNIT_ASSERT(lfc->type()==LF_CROSS);
    
    r = lfc->getLoxel(3,0,27,10,"r");
    g = lfc->getLoxel(3,0,27,10,"g");
    b = lfc->getLoxel(3,0,27,10,"b");
    
    CPPUNIT_ASSERT(r*255==104);
    CPPUNIT_ASSERT(g*255==75);
    CPPUNIT_ASSERT(b*255==45);
    
    r = lfc->getLoxel(0,2,27,10,"r");
    g = lfc->getLoxel(0,2,27,10,"g");
    b = lfc->getLoxel(0,2,27,10,"b");
    
    CPPUNIT_ASSERT(r*255==104);
    CPPUNIT_ASSERT(g*255==75);
    CPPUNIT_ASSERT(b*255==45);
    
    r = lfc->getLoxel(0,1,11,3,"r");
    g = lfc->getLoxel(0,1,11,3,"g");
    b = lfc->getLoxel(0,1,11,3,"b");
    
    CPPUNIT_ASSERT(r*255==63);
    CPPUNIT_ASSERT(g*255==70);
    CPPUNIT_ASSERT(b*255==22);
    
    
}





void test_lightfield::test_instantiate_Lightfield()
{
    // test instancing via the default constructor and open
    OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield_4D();
    // test open from hdf5
    CPPUNIT_ASSERT(lf->open(imgnames["4D_high_rgb_h5"]));
    
    // test has property method
    CPPUNIT_ASSERT(lf->hasProperty("width"));
    CPPUNIT_ASSERT(!lf->hasProperty("notThere"));
    CPPUNIT_ASSERT(lf->type()==LF_4D);
    
    // test getting properties
    float tmp; int tmp2;
    CPPUNIT_ASSERT(lf->getProperty("aperture",tmp));
    CPPUNIT_ASSERT(tmp==2.8f);
    CPPUNIT_ASSERT(lf->getProperty("height",tmp2));
    CPPUNIT_ASSERT(tmp2==64);
    
    // create pointer to a map and a MultiArray to keep the addresses of the lf data
    map< string,OpenLF::image::ImageChannel> *test_channels = NULL;
    OpenLF::image::ImageChannel *test_image = NULL;
    
    // get the pointers to the lf data
    lf->data(&test_channels);
    lf->data("g",&test_image);
    
    CPPUNIT_ASSERT(test_channels!=NULL);
    CPPUNIT_ASSERT(test_image!=NULL);
    
    string p = test_result_dir+"4D_high_rgb_h5.png";
    OpenLF::image::io::imsave(p,*test_channels);
    p = test_result_dir+"4D_high_rgb_h5_g.png";
    OpenLF::image::io::imsave(p,*test_image);
    
    test_channels->clear();
    test_image = NULL;
    
    // test open new data set from config file
    CPPUNIT_ASSERT(lf->open(cfgnames["4D_wide_rgb"]));
    
    // get the pointers to the lf data
    lf->data(&test_channels);
    lf->data("g",&test_image);
    
    CPPUNIT_ASSERT(test_channels!=NULL);
    CPPUNIT_ASSERT(test_image!=NULL);
    
    p = test_result_dir+"4D_wide_rgb.png";
    OpenLF::image::io::imsave(p,*test_channels);
    p = test_result_dir+"4D_wide_rgb_g.png";
    OpenLF::image::io::imsave(p,*test_image);
}

void test_lightfield::test_multipleWaysOfInstantiating(){
    //As one can see in this example, there is different ways of loading
    //and saving Lightfield data
    
    //Loading ROI of lightfield to an ImageChannel map
    map< string,OpenLF::image::ImageChannel> channels;
    OpenLF::lightfield::Properties properties;
    // pointer storing the FileHandler instance
    OpenLF::lightfield::io::DataHandler *dataHandler;
    // init FileHandler and test if read data works
    dataHandler = new OpenLF::lightfield::io::FileHandler(cfgnames["4D_diversity_roi"],&properties);
    CPPUNIT_ASSERT(dataHandler->readData(channels));
    string p = test_result_dir+"4D_div_roi.png";
    OpenLF::image::io::imsave(p,channels);
    //Saving red channel
    vector<string> keys_to_save = {"r"};
    p = test_result_dir+"4D_div_red.png";
    OpenLF::image::io::imsave(p,channels,keys_to_save);
    
    //Loading Lightfield data to a Lightfield object        
    OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield_4D();
    // test open from config-file
    CPPUNIT_ASSERT( lf ->open(cfgnames["4D_diversity"]));
    //Saving blue channel
    OpenLF::image::ImageChannel *blue = NULL;
    lf->data("b",&blue);
    p = test_result_dir+"4D_div_blue.png";
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(p,*blue));
}

void test_lightfield::test_epi_handling()
{
    //**************************************************
    //*** Buddha
    //**************************************************
/*
    map <int,string> buddha_4d;
    for (int i=0, i<=80, i++) {
        if(i<10) {
        string a = "000" + i;
        }
        else {
        string a = "00" + i;
        }
    	//imgnames["Buddha_4D"+a] = test_lf_Buddha_4D+a+".png";
        buddha_4d[i] = test_lf_Buddha_4D + a;
    }
    
    map <int,string> buddha_h;
    for (int i=0, i<=8, i++) {
       
        string a = "000" + i;

        //imgnames["Buddha_h"+a] = test_lf_Buddha_h+a+".png";
        buddha_h[i] = test_lf_Buddha_h + a;
    }
    
    map <int,string> buddha_v;
    for (int i=0, i<=8, i++) {

        string a = "000" + i;

        //imgnames["Buddha_v"+a] = test_lf_Buddha_v+a+".png";
        buddha_v[i] = test_lf_Buddha_v + a;
    }
*/
  

    
    //****************************************************************
    //*** Lightfield 3D
    //****************************************************************

    OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield_3D();
    CPPUNIT_ASSERT(lf->open(cfgnames["3DH_wide_rgb"]));
    
    vigra::MultiArrayView<2,float> epi_3DH_h0 = lf->getHorizontalEpiChannel("r",24,0,0);
    std::string filename3 = test_data2_dir+"Epi3DH0.jpg";
    OpenLF::image::io::imsave(filename3, epi_3DH_h0);

    vigra::MultiArrayView<2,float> epi_3DH_h1 = lf->getHorizontalEpiChannel("r",24,0,1);
    std::string filename4 = test_data2_dir+"Epi3DH1.jpg";
    OpenLF::image::io::imsave(filename4, epi_3DH_h1);

    vigra::MultiArrayView<2,float> epi_3DH_h2 = lf->getHorizontalEpiChannel("r",24,0,2);
    std::string filename5 = test_data2_dir+"Epi3DH2.jpg";
    OpenLF::image::io::imsave(filename5, epi_3DH_h2);


    //**************************************************
    //*** Lightfield 4D
    //**************************************************
    
    map<string,OpenLF::image::ImageChannel> epi_r_h0;
    OpenLF::image::io::imread(imgnames["4D_wide_r_epi_h0"],epi_r_h0);

    vigra::MultiArray<2,float> image(15,5);

    for( int i=0; i<5; i++)
    {
        for( int j=0; j<15; j++)
        {
            CPPUNIT_ASSERT(image(j,i)==0.0f);
        }
    }

    
    for( int i=0; i<5; i++)
    {
        for( int j=0; j<15; j++)
        {
            image(j,i) = epi_r_h0["bw"](j,i);
            CPPUNIT_ASSERT(image(j,i)!=0.0f);
        }
    }

    std::string filename1 = test_data2_dir+"image.jpg";
    std::string filename2 = test_data2_dir+"Epi4DH.jpg";

    OpenLF::image::io::imsave(filename1, image);
    OpenLF::image::io::imsave(filename2, epi_r_h0["bw"]);

    //-------------------------
    
    lf = new OpenLF::lightfield::Lightfield_4D();
    CPPUNIT_ASSERT(lf->open(cfgnames["4D_wide_rgb"]));
    
    map<string,OpenLF::image::ImageChannel> image4D;
    OpenLF::image::io::imread(imgnames["4D_wide_rgb"], image4D);

    std::string filename6 = test_data2_dir+"image4D.jpg";
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename6, image4D));

    vigra::MultiArrayView<2,float> epi_h0 = lf->getHorizontalEpiChannel("r",24,0,0);
    vigra::MultiArrayView<2,float> epi_h1 = lf->getHorizontalEpiChannel("r",24,0,1);
    vigra::MultiArrayView<2,float> epi_h2 = lf->getHorizontalEpiChannel("r",24,0,2);
    vigra::MultiArrayView<2,float> epi_h3 = lf->getHorizontalEpiChannel("r",24,0,3);

    std::string filename7 = test_data2_dir+"epi4D_24_0.jpg";
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename7, epi_h0));
    std::string filename8 = test_data2_dir+"epi4D_24_1.jpg";
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename8, epi_h1));
    std::string filename9 = test_data2_dir+"epi4D_24_2.jpg";
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename9, epi_h2));
    std::string filename10 = test_data2_dir+"epi4D_24_3.jpg";
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename10, epi_h3));

    CPPUNIT_ASSERT(epi_h0.width() == lf->imgWidth());
    CPPUNIT_ASSERT(epi_h0.height() == lf->cams_h());
    CPPUNIT_ASSERT(epi_h1.width() == lf->imgWidth()-6);
    CPPUNIT_ASSERT(epi_h1.height() == lf->cams_h());
    CPPUNIT_ASSERT(epi_h2.width() == lf->imgWidth()-12);
    CPPUNIT_ASSERT(epi_h2.height() == lf->cams_h());
    CPPUNIT_ASSERT(epi_h3.width() == lf->imgWidth()-18);
    CPPUNIT_ASSERT(epi_h3.height() == lf->cams_h());

    //****************************************************************
    //**** single image
    //****************************************************************
    OpenLF::lightfield::Lightfield* lf1 = new OpenLF::lightfield::Lightfield_4D();
    CPPUNIT_ASSERT(lf1->open(cfgnames["4D_wide_rgb"]));
    vigra::MultiArrayView<2,float> image1;
    lf1->getImage(1,1,"r",image1);
    std::string filename11 = test_data2_dir+"LF4Dimage1.jpg";
    vigra::MultiArrayView<2,float> image1view = image1;
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename11, image1view));
 
    //****************************************************************
    //**** ROI
    //****************************************************************

    lf = new OpenLF::lightfield::Lightfield_4D();
    CPPUNIT_ASSERT(lf->open(cfgnames["4D_wide_rgb"]));
    //vigra::MultiArray<2,float> ROI(10,10); 

    //****************************************************************
    //**** Loxel
    //****************************************************************

    lf = new OpenLF::lightfield::Lightfield_4D();
    lf->open(cfgnames["4D_wide_rgb"]);
    
    int w = lf->imgWidth();
    int h = lf->imgHeight();
    CPPUNIT_ASSERT(w==64);
    CPPUNIT_ASSERT(h==48);
    vigra::MultiArray<2,float> Loxels(w,h); 

    for( int i=0; i<h; i++)
    {
        for( int j=0; j<w; j++)
        {
            Loxels(j,i) = lf->getLoxel(1, 1, j, i, "r");
        }
    }
    
    std::string filename12 = test_data2_dir+"LF4DLoxels1.jpg";
    CPPUNIT_ASSERT(OpenLF::image::io::imsave(filename12, Loxels));
    
}

void test_lightfield::test_image_access(){
    /*
     * This test is testing the getImage() functions of the Lightfield classes.
     */
    
    //==========================================================================
    // test 4D 
    //==========================================================================
    
    //Loading Lightfield data to a Lightfield object        
    //OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield_4D();
    // test open from config-file
    //CPPUNIT_ASSERT( lf ->open(cfgnames["4D_diversity"]));
    //Testing getImage to MultiArrayView
    //vigra::MultiArrayView<2,float> fish_mav_1 = vigra::MultiArrayView<2,float>();
    //lf->getImage(0,2,"b",fish_mav_1);
    //OpenLF::image::io::imsave(test_result_dir+"4D_getImageFish_MAV_b.jpg",fish_mav_1);
    
    //Testing getImage() to MultiArray
    //vigra::MultiArray<2,float> camel_ma = vigra::MultiArray<2,float>();
    //lf->getImage(3,0,camel_ma);
    //string filename = test_result_dir+"4D_getImageCamel_MA.jpg";
    //SegFault
    //vigra::exportImage(camel_ma,vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
    //OpenLF::image::ImageChannel camel_fromMA(camel_ma);
    //SegFault
    //OpenLF::image::io::imsave(test_result_dir+"4D_getImageCamel_ICfromMA.jpg",camel_fromMA);
    
    // Generating ImageChannel from the MultiArrayView
    // This produces very weird output. I don't understand this bug so far.
    //OpenLF::image::ImageChannel fish_ic(fish_mav_1);
     //SegFault
    //OpenLF::image::io::imsave(test_result_dir+"4D_getImageFish_ICfromMAVfromLF_b.jpg",fish_ic);
    //For comparison
    //map< std::string,OpenLF::image::ImageChannel > tmpMap;
    //SegFault
    //OpenLF::image::io::imread(test_data_dir+"OpenLF_testLF/4D/h4_v3_h60_w80/rgb/0009.jpg",tmpMap);
    //OpenLF::image::ImageChannel tmpIC = tmpMap["r"];
    //vigra::MultiArrayView<2,float> tmpMAV = *tmpIC.image();
    //OpenLF::image::ImageChannel fromFishMAV(tmpMAV);
    //OpenLF::image::io::imsave(test_result_dir+"4D_ImageChannelFromMAV_normal.jpg",fromFishMAV);
    
    
}
