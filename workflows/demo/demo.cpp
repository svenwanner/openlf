#include <cstdlib>

using namespace std;

#include "My4DOperator.hpp"

#include "lightfield/Lightfield.hpp"

int main(int argc, char** argv) {
    
    if(argc>=2) {
        
        OpenLF::lightfield::Lightfield lf;
        try {
            // the argument is the filename of a lightfield
            // either of a hdf5 or a config file
            lf.open(argv[1]);
        }
        catch(exception &e) {
            e.what();
            return -1;
        }

        // create your operator
        My4DOperator myOp;
        // link the light field to it
        myOp.set(&lf);
        // apply the operator
        myOp.process();
        
        
        if(argc==3) {
           // the argument is the filename to save
           // your processed light field
            lf.save(argv[2]);
        }

        return 0;
    }
    else {
        return -1;
    }
}

