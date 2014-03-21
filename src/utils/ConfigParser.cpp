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

#include "utils/ConfigParser.hpp"

OpenLF::ConfigParser::ConfigParser() {}

OpenLF::ConfigParser::ConfigParser(string filename)
{
    ifstream cfgfile(filename.c_str());
    if (cfgfile.good()) {
        try {
            
            __parse__(cfgfile);
            
        } catch(exception &e) {
            cout << "failed to parse: " << filename << endl;
            cout << e.what() << endl;
        }
    }
    else throw Parse_Exception("ConfigParser: error while parsing configfile!");
}

OpenLF::ConfigParser::ConfigParser(const char* filename)
{
    ifstream cfgfile(filename);
    if (cfgfile.good()) {
        try {
            
            __parse__(cfgfile);
            
        } catch(exception &e) {
            cout << "failed to parse: " << filename << endl;
            cout << e.what() << endl;
        }
    }
    else throw Parse_Exception("ConfigParser: error while parsing configfile!");
}

OpenLF::ConfigParser::ConfigParser(const ConfigParser& orig) {
}

OpenLF::ConfigParser::~ConfigParser() {
}

bool OpenLF::ConfigParser::get_field(string name, string &value)
{
    if ( string_fields.find(name) == string_fields.end() ) {
        return false;
    } else {
        value = string_fields[name];
        return true;
    }
}

bool OpenLF::ConfigParser::get_field(string name, int &value) 
{
    if ( number_fields.find(name) == number_fields.end() ) {
        return false;
    } else {
        value = (int)number_fields[name];
        return true;
    }
}

bool OpenLF::ConfigParser::get_field(string name, float &value) 
{
    if ( number_fields.find(name) == number_fields.end() ) {
        return false;
    } else {
        value = (float)number_fields[name];
        return true;
    }
}

bool OpenLF::ConfigParser::get_field(string name, double &value) 
{
    if ( number_fields.find(name) == number_fields.end() ) {
        return false;
    } else {
        value = number_fields[name];
        return true;
    }
}


void OpenLF::ConfigParser::parse(const char* filename)
{
    number_fields.clear();
    string_fields.clear();
    
    ifstream cfgfile(filename);
    if (cfgfile.good()) {
        try {
            
            __parse__(cfgfile);
            
        } catch(exception &e) {
            cout << "failed to parse: " << filename << endl;
            cout << e.what() << endl;
        }
    }
    else throw Parse_Exception("ConfigParser: error while parsing configfile!");
}
    

void OpenLF::ConfigParser::parse(string filename)
{
    parse(filename.c_str());
}


void OpenLF::ConfigParser::__parse__(ifstream &cfgfile)
{
    string line;

    if (cfgfile.is_open())
    {
        while ( getline (cfgfile,line) )
        {
            if(line.at(0)!='#'){
                typedef vector< boost::iterator_range<string::iterator> > find_vector_type;
                find_vector_type FindVec;
                boost::ifind_all( FindVec, line, "=" );
                typedef vector< string > split_vector_type;
                split_vector_type fields;

                boost::split( fields, line, boost::is_any_of("="), boost::token_compress_on );

                size_t pos=-1;
                string tmp;
                pos = fields[1].find(';');
                if(pos==string::npos) 
                    throw Parse_Exception("ConfigParser: error while parsing, missing semicolon!");
                tmp = fields[1].substr(0,pos);
                fields[1] = tmp;

                // if value is in quotation marks handle as string else as number 
                pos = fields[1].find('"');
                if(pos!=string::npos) 
                {
                    tmp = fields[1].substr(1,fields[1].size()-2);
                    fields[1] = tmp;
                    string_fields[fields[0]] = fields[1];
                }
                else 
                {
                    number_fields[fields[0]] = boost::lexical_cast<double>(fields[1]);
                }
            }
        }
        cfgfile.close();
    }        
}

