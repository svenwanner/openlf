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


#include "lightfield/lightfield_base.hpp"

OpenLF::Lightfield_base::Lightfield_base() {
    print(1,"Lightfield_base() called...");
    _valid = false;
    init_properties(-1,-1,-1,-1,0,-1.0f,-1.0f,-1.0f,"");
}

OpenLF::Lightfield_base::Lightfield_base(int width, int height, int cams_h, int cams_v, int channels, string type) {
    print(1,"Lightfield_base(int,int,int,int,int,string) called...");
    _valid = false;
    init_properties(width,height,cams_h,cams_v,channels,-1.0f,-1.0f,-1.0f,type);
}

OpenLF::Lightfield_base::Lightfield_base(int width, int height, int cams_h, int cams_v, int channels, float baseline_h, float baseline_v, float focal_length, string type) {
    print(1,"Lightfield_base(int,int,int,int,int,string) called...");
    _valid = false;
    init_properties(width,height,cams_h,cams_v,channels,baseline_h,baseline_v,focal_length,type);
}

OpenLF::Lightfield_base::Lightfield_base(const Lightfield_base& orig) {
    _valid = false;
    print(1,"copy Lightfield_base(Lightfield_base&) called...");
}

OpenLF::Lightfield_base::~Lightfield_base() {
    print(1,"Lightfield_base destroyed...");
    release();
}

void OpenLF::Lightfield_base::release() 
{
    print(2,"Lightfield_base::release called...");
    for(int c=0; c<_data.size(); c++) {
        _data[c].~MultiArray();       
    }
    _data.clear();
    _labels.clear();
    _valid = false;
}


/* ######################
   GETTER SETTER METHODS
   ###################### */

int OpenLF::Lightfield_base::cams_v() const  
{
    return _num_of_cams_v;
}

int OpenLF::Lightfield_base::cams_h() const 
{
    return _num_of_cams_h;
}
    
int OpenLF::Lightfield_base::width() const  
{
    return _width;
}

int OpenLF::Lightfield_base::height() const 
{
    return _height;
}

int OpenLF::Lightfield_base::channels() const  
{
    return _data.size();
}

float OpenLF::Lightfield_base::focal_length() const 
{
    return _focal_length;
}

float OpenLF::Lightfield_base::baseline_v() const 
{
    return _baseline_v;
}

float OpenLF::Lightfield_base::baseline_h() const 
{
    return _baseline_h;
}

string OpenLF::Lightfield_base::type() const  
{
    return _type;
}

bool OpenLF::Lightfield_base::valid() const  
{
    return _valid;
}



void OpenLF::Lightfield_base::get_channel(int index, vigra::MultiArray<4,float>&)
{
    
}
   
void OpenLF::Lightfield_base::get_channel(string label, vigra::MultiArray<4,float>&) 
{
    
}

string OpenLF::Lightfield_base::get_label(int index) 
{
    if(index >= 0 && index < _labels.size()) {
        return _labels[index];
    }
    else
        throw OpenLF_Exception("Unexpected label access in Lightfield_base::get_label!");
}

vigra::Shape4 OpenLF::Lightfield_base::shape() 
{
    if(_data.size()>0) {
        return _data[0].shape();
    }
}









/* ######################
   CHANGE CONTENT METHODS
   ###################### */

void OpenLF::Lightfield_base::delete_channel(int index) 
/* TEST in lightfield_base_test::testConstructor() */
{
    print(2,"Lightfield_base::delete_channel(int) called...");
    
    if(index>=0 && index<_data.size()) {
       // move element to delete to the back of the vector
        _data[index] = move(_data.back());
        _labels[index] = move(_labels.back());
        
        //call destructor and remove last element
        _data[_data.size()-1].~MultiArray();
        _data.pop_back();
        _labels.pop_back();
    }
}

void OpenLF::Lightfield_base::delete_channel(string label) 
/* TEST in lightfield_base_test::testConstructor() */
{
    print(2,"Lightfield_base::delete_channel(string) called...");
    
    int index = get_data_index(label);
    delete_channel(index);
}




/* ########################
   PROTECTED HELPER METHODS
   ######################## */

void OpenLF::Lightfield_base::init_properties(int width, int height, int cams_h, int cams_v, int channels, float baseline_h, float baseline_v, float focal_length, string type) 
{
    print(2,"Lightfield_base::init_properties called...");
    
    // if not one of the specified types throw Exception
    if(type == "3DH" || type == "3DV" || type == "4D" || type == "CROSS" || type == "") {
        
        if(cams_h>1 && cams_v==1) {
            type = "3DH";
        }
        if(cams_v>1 && cams_h==1) {
            type = "3DV";
        }
 
        if(type == "3DH" && cams_v!=1)
            throw OpenLF_Exception("Structure inconsistency in Lightfield_base::init_properties, type 3DH and more than one camera in vertical direction is contradictory!");
        if(type == "3DV" && cams_h!=1)
            throw OpenLF_Exception("Structure inconsistency in Lightfield_base::init_properties, type 3DV and more than one camera in horizontal direction is contradictory!");
        
        // set properties
        _width = width;
        _height = height;
        _num_of_cams_v = cams_v;
        _num_of_cams_h = cams_h;
        _focal_length = focal_length;
        _baseline_v = baseline_v;
        _baseline_h = baseline_h;
        _type = type;
    }
    else {
        throw OpenLF_Exception("Type Exception in Lightfield_base::init_properties, type not specified!");
    }
    
    if(channels > 0 && _width>0 && _height>0 && cams_h>0 && cams_v>0 && type != "")
    {
        _valid = true;
    
        // init as much MultiArrays as channels specified
        for(int c=0; c<channels; c++) {

            // check if 1 channel is specified then label as bw
            if(channels==1) {
                _labels.push_back("bw");
            }
            // if 3 channels are specified label as rgb
            else if(channels==3) {
                switch(c) {
                    case 0:
                        _labels.push_back("r");
                        break;
                    case 1:
                        _labels.push_back("g");
                        break;
                    case 2:
                        _labels.push_back("b");
                        break;
                }
            }
            // otherwise set index as label
            else {
                _labels.push_back(to_string(c));
            }

            // create MultiArray for each channel and init with zero
            _data.push_back(vigra::MultiArray<4,float>(vigra::Shape4(_width,_height,_num_of_cams_h,_num_of_cams_v)));
            _data[c] = 0;
        }
    }  
}

int OpenLF::Lightfield_base::get_data_index(string label) {
    print(2,"Lightfield_base get_data_index(string) called...");
    
    int index_found = -1;
    
    // if size of _labels and of _data isn't the same throw exception
    if(_labels.size() != _data.size())
        throw OpenLF_Exception("Amount of labels Exception in Lightfield_base::get_data_index, size of labels and data is inconsistent!");
    
    // search label index and return when found, otherwise return -1
    for(int c=0; c<_data.size(); c++) {
        if(_labels[c] == label) {
            
            // if the label was found before throw exception
            if(index_found!=-1)
                throw OpenLF_Exception("Double label Exception in Lightfield_base::get_data_index, label names are not unique!");
            index_found = c;
        }
    }
    return index_found;
}