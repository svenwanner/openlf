#include "image/image.hpp"
#include "visualize/imgshow.hpp"

OpenLF::Image::Image() 
{
    print(1,"Image() called...");
    
    // set properties
    this->_width = 0;
    this->_height = 0;
    this->_label = "";
}

OpenLF::Image::Image(int width, int height, int channels) 
{
    print(1,"Image(int,int,int) called...");
    if(channels <= 0) throw -1;
    
    // set properties
    this->_width = width;
    this->_height = height;
    
    // specifiy label depending on number of channels
    switch(channels) {
        case 1: this->_label = "bw"; break;
        case 2: this->_label = "vec"; break;
        case 3: this->_label = "rgb"; break;
        default: this->_label = ""; break;
    }
    
    // allocate memory
    for(int c=0; c<channels; c++) 
        this->_data.push_back(new vigra::MultiArray<2,float>(vigra::Shape2(this->_width,this->_height)));               
}

OpenLF::Image::Image(const char* filename) 
{
    print(1,"Image(const char*) called..");
    load(filename);
}

OpenLF::Image::Image(string filename) 
{
    print(1,"Image(string) called..");
    load(filename.c_str());
}

OpenLF::Image::Image(const Image& orig) 
{
    // set properties
    this->_width = orig.width();
    this->_height = orig.height();
    
    // allocate memory
    for(int c=0; c<this->_data.size(); c++) 
        this->_data.push_back(new vigra::MultiArray<2,float>(vigra::Shape2(this->_width,this->_height)));
}

OpenLF::Image::~Image() 
{
    for(int c=0; c<channels(); c++) 
        this->_data[c]->~MultiArray();
    this->_data.clear();
}









/* ######################
   GETTER SETTER METHODS
   ###################### */
    
int OpenLF::Image::width() const 
{
    return this->_width;
}

int OpenLF::Image::height() const 
{
    return this->_height;
}

int OpenLF::Image::channels() const 
{
    return this->_data.size();
}

string OpenLF::Image::label() const 
{
    return this->_label;
}

void OpenLF::Image::set_label(string label) 
{
    this->_label = label;
}

void OpenLF::Image::fill_image_channel(int channel, float value, float std) 
{
    srand (time(NULL));
    float std_dev = 0;
    float tmp_value = 0; 
    float* data_ptr = this->_data[channel]->data();
    
    for(int n=0; n<this->_width*this->_height; n++) {
        if(std>0) {
            std_dev = (float)rand()/RAND_MAX*std;
        }
        data_ptr[n] = value+std_dev;
    }
}






/* ######################
         IO METHODS
   ###################### */

void OpenLF::Image::load(const char* filename) 
{    
    //TODO: check if file is .exr and load without norming   
    
    //if image is not empty, delete channels
    if(this->_data.size()>0) {
        for(int c=0; c<channels(); c++) {
            this->_data[c]->~MultiArray();
        }
        this->_data.clear();
    }
    
 
    try {
        // import image info from file
        vigra::ImageImportInfo info(filename);
        
        if(info.isGrayscale()) {
            print(1,"load grayscale image...");
            
            // uint image to import data from file
            vigra::MultiArray<2, vigra::UInt8> in(info.width(), info.height());
            
            // allocate memory
            this->_data.push_back(new vigra::MultiArray<2,float>(info.width(), info.height()));
           
            // import data
            vigra::importImage(info, vigra::destImage(in));
            
            // copy data into object and map to range [1,0]
            vigra::UInt8* data_ptr = in.data();
            for(int n=0; n<info.width()*info.height(); n++) {
                this->_data[0]->data()[n] = ((float)data_ptr[n])/255.0;
            }
           
            // set properties
            this->_width = info.width();
            this->_height = info.height();
            this->_label = "bw";
        
        } else if(info.isColor()) {
            print(1,"load rgb image...");
            
            // uint rgb image to import data from file
            vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > in(info.shape());
            
            // allocate memory
            for(int c=0; c<3; c++)
                this->_data.push_back(new vigra::MultiArray<2,float>(info.width(), info.height()));
       
            // import data
            vigra::importImage(info, in);
            
            // copy data into object and map to range [1,0]
            int index;
            for(int x=0; x<info.width(); x++) {
                for(int y=0; y<info.height(); y++) {
                    index = x*info.width()+y;
                    this->_data[0]->data()[index] = in(y,x)[0]/255.0f;
                    this->_data[1]->data()[index] = in(y,x)[1]/255.0f;
                    this->_data[2]->data()[index] = in(y,x)[2]/255.0f;
                }
            }
            
            // set properties
            this->_width = info.width();
            this->_height = info.height();
            this->_label = "rgb";
            
        } else {
            throw OpenLF_Exception("Only grayscale and rgb images supported in Image::load()!");
        }
    }
    catch(exception & e) {
        cout << e.what() << endl;
    }
}


void OpenLF::Image::save(string filename)
{
    //TODO: add OpenEXR export
    
    string ftype = OpenLF::find_ftype(filename);
    
    if(this->_label == "bw") {
        string msg = "save bw image as " + ftype +"..."; print(1,msg.c_str());
        
        if(ftype=="jpg")
            vigra::exportImage(*this->_data[0], vigra::ImageExportInfo(filename.c_str()).setCompression("JPEG QUALITY=75"));
        else
            vigra::exportImage(*this->_data[0], filename.c_str());
    }
    
    else {
        string msg = "save " + this->_label + " image as " + ftype +"..."; print(1,msg.c_str());
     
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

float* OpenLF::Image::get_channel(int channel) 
{
    print(3,"get_channel(int)");    
    if(channel>=0 && channel<this->_data.size()) {
        return this->_data[channel]->data();
    }
}

void OpenLF::Image::swap_channel(int channel, vigra::MultiArray<2,float>& array) 
{
    print(3,"get_channel(int)");    
    if(channel<0 || channel>=this->_data.size()) throw OpenLF_Exception("channel doesn't exist exception in Image::swap_channel(int,MultiArray<2,float>&)!");
    try {
        // swap data of channel into array by copying shape and data pointer
        this->_data[channel]->swap(array);
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

float OpenLF::Image::access_pixel(int x,int y, int channel) 
{
    print(3,"access_pixel(int,int,int)");
    try {
        if(channel<0 || channel>=this->_data.size()) throw OpenLF_Exception("channel doesn't exist exception in Image::acccess_pixel(int,int,int)!");
        if(x<0 || x>=this->_width) throw OpenLF_Exception("out of range row access in Image::acccess_pixel(int,int,int)!");
        if(y<0 || y>=this->_height) throw OpenLF_Exception("out of range column access in Image::acccess_pixel(int,int,int)!");
        return this->_data[channel]->data()[x*this->_width+y];
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

void OpenLF::Image::get_pixel(int x, int y, vector<float> &values) 
{
    print(3,"get_pixel(int,int,vector<float>)");
    values.clear();
    for(int c=0; c<this->_data.size(); c++) {
        values.push_back(access_pixel(x,y,c));
    }
}

void OpenLF::Image::get_rgb(vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> >& rgb_img) 
{      
    // copy data into vigra RGB image
    int n=0;
    for(int x=0; x<this->_width; x++) {
        for(int y=0; y<this->_height; y++) {
            for(int c=0; c<3; c++) {
                if(c<this->_data.size())
                    rgb_img.data()[n][c] = (int)(this->_data[c]->data()[this->_width*x+y]*255);
                else
                    rgb_img.data()[n][c] = 0;
            }
            n++;
        }
    }
}
