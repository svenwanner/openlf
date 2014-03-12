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


#include "image/image.hpp"
#include "visualize/imgshow.hpp"

OpenLF::Image::Image() 
/* TEST in image_test::testConstructor() */
{
    print(1,"Image() called...");
    
    // set properties
    _width = 0;
    _height = 0;
    _label = "";
    _num_of_channels = 0;
}

OpenLF::Image::Image(int width, int height, int channels)  
/* TEST in image_test::testConstructor() */
{
    print(1,"Image(int,int,int) called...");
    
    if(channels < 0) throw  OpenLF_Exception("Channel needs to be a posiiv integer in Constructor!");
    
    // set properties
    _width = width;
    _height = height;
    
    // specifiy label depending on number of channels
    switch(channels) {
        case 1: _label = "bw"; break;
        case 2: _label = "vec"; break;
        case 3: _label = "rgb"; break;
        default: _label = ""; break;
    }
    
    // allocate memory
    for(int c=0; c<channels; c++) 
        _data.push_back(new vigra::MultiArray<2,float>(vigra::Shape2(this->_width,this->_height)));     
    
    _num_of_channels = _data.size();
}

OpenLF::Image::Image(const char* filename)  
/* TEST in image_test::testConstructor() */
{
    print(1,"Image(const char*) called...");
    
    load(filename);
}

OpenLF::Image::Image(string filename)  
/* TEST in image_test::testConstructor() */
{
    print(1,"Image(string) called...");
    
    load(filename.c_str());
}

OpenLF::Image::Image(const Image& orig) 
/* image_test::testCopyConstructor() */
{       
    print(1,"Image(const Image&) called...");
    
    // set properties
    _width = orig.width();
    _height = orig.height();
    _label = orig.label();
    
    // pointer to data
    float* data_ptr = NULL;
    float* other_data_ptr = NULL;
    
    // allocate memory
    for(int c=0; c<orig.channels(); c++) {
        _data.push_back(new vigra::MultiArray<2,float>(vigra::Shape2(_width,_height)));
        
        try {
            // get data pointer of current channel
            data_ptr = _data[c]->data();
            other_data_ptr = orig._data[c]->data();
            if(!data_ptr) throw OpenLF_Exception("Getting this data pointer failed in Image:: CopyConstructor!");
            if(!other_data_ptr) throw OpenLF_Exception("Getting other data pointer failed in Image:: CopyConstructor!");

            // copy data 
            for(int n=0; n<_width*_height; n++) {
                data_ptr[n] = other_data_ptr[n];
            }
        } catch(exception & e) {
            cout << e.what() << endl;
        }
        
    }
    _num_of_channels = _data.size();
}

OpenLF::Image::~Image() 
{
    print(1,"~Image() called...");
    for(int c=0; c<channels(); c++) {
        this->_data[c]->~MultiArray();
        delete this->_data[c];
    }
    this->_data.clear();
}









/* ######################
   GETTER SETTER METHODS
   ###################### */
    
int OpenLF::Image::width() const  
/* TEST in image_test::testConstructor() */
{
    return _width;
}

int OpenLF::Image::height() const  
/* TEST in image_test::testConstructor() */
{
    return _height;
}

int OpenLF::Image::channels() const  
/* TEST in image_test::testConstructor() */
{
    return _num_of_channels;
}

string OpenLF::Image::label() const  
/* TEST in image_test::testConstructor() */
{
    return _label;
}

void OpenLF::Image::set_label(string label)  
/* TEST in image_test::testConstructor() */
{
    print(1,"Image::set_label(string) called...");
    
    _label = label;
}

void OpenLF::Image::fill_image_channel(int channel, float value, float std)  
/* TEST in image_test::testConstructor() */
{
    print(1,"Image::fill_image_channel(int,float,std) called...");
    
    srand (time(NULL));
    float std_dev = 0;
    float* data_ptr = NULL;
    
    try {
        // get data pointer 
        data_ptr = _data[channel]->data();
        
        if(_num_of_channels<=0 || channel >= _num_of_channels || data_ptr == NULL)
            throw OpenLF_Exception("Channel access exception in Image::fill_image_channel()!");

        // fill channel with value plus a random value if std>0
        for(int n=0; n<_width*_height; n++) {
            if(std>0) {
                std_dev = (float)rand()/RAND_MAX*std;
            }
            data_ptr[n] = value+std_dev;
        }
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

void OpenLF::Image::add_channel() {
/* TEST in image_test::addCannel() */
    print(1,"Image::add_channel() called...");
    
    if(_width>0 && _height>0) {
        _data.push_back(new vigra::MultiArray<2,float>(vigra::Shape2(_width,_height)));
        *_data[_num_of_channels-1] = 0;
    }
    _num_of_channels = _data.size();
}

void OpenLF::Image::add_channel(float* data) {
/* TEST in image_test::addCannel() */
    print(1,"Image::add_channel(float*) called...");
    
    float* data_ptr = NULL;
    try {
        _data.push_back(new vigra::MultiArray<2,float>(vigra::Shape2(_width,_height)));
        data_ptr = _data[_num_of_channels-1]->data();
        
        if(data_ptr == NULL)
            throw OpenLF_Exception("Channel access exception in Image::add_channel()!");
        
        // copy data
        for(int n=0; n<_width*_height; n++) {
            data_ptr[n] = data[n];
        }
    } catch(exception & e) {
        cout << e.what() << endl;
    }
    _num_of_channels = _data.size();
}

void OpenLF::Image::add_channel(int channel, const OpenLF::Image& orig)
/* Test: image_test::conversionOpenCV() */
{ 
    print(1,"Image::add_channel(int,const Image&) called...");
    
    try {
        // pointer to data arrays
        float* data_ptr = NULL;
        float* orig_data_ptr = NULL;
    
        // check for shape consistency
        if(orig.width()!=_width || orig.height() != _height)
            throw OpenLF_Exception("Shape mismatch in Image::add_channel(const OpenLF::Image&)!");
        
        // add MultiArray to _data and get data pointers
        _data.push_back(new vigra::MultiArray<2,float>(vigra::Shape2(_width,_height)));
        orig_data_ptr = orig.get_channel(channel);
        
        if(orig_data_ptr == NULL)
            throw OpenLF_Exception("Channel access in passed instance exception in Image::add_channel(int, const OpenLF::Image&)!");
        
        // copy data
        for(int n=0; n<_width*_height; n++) {
            _data[_num_of_channels]->data()[n] = orig_data_ptr[n];
        }
    } catch(exception & e) {
        cout << e.what() << endl;
    }
    _num_of_channels = _data.size();
}

void OpenLF::Image::set_channel(float* data, int channel) 
/* TEST in image_test::addCannel() */
{
    print(1,"Image::set_channel(float*,int) called...");
    
    float* data_ptr = NULL;
    
    try {
        if(channel < 0 || channel >= _num_of_channels)
            throw OpenLF_Exception("Access to not existing channel exception in Image::set_channel()!");
        
        /// get data pointer
        data_ptr = _data[channel]->data();
        if(data_ptr == NULL)
            throw OpenLF_Exception("Channel access exception in Image::add_channel()!");
        
        // copy data
        for(int n=0; n<_width*_height; n++) {
            data_ptr[n] = data[n];
        }
        
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

void OpenLF::Image::copy_channel(int channel, const Image& orig)
/* TEST in image_test::conversionOpenCV() */
{    
    print(1,"Image::copy_channel(int,const Image&) called...");
    
    try {
        // delete existing data
        if(_num_of_channels>0) {
            for(int c=0; c<_num_of_channels; c++) {
                _data[c]->~MultiArray();
            }
            _data.clear();
        }
        
        float* orig_data = NULL;

        /// set properties
        _width = orig.width();
        _height = orig.height();
        _label = "bw";

        // copy channel
        _data.push_back(new vigra::MultiArray<2,float>(vigra::Shape2(_width,_height)));
        orig_data = orig.get_channel(channel);
        if(orig_data == NULL) OpenLF_Exception("Channel access exception in Image::copy_channel(int, const Image&)!");
        for(int n=0; n<_width*_height; n++) {
            _data[0]->data()[n] = orig_data[n];
        }
            
    } catch(exception & e) {
        cout << e.what() << endl;
    }
    _num_of_channels = _data.size();
}




/* ######################
         IO METHODS
   ###################### */

void OpenLF::Image::load(const char* filename)  
/* TEST in image_test::testConstructor() */
{    
    print(1,"Image::load(const char*) called...");
    
    //TODO: check if file is .exr and load without norming   
    
    //if image is not empty, delete channels
    if(_data.size()>0) {
        for(int c=0; c<_num_of_channels; c++) {
            _data[c]->~MultiArray();
        }
        _data.clear();
    }
    
 
    try {
        // import image info from file
        vigra::ImageImportInfo info(filename);
        
        if(info.isGrayscale()) {
            print(2,"Image -> load grayscale image...");
            
            // uint image to import data from file
            vigra::MultiArray<2, vigra::UInt8> in(info.width(), info.height());
            
            // allocate memory
            _data.push_back(new vigra::MultiArray<2,float>(info.width(), info.height()));
           
            // import data
            vigra::importImage(info, vigra::destImage(in));
            
            // copy data into object and map to range [1,0]
            vigra::UInt8* data_ptr = in.data();
            for(int n=0; n<info.width()*info.height(); n++) {
                _data[0]->data()[n] = ((float)data_ptr[n])/255.0;
            }
           
            // set properties
            _width = info.width();
            _height = info.height();
            _label = "bw";
            _num_of_channels = 1;
        
        } else if(info.isColor()) {
            print(2,"Image -> load rgb image...");
            
            // uint rgb image to import data from file
            vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info.shape());
            
            // allocate memory
            for(int c=0; c<3; c++)
                _data.push_back(new vigra::MultiArray<2,float>(info.width(), info.height()));
       
            // import data
            vigra::importImage(info, in);
            
            // copy data into object and map to range [1,0]
            int index;
            for(int x=0; x<info.width(); x++) {
                for(int y=0; y<info.height(); y++) {
                    index = y*info.width()+x;
                    _data[0]->data()[index] = in(x,y)[0]/255.0f;
                    _data[1]->data()[index] = in(x,y)[1]/255.0f;
                    _data[2]->data()[index] = in(x,y)[2]/255.0f;
                }
            }
            
            // set properties
            _width = info.width();
            _height = info.height();
            _label = "rgb";
            _num_of_channels = 3;
            
        } else {
            throw OpenLF_Exception("Only grayscale and rgb images supported in Image::load()!");
        }
    }
    catch(exception & e) {
        cout << e.what() << endl;
    }
}


void OpenLF::Image::save(string filename)  
/* TEST in image_test::testConstructor() */
{
    print(1,"Image::save(string) called...");
    //TODO: add OpenEXR export
    
    string ftype = OpenLF::find_ftype(filename);
    
    if(_label == "bw") {
        string msg = "save bw image as " + ftype +"..."; print(1,msg.c_str());
        
        if(ftype=="jpg")
            vigra::exportImage(*_data[0], vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
        else
            vigra::exportImage(*_data[0], filename.c_str());
    }
    
    else {
        string msg = "save " + _label + " image as " + ftype +"..."; print(1,msg.c_str());
     
        //make rgb container
        vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > out_img(vigra::Shape2(this->_width,this->_height));
        out_img.init(0);
        
        //fill rgb container with data
        get_rgb(out_img);
    
        if(ftype=="jpg")
            vigra::exportImage(out_img, vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
        else
            vigra::exportImage(out_img, filename.c_str());
    }

}







/* ######################
    ACCESS DATA METHODS
   ###################### */

float* OpenLF::Image::get_channel(int channel) const
/* TEST in image_test::testCannelAcccess() */
{    
    print(1,"Image::get_channel(int) called...");    
    
    if(channel>=0 && channel<_num_of_channels) {
        return _data[channel]->data();
    }
    else return NULL;
}

void OpenLF::Image::swap_channel(int channel, vigra::MultiArray<2,float>& array) 
/* TEST in image_test::testCannelAcccess() */
{
    print(1,"Image::swap_channel(int,MultiArray) called...");    
    
    if(channel<0 || channel>=_num_of_channels) throw OpenLF_Exception("channel doesn't exist exception in Image::swap_channel(int,MultiArray<2,float>&)!");
    try {
        // swap data of channel into array by copying shape and data pointer
        _data[channel]->swap(array);
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

float OpenLF::Image::access_pixel(int x,int y, int channel)
/* TEST in image_test::testCannelAcccess() */
{
    print(1,"Image::access_pixel(int,int,int) called...");
    
    try {
        if(channel<0 || channel>=_num_of_channels) throw OpenLF_Exception("channel doesn't exist exception in Image::acccess_pixel(int,int,int)!");
        if(x<0 || x>=_width) throw OpenLF_Exception("out of range row access in Image::acccess_pixel(int,int,int)!");
        if(y<0 || y>=_height) throw OpenLF_Exception("out of range column access in Image::acccess_pixel(int,int,int)!");
        return _data[channel]->data()[x*_width+y];
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

void OpenLF::Image::get_pixel(int x, int y, vector<float> &values)  
/* TEST in image_test::testConstructor() */
{    
    print(1,"Image::get_pixel(int,int,vector<float>) called...");
    values.clear();
    for(int c=0; c<_num_of_channels; c++) {
        values.push_back(access_pixel(x,y,c));
    }
}

void OpenLF::Image::get_rgb(vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> >& rgb_img) 
/* TEST in image_test::testConstructor() */
{      
    print(1,"Image::get_rgb(MultiArray) called...");
    // copy data into vigra RGB image
    int n=0;
    for(int x=0; x<_width; x++) {
        for(int y=0; y<_height; y++) {
            for(int c=0; c<3; c++) {
                if(c<_num_of_channels)
                    rgb_img.data()[n][c] = (int)(_data[c]->data()[_width*x+y]*255);
                else
                    rgb_img.data()[n][c] = 0;
            }
            n++;
        }
    }
}

void OpenLF::Image::get_opencv(cv::Mat& cv_mat) 
/* TEST in image_test::conversionOpenCV() */
{    
    print(1,"Image::get_opencv(Mat&) called...");
    try {
        if(label()=="bw") { 
            if(_num_of_channels > 0) { 
                cv_mat = cv::Mat::zeros(_height,_width,CV_32FC1);
                cv_mat.data = (uchar*)_data[0]->data();
            } else throw OpenLF_Exception("Unresolved bw channel access in Image::get_opencv(cv::Mat&)!");
        }
        else if(label()=="vec") {
            if(_num_of_channels > 1) { 
                cv_mat = cv::Mat::zeros(_height,_width,CV_32FC2);

                for(int x=0; x<width(); x++) {
                    for(int y=0; y<height(); y++) {
                        cv_mat.at<cv::Vec2f>(y,x)[0] = _data[0]->data()[width()*y+x];
                        cv_mat.at<cv::Vec2f>(y,x)[1] = _data[1]->data()[width()*y+x];
                    }
                }       
            } else throw OpenLF_Exception("Unresolved vector channel access in Image::get_opencv(cv::Mat&)!");
        }
        else if(label()=="rgb") {
            if(_num_of_channels > 1) {
                cv_mat = cv::Mat::zeros(_height,_width,CV_32FC3);

                for(int x=0; x<width(); x++) {
                    for(int y=0; y<height(); y++) {
                         cv_mat.at<cv::Vec3f>(y,x)[0] = _data[2]->data()[width()*y+x];
                         cv_mat.at<cv::Vec3f>(y,x)[1] = _data[1]->data()[width()*y+x];
                         cv_mat.at<cv::Vec3f>(y,x)[2] = _data[0]->data()[width()*y+x];
                    }
                } 
            } else throw OpenLF_Exception("Unresolved rgb channel access in Image::get_opencv(cv::Mat&)!");
        }
        
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

void OpenLF::Image::get_opencv(int channel, cv::Mat& cv_mat) 
/* TEST in image_test::conversionOpenCV() */
{
    print(1,"Image::get_opencv(int,Mat&) called...");
    try {
        if(_num_of_channels > 0 && channel < _num_of_channels) { 
            cv_mat = cv::Mat::zeros(_height,_width,CV_32FC1);
            cv_mat.data = (uchar*)_data[channel]->data();
        } else throw OpenLF_Exception("Unresolved channel access in Image::get_opencv(int,cv::Mat&)!");
        
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}
