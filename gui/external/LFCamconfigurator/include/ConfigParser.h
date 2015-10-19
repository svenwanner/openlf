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

#ifndef CONFIGPARSER_H_
#define CONFIGPARSER_H_
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#ifndef Q_MOC_RUN  // Problem with Qt 4.8 moc and boost 1.55
#include <boost/algorithm/string_regex.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#endif
#include <fstream>
#include <iostream>

using namespace std;


//! removes spaces and tabs from a string
/*!
 \param input string
 \param result string without spaces and tabs
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
void remove_leading_spaces_from_string(string input,string &result);




struct Parse_Exception : public exception
{
   string s;
   Parse_Exception(string ss) : s(ss) {}
   ~Parse_Exception() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};


//! Configuration file parser class
/*!
 This class can load simple configfiles containing numbers and strings.
 The structure of configfile entries is field : value;
 If the values are strings they need to be in quotation marks:
 e.g. a number: myNum : 100
 e.g. a string: myStr : "Hello World"
 The values can be accessed by get_field methods which can set the value as string,
 integer, float or double.
 \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
class ConfigParser {
public:

    double resolution_X__px;
    double delta_D_X__m;
    double delta_D_Y__m;
    double D1_Y__m;
    double D1_X__m;
    double D2_X__m;
    double D2_Y__m;
    double delta_d_X__px;
    double delta_d_Y__px;
    double theta_X__pxm;
    double theta_Y__pxm;
    double DH_X__m;
    double DH_Y__m;
    double focalLength__m;
    double focal_length_X__px;
    double focal_length_Y__px;
    double baseline_X__m;
    double baseline_Y__m;
    double baseline_ratio;
    double sensor_X__m;
    double sensor_Y__m;
    double resolution_Y__px;
    double d1_X__px;
    double d1_Y__px;
    double d2_X__px;
    double d2_Y__px;
    double dH_X__px;
    double dH_Y__px;
    double AspectRatio;
    double Pixelsize_X__m;
    double Pixelsize_Y__m;
    double PixelAspectRatio;
    double delta_d_inaccuracy_ST__px;
    double DoF_D_N__m;
    double DoF_D_F__m;
    double f_number;
    double DoF_H__m;
    double DoF_subject_distance__m;
    double DoF_DoF__m;
    double CamX;
    double CamY;
    double delta_b__m;
    double delta_f__m;
    double delta_rot__deg;
    double CircleofConfusion__m;


    ConfigParser(string filename);
    //Properties(const Properties& orig);
    virtual ~ConfigParser();


    //! prints the properties on the console
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void log();



    //! overload of += operator
    /*!
     Important: the properties on the right hand side of the operator
     is added to the left hand side. If both have fields with the same
     name the fields from lhs stay unchanged, the rhs values are ignored.
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    ConfigParser & operator+=(ConfigParser &rhs);


    //! clears the property fields
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void clear();


    //! check if the field name exist
    /*!
     \param fieldname
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool has_field(string fieldname);



    //! access value by name
    /*!
     \param name of the field
     \param value variable to pass the value to
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool get_field(string name, double &value);

    //! parse the file passed
    /*!
     \param filename cfgfile the ifstream object of the file loaded
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void parse(string filename);

    //! parse the file passed
    /*!
     \param filename cfgfile the ifstream object of the file loaded
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void parse(const char* filename);


private:

    //! parsing the input file
    /*!
     \param cfgfile the ifstream object of the file loaded
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void __parse__(ifstream &cfgfile);

    map<string,double> number_fields; //!< map to store the number fields and values
    map<string,string> string_fields; //!< map to store the string fields and values

};



#endif /* CONFIGPARSER_H_ */
