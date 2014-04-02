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

#include "lightfield/Properties.hpp"

OpenLF::lightfield::Properties::Properties() 
{
    print(1,"lightfield::Properties() called...");
}

OpenLF::lightfield::Properties::Properties(string filename)
{
    print(1,"lightfield::Properties(filename) called...");
    
    ifstream cfgfile(filename.c_str());
    if (cfgfile.good()) {
        try {
            
            __parse__(cfgfile);
            
        } catch(exception &e) {
            string msg = "failed to parse: \n" +  string(filename);
            warning(msg);
            warning(e.what());
        }
    }
    else throw Parse_Exception("Properties: error while parsing configfile!");
}

OpenLF::lightfield::Properties::Properties(const char* filename)
{
    print(1,"lightfield::Properties(filename) called...");
    
    ifstream cfgfile(filename);
    if (cfgfile.good()) {
        try {
            
            __parse__(cfgfile);
            
        } catch(exception &e) {
            string msg = "failed to parse: \n" + string(filename);
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
    number_fields.clear();
    string_fields.clear();
}

void OpenLF::lightfield::Properties::clear() {
    number_fields.clear();
    string_fields.clear();
}








int OpenLF::lightfield::Properties::sizeof_num_field()
{
    print(1,"lightfield::Properties::sizeof_num_fields() called...");
    
    return number_fields.size();
}

int OpenLF::lightfield::Properties::sizeof_str_field() 
{
    print(1,"lightfield::Properties::sizeof_str_fields() called...");
    
    return string_fields.size();
}

void OpenLF::lightfield::Properties::get_num_field_keys(vector<string> &keys)
{
    for (auto& k : number_fields) {
        keys.push_back(k.first);
    }
}

void OpenLF::lightfield::Properties::get_str_field_keys(vector<string> &keys)
{
    for (auto& k : string_fields) {
        keys.push_back(k.first);
    }
}



bool OpenLF::lightfield::Properties::has_field(string fieldname) 
{
    for (auto& k : number_fields) {
        if(k.first==fieldname)
            return true;
    }
    for (auto& k : string_fields) {
        if(k.first==fieldname)
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

bool OpenLF::lightfield::Properties::get_field(string name, string &value)
{
    print(1,"lightfield::Properties::get_field(name,value) called...");
    
    if ( string_fields.find(name) == string_fields.end() ) {
        return false;
    } else {
        value = string_fields[name];
        return true;
    }
}

bool OpenLF::lightfield::Properties::get_field(string name, int &value) 
{
    print(1,"lightfield::Properties::get_field(name,value) called...");
    
    if ( number_fields.find(name) == number_fields.end() ) {
        return false;
    } else {
        value = (int)number_fields[name];
        return true;
    }
}

bool OpenLF::lightfield::Properties::get_field(string name, float &value) 
{
    print(1,"lightfield::Properties::get_field(name,value) called...");
    
    if ( number_fields.find(name) == number_fields.end() ) {
        return false;
    } else {
        value = (float)number_fields[name];
        return true;
    }
}

bool OpenLF::lightfield::Properties::get_field(string name, double &value) 
{
    print(1,"lightfield::Properties::get_field(name,value) called...");
    
    if ( number_fields.find(name) == number_fields.end() ) {
        return false;
    } else {
        value = number_fields[name];
        return true;
    }
}

void OpenLF::lightfield::Properties::set_lftype(LF_TYPE lftype)
{
    print(1,"lightfield::Properties::set_lftype(lftype) called...");
    
    number_fields["type"] = (double)lftype;
}

void OpenLF::lightfield::Properties::set_field(string name, string value)
{
    print(1,"lightfield::Properties::set_field(name,value) called...");
    
    string_fields[name] = value;
}

void OpenLF::lightfield::Properties::set_field(string name, int value)
{
    print(1,"lightfield::Properties::set_field(name,value) called...");
    
    number_fields[name] = (double)value;
}

void OpenLF::lightfield::Properties::set_field(string name, float value)
{
    print(1,"lightfield::Properties::set_field(name,value) called...");
    
    number_fields[name] = (double)value;
}

void OpenLF::lightfield::Properties::set_field(string name, double value)
{
    print(1,"lightfield::Properties::set_field(name,value) called...");
    
    number_fields[name] = value;
}










void OpenLF::lightfield::Properties::parse(const char* filename)
{
    print(1,"lightfield::Properties::parse(filename) called...");
    
    number_fields.clear();
    string_fields.clear();
    
    ifstream cfgfile(filename);
    if (cfgfile.good()) {
        try {
            
            __parse__(cfgfile);
            
        } catch(exception &e) {
            string msg = "failed to parse: \n" + string(filename);
            warning(msg);
            warning(e.what());
        }
    }
    else throw Parse_Exception("Properties: error while reading configfile!");
}
    

void OpenLF::lightfield::Properties::parse(string filename)
{
    print(1,"lightfield::Properties::parse(filename) called...");
    
    parse(filename.c_str());
}


void OpenLF::lightfield::Properties::__parse__(ifstream &cfgfile)
{
    print(1,"lightfield::Properties::__parse__(cfgfile) called...");
    
    string line;

    if (cfgfile.is_open())
    {
        while ( getline (cfgfile,line) )
        {
            if(line.size()>=1) {
                if(line.at(0)!='#' && line.at(0)!='[' && line.at(0)!='\n' && line.at(0)!=' ') {

                    // check for ":" char and split string in left and right from ":"
                    typedef vector< boost::iterator_range<string::iterator> > find_vector_type;
                    find_vector_type FindVec;
                    boost::ifind_all( FindVec, line, ":=" );
                    typedef vector< string > split_vector_type;
                    split_vector_type fields;
                    boost::split( fields, line, boost::is_any_of(":="), boost::token_compress_on );

                    string tmp;
                    OpenLF::helpers::remove_leading_spaces_from_string(fields[0],tmp);
                    fields[0]=tmp;
                    if(fields.size()>1) {
                        size_t pos=-1;
                        OpenLF::helpers::remove_leading_spaces_from_string(fields[1],tmp);
                        fields[1]=tmp;
                        
                        // if value is in quotation marks handle as string else as number 
                        pos = fields[1].find('"');
                        if(pos!=string::npos) 
                        {
                            fields[1].erase(std::remove(fields[1].begin(), fields[1].end(), '"'), fields[1].end());
                            string_fields[fields[0]] = fields[1];
                        }
                        else 
                        {
                            number_fields[fields[0]] = boost::lexical_cast<double>(fields[1]);
                        }
                    }
                }
            }       
        }
        cfgfile.close();     
    }        
}

