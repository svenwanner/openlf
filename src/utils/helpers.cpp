#include "utils/helpers.hpp"

string OpenLF::find_ftype(string filepath) {
    vector<std::string> splited;
    boost::split(splited, filepath, boost::is_any_of("."));
    return splited[splited.size()-1];
}
