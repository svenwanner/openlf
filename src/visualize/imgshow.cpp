#include "visualize/imgshow.hpp"


void OpenLF::linearRangeMapping(vigra::MultiArray<2,float>& fimg, vigra::MultiArray<2, vigra::UInt8>& img) {
    print(3,"linearRangeMapping(MultiArray<2,float>&,MultiArray<2,UInt8>&) called...");
    //functor to find range
    try {
        vigra::FindMinMax<vigra::FImage::PixelType> minmax; 
        //find original range
        vigra::inspectImage(vigra::srcImageRange(fimg), minmax);
        if(minmax.max<=minmax.min) throw OpenLF_Exception("linearRangeMapping failed, no distance to map!");
        //transform to range 0...255
        vigra::transformImage(vigra::srcImageRange(fimg), vigra::destImage(img),
                              vigra::linearRangeMapping( minmax.min, minmax.max, 0, 255) );
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

void OpenLF::linearRangeMapping(vigra::MultiArray<2,double>& dimg,vigra::MultiArray<2, vigra::UInt8>& img) {
    print(3,"linearRangeMapping(MultiArray<2,double>&,MultiArray<2,UInt8>&) called...");
    try {
    //functor to find range
        vigra::FindMinMax<vigra::DImage::PixelType> minmax;
        //find original range
        vigra::inspectImage(vigra::srcImageRange(dimg), minmax);
        if(minmax.max<=minmax.min) throw OpenLF_Exception("linearRangeMapping failed, no distance to map!");
        //transform to range 0...255
        vigra::transformImage(vigra::srcImageRange(dimg), vigra::destImage(img),
                              vigra::linearRangeMapping( minmax.min, minmax.max, 0, 255) );
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

void OpenLF::show(vigra::MultiArray<2,float>& img, const char* title) {
    print(3,"show(MultiArray<2,float>&,const char*)");
    cv::Mat cvimg;
    cvimg = cv::Mat::zeros(img.width(),img.height(),CV_8UC1);
    vigra::MultiArray<2,vigra::UInt8> img_u8(vigra::Shape2(img.width(),img.height()));
    linearRangeMapping(img,img_u8);
    cvimg.data = (uchar*)img_u8.data();
    show(cvimg,title);
}

void OpenLF::show(vigra::MultiArray<2,vigra::UInt8>& img, const char* title) {
    print(3,"show(MultiArray<2,UInt8>&,const char*)");
    cv::Mat cvimg;
    cvimg = cv::Mat::zeros(img.width(),img.height(),CV_8UC1);
    cvimg.data = (uchar*)img.data();
    show(cvimg,title);
}

void OpenLF::show(cv::Mat img, const char* title) {
    print(3,"show(Mat,const char*)");
    try {
        if(img.data == NULL) throw OpenLF_Exception("No image data available for show()!");

        cv::namedWindow( title, cv::WINDOW_AUTOSIZE ); // create a window for display
        cv::imshow( title, img ); // show image inside it
        cv::waitKey(0); //wait before close image
    }
    catch(exception & e) {
        cout << e.what() << endl;
    }
}

void OpenLF::imshow(OpenLF::Image& img, const char* title) {
    try {
        if(img.label()=="bw" || img.label()=="rgb") {
            cv::Mat cv_mat;
            img.get_opencv(cv_mat);
            cv::namedWindow(title, CV_WINDOW_AUTOSIZE);
            cv::imshow(title, cv_mat);
            cv::waitKey();
        }   
        else {
            throw OpenLF_Exception("Only grayscale and rgb images supported in show!");
        }
    } catch(exception & e) {
        cout << e.what() << endl;
    }
}

//void OpenLF::imshow(OpenLF::Image& img, const char* title) {
//    print(3,"imshow(Image&,const char*)");
//    try {
//        cv::Mat cvimg;
//        if(img.label()=="bw") {
//            cout << "show bw image" << endl;
//            vigra::MultiArray<2,float> img_f32;
//            img.swap_channel(0,img_f32);           
//            show(img_f32);
//        } 
//        else if(img.label()=="rgb") { 
////            cvimg = cv::Mat::zeros(img.width(),img.height(),CV_8UC3);
////            vigra::MultiArray<2, vigra::RGBValue<vigra::UInt8> > rgb_img;
////            img.get_rgb_compact(rgb_img);
////            cvimg.data = (uchar*)rgb_img.data();
//
//        } else {
//            throw OpenLF_Exception("Only grayscale and rgb images supported in show!");
//        }
//        show(cvimg,title);
//    }
//    catch(exception & e) {
//        cout << e.what() << endl;
//    }
//}
//
//void OpenLF::imshow(OpenLF::Image& img, int channel, const char* title) {
//    try {
//        
//    }
//    catch(exception & e) {
//        cout << e.what() << endl;
//    }
//}