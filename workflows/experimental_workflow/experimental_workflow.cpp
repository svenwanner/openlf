/* 
 * File:   experimental_workflow.cpp
 * Author: swanner
 *
 * Created on February 20, 2014, 1:28 AM
 */

#include "global.hpp"
#include "image/image.hpp"
#include "lightfield/lightfield.hpp"
#include "visualize/imgshow.hpp"



using namespace std;


int main(int argc, char** argv) {
    
    string fname = "/home/swanner/Dropbox/test_images/lena_rgb.png";
//    string fname = "/home/swanner/Dropbox/test_images/lena.png";
    OpenLF::Image img(fname.c_str());
    //OpenLF::imshow(img,"blub");

    vigra::MultiArray<2,float> tmp;
    img.swap_channel(1,tmp);
    
    OpenLF::show(tmp,"test");
    return 0;
}
