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
        EpiIterator_4D *iter_v = lf->createEpiIterator<EpiIterator_4D>(VERTICAL);

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
    vigra::MultiArrayView<2,float> epi_Cross_h0 = lf->getHorizontalEpiChannel("r",24,2,0);
    vigra::MultiArrayView<2,float> epi_Cross_h1 = lf->getHorizontalEpiChannel("r",24,2,1);
    vigra::MultiArrayView<2,float> epi_Cross_v0 = lf->getVerticalEpiChannel("r",32,3,0);
    vigra::MultiArrayView<2,float> epi_Cross_v1 = lf->getVerticalEpiChannel("r",32,3,1);
     
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