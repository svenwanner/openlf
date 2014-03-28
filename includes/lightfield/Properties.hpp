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

#ifndef PROPERTIES_HPP
#define	PROPERTIES_HPP

#include "global.hpp"
#include "utils/helpers.hpp"

struct Parse_Exception : public exception
{
   string s;
   Parse_Exception(string ss) : s(ss) {}
   ~Parse_Exception() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};


namespace OpenLF {
    namespace lightfield {
    
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
class Properties {
public:
    Properties();
    Properties(string filename);
    Properties(const char* filename);
    Properties(const Properties& orig);
    virtual ~Properties();
    
    
    
    
    
    //! get size of number_fields map
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    int sizeof_num_field();
    
    //! get size of string_fields map
    /*!
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    int sizeof_str_field();

    //! get list of number_fields map keys
    /*!
     \param keys reference to a vector of strings to store the keys
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void get_num_field_keys(vector<string> &keys);
    
    //! get list of string_fields map keys
    /*!
     \param keys reference to a vector of strings to store the keys
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void get_str_field_keys(vector<string> &keys);
    
    


    
    //! access LF_TYPE parsed
    /*!
     \param lftype variable to be set
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool get_lftype(LF_TYPE &lftype);
    
    //! access value by name
    /*!
     \param name of the field
     \param value variable to pass the value to
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool get_field(string name, string &value);
    
    //! access value by name
    /*!
     \param name of the field
     \param value variable to pass the value to
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool get_field(string name, int &value);
    
    //! access value by name
    /*!
     \param name of the field
     \param value variable to pass the value to
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool get_field(string name, float &value);
    
    //! access value by name
    /*!
     \param name of the field
     \param value variable to pass the value to
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    bool get_field(string name, double &value);
    
    //! set LF_TYPE parsed
    /*!
     \param lftype variable to be set
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void set_lftype(LF_TYPE lftype);
    
    //! set value by name
    /*!
     \param name of the field
     \param value variable to pass the value to
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void set_field(string name, string value);
    
    //! set value by name
    /*!
     \param name of the field
     \param value variable to pass the value to
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void set_field(string name, int value);
    
    //! set value by name
    /*!
     \param name of the field
     \param value variable to pass the value to
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void set_field(string name, float value);
    
    //! set value by name
    /*!
     \param name of the field
     \param value variable to pass the value to
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void set_field(string name, double value);
    
    
    
    
    
    //! parse the file passed
    /*!
     \param filename cfgfile the ifstream object of the file loaded
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void parse(const char* filename);
    
    //! parse the file passed
    /*!
     \param filename cfgfile the ifstream object of the file loaded
     \author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
    */
    void parse(string filename);

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
}}
#endif	/* PROPERTIES_HPP */

