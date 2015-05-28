/*
* Created by LukasDSauer on 24.05.15.
*/

#ifndef HDF5MEMORY_HPP
#define HDF5MEMORY_HPP

#include "OpenLF/global.hpp"
#include "OpenLF/lightfield/Lightfield.hpp"
#include "OpenLF/image/Channel.hpp"

namespace OpenLF {
    namespace operators {

class HDF5Memory {
public:
    HDF5Memory(std::string filename, std::string operator_name);
    HDF5Memory(std::string  filename, std::string operator_name, OpenLF::lightfield::Lightfield *lf);
    void saveProcessResult(std::string process_name, OpenLF::image::ImageChannel &result);
    void openChannel(std::string channel_name, OpenLF::image::ImageChannel &img_channel)
    ~HDF5Memory(){};

private:
    vigra::HDF5File file; };

}}

#endif //HDF5MEMORY_HPP
