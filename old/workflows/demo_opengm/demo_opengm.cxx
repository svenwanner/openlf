#include <cstdlib>
#include <iostream>
#include "OpenLF/operators/opengm.hpp"
#include "OpenLF/lightfield/Lightfield.hpp"

int main(int argc, char** argv) {
    
    if(argc>=2) {
        
        OpenLF::lightfield::Lightfield myLf;
        
        try {
            // the argument is the filename of a lightfield
            // either of a hdf5 or a config file
	    std::cout << "load lightfield... "<<std::flush;
            myLf.open(argv[1]);
	    std::cout << "ok" << std::endl;
        }
        catch(std::exception &e) {
            e.what();
            return -1;
        }

        
	std::cout << myLf.cams_h()<< " x " << myLf.cams_v() <<" :: " << myLf.imgWidth() << " x " << myLf.imgHeight() <<std::endl;

	std::cout << "process... "<<std::flush;
        // create your operator
        OpenGM<> myOp({"r"}, {});
        // link the light field to it
        myOp.set(&myLf);
        // apply the operator
        myOp.process();
	std::cout << "ok" << std::endl;
    
        return 0;
    }
    else {
      std::cout << " wrong number of input parameters" << std::endl;
        return -1;
    }
}


