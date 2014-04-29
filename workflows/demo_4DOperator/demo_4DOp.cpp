#include <cstdlib>

using namespace std;

#include "My4DOperator.hpp"
#include "lightfield/Lightfield.hpp"

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
        
        // get image channel
        vigra::MultiArrayView<2,float> img_4;
        myLf.getImage(4,4,"bw",img_4);
        OpenLF::image::io::imsave("/home/swanner/Desktop/img_4.png",img_4);
        
        
        // get epi channel
        cout << "dsdsdsdsdsdsdsdsd" << endl;
        vigra::MultiArrayView<2,float> epi_h;
        myLf.getHorizontalEpiChannel(4,124,4,"bw",epi_h);
        OpenLF::image::io::imsave("/home/swanner/Desktop/epi_h.png",epi_h);
        
        vigra::MultiArrayView<2,float> epi_v;
        myLf.getVerticalEpiChannel(4,178,"bw",epi_v);
        OpenLF::image::io::imsave("/home/swanner/Desktop/epi_v.png",epi_v);
        
        
        // get epi bw images copies
        vigra::MultiArray<2,float> epi_bw_h;
        myLf.getHorizontalEpi(4,124,epi_bw_h);
        OpenLF::image::io::imsave("/home/swanner/Desktop/epi_bw_h.png",epi_bw_h);
        
        vigra::MultiArray<2,float> epi_bw_v;
        myLf.getVerticalEpi(4,178,epi_bw_v);
        OpenLF::image::io::imsave("/home/swanner/Desktop/epi_bw_v.png",epi_bw_v);
        

        // get rgb or bw image copies
        vigra::MultiArray<2,float> img_bw;
        vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8>> img_rgb;
        
        myLf.getImage(4,4,img_bw);
        myLf.getImage(4,4,img_rgb);
        OpenLF::image::io::imsave("/home/swanner/Desktop/img_bw.png",img_bw);
        OpenLF::image::io::imsave("/home/swanner/Desktop/img_rgb.png",img_rgb);
        
        
        cout << "process... ";
        // create your operator
        My4DOperator myOp;
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


