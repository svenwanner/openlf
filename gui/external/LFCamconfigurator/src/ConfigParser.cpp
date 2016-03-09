/*
* Copyright (c) 2014 Maximilian Diebold - Heidelberg Collaboratory for Image Processing
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

#include "ConfigParser.h"

ConfigParser::ConfigParser(string filename)
{
    this->resolution_X__px=0;
    this->resolution_Y__px=0;
    this->AspectRatio=0;

    this->delta_D_X__m=0;
    this->delta_D_Y__m=0;

    this->delta_d_X__px=0;
    this->delta_d_Y__px=0;

    this->theta_X__pxm=0;
    this->theta_Y__pxm=0;

    this->DH_X__m=0;
    this->DH_Y__m=0;

    this->focalLength__m=0;
    this->focal_length_X__px=0;
    this->focal_length_Y__px=0;

    this->baseline_X__m=0;
    this->baseline_Y__m=0;
    this->baseline_ratio=0;

    this->sensor_X__m=0;
    this->sensor_Y__m=0;

    this->dH_X__px=0;
    this->dH_Y__px=0;

    this->Pixelsize_X__m=0;
    this->Pixelsize_Y__m=0;
    this->PixelAspectRatio=0;

    this->delta_d_inaccuracy_ST__px=0;

    this->DoF_D_N__m=0;
    this->DoF_D_F__m=0;
    this->f_number=0;
    this->DoF_H__m=0;
    this->DoF_subject_distance__m=0;
    this->DoF_DoF__m=0;
    this->CircleofConfusion__m=0;

    this->CamX = 0;
    this->CamY = 0;

    this->delta_b__m = 0;
    this->delta_f__m = 0;
    this->delta_rot__deg = 0;

    ifstream cfgfile(filename.c_str());
    if (cfgfile.good()) {
        try {

           parse(filename);

        } catch(exception &e) {
            string msg = "failed to parse: \n" +  string(filename);
        }
    }
    else throw Parse_Exception("Properties: error while parsing configfile!");
}
//OpenLF::Properties::Properties(const Properties& orig) {
//}

ConfigParser::~ConfigParser()
{
    number_fields.clear();
    string_fields.clear();
}

bool ConfigParser::has_field(string fieldname)
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

bool ConfigParser::get_field(string name, double &value)
{
    if ( number_fields.find(name) == number_fields.end() ) {
        return false;
    } else {
        value = number_fields[name];
        return true;
    }
}

void ConfigParser::parse(string filename)
{
   parse(filename.c_str());

    this->get_field("FocalLength__m",this->focalLength__m);
    this->get_field("Pixelsize_h__m",this->Pixelsize_X__m);
    this->get_field("Pixelsize_v__m",this->Pixelsize_Y__m);
    this->get_field("resolution_h__px",this->resolution_X__px);
    this->get_field("resolution_v__px",this->resolution_Y__px);
    this->get_field("sensor_h__m",this->sensor_X__m);
    this->get_field("sensor_v__m",this->sensor_Y__m);
    this->get_field("baseline_h__m",this->baseline_X__m);
    this->get_field("baseline_v__m",this->baseline_Y__m);
    this->get_field("cam_h",this->CamX);
    this->get_field("cam_v",this->CamY);
    this->get_field("f_number",this->f_number);
    this->get_field("DoF_subject_distance__m",this->DoF_subject_distance__m);
    this->get_field("delta_b__m",this->delta_b__m);
    this->get_field("delta_f__m",this->delta_f__m);
    this->get_field("delta_d_inaccuracy_ST__px",this->delta_d_inaccuracy_ST__px);
    this->get_field("delta_d_h__px",this->delta_d_X__px);this->delta_d_X__px = this->delta_d_X__px/2;
    this->get_field("delta_d_v__px",this->delta_d_Y__px);this->delta_d_Y__px = this->delta_d_Y__px/2;
    this->get_field("dH_v__px",this->dH_Y__px);
    this->get_field("dH_h__px",this->dH_X__px);
    this->get_field("DH_h__m",this->DH_X__m);
    this->get_field("DH_v__m",this->DH_Y__m);
    this->get_field("CircleofConfusion__m",this->CircleofConfusion__m);
}

void ConfigParser::parse(const char* filename)
{
    number_fields.clear();
    string_fields.clear();

    ifstream cfgfile(filename);
    if (cfgfile.good()) {
        try {

            __parse__(cfgfile);

        } catch(exception &e) {
            string msg = "failed to parse: \n" + string(filename);
        }
    }
    else throw Parse_Exception("Properties: error while reading configfile!");
}


void ConfigParser::__parse__(ifstream &cfgfile)
{
    string line;

    if (cfgfile.is_open())
    {
        while ( getline (cfgfile,line) )
        {
            if(line.size()>=1) {
                if(line.at(0)!='#' && line.at(0)!='[' && line.at(0)!='\n' && line.at(0)!=' ') {

                    // check for ":" char and split string in left and right from ":"
                    typedef vector< boost::iterator_range<string::iterator>> find_vector_type;
                    find_vector_type FindVec;
                    boost::ifind_all( FindVec, line, ":=" );
                    typedef vector< string > split_vector_type;
                    split_vector_type fields;
                    boost::split( fields, line, boost::is_any_of(":="), boost::token_compress_on );

                    string tmp;
                    remove_leading_spaces_from_string(fields[0],tmp);
                    fields[0]=tmp;
                    if(fields.size()>1) {
                        size_t pos=-1;
                        remove_leading_spaces_from_string(fields[1],tmp);
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

void remove_leading_spaces_from_string(string input,string &result)
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
