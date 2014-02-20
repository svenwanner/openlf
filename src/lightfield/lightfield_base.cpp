#include "lightfield/lightfield_base.hpp"

OpenLF::Lightfield_base::Lightfield_base() {
    print(1,"Lightfield_base initialized...");
}

OpenLF::Lightfield_base::Lightfield_base(const Lightfield_base& orig) {
    print(1,"copy Lightfield_base...");
}

OpenLF::Lightfield_base::~Lightfield_base() {
    print(1,"Lightfield_base destroyed...");
}

