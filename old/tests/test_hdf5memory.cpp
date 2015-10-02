//
// Created by lukasdsauer on 01.06.15.
//

#include <OpenLF/lightfield/Lightfield_4D.hpp>
#include "test_hdf5memory.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(test_hdf5memory);

test_hdf5memory::test_hdf5memory() {
}

test_hdf5memory::~test_hdf5memory() {
}

void test_hdf5memory::setUp() {

}

void test_hdf5memory::tearDown() {
}

void test_hdf5memory::testBasic() {
    //Generating a HDF5-File for the test.
    OpenLF::lightfield::Lightfield *lf = new OpenLF::lightfield::Lightfield_4D(test_lf_4D_high+"4D_high_rgb.lf");
    lf->save(test_result_dir+"HDF5Memory_test.lf");

    // Initiliazing the HDF5Memory object using the file we just generated
    OpenLF::operators::HDF5Memory file(test_result_dir+"HDF5Memory_test.lf", "MyOperator123");

    // Test save a MultiArrayView
    vigra::MultiArrayView<2,float> *img = new vigra::MultiArrayView<2,float>();
    lf->getImage(2,2,"r", *img);
    file.saveProcessResult("red2_2_MAV", *img);

    // Test open to a ImageChannel (relative path)
    OpenLF::image::ImageChannel *input = new OpenLF::image::ImageChannel();
    file.openChannel("red2_2_MAV", *input);
    OpenLF::image::io::imsave(test_result_dir+"HDF5Memory_openchannel_relative_IC.jpg",*input);

    // Test save an ImageChannel (absolute path)
    file.saveProcessResult("/MyOperator123/red2_2_IC", *input);

    // Test open to MultiArray (relative path)
    vigra::MultiArray<2,float> *input_MA = new vigra::MultiArray<2,float>();
    file.openChannel("red2_2_IC", *input_MA);
    OpenLF::image::io::imsave(test_result_dir+"HDF5Memory_openchannel_relative_MA.jpg",*input_MA);

    vigra::MultiArray<2,float> *input_MA2 = new vigra::MultiArray<2,float>();

    // Test open to MultiArray (absolute path)
    file.openChannel("/LF/r",*input_MA2);
    OpenLF::image::io::imsave(test_result_dir+"HDF5Memory_openchannel_absolute_MA.jpg",*input_MA2);

    // Test open to MultiArray (absolute path)
    OpenLF::image::ImageChannel *input2 = new OpenLF::image::ImageChannel();
    file.openChannel("/LF/g",*input2);
    OpenLF::image::io::imsave(test_result_dir+"HDF5Memory_openchannel_absolute_IC.jpg",*input2);

}