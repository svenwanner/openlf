//
// Created by lukasdsauer on 24.05.15.
//

#include "OpenLF/operators/HDF5Memory.hpp"

OpenLF::operators::HDF5Memory::HDF5Memory(std::string filename, std::string operator_name){
    //The file will not be overwritten, it will be opened in Read&Write-Mode
    file = vigra::HDF5File(filename, vigra::HDF5File::OpenMode::ReadWrite);
    //Every operator will be getting its own group in the HDF5File
    file.cd_mk(operator_name);
}

OpenLF::operators::HDF5Memory::HDF5Memory(std::string filename, std::string operator_name, OpenLF::lightfield::Lightfield *lf){
    lf->save(filename);
    file = vigra::HDF5File(filename, vigra::HDF5File::OpenMode::ReadWrite);
    //Every operator will be getting its own group in the HDF5File
    file.cd_mk(operator_name);
}

void OpenLF::operators::HDF5Memory::saveProcessResult(std::string process_name, OpenLF::image::ImageChannel &result) {
    file.write(process_name, *(result->data()) );
}

void OpenLF::operators::HDF5Memory::openChannel(std::string channel_name, OpenLF::image::ImageChannel &img_channel) {
    vigra::MultiArrayView<2,float> data;
    // If channel_name's first character is a "/", the path will be interpreted as absolute, otherwise it will be a
    // a relative path from the current group ( the group that is named like the operator).
    file.read(channel_name, data);
    img_channel = OpenLF::image::ImageChannel(data);
}
