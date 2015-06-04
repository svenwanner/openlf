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
void OpenLF::operators::HDF5Memory::saveProcessResult(std::string process_name, vigra::MultiArrayView<2,float> &result) {
    file.write(process_name, result );
}

void OpenLF::operators::HDF5Memory::saveProcessResult(std::string process_name, OpenLF::image::ImageChannel &result) {
    file.write(process_name, *(result.image()) );
}

void OpenLF::operators::HDF5Memory::openChannel(std::string channel_name, OpenLF::image::ImageChannel &img_channel) {
    vigra::ArrayVector<long long unsigned int> size = file.getDatasetShape(channel_name);

    // size[0] is the width of the dataset, size[1] is its height
    vigra::MultiArray<2,float> *data = new vigra::MultiArray<2,float>(vigra::MultiArray<2,float>::difference_type(size[0],size[1]));
    file.read(channel_name,*data);
    img_channel.init(size[0],size[1],data->data());

}

void OpenLF::operators::HDF5Memory::openChannel(std::string channel_name, vigra::MultiArray<2,float> &img_channel) {
    // If channel_name's first character is a "/", the path will be interpreted as absolute, otherwise it will be a
    // a relative path from the current group ( the group that is named like the operator).
    file.readAndResize(channel_name, img_channel);
}
