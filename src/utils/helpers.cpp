#include "utils/helpers.hpp"

string OpenLF::helpers::find_ftype(string filepath) 
{
    vector<std::string> splited;
    boost::split(splited, filepath, boost::is_any_of("."));
    return splited[splited.size()-1];
}

bool OpenLF::helpers::filenames_from_directory(string dir, vector<string> &list) {
    
    // read filenames from directory
    boost::filesystem::directory_iterator iterator(dir);
    for(; iterator != boost::filesystem::directory_iterator(); ++iterator) {
        list.push_back(iterator->path().filename().generic_string());
    }
    
    sort (list.begin(), list.end());
    
    if(list.size()>0) return true;
    return false;
}