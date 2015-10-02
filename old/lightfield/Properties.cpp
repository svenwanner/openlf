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

#include "OpenLF/lightfield/Properties.hpp"

OpenLF::lightfield::Properties::Properties() 
{
    print(1,"lightfield::Properties() called...");
}

OpenLF::lightfield::Properties::Properties(const std::string filename)
{
    print(1,"lightfield::Properties(filename) called...");
    
    std::ifstream cfgfile(filename.c_str());
    if (cfgfile.good()) {
        try {
            
            __parse__(cfgfile);
            
        } catch(std::exception &e) {
            std::string msg = "failed to parse: \n" +  std::string(filename);
            warning(msg);
            warning(e.what());
        }
    }
    else throw Parse_Exception("Properties: error while parsing configfile!");
}

OpenLF::lightfield::Properties::Properties(const char* filename)
{
    print(1,"lightfield::Properties(filename) called...");
    
    std::ifstream cfgfile(filename);
    if (cfgfile.good()) {
        try {
            
            __parse__(cfgfile);
            
        } catch(std::exception &e) {
            std::string msg = "failed to parse: \n" + std::string(filename);
            warning(msg);
            warning(e.what());
        }
    }
    else throw Parse_Exception("Properties: error while parsing configfile!");
}

//OpenLF::Properties::Properties(const Properties& orig) {
//}

OpenLF::lightfield::Properties::~Properties() 
{
    print(1,"lightfield::~Properties() called...");
    m_number_fields.clear();
    m_string_fields.clear();
}


void OpenLF::lightfield::Properties::log()
{
    std::string text = "\n#### Properties ####\n";
    
    text += "#\n# number fields:\n";
    for(number_fields_iter iter = m_number_fields.begin(); iter != m_number_fields.end(); iter++) {
    //for (auto& k : this->number_fields) {
        text += "# "+iter->first+" = "+boost::lexical_cast<std::string>(iter->second)+"\n";
    }
    
    text += "#\n# std::string fields:\n";
    for(string_fields_iter iter = m_string_fields.begin(); iter != m_string_fields.end(); iter++) {
    //for (auto& k : this->std::string_fields) {
        text += "# "+iter->first+" = "+iter->second+"\n";
    }
    cout << text << "\n";
}




OpenLF::lightfield::Properties & OpenLF::lightfield::Properties::operator+=(OpenLF::lightfield::Properties &rhs)
{ 
    std::string key;
    double nvalue;
    std::string svalue;
    
    for(number_fields_iter iter = rhs.m_number_fields.begin(); iter != rhs.m_number_fields.end(); iter++) {
    //for (auto& iter : rhs.number_fields) {
        key = iter->first;
        rhs.get_field(key,nvalue);
        this->set_field(key,nvalue);
      
    }
    
    for(string_fields_iter iter = rhs.m_string_fields.begin(); iter != rhs.m_string_fields.end(); iter++) {
    //for (auto& iter : rhs.string_fields) {
        key = iter->first;
        rhs.get_field(key,svalue);
        this->set_field(key,svalue);
    }
    return *this;  
}


void OpenLF::lightfield::Properties::clear() {
    m_number_fields.clear();
    m_string_fields.clear();
}








int OpenLF::lightfield::Properties::sizeof_num_field() const
{
    print(1,"lightfield::Properties::sizeof_num_fields() called...");
    
    return m_number_fields.size();
}

int OpenLF::lightfield::Properties::sizeof_str_field() const 
{
    print(1,"lightfield::Properties::sizeof_str_fields() called...");
    
    return m_string_fields.size();
}

void OpenLF::lightfield::Properties::get_num_field_keys(std::vector<std::string> &keys)
{
    for(number_fields_iter iter = m_number_fields.begin(); iter != m_number_fields.end(); iter++) {
    //for (auto& k : number_fields) {
        keys.push_back(iter->first);
    }
}

void OpenLF::lightfield::Properties::get_str_field_keys(std::vector<std::string> &keys)
{
    for(string_fields_iter iter = m_string_fields.begin(); iter != m_string_fields.end(); iter++) {
    //for (auto& k : string_fields) {
        keys.push_back(iter->first);
    }
}



bool OpenLF::lightfield::Properties::has_field(const std::string fieldname)
{
    for(number_fields_iter iter = m_number_fields.begin(); iter != m_number_fields.end(); iter++) {
    //for (auto& k : number_fields) {
        if(iter->first==fieldname)
            return true;
    }
    for(string_fields_iter iter = m_string_fields.begin(); iter != m_string_fields.end(); iter++) {
    //for (auto& k : string_fields) {
        if(iter->first==fieldname)
            return true;
    }
    return false;
}





bool OpenLF::lightfield::Properties::get_lftype(LF_TYPE &lftype)
{
    print(1,"lightfield::Properties::get_lftype(&lftype) called...");
    
    int lft;
    
    if(get_field("type",lft)) {
        switch(lft) {
            case 1: lftype = LF_4D; break;
            case 2: lftype = LF_3DH; break;
            case 3: lftype = LF_3DV; break;
            case 4: lftype = LF_CROSS; break;
            default: return false;
        }
        return true;
    }
    else {
        return false;
    }
}

bool OpenLF::lightfield::Properties::get_field(const std::string name, std::string &value)
{
    print(1,"lightfield::Properties::get_field(name,value) called...");
    
    if ( m_string_fields.find(name) == m_string_fields.end() ) {
        return false;
    } else {
        value = m_string_fields[name];
        return true;
    }
}

bool OpenLF::lightfield::Properties::get_field(const std::string name, int &value)
{
    print(1,"lightfield::Properties::get_field(name,value) called...");
    
    if ( m_number_fields.find(name) == m_number_fields.end() ) {
        return false;
    } else {
        value = (int)m_number_fields[name];
        return true;
    }
}

bool OpenLF::lightfield::Properties::get_field(const std::string name, float &value)
{
    print(1,"lightfield::Properties::get_field(name,value) called...");
    
    if ( m_number_fields.find(name) == m_number_fields.end() ) {
        return false;
    } else {
        value = (float)m_number_fields[name];
        return true;
    }
}

bool OpenLF::lightfield::Properties::get_field(const std::string name, double &value)
{
    print(1,"lightfield::Properties::get_field(name,value) called...");
    
    if ( m_number_fields.find(name) == m_number_fields.end() ) {
        return false;
    } else {
        value = m_number_fields[name];
        return true;
    }
}

void OpenLF::lightfield::Properties::set_lftype(LF_TYPE lftype)
{
    print(1,"lightfield::Properties::set_lftype(lftype) called...");
    
    m_number_fields["type"] = (double)lftype;
}

void OpenLF::lightfield::Properties::set_field(const std::string name, const std::string value)
{
    print(1,"lightfield::Properties::set_field(name,value) called...");
    
    m_string_fields[name] = value;
}

void OpenLF::lightfield::Properties::set_field(const std::string name, int value)
{
    print(1,"lightfield::Properties::set_field(name,value) called...");
    
    m_number_fields[name] = (double)value;
}

void OpenLF::lightfield::Properties::set_field(const std::string name, float value)
{
    print(1,"lightfield::Properties::set_field(name,value) called...");
    
    m_number_fields[name] = (double)value;
}

void OpenLF::lightfield::Properties::set_field(const std::string name, double value)
{
    print(1,"lightfield::Properties::set_field(name,value) called...");
    
    m_number_fields[name] = value;
}










void OpenLF::lightfield::Properties::parse(const char* filename)
{
    print(1,"lightfield::Properties::parse(filename) called...");
    
    m_number_fields.clear();
    m_string_fields.clear();
    
    std::ifstream cfgfile(filename);
    if (cfgfile.good()) {
        try {
            
            __parse__(cfgfile);
            
        } catch(std::exception &e) {
            std::string msg = "failed to parse: \n" + std::string(filename);
            warning(msg);
            warning(e.what());
        }
    }
    else throw Parse_Exception("Properties: error while reading configfile!");
}
    

void OpenLF::lightfield::Properties::parse(const std::string filename)
{
    print(1,"lightfield::Properties::parse(filename) called...");
    
    parse(filename.c_str());
}


void OpenLF::lightfield::Properties::__parse__(std::ifstream &cfgfile)
{
    print(1,"lightfield::Properties::__parse__(cfgfile) called...");
    
    std::string line;

    if (cfgfile.is_open())
    {
        while ( getline (cfgfile,line) )
        {
            if(line.size()>=1) {
                if(line.at(0)!='#' && line.at(0)!='[' && line.at(0)!='\n' && line.at(0)!=' ') {

                    // check for ":" char and split std::string in left and right from ":"
                    typedef std::vector< boost::iterator_range<std::string::iterator> > find_vector_type;
                    find_vector_type FindVec;
                    boost::ifind_all( FindVec, line, ":=" );
                    typedef std::vector< std::string > split_vector_type;
                    split_vector_type fields;
                    boost::split( fields, line, boost::is_any_of(":="), boost::token_compress_on );

                    std::string tmp;
                    OpenLF::helpers::remove_leading_spaces_from_string(fields[0],tmp);
                    fields[0]=tmp;
                    if(fields.size()>1) {
                        size_t pos=-1;
                        OpenLF::helpers::remove_leading_spaces_from_string(fields[1],tmp);
                        fields[1]=tmp;
                        
                        // if value is in quotation marks handle as string else as number 
                        pos = fields[1].find('"');
                        if(pos!=std::string::npos) 
                        {
                            fields[1].erase(std::remove(fields[1].begin(), fields[1].end(), '"'), fields[1].end());
                            m_string_fields[fields[0]] = fields[1];
                        }
                        else 
                        {
                            m_number_fields[fields[0]] = boost::lexical_cast<double>(fields[1]);
                        }
                    }
                }
            }       
        }
        cfgfile.close();     
    }        
}

