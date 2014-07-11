#include <cstdlib>

using namespace std;

#include "My4DOperator.hpp"
#include "OpenLF/lightfield/Lightfield.hpp"

int main(int argc, char** argv) {
    
    if(argc>=2) {
        
        OpenLF::lightfield::Lightfield myLf;
        
        try {
            // the argument is the filename of a lightfield
            // either of a hdf5 or a config file
            cout << "load lightfield... ";
            myLf.open(argv[1]);
            cout << "ok" << endl;
        }
        catch(exception &e) {
            e.what();
            return -1;
        }
        
//        cout << "0,0,0,0 r:" << myLf.getLoxel(0,0,0,0,"r") << endl;
//        cout << "0,0,0,0 g:" << myLf.getLoxel(0,0,0,0,"g") << endl;
//        cout << "0,0,0,0 b:" << myLf.getLoxel(0,0,0,0,"b") << endl;
//        cout << "8,0,3203,2231 r:" << myLf.getLoxel(8,0,3203,2231,"r") << endl;
//        cout << "8,0,3203,2231 g:" << myLf.getLoxel(8,0,3203,2231,"g") << endl;
//        cout << "8,0,3203,2231 b:" << myLf.getLoxel(8,0,3203,2231,"b") << endl;
//        
//        vector<string> chs {"r","g"};
//        vector<float> vals;
//        myLf.getLoxel(0,0,0,0,chs,vals);
//        cout << "0,0,0,0 vr:" << vals[0] << endl;
//        cout << "0,0,0,0 vg:" << vals[1] << endl;
//        myLf.getLoxel(8,0,3203,2231,chs,vals);
//        cout << "8,0,3203,2231 vr:" << vals[0] << endl;
//        cout << "8,0,3203,2231 vg:" << vals[1] << endl;
        
        // get image channel
//        vigra::MultiArrayView<2,float> img_4;
//        myLf.getImage(4,4,"r",img_4);
//        OpenLF::image::io::imsave("/home/swanner/Desktop/img_cv.png",img_4);
//        
//        vigra::MultiArrayView<2,float> img_full;
//        map<string,OpenLF::image::ImageChannel> *lf = myLf.data();
//        OpenLF::image::io::imsave("/home/swanner/Desktop/lf.png",*lf);
//        
//        // get epi channel
//        vigra::MultiArrayView<2,float> epi_h = myLf.getHorizontalEpiChannel(4,124,"r",5);
//        OpenLF::image::io::imsave("/home/swanner/Desktop/epi_h.png",epi_h);
//        
//        vigra::MultiArrayView<2,float> epi_v = myLf.getVerticalEpiChannel(4,178,"r",5);
//        cout << "epi_v.shape: " << epi_v.shape()[0] << "," << epi_v.shape()[1] << endl;
//        OpenLF::image::io::imsave("/home/swanner/Desktop/epi_v.png",epi_v);
//        
//        
//        // get epi bw images copies
//        vigra::MultiArray<2,float> epi_bw_h;
//        myLf.getHorizontalEpi(4,124,3,epi_bw_h);
//        OpenLF::image::io::imsave("/home/swanner/Desktop/epi_bw_h.png",epi_bw_h);
//        
//        vigra::MultiArray<2,float> epi_bw_v;
//        myLf.getVerticalEpi(4,178,epi_bw_v);
//        OpenLF::image::io::imsave("/home/swanner/Desktop/epi_bw_v.png",epi_bw_v);
        

        // get rgb or bw image copies
        vigra::MultiArray<2,float> img_bw;
        vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>> img_rgb;
        
        myLf.getImage(4,4,img_bw);
        myLf.getImage(4,4,img_rgb);
        OpenLF::image::io::imsave("/home/swanner/Desktop/img_bw.png",img_bw);
        OpenLF::image::io::imsave("/home/swanner/Desktop/img_rgb.png",img_rgb);
        
        
        cout << "process... ";
        // create your operator
        std::vector<std::string> inslots;
        std::vector<std::string> outslots;
        My4DOperator myOp(inslots,outslots);
        // link the light field to it
        myOp.set(&myLf);
        // apply the operator
        myOp.process();
        cout << "ok" << endl;
        
        if(argc==3) {
           // the argument is the filename to save
           // your processed light field
            cout << "save... ";
            myLf.save(argv[2]);
            cout << "ok" << endl;
        }

        return 0;
    }
    else {
        return -1;
    }
}


