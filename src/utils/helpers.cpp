#include "utils/helpers.hpp"

string OpenLF::helpers::find_ftype(string filepath) 
{
    vector<std::string> splited;
    boost::split(splited, filepath, boost::is_any_of("."));
    return splited[splited.size()-1];
}

bool OpenLF::helpers::filenames_from_directory(string dir, vector<string> &list)
{
    
    // read filenames from directory
    boost::filesystem::directory_iterator iterator(dir);
    for(; iterator != boost::filesystem::directory_iterator(); ++iterator) {
        list.push_back(iterator->path().filename().generic_string());
    }
    
    sort (list.begin(), list.end());
    
    if(list.size()>0) return true;
    return false;
}

void OpenLF::helpers::remove_leading_spaces_from_string(string input,string &result) 
{   result="";
    vector<string> strVec; 
    boost::algorithm::split(strVec,input,boost::is_any_of("\t "),boost::token_compress_on);
        
    bool placeholder = false;
    bool full_string = false;
    size_t pos=-1;
    for(unsigned int i=0; i<strVec.size(); i++) {
        if(strVec[i].size()>0) {
            pos = strVec[i].find('"');
            if(pos!=string::npos)
                placeholder=!placeholder;
            
            if(strVec[i].at(0)=='"' && strVec[i].at(strVec[i].size()-1)=='"')
                full_string = true;
            
            result+=strVec[i];
            if(placeholder && !full_string)
                result+=" ";
        }
    }
}


string OpenLF::helpers::make_absolute_path(string filename, string relative_part) 
{
    string abs_path;
    // make a path object of the filename
    boost::filesystem::path fpath(filename);
    // get the directory path of the filename
    boost::filesystem::path dir = fpath.parent_path();
    // make an absolute path by concatenating the dir and the relative_part
    abs_path = dir.string()+"/"+relative_part;
    return abs_path;
} 


bool OpenLF::helpers::remove_by_value(vector<string> &list, string value) 
{
    for( auto iter = list.begin(); iter != list.end(); ++iter )
    {
        if( *iter == value ) {
            list.erase( iter );
            return true;
        }
    }
    return false;
}


void OpenLF::helpers::get_attribute_list(string filename, string GroupID, vector<string> &attrs, vector<bool> &isString) {
    H5::H5File file = H5::H5File( filename.c_str(), vigra::HDF5File::Open );
    H5::Group group = file.openGroup(GroupID.c_str());
    H5::Attribute attr;
    int num = group.getNumAttrs();
    for (int i =0;i<num;i++){
        attr = group.openAttribute(i);
        H5::DataType dtype;
        dtype = attr.getDataType();
      
        attrs.push_back(attr.getName());
        isString.push_back(dtype.isVariableStr());
    } 
    file.close();
}
  