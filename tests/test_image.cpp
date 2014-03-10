#include "test_image.hpp"
#include "image/image.hpp"
#include "visualize/imgshow.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(image_test);

image_test::image_test() {
}

image_test::~image_test() {
}

void image_test::setUp() {
    lena_rgb_path = test_data_dir+"lena_rgb.jpg";
    lena_bw_path = test_data_dir+"lena_bw.jpg";
    lena_width = 512;
    lena_height = 576;
}

void image_test::tearDown() {
}

void image_test::testConstructor() {
    
    // output filename pattern
    string filename_pattern = string(test_result_dir)+"save_test_";
    string filename;
    
    OpenLF::Image* img = new OpenLF::Image();
    
    CPPUNIT_ASSERT(img->width()==0);
    CPPUNIT_ASSERT(img->height()==0);
    CPPUNIT_ASSERT(img->channels()==0);
    CPPUNIT_ASSERT(img->label()=="");
    img->set_label("test");
    CPPUNIT_ASSERT(img->label()=="test");
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
    img->fill_image_channel(0,0.8,0.1);
    img->fill_image_channel(1,0.2,0.05);
    
    CPPUNIT_ASSERT(img->width()==10);
    CPPUNIT_ASSERT(img->height()==10);
    CPPUNIT_ASSERT(img->channels()==2);
    CPPUNIT_ASSERT(img->label()=="vec");
    
    // test vec image saving
    filename = filename_pattern+"vec.jpg"; img->save(filename);
    filename = filename_pattern+"vec.png"; img->save(filename);
    filename = filename_pattern+"vec.tif"; img->save(filename);
    filename = filename_pattern+"vec.gif"; img->save(filename);
    filename = filename_pattern+"vec.bmp"; img->save(filename);
    //filename = filename_pattern+"vec.exr"; img->save(filename);
    
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
    
    CPPUNIT_ASSERT(img->width()==lena_width);
    CPPUNIT_ASSERT(img->height()==lena_height);
    CPPUNIT_ASSERT(img->channels()==1);
    CPPUNIT_ASSERT(img->label()=="bw");
    
    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
        img->get_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i],px);
        total_diff = total_diff + abs(LENA_TEST_COL_BW[i]/255.0f-px[0]);
    }
    CPPUNIT_ASSERT(total_diff<1e-9);
   
    //OpenLF::imshow(*img,"bw");
    
    // test bw image saving
    filename = filename_pattern+"bw.jpg"; img->save(filename);
    filename = filename_pattern+"bw.png"; img->save(filename);
    filename = filename_pattern+"bw.tif"; img->save(filename);
    filename = filename_pattern+"bw.gif"; img->save(filename);
    filename = filename_pattern+"bw.bmp"; img->save(filename);
    //filename = filename_pattern+"bw.exr"; img->save(filename);
    
    img->~Image();
    
    // test rgb image loading from file
    total_diff = 0.0f;
    img = new OpenLF::Image(lena_rgb_path);
    
    CPPUNIT_ASSERT(img->width()==lena_width);
    CPPUNIT_ASSERT(img->height()==lena_height);
    CPPUNIT_ASSERT(img->channels()==3);
    CPPUNIT_ASSERT(img->label()=="rgb");
    
    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
        img->get_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i],px);
        total_diff = total_diff + abs(LENA_TEST_COL_R[i]/255.0f-px[0]);
        //cout << "rgb test: " << LENA_TEST_COL_R[i] << " " << px[0]*255.0 << endl;
        total_diff = total_diff + abs(LENA_TEST_COL_G[i]/255.0f-px[1]);
        //cout << "rgb test: " << LENA_TEST_COL_G[i] << " " << px[1]*255.0 << endl;
        total_diff = total_diff + abs(LENA_TEST_COL_B[i]/255.0f-px[2]);
        //cout << "rgb test: " << LENA_TEST_COL_B[i] << " " << px[2]*255.0 << endl;
    }
    CPPUNIT_ASSERT(total_diff<1e-9);
    
//    cv::Mat tmp;
//    img->get_opencv(2,tmp);
//    OpenLF::show(tmp,"channel 3");
    
//    OpenLF::imshow(*img,"rgb");
    
    // test rgb image saving
    filename = filename_pattern+"rgb.jpg"; img->save(filename);
    filename = filename_pattern+"rgb.png"; img->save(filename);
    filename = filename_pattern+"rgb.tif"; img->save(filename);
    filename = filename_pattern+"rgb.gif"; img->save(filename);
    filename = filename_pattern+"rgb.bmp"; img->save(filename);
    //filename = filename_pattern+"rgb.exr"; img->save(filename);
    
    img->~Image();
    //delete img;
}



void image_test::testCopyConstructor() 
{       
    //open lena rgb image
    OpenLF::Image img = OpenLF::Image(lena_rgb_path);
    OpenLF::Image img_cp = OpenLF::Image(img);
    
    float total_diff = 0.0f;
    vector<float> px;
    
    // check props of image copy
    CPPUNIT_ASSERT(img_cp.width()==lena_width);
    CPPUNIT_ASSERT(img_cp.height()==lena_height);
    CPPUNIT_ASSERT(img_cp.channels()==3);
    CPPUNIT_ASSERT(img_cp.label()=="rgb");
    
    // test if pixel are correct in image copy
    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
        img_cp.get_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i],px);
        total_diff = total_diff + abs(LENA_TEST_COL_R[i]/255.0f-px[0]);
        total_diff = total_diff + abs(LENA_TEST_COL_G[i]/255.0f-px[1]);
        total_diff = total_diff + abs(LENA_TEST_COL_B[i]/255.0f-px[2]);
    }
    CPPUNIT_ASSERT(total_diff<1e-9);
}



void image_test::testCannelAcccess() 
{
    //open lena rgb image
    OpenLF::Image img = OpenLF::Image(lena_rgb_path);
    
    // test get_channel
    float *r = img.get_channel(0);
    float *g = img.get_channel(1);
    float *b = img.get_channel(2);
    float total_diff = 0.0f;
    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
        int pos = img.width()*LENA_TEST_POS_X[i]+LENA_TEST_POS_Y[i];
        total_diff = total_diff + abs(LENA_TEST_COL_R[i]/255.0f-r[pos]);
        total_diff = total_diff + abs(LENA_TEST_COL_G[i]/255.0f-g[pos]);
        total_diff = total_diff + abs(LENA_TEST_COL_B[i]/255.0f-b[pos]);
    }
    CPPUNIT_ASSERT(total_diff<1e-9);
    
    // test access_pixel
    float px;
    total_diff = 0.0f;
    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
        px = img.access_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i], 0);
        total_diff = total_diff + abs(LENA_TEST_COL_R[i]/255.0f-px);
        px = img.access_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i], 1);
        total_diff = total_diff + abs(LENA_TEST_COL_G[i]/255.0f-px);
        px = img.access_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i], 2);
        total_diff = total_diff + abs(LENA_TEST_COL_B[i]/255.0f-px);
    }
    CPPUNIT_ASSERT(total_diff<1e-9);
    
    // test swap_channel
    vigra::MultiArray<2,float> array = vigra::MultiArray<2,float>(vigra::Shape2(lena_width,lena_height));
    img.swap_channel(0,array);
    
    total_diff = 0.0f;
    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
        int pos = img.width()*LENA_TEST_POS_X[i]+LENA_TEST_POS_Y[i];
        total_diff = total_diff + abs(LENA_TEST_COL_R[i]/255.0f-array.data()[pos]);
    }
    
    CPPUNIT_ASSERT(total_diff<1e-9);
}


void image_test::addCannel() {
//    //open lena rgb img
//    OpenLF::Image img = OpenLF::Image(lena_rgb_path);
//    OpenLF::Image vec = OpenLF::Image(lena_width,lena_height,2);
//    
//    float *r = img.get_channel(0);
//    float *g = img.get_channel(1);
//    float *b = img.get_channel(2);
//    
//    // test to add default cannel
//    vec.add_channel();
//    CPPUNIT_ASSERT(vec.channels()==3);
//    vec.set_label("rgb");
//    CPPUNIT_ASSERT(vec.label()=="rgb");
//    
//    // test to set cannel
//    vec.set_channel(r,0);
//    vec.set_channel(g,1);
//    vec.set_channel(b,2);
//    
//    float px;
//    float total_diff = 0.0f;
//    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
//        px = vec.access_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i], 0);
//        total_diff = total_diff + abs(LENA_TEST_COL_R[i]/255.0f-px);
//        px = vec.access_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i], 1);
//        total_diff = total_diff + abs(LENA_TEST_COL_G[i]/255.0f-px);
//        px = vec.access_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i], 2);
//        total_diff = total_diff + abs(LENA_TEST_COL_B[i]/255.0f-px);
//    }
//    CPPUNIT_ASSERT(total_diff<1e-9);
//    
//    // test to add channel using data
//    OpenLF::Image rgb = OpenLF::Image(lena_width,lena_height,0);
//    rgb.add_channel(r);
//    rgb.add_channel(g);
//    rgb.add_channel(b);
//    
//    px = 0;
//    total_diff = 0.0f;
//    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
//        px = rgb.access_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i], 0);
//        total_diff = total_diff + abs(LENA_TEST_COL_R[i]/255.0f-px);
//        px = rgb.access_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i], 1);
//        total_diff = total_diff + abs(LENA_TEST_COL_G[i]/255.0f-px);
//        px = rgb.access_pixel(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i], 2);
//        total_diff = total_diff + abs(LENA_TEST_COL_B[i]/255.0f-px);
//    }
//    CPPUNIT_ASSERT(total_diff<1e-9);
}

void image_test::conversionOpenCV() {
    //open lena rgb img
    OpenLF::Image rgb = OpenLF::Image(lena_rgb_path);
    OpenLF::Image bw = OpenLF::Image(lena_bw_path);
    OpenLF::Image vec = OpenLF::Image(lena_width,lena_height,2);
    
    //OpenLF::imshow(bw,"bw");
    //OpenLF::imshow(rgb,"rgb");
    
    // test copy_channel
    vec.copy_channel(0,rgb);
    vec.add_channel(1,rgb);
    vec.set_label("vec");
    
    CPPUNIT_ASSERT(vec.width()==lena_width);
    CPPUNIT_ASSERT(vec.height()==lena_height);
    CPPUNIT_ASSERT(vec.channels()==2);
    CPPUNIT_ASSERT(vec.label()=="vec");
    
    cv::Mat cv_bw;
    cv::Mat cv_bw2;
    cv::Mat cv_vec;
    cv::Mat cv_rgb;
    
    // test opencv conversion based on image label 
    bw.get_opencv(cv_bw);
    vec.get_opencv(cv_vec);
    rgb.get_opencv(cv_rgb);
    
    //OpenLF::show(cv_rgb,"cv_rgb");
    //OpenLF::show(cv_bw,"cv_bw");
    
    // test opencv conversion specifying the channel
    rgb.get_opencv(0,cv_bw2);
    
    //OpenLF::show(cv_bw2,"cv_bw2");
    
    float px = 0;
    float total_diff_bw = 0.0f;
    float total_diff_bw2 = 0.0f;
    float total_diff_vec = 0.0f;
    float total_diff_rgb = 0.0f;
   
    for(int i=0; i<NUMBER_OF_CHECKPOINTS; i++) {
        px = cv_bw.at<float>(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i]);
        total_diff_bw = total_diff_bw + abs(LENA_TEST_COL_BW[i]/255.0f-px);
        
        px = cv_bw2.at<float>(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i]);
        total_diff_bw2 = total_diff_bw2 + abs(LENA_TEST_COL_R[i]/255.0f-px);
        
        px = cv_vec.at<cv::Vec2f>(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i])[0];
        total_diff_vec = total_diff_vec + abs(LENA_TEST_COL_R[i]/255.0f-px);
        px = cv_vec.at<cv::Vec2f>(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i])[1];
        total_diff_vec = total_diff_vec + abs(LENA_TEST_COL_G[i]/255.0f-px);
        
        px = cv_rgb.at<cv::Vec3f>(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i])[0];
        total_diff_rgb = total_diff_rgb + abs(LENA_TEST_COL_B[i]/255.0f-px);
        px = cv_rgb.at<cv::Vec3f>(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i])[1];
        total_diff_rgb = total_diff_rgb + abs(LENA_TEST_COL_G[i]/255.0f-px);
        px = cv_rgb.at<cv::Vec3f>(LENA_TEST_POS_X[i],LENA_TEST_POS_Y[i])[2];
        total_diff_rgb = total_diff_rgb + abs(LENA_TEST_COL_R[i]/255.0f-px);
    }
    CPPUNIT_ASSERT(total_diff_bw<1e-9);
    CPPUNIT_ASSERT(total_diff_bw2<1e-9);
    CPPUNIT_ASSERT(total_diff_vec<1e-9);
    CPPUNIT_ASSERT(total_diff_rgb<1e-9);
}