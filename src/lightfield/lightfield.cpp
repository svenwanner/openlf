#include "lightfield/lightfield.hpp"

OpenLF::Lightfield::Lightfield() {
    print(1,"Lightfield() called...");
}

OpenLF::Lightfield::Lightfield(const Lightfield& orig) {
    print(1,"copy Lightfield...");
}

OpenLF::Lightfield::~Lightfield() {
    print(1,"Lightfield destroyed...");
}

