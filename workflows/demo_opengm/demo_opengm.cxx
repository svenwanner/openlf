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
	    std::cout << "load lightfield... ";
            myLf.open(argv[1]);
	    std::cout << "ok" << std::endl;
        }
        catch(std::exception &e) {
            e.what();
            return -1;
        }

        
	std::cout << "process... ";
        // create your operator
        OpenGM<> myOp;
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


