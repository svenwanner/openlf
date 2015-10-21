/*
* Copyright (c) 2014 Maximilian Diebold
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

#include "clif/clif_vigra.hpp"
#include "clif/subset3d.hpp"
#include "clif/clif_cv.hpp"


//For 4D Light Field -> also able to handle special 4D Light Fields (3D horizontal 3D Vertical)
template <class Type_A> void displayHandler<Type_A>::disp_LFanimated(const char* winname)
{
    int LF_col = this->LightField->LF_data.shape()[3];
    int LF_row = this->LightField->LF_data.shape()[4];
    int Color_Channels = this->LightField->LF_data.shape()[0];

    int controlKey = 0;
    int Stop = 0;
    int SwapValue = 0;
    int Wait = 0;
    if (this->LightField->type == "horizontal"){SwapValue = 98;}
    if (this->LightField->type == "vertical"){SwapValue = 99;}
    int t = (LF_row-1)/2;//displayed light field row nr t selection is made with cursor
    int tt = (LF_col-1)/2;//dispayed light field column nr tt selection is made with cursor
    int ESC_KEY = 27;
//    int UP_ARROW = 65362;
//    int DOWN_ARROW = 65364;
//    int LEFT_ARROW = 65361;
//    int RIGHT_ARROW = 65363;
    int S_Key = 115;

    int SPACE = 32;

    cv::namedWindow(winname,CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);
    while(1)
    {
      if (SwapValue == 99){
          for (int i = 0 ; i < LF_row ;i++){
            vigra::MultiArray <3, Type_A> array3 = this->LightField->dataTranslatedCut->bindAt(4,i).bindAt(3,tt);
            cv::Mat Image;
            if (type_name<Type_A>::name() == static_cast<const char*>("unsigned char")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC1,array3.data());
                }
            }
            else if (type_name<Type_A>::name() == static_cast<const char*>("unsigned short")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC1,array3.data());
                }
            }
            if (Color_Channels == 3){
                cv::cvtColor(Image, Image, CV_RGB2BGR);
            }
            cv::imshow(winname,Image);
            if (Wait == 0) {controlKey = static_cast<int>(cv::waitKey(200));}
            if (controlKey == ESC_KEY) {Stop = controlKey ; cv::destroyWindow(winname); break;}
            if (controlKey == S_Key){ Wait=1; controlKey = static_cast<int>(cv::waitKey());}
            else {Wait = 0;}
//            if (c == LEFT_ARROW && tt > 0){ tt--;std::cout << tt << std::endl;}
//            if (c == RIGHT_ARROW && tt < LF_col-1){ tt++;std::cout << tt << std::endl;}
            if (controlKey == SPACE){ SwapValue=98; break; }
        }
        if (Stop == ESC_KEY) {cv::destroyWindow(winname); break;}
      }
      if (SwapValue == 99){
        for (int i = 2 ; i < LF_row ;i++){
            vigra::MultiArray <3, Type_A> array3 = this->LightField->dataTranslatedCut->bindAt(4,LF_row-i).bindAt(3,tt);
            cv::Mat Image;
            if (type_name<Type_A>::name() == static_cast<const char*>("unsigned char")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC1,array3.data());
                }
            }
            else if (type_name<Type_A>::name() == static_cast<const char*>("unsigned short")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC1,array3.data());
                }
            }
            if (Color_Channels == 3){
                cv::cvtColor(Image, Image, CV_RGB2BGR);
            }
            cv::imshow(winname,Image);
            if (Wait == 0) {controlKey = static_cast<int>(cv::waitKey(200));}
            if (controlKey == ESC_KEY) {Stop = controlKey ; cv::destroyWindow(winname); break;}
            if (controlKey == S_Key){ Wait=1; controlKey = static_cast<int>(cv::waitKey());}
            else {Wait = 0;}
//            if (c == LEFT_ARROW && tt > 0){ tt--;std::cout << tt << std::endl;}
//            if (c == RIGHT_ARROW && tt < LF_col-1){ tt++;std::cout << tt << std::endl;}
            if (controlKey == SPACE){ SwapValue=98; break; }
        }
        if (Stop == ESC_KEY) {cv::destroyWindow(winname); break;}
      }
      if (SwapValue == 98){
        for (int i = 0 ; i < LF_col ;i++){
            vigra::MultiArray <3, Type_A> array3 = this->LightField->dataTranslatedCut->bindAt(4,t).bindAt(3,i);
            cv::Mat Image;
            if (type_name<Type_A>::name() == static_cast<const char*>("unsigned char")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC1,array3.data());
                }
            }
            else if (type_name<Type_A>::name() == static_cast<const char*>("unsigned short")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC1,array3.data());
                }
            }
            if (Color_Channels == 3){
                cv::cvtColor(Image, Image, CV_RGB2BGR);
            }
            cv::imshow(winname,Image);
            if (Wait == 0) {controlKey = static_cast<int>(cv::waitKey(200));}
            if (controlKey == ESC_KEY) {Stop = controlKey ; cv::destroyWindow(winname); break;}
            if (controlKey == S_Key){ Wait=1; controlKey = static_cast<int>(cv::waitKey());}
            else {Wait = 0;}
//            if (c == UP_ARROW && t > 0){ t--;std::cout << t << std::endl;}
//            if (c == DOWN_ARROW && t < LF_row-1){ t++;std::cout << t << std::endl;}
            if (controlKey == SPACE){ SwapValue = 99; break;}
        }
        if (Stop == ESC_KEY) {cv::destroyWindow(winname); break;}
      }
      if (SwapValue == 98){
        for (int i = 2 ; i < LF_col ;i++){
            vigra::MultiArray <3, Type_A> array3 = this->LightField->dataTranslatedCut->bindAt(4,t).bindAt(3,LF_col-i);
            cv::Mat Image;
            if (type_name<Type_A>::name() == static_cast<const char*>("unsigned char")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC1,array3.data());
                }
            }
            else if (type_name<Type_A>::name() == static_cast<const char*>("unsigned short")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC1,array3.data());
                }
            }
            if (Color_Channels == 3){
                cv::cvtColor(Image, Image, CV_RGB2BGR);
            }
            cv::imshow(winname,Image);
            if (Wait == 0) {controlKey = static_cast<int>(cv::waitKey(200));}
            if (controlKey == ESC_KEY) {Stop = controlKey ; cv::destroyWindow(winname); break;}
            if (controlKey == S_Key){ Wait=1; controlKey = static_cast<int>(cv::waitKey());}
            else {Wait = 0;}
//            if (c == UP_ARROW && t > 0){ t--;std::cout << t << std::endl;}
//            if (c == DOWN_ARROW && t < LF_row-1){ t++;std::cout << t << std::endl;}
            if (controlKey == SPACE){ SwapValue = 99; break;}
        }
        if (Stop == ESC_KEY) {cv::destroyWindow(winname); break;}
      }
   }
}

//For cross structured Light Field
template <class Type_A> void displayHandler<Type_A>::disp_LFanimated_cross(const char* winname)
{
    int LF_col = this->LightField_Ch->LF_data.shape()[3];
    int LF_row = this->LightField_Cv->LF_data.shape()[4];
    int Color_Channels = this->LightField_Cv->LF_data.shape()[0];

    int controlKey = 0;
    int Stop = 0;
    int SwapValue = 98;
    int ESC_KEY = 27;
    int SPACE = 32;
    int S_Key = 115;
    int Wait=0;

    std::cout << "Img_column: " << LF_col << std::endl;
    std::cout << "Img_row: " << LF_row << std::endl;

    cv::namedWindow(winname,CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);
    while(1)
    {
      if (SwapValue == 99){
          for (int i = 0 ; i < LF_row ;i++){
            vigra::MultiArray <3, Type_A> array3 = this->LightField_Cv->dataTranslatedCut->bindAt(4,i).bindAt(3,0);
            cv::Mat Image;
            if (type_name<Type_A>::name() == static_cast<const char*>("unsigned char")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC1,array3.data());
                }
            }
            else if (type_name<Type_A>::name() == static_cast<const char*>("unsigned short")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC1,array3.data());
                }
            }
            if (Color_Channels == 3){
                cv::cvtColor(Image, Image, CV_RGB2BGR);
            }
            cv::imshow(winname,Image);
            if (Wait == 0) {controlKey = static_cast<int>(cv::waitKey(200));}
            if (controlKey == ESC_KEY) {Stop = controlKey ; cv::destroyWindow(winname); break;}
            if (controlKey == S_Key){ Wait=1; controlKey = static_cast<int>(cv::waitKey());}
            else {Wait = 0;}
            if (controlKey == SPACE){ SwapValue=98; break; }
        }
        if (Stop == ESC_KEY) {cv::destroyWindow(winname); break;}
      }
      if (SwapValue == 99){
        for (int i = 2 ; i < LF_row ;i++){
            vigra::MultiArray <3, Type_A> array3 = this->LightField_Cv->dataTranslatedCut->bindAt(4,LF_row-i).bindAt(3,0);
            cv::Mat Image;
            if (type_name<Type_A>::name() == static_cast<const char*>("unsigned char")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC1,array3.data());
                }
            }
            else if (type_name<Type_A>::name() == static_cast<const char*>("unsigned short")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC1,array3.data());
                }
            }
            if (Color_Channels == 3){
                cv::cvtColor(Image, Image, CV_RGB2BGR);
            }
            cv::imshow(winname,Image);
            if (Wait == 0) {controlKey = static_cast<int>(cv::waitKey(200));}
            if (controlKey == ESC_KEY) {Stop = controlKey ; cv::destroyWindow(winname); break;}
            if (controlKey == S_Key){ Wait=1; controlKey = static_cast<int>(cv::waitKey());}
            else {Wait = 0;}
            if (controlKey == SPACE){ SwapValue=98; break; }
        }
        if (Stop == ESC_KEY) {cv::destroyWindow(winname); break;}
      }
      if (SwapValue == 98){
        for (int i = 0 ; i < LF_col ;i++){
            vigra::MultiArray <3, Type_A> array3 = this->LightField_Ch->dataTranslatedCut->bindAt(4,0).bindAt(3,i);
            cv::Mat Image;
            if (type_name<Type_A>::name() == static_cast<const char*>("unsigned char")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC1,array3.data());
                }
            }
            else if (type_name<Type_A>::name() == static_cast<const char*>("unsigned short")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC1,array3.data());
                }
            }
            if (Color_Channels == 3){
                cv::cvtColor(Image, Image, CV_RGB2BGR);
            }
            cv::imshow(winname,Image);
            if (Wait == 0) {controlKey = static_cast<int>(cv::waitKey(200));}
            if (controlKey == ESC_KEY) {Stop = controlKey ; cv::destroyWindow(winname); break;}
            if (controlKey == S_Key){ Wait=1; controlKey = static_cast<int>(cv::waitKey());}
            else {Wait = 0;}
            if (controlKey == SPACE){ SwapValue = 99; break;}
        }
        if (Stop == ESC_KEY) {cv::destroyWindow(winname); break;}
      }
      if (SwapValue == 98){
        for (int i = 2 ; i < LF_col ;i++){
            vigra::MultiArray <3, Type_A> array3 = this->LightField_Ch->dataTranslatedCut->bindAt(4,0).bindAt(3,LF_col-i);
            cv::Mat Image;
            if (type_name<Type_A>::name() == static_cast<const char*>("unsigned char")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_8UC1,array3.data());
                }
            }
            else if (type_name<Type_A>::name() == static_cast<const char*>("unsigned short")){
                if (Color_Channels == 3){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC3,array3.data());
                }
                if (Color_Channels == 1){
                    Image = cv::Mat(cv::Size(array3.shape(1),array3.shape(2)),CV_16UC1,array3.data());
                }
            }
            if (Color_Channels == 3){
                cv::cvtColor(Image, Image, CV_RGB2BGR);
            }
            cv::imshow(winname,Image);
            if (Wait == 0) {controlKey = static_cast<int>(cv::waitKey(200));}
            if (controlKey == ESC_KEY) {Stop = controlKey ; cv::destroyWindow(winname); break;}
            if (controlKey == S_Key){ Wait=1; controlKey = static_cast<int>(cv::waitKey());}
            else {Wait = 0;}
            if (controlKey == SPACE){ SwapValue = 99; break;}
        }
        if (Stop == ESC_KEY) {cv::destroyWindow(winname); break;}
      }
   }
}

#endif /* GUI_H_  */



