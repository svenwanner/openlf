/*
* Copyright (c) 2014 Sven Wanner
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of 
* this software and associated documentation files (the "Software"), to deal in 
* the Software without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
* Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all 
* copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "OpenLF/utils/helpers.hpp"

std::string OpenLF::helpers::find_ftype(std::string filepath) 
{
    std::vector<std::string> splited;
    boost::split(splited, filepath, boost::is_any_of("."));
    return splited[splited.size()-1];
}

bool OpenLF::helpers::filenames_from_directory(std::string dir, std::vector<std::string> &list)
{
    
    // read filenames from directory
    boost::filesystem::directory_iterator iterator(dir);
    for(; iterator != boost::filesystem::directory_iterator(); ++iterator) {
        list.push_back(iterator->path().filename().generic_string());
    }
    
    std::sort (list.begin(), list.end());
    
    if(list.size()>0) return true;
    return false;
}

void OpenLF::helpers::remove_leading_spaces_from_string(std::string input,std::string &result) 
{   result="";
    std::vector<std::string> strVec; 
    boost::algorithm::split(strVec,input,boost::is_any_of("\t "),boost::token_compress_on);
        
    bool placeholder = false;
    bool full_string = false;
    size_t pos=-1;
    for(unsigned int i=0; i<strVec.size(); i++) {
        if(strVec[i].size()>0) {
            pos = strVec[i].find('"');
            if(pos!=std::string::npos)
                placeholder=!placeholder;
            
            if(strVec[i].at(0)=='"' && strVec[i].at(strVec[i].size()-1)=='"')
                full_string = true;
            
            result+=strVec[i];
            if(placeholder && !full_string)
                result+=" ";
        }
    }
}


std::string OpenLF::helpers::make_absolute_path(std::string filename, std::string relative_part) 
{
    std::string abs_path;
    // make a path object of the filename
    boost::filesystem::path fpath(filename);
    // get the directory path of the filename
    boost::filesystem::path dir = fpath.parent_path();
    // make an absolute path by concatenating the dir and the relative_part
    abs_path = dir.string()+"/"+relative_part;
    return abs_path;
} 


bool OpenLF::helpers::remove_by_value(std::vector<std::string> &list, std::string value) 
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


void OpenLF::helpers::get_attribute_list(std::string filename, std::string GroupID, std::vector<std::string> &attrs, std::vector<bool> &isString) {
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
  