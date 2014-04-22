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
            cout << "load... ";
            myLf.open(argv[1]);
            cout << "ok" << endl;
        }
        catch(exception &e) {
            e.what();
            return -1;
        }
        
        vigra::MultiArrayView<2,float> img_0;
        myLf.getImage(0,0,"r",img_0);
        vigra::MultiArrayView<2,float> img_1;
        myLf.getImage(4,4,"r",img_1);
        
        OpenLF::image::io::imsave("/home/swanner/Desktop/img_1.png",img_0);
        OpenLF::image::io::imsave("/home/swanner/Desktop/img_2.png",img_1);

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


