#include "test_lukas.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_lukas);

test_lukas::test_lukas() {
}

test_lukas::~test_lukas() {   
}

void test_lukas::setUp() {
}

void test_lukas::tearDown() {   
    cout << "\n\nall tests finished" << endl;
}

void test_lukas::test_exmp(){
//    //File paths
//    const string dir = test_data_dir+"OpenLF_testLF/Buddha/";
//    const string fname = dir+"buddha.h5";
//    const string output_dir = dir+"output/";
//    
//    
//    // test instancing via the default constructor and open
//    OpenLF::lightfield::Lightfield* lf = new OpenLF::lightfield::Lightfield_4D();
//    // test open from hdf5
//    CPPUNIT_ASSERT(lf->open(fname));
//    
//    string p;
//    
//    // create pointer to a map and a MultiArray to keep the addresses of the lf data
//    map< string,OpenLF::image::ImageChannel> *test_channels = NULL;
//    OpenLF::image::ImageChannel *test_image = NULL;
//    
//    // get the pointers to the lf data
//    lf->data(&test_channels);
//    lf->data("g",&test_image);
//    
//    CPPUNIT_ASSERT(test_channels!=NULL);
//    CPPUNIT_ASSERT(test_image!=NULL);
//    
//    p = output_dir+"4D_wide_rgb.png";
//    OpenLF::image::io::imsave(p,*test_channels);
//    p = output_dir+"4D_wide_rgb_g.png";
//    OpenLF::image::io::imsave(p,*test_image);
}