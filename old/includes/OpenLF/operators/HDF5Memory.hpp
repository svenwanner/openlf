/*
 *
 * Created by LukasDSauer on 24.05.15.
 *
 * Filename: HDF5Memory.hpp
 *
 * Description: This class allows an Operator object to save results to a HDF5 file during the computation process.
 *              Furthermore, you can open results from the file.
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
    //! creates a new HDF5Memory object
    /*!
     \param filename The name of the .h5-File that the object will read from or write to (If it exists, it will be opened in ReadWrite-Mode, otherwise, a new file will be created.)
     \param operator_name This should be the name of the operator. The object will then save everything to a group with this name.
     */
    HDF5Memory(std::string filename, std::string operator_name);
    //! creates a new HDF5Memory object
    /*!
     \param filename The name of the .h5-File that the object will read from or write to. Attention: An existing file will be overwritten!!!
     \param operator_name This should be the name of the operator. The object will then save everything to a group with this name.
     \param lf The object will save this Lightfield as the "original" Lightfield to the file.
     */
    HDF5Memory(std::string  filename, std::string operator_name, OpenLF::lightfield::Lightfield *lf);
    //! saves a result (given as a MultiArrayView) of the process to the .h5-File
    /*!
     \param process_name The name of the dataset that will be saved. Use the name of the process, e.g. "compute" or "precompute".
     \param result The channel that will be saved.
     */
    void saveProcessResult(std::string process_name, vigra::MultiArrayView<2,float> &result);
    //! saves a result (given as a ImageChannel) of the process to the .h5-File
    /*!
     \param process_name The name of the dataset that will be saved. Use the name of the process, e.g. "compute" or "precompute".
     \param result The channel that will be saved.
     */
    void saveProcessResult(std::string process_name, OpenLF::image::ImageChannel &result);
    //! open a dataset from the .h5-File to a MultiArray
    /*!
     \param channel_name The path of the channel, you want to open. If the first character is a "/", the path will be interpreted as absolute, otherwise it will be a relative path from the group that is named like the operator.
     \param img_channel The MultiArray object that the data will be loaded to.
     */
    void openChannel(std::string channel_name, vigra::MultiArray<2,float> &img_channel);
    //! open a dataset from the .h5-File to an ImageChannel
    /*!
     \param channel_name The path of the channel, you want to open. If the first character is a "/", the path will be interpreted as absolute, otherwise it will be a relative path from the group that is named like the operator.
     \param img_channel The ImageChannel object that the data will be loaded to.
     */
    void openChannel(std::string channel_name, OpenLF::image::ImageChannel &img_channel);

    ~HDF5Memory(){};

private:
    vigra::HDF5File file;

};

}}

#endif //HDF5MEMORY_HPP
