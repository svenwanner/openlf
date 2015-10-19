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

#include <iostream>
#include <cmath>
#include <class_LFsetup.h>
#include <iomanip>      // std::setprecision
#ifndef Q_MOC_RUN      // Problem with Qt 4.8 moc and boost 1.55
#include <boost/format.hpp> 
#endif
#include <fstream>
#include <iostream>
#include <random>

void LFsetup::deleteValid(){

	if (set.resolution_X__px__userInput == false) {
		set_valid.resolution_X__px = false;
	}
	if (set.resolution_Y__px__userInput == false){
		set_valid.resolution_Y__px = false;
	}
	if (set.AspectRatio__userInput == false) {
		set_valid.AspectRatio = false;
	}
	if (set.Pixelsize_X__m__userInput == false){
		set_valid.Pixelsize_X__m = false;
	}
	if (set.Pixelsize_Y__m__userInput == false){
		set_valid.Pixelsize_Y__m = false;
	}
	if (set.PixelAspectRatio__userInput == false) {
		set_valid.PixelAspectRatio = false;
	}
	if (set.sensor_X__m__userInput == false){
		set_valid.sensor_X__m = false;
	}
	if (set.sensor_Y__m__userInput == false){
		set_valid.sensor_Y__m = false;
	}
	if (set.DH_X__m__userInput == false){
		set_valid.DH_X__m = false;
	}
	if (set.DH_Y__m__userInput == false){
		set_valid.DH_Y__m = false;
	}
	if (set.dH_X__px__userInput == false){
		set_valid.dH_X__px = false;
	}
	if (set.dH_Y__px__userInput == false){
		set_valid.dH_Y__px = false;
	}
    if (set.theta_X__pxm__userInput == false){
        set_valid.theta_X__pxm = false;
	}
    if (set.theta_Y__pxm__userInput == false){
        set_valid.theta_Y__pxm = false;
	}
	if (set.delta_d_X__px__userInput == false){
		set_valid.delta_d_X__px = false;
	}
	if (set.delta_d_Y__px__userInput == false){
		set_valid.delta_d_Y__px = false;
	}
	if (set.delta_D_X__m__userInput == false){
		set_valid.delta_D_X__m = false;
	}
	if (set.delta_D_Y__m__userInput == false){
		set_valid.delta_D_Y__m = false;
	}
	if (set.d1_X__px__userInput == false){
		set_valid.d1_X__px = false;
	}
	if (set.d1_Y__px__userInput == false){
		set_valid.d1_Y__px = false;
	}
	if (set.D1_X__m__userInput == false){
		set_valid.D1_X__m = false;
	}
	if (set.D1_Y__m == false){
		set_valid.D1_Y__m = false;
	}
	if (set.d2_X__px__userInput == false){
		set_valid.d2_X__px = false;
	}
	if (set.d2_Y__px__userInput == false){
		set_valid.d2_Y__px = false;
	}
	if (set.D2_X__m__userInput == false){
		set_valid.D2_X__m = false;
	}
	if (set.D2_Y__m__userInput == false){
		set_valid.D2_Y__m = false;
	}
	if (set.focal_length_X__px__userInput == false){
		set_valid.focal_length_X__px = false;
	}
	if (set.focal_length_Y__px__userInput == false){
		set_valid.focal_length_Y__px = false;
	}
	if (set.delta_focal_length__m__userInput == false){
		set_valid.delta_focal_length__m = false;
	}
	if (set.baseline_X__m__userInput == false){
		set_valid.baseline_X__m = false;
	}
	if (set.baseline_Y__m__userInput == false){
		set_valid.baseline_Y__m = false;
	}
	if (set.delta_baseline__m__userInput == false){
		set_valid.delta_baseline__m= false;
	}
    if (set.delta_rotation__deg__userInput == false){
        set_valid.delta_rotation__deg= false;
    }
	if (set.baseline_ratio__userInput == false){
		set_valid.baseline_ratio = false;
	}
	if (set.focalLength__m__userInput == false){
		set_valid.focalLength__m = false;
	}
	if (set.DoF_D_N__m__userInput == false){
		set_valid.DoF_D_N__m = false;
	}
	if (set.DoF_D_F__m__userInput == false){
		set_valid.DoF_D_F__m = false;
	}
	if (set.f_number__userInput == false){
		set_valid.f_number = false;
	}
	if (set.DoF_H__m__userInput == false){
		set_valid.DoF_H__m = false;
	}
	if (set.DoF_subject_distance__m__userInput == false){
		set_valid.DoF_subject_distance__m = false;
	}
	if (set.DoF_DoF__m__userInput == false){
		set_valid.DoF_DoF__m = false;
	}
 	if (set.delta_d_inaccuracy_ST__px__userInput == false){
		set_valid.delta_d_inaccuracy_ST__px = false;
	}       
 	if (set.Cam_X__userInput == false){
		set_valid.Cam_X = false;
	}
    if (set.Cam_Y__userInput == false){
        set_valid.Cam_Y = false;
	}
    if (set.CircleofConfusion__m__userInput == false){
        set_valid.CircleofConfusion__m = false;
    }
}

void LFsetup::expBlender(std::string filename){

	double camX = set.Cam_X;
	double camY = set.Cam_Y;

	 std::random_device rd;
	 std::mt19937 gen(rd());

     //std::cout << set.delta_rotation__deg << std::endl;

     std::normal_distribution<> baselineJitter(0,set.delta_baseline__m);
     std::normal_distribution<> focalLengthJitter(0,set.delta_focal_length__m);
     std::normal_distribution<> rotationJitter(0,set.delta_rotation__deg);
         
	 std::ofstream file;
	 file.clear();
     file.open(filename, std::fstream::out);

     file << "[Camera_Setup]\n";
     file << "resolution_h__px=";
     file << (set.resolution_X__px);
     file << "\n";
     file << "resolution_v__px=";
     file << (set.resolution_Y__px);
     file << "\n";

     file << "cam_h=";
     file << (set.Cam_X);
     file << "\n";
     file << "cam_v=";
     file << (set.Cam_Y);
     file << "\n";

     file << "baseline_h__m=";
     file << (set.baseline_X__m);
     file << "\n";
     file << "baseline_v__m=";
     file << (set.baseline_Y__m);
     file << "\n";

     file << "Pixelsize_h__m=";
     file << (set.Pixelsize_X__m);
     file << "\n";
     file << "Pixelsize_v__m=";
     file << (set.Pixelsize_Y__m);
     file << "\n";


     file << "sensor_X__m=";
     file << (set.sensor_X__m);
     file<< "\n";
     file << "sensor_Y__m=";
     file << (set.sensor_Y__m);
     file << "\n";

     file << "FocalLength__m=";
     file << (set.focalLength__m);
     file << "\n";


     file << "f_number=";
     file << (set.f_number);
     file << "\n";
     file << "DoF_subject_distance__m=";
     file << (set.DoF_subject_distance__m);
     file << "\n";
     file << "CircleofConfusion__m=";
     file << (set.CircleofConfusion__m);
     file << "\n";

     file << "\n[LFSetup_Parameter]\n";
     file << "DH_h__m=";
     file << (set.DH_X__m);
     file << "\n";
     file << "DH_v__m=";
     file << (set.DH_Y__m);
     file << "\n";
     file << "delta_d_h__px=";
     file << (set.delta_d_X__px*2);
     file << "\n";
     file << "delta_d_v__px=";
     file << (set.delta_d_Y__px*2);
     file << "\n";
     file << "delta_b__m=";
     file << (set.delta_baseline__m);
     file << "\n";
     file << "delta_f__m=";
     file << (set.delta_focal_length__m);
     file << "\n";
     file << "delta_d_inaccuracy_ST__px=";
     file << (set.delta_d_inaccuracy_ST__px);
     file << "\n";
     file << "baselineJitterX=";
     file << set.delta_baseline_X_tagged;
     file << "\n";
     file << "baselineJitterY=";
     file << set.delta_baseline_Y_tagged;
     file << "\n";
     file << "baselineJitterZ=";
     file << set.delta_baseline_Z_tagged;
     file << "\n";
     file << "rotationJitterX=";
     file << set.delta_rotation_X_tagged;
     file << "\n";
     file << "rotationJitterY=";
     file << set.delta_rotation_Y_tagged;
     file << "\n";
     file << "rotationJitterZ=";
     file << set.delta_rotation_Z_tagged;
     file << "\n";
     file << "baseline_jitter=";
     file << (set.delta_baseline__m);
     file << "\n";
     file << "focalLength_jitter=";
     file << (set.delta_focal_length__m);
     file << "\n";
     file << "rotation_jitter=";
     file << (set.delta_baseline__m);
     file << "\n";

	 file << "[CameraSetup]\n";
     file << "xRes=";
     file << (set.resolution_X__px);
     file << "\n";
     file << "yRes=";
     file << (set.resolution_Y__px);
     file << "\n";
     file << "PixelAspectRatioX=";
     file << (set.PixelAspectRatio*16);
     file << "\n";
	 file << "PixelAspectRatioY=16 \n";
	// if fixed es equal to one we fix the entire setup to the horizontal sensor size (X) if fixed is two we fix the size to the vertival direction (y)
	 file << "Fixed=1\n";
     file << "SensorSize: ";
     file << (set.sensor_X__m);
     file << "\n";

	 file << "Grid=1\n";
	 file << "structure=1\n";
	 file << "viewdirection=1\n";
     file << "camX=";
     file << (camX);
     file << "\n";
     file << "camY=";
     file << (camY);
     file << "\n";
     file << "baselineX=";
     file << (set.baseline_X__m);
     file << "\n";
     file << "baselineY=";
     file << (set.baseline_Y__m);
     file << "\n";
     file << "FocalLength=";
     file << (set.focalLength__m);
     file << "\n";

	 file << "\n[CyclesRenderEngine]\n";
     file << "fstop=";
     file << (set.f_number);
     file << "\n";
     file << "focusedDistance=";
     file << (set.DoF_subject_distance__m);
     file << "\n";
	 file << "NoBlades=5\n";
	 file << "rotationOffset=5\n";

	 file << "\n[EstimationCube]\n";
     file << "DH_X__m=";
     file << (set.DH_X__m);
     file << "\n";
     file << "DH_Y__m=";
     file << (set.DH_Y__m);
     file << "\n";
     file << "D1_Y__m=";
     file << (set.D1_Y__m);
     file << "\n";
     file << "D1_X__m=";
     file << (set.D1_X__m);
     file << "\n";
     file << "D2_X__m=";
     file << (set.D2_X__m);
     file << "\n";
     file << "D2_Y__m=";
     file << (set.D2_Y__m);
     file << "\n";
     file << "delta_D_X__m=";
     file << (set.delta_D_X__m);file << "\n";
     file << "delta_D_Y__m=";
     file << (set.delta_D_Y__m);
     file << "\n";
     file << "FramesizeDH_X__m=";
     file << (set.FramesizeDH_X__m);
     file << "\n";
     file << "FramesizeDH_Y__m=";
     file << (set.FramesizeDH_Y__m);
     file << "\n";
     file << "FramesizeD1_X__m=";
     file << (set.FramesizeD1_X__m);
     file << "\n";
     file << "FramesizeD1_Y__m=";
     file << (set.FramesizeD1_Y__m);
     file << "\n";
     file << "FramesizeD2_X__m=";
     file << (set.FramesizeD2_X__m);
     file << "\n";
     file << "FramesizeD2_Y__m=";
     file << (set.FramesizeD2_Y__m);
     file << "\n";

	 file << "\n[DOFinfo]\n";

     file << "DoF_D_N__m=";
     file << (set.DoF_D_N__m);
     file << "\n";
     file << "DoF_D_F__m=";
     file << (set.DoF_D_F__m);
     file << "\n";
     file << "DoF_H__m=";
     file << (set.DoF_H__m);
     file << "\n";
     file << "DoF_DoF__m=";
     file << (set.DoF_DoF__m);
     file << "\n";

	 file << "\n[Miscellaneous]\n";

     file << "dH_X__px=";
     file << (set.dH_X__px);
     file << "\n";
     file << "dH_Y__px=";
     file << (set.dH_Y__px);
     file << "\n";
     file << "d1_X__px=";
     file << (set.d1_X__px);
     file << "\n";
     file << "d1_Y__px=";
     file << (set.d1_Y__px);
     file << "\n";
     file << "d2_X__px=";
     file << (set.d2_X__px);
     file << "\n";
     file << "d2_Y__px=";
     file << (set.d2_Y__px);
     file << "\n";
     file << "baseline_jitter=";
     file << (set.delta_baseline__m);
     file << "\n";
     file << "focalLength_jitter=";
     file << (set.delta_focal_length__m);
     file << "\n";
     file << "rotation_jitter=";
     file << (set.delta_baseline__m);
     file << "\n";

	 file << "\n[CameraPositions]\n";
	 for (int i = 0 ; i < camY ; i++){
		 for (int j = 0 ; j < camX ; j++){
			 int iterator = j+i*camX;
             double tmpA = 0;
             double tmpB = 0;
             double tmpC = 0;
             if (set.delta_baseline_X_tagged){
                 tmpA = set.baseline_X__m*(double)(j)-set.baseline_X__m*round((camX-1)/2)+baselineJitter(gen);
             }
             else
             {
                 tmpA = set.baseline_X__m*(double)(j)-set.baseline_X__m*round((camX-1)/2);
             }
             if (set.delta_baseline_Y_tagged){
                 tmpB = -set.baseline_Y__m*(double)(i)+set.baseline_Y__m*round((camY-1)/2)+baselineJitter(gen);
             }
             else
             {
                 tmpB = -set.baseline_Y__m*(double)(i)+set.baseline_Y__m*round((camY-1)/2);
             }
             if (set.delta_baseline_Z_tagged){
                 tmpC = baselineJitter(gen);
             }
             else
             {
                 tmpC = 0;
             }

             char a[4];
             sprintf(a,"%03d", iterator);

             file << "positionsX_";
             file << a;
             file << "=";
             file << tmpA;
             file << "\n";
             file << "positionsY_";
             file << a;
             file << "=";
             file << tmpB;
             file << "\n";
             file << "positionsZ_";
             file << a;
             file << "=";
             file << tmpC;
             file << "\n";

             double tmpD = 0;
             double tmpE = 0;
             double tmpF = 0;
             if (set.delta_rotation_X_tagged){
                 tmpD = rotationJitter(gen);
             }
             else
             {
                 tmpD = 0;
             }
             if (set.delta_rotation_Y_tagged){
                 tmpE = rotationJitter(gen);
             }
             else
             {
                 tmpE = 0;
             }
             if (set.delta_rotation_Z_tagged){
                 tmpF = rotationJitter(gen);
             }
             else
             {
                 tmpF = 0;
             }

             file << "rotationX_";
             file << a;
             file << "=";
             file << tmpD;
             file << "\n";
             file << "rotationY_";
             file << a;
             file << "=";
             file << tmpE;
             file << "\n";
             file << "rotationZ_";
             file << a;
             file << "=";
             file << tmpF;
             file << "\n";

		 }
	 }
	 file << "\n[CameraFocalLength]\n";
	 for (int i = 0 ; i < camX*camY ; i++){
            char s[4];
            sprintf(s, "%03d", i);
            double tmpA = set.focalLength__m +focalLengthJitter(gen);
            file << "focalLength_";
            file << s;
            file << "=";
            file << tmpA;
            file << "\n";
	}
	 file.close();

}

void LFsetup::save(std::string filename){


    std::ofstream file1;
    file1.clear();
    file1.open(filename, std::fstream::out);

    file1 << "[Camera_Setup]\n";
    file1 << "resolution_h__px=";
    file1 << (set.resolution_X__px);
    file1 << "\n";
    file1 << "resolution_v__px=";
    file1 << (set.resolution_Y__px);

    file1 << "\n";

    file1 << "cam_h=";
    file1 << (set.Cam_X);
    file1 << "\n";
    file1 << "cam_v=";
    file1 << (set.Cam_Y);
    file1 << "\n";

    file1 << "baseline_h__m=";
    file1 << (set.baseline_X__m);
    file1 << "\n";
    file1 << "baseline_v__m=";
    file1 << (set.baseline_Y__m);
    file1 << "\n";

    file1 << "Pixelsize_h__m=";
    file1 << (set.Pixelsize_X__m);
    file1 << "\n";
    file1 << "Pixelsize_v__m=";
    file1 << (set.Pixelsize_Y__m);
    file1 << "\n";


    file1 << "sensor_X__m=";
    file1 << (set.sensor_X__m);
    file1 << "\n";
    file1 << "sensor_Y__m=";
    file1 << (set.sensor_Y__m);
    file1 << "\n";

    file1 << "FocalLength__m=";
    file1 << (set.focalLength__m);
    file1 << "\n";


    file1 << "f_number=";
    file1 << (set.f_number);
    file1 << "\n";
    file1 << "DoF_subject_distance__m=";
    file1 << (set.DoF_subject_distance__m);
    file1 << "\n";
    file1 << "CircleofConfusion__m=";
    file1 << (set.CircleofConfusion__m);

    file1 << "\n[LFSetup_Parameter]\n";
    file1 << "DH_h__m=";
    file1 << (set.DH_X__m);
    file1 << "\n";
    file1 << "DH_v__m=";
    file1 << (set.DH_Y__m);
    file1 << "\n";
    file1 << "dH_h__px=";
    file1 << (set.dH_X__px);
    file1 << "\n";
    file1 << "dH_v__px=";
    file1 << (set.dH_Y__px);
    file1 << "\n";
    file1 << "delta_d_h__px=";
    file1 << (set.delta_d_X__px*2);
    file1 << "\n";
    file1 << "delta_d_v__px=";
    file1 << (set.delta_d_Y__px*2);
    file1 << "\n";
    file1 << "delta_b__m=";
    file1 << (set.delta_baseline__m);
    file1 << "\n";
    file1 << "delta_f__m=";
    file1 << (set.delta_focal_length__m);
    file1 << "\n";
    file1 << "delta_d_inaccuracy_ST__px=";
    file1 << (set.delta_d_inaccuracy_ST__px);
    file1 << "\n";
    file1 << "baselineJitterX=";
    file1 << set.delta_baseline_X_tagged;
    file1 << "\n";
    file1 << "baselineJitterY=";
    file1 << set.delta_baseline_Y_tagged;
    file1 << "\n";
    file1 << "baselineJitterZ=";
    file1 << set.delta_baseline_Z_tagged;
    file1 << "\n";
    file1 << "rotationJitterX=";
    file1 << set.delta_rotation_X_tagged;
    file1 << "\n";
    file1 << "rotationJitterY=";
    file1 << set.delta_rotation_Y_tagged;
    file1 << "\n";
    file1 << "rotationJitterZ=";
    file1 << set.delta_rotation_Z_tagged;
    file1 << "\n";
    file1 << "baseline_jitter=";
    file1 << (set.delta_baseline__m);
    file1 << "\n";
    file1 << "focalLength_jitter=";
    file1 << (set.delta_focal_length__m);
    file1 << "\n";
    file1 << "rotation_jitter=";
    file1 << (set.delta_baseline__m);
    file1 << "\n";
    file1.close();
}

void LFsetup::expLF_Framework(std::string filename){


    std::ofstream file1;
    file1.clear();
    file1.open(filename, std::fstream::out);


            file1 << "[light field parameter]\n";
            file1 << "\n";
            file1 << "source : '4D_high_bw.png'\n";
            file1 << "\n";
            file1 << "# LF_TYPE can be LF_4D=1, LF_3DH=2, LF_3DV=3, LF_CROSS=4\n";

            if (set.Cam_X == 1 && set.Cam_Y != 1)  file1 << "type : 3\n";
            else if (set.Cam_X != 1 && set.Cam_Y == 1) file1 << "type : 2\n";
            else file1 << "type : 1\n";

            file1 << "\n";
            file1 << "#number of cameras horizontal\n";
            file1 << "cams_h : ";
            file1 << set.Cam_X;
            file1 << "\n";
            file1 << "\n";
            file1 << "#number of cameras vertical\n";
            file1 << "cams_v : ";
            file1 << set.Cam_Y;
            file1 <<"\n";
            file1 << "\n";
            file1 << "#image width in px\n";
            file1 << "width	: ";
            file1 << set.resolution_X__px;
            file1 <<"\n";
            file1 << "\n";
            file1 << "#image height in px\n";
            file1 << "height : ";
            file1 << set.resolution_Y__px;
            file1 <<"\n";
            file1 << "\n";
            file1 << "#horizontal camera distance in m\n";
            file1 << "baseline_h :";
            file1 <<set.baseline_X__m;
            file1 <<"\n";
            file1 << "\n";
            file1 << "#vertical camera distance in m\n";
            file1 << "baseline_v : " ;
            file1 << set.baseline_Y__m;
            file1 <<"\n";
            file1 << "\n";
            file1 << "#focal length in m\n";
            file1 << "focal_length : ";
            file1 << set.focalLength__m;
            file1 <<"\n";
            file1 << "\n";
            file1 << "#horopter in m\n";
            file1 << "DH_h :" ;
            file1 << set.DH_X__m;
            file1 <<"\n";
            file1 << "DH_v :" ;
            file1 << set.DH_Y__m;
            file1 <<"\n";
            file1 << "\n";
            file1 << "#pixel aspect ratio (h/v;\n";
            file1 << "pixel_aspect_ratio : " ;
            file1 << set.PixelAspectRatio;
            file1 <<"\n";
            file1 << "\n";
            file1 << "#camera aperture\n";
            file1 << "aperture : " ;
            file1 << set.f_number;
            file1 <<"\n";
            file1 << "\n";
            file1 << "#sensor size in m\n";

            file1 << "sensor_size_h : ";
            file1 << set.sensor_X__m;
            file1 <<"\n";
            file1 << "sensor_size_v : ";
            file1 << set.sensor_Y__m;
            file1 <<"\n";


}

void LFsetup::setValidifUserInput(){

	//Wenn User Input True dann soll auch valid true sein auser wenn der Wert Null ist, dann soll ( siehe Nachster Block ) das valid flag wieder gelöscht werden.
		if (set.resolution_X__px__userInput) set_valid.resolution_X__px = true;
		if (set.resolution_Y__px__userInput) set_valid.resolution_Y__px = true;
		if (set.AspectRatio__userInput) set_valid.AspectRatio = true;

		if (set.Pixelsize_X__m__userInput) set_valid.Pixelsize_X__m = true;
		if (set.Pixelsize_Y__m__userInput) set_valid.Pixelsize_Y__m = true;
		if (set.PixelAspectRatio__userInput) set_valid.PixelAspectRatio = true;

		if (set.sensor_X__m__userInput) set_valid.sensor_X__m = true;
		if (set.sensor_Y__m__userInput) set_valid.sensor_Y__m = true;

		if (set.DH_X__m__userInput) set_valid.DH_X__m = true;
		if (set.DH_Y__m__userInput) set_valid.DH_Y__m = true;

		if (set.dH_X__px__userInput) set_valid.dH_X__px = true;
		if (set.dH_Y__px__userInput) set_valid.dH_Y__px = true;

        if (set.theta_X__pxm__userInput) set_valid.theta_X__pxm = true;
        if (set.theta_Y__pxm__userInput) set_valid.theta_Y__pxm = true;

		if (set.delta_d_X__px__userInput) set_valid.delta_d_X__px = true;
		if (set.delta_d_Y__px__userInput) set_valid.delta_d_Y__px = true;

		if (set.delta_D_X__m__userInput) set_valid.delta_D_X__m = true;
		if (set.delta_D_Y__m__userInput) set_valid.delta_D_Y__m = true;

		if (set.d1_X__px__userInput) set_valid.d1_X__px = true;
		if (set.d1_Y__px__userInput) set_valid.d1_Y__px = true;

		if (set.D1_X__m__userInput) set_valid.D1_X__m = true;
		if (set.D1_Y__m__userInput) set_valid.D1_Y__m = true;

		if (set.d2_X__px__userInput) set_valid.d2_X__px = true;
		if (set.d2_Y__px__userInput) set_valid.d2_Y__px = true;

		if (set.D2_X__m__userInput) set_valid.D2_X__m = true;
		if (set.D2_Y__m__userInput) set_valid.D2_Y__m = true;

        if (set.focal_length_X__px__userInput) set_valid.focal_length_X__px = true;
		if (set.focal_length_Y__px__userInput) set_valid.focal_length_Y__px = true;

        if (set.delta_focal_length__m__userInput) set_valid.delta_focal_length__m = true;
        if (set.delta_rotation__deg__userInput) set_valid.delta_rotation__deg = true;

		if (set.baseline_X__m__userInput) set_valid.baseline_X__m = true;
		if (set.baseline_Y__m__userInput) set_valid.baseline_Y__m = true;
		if (set.baseline_ratio__userInput) set_valid.baseline_ratio = true;

        if (set.delta_baseline__m__userInput) set_valid.delta_baseline__m = true;

		if (set.focalLength__m__userInput) set_valid.focalLength__m = true;

		if (set.DoF_D_N__m__userInput) set_valid.DoF_D_N__m = true;

		if (set.DoF_D_F__m__userInput) set_valid.DoF_D_F__m = true;

		if (set.f_number__userInput) set_valid.f_number = true;

		if (set.DoF_H__m__userInput) set_valid.DoF_H__m = true;

		if (set.DoF_subject_distance__m__userInput) set_valid.DoF_subject_distance__m = true;
               
        if (set.delta_d_inaccuracy_ST__px__userInput) set_valid.delta_d_inaccuracy_ST__px = true;

        if (set.DoF_DoF__m__userInput) set_valid.DoF_DoF__m = true;
        if (set.CircleofConfusion__m__userInput) set_valid.CircleofConfusion__m = true;

        if (set.Cam_X__userInput) set_valid.Cam_X = true;
        if (set.Cam_Y__userInput) set_valid.Cam_Y = true;

        if (set.delta_d_inaccuracy_ST__px__userInput) set_valid.delta_d_inaccuracy_ST__px = true;

}

void LFsetup::deleteInvalidUserInputs(){

	//Wenn ich wert Lösche muss valid auf false gesetzt werden auserdem wenn der userInput auf true und wert null ist soll dennoch valid auf false gesetzt werden
	if (set.resolution_X__px <= 0) {
		set.resolution_X__px__userInput = false;
        set_valid.resolution_X__px = false;
	}
	if (set.resolution_Y__px <= 0){
		set.resolution_Y__px__userInput = false;
		set_valid.resolution_Y__px = false;
	}
	if (set.AspectRatio <= 0) {
		set.AspectRatio__userInput = false;
		set_valid.AspectRatio = false;
	}
	if (set.Pixelsize_X__m <= 0){
		set.Pixelsize_X__m__userInput = false;
		set_valid.Pixelsize_X__m = false;
	}
	if (set.Pixelsize_Y__m <= 0){
		set.Pixelsize_Y__m__userInput = false;
		set_valid.Pixelsize_Y__m = false;
	}
	if (set.PixelAspectRatio <= 0) {
		set.PixelAspectRatio__userInput = false;
		set_valid.PixelAspectRatio = false;
	}
	if (set.sensor_X__m <= 0){
		set.sensor_X__m__userInput = false;
		set_valid.sensor_X__m = false;
	}
	if (set.sensor_Y__m <= 0){
		set.sensor_Y__m__userInput = false;
		set_valid.sensor_Y__m = false;
	}
	if (set.DH_X__m <= 0){
		set.DH_X__m__userInput = false;
		set_valid.DH_X__m = false;
	}
	if (set.DH_Y__m <= 0){
		set.DH_Y__m__userInput = false;
		set_valid.DH_Y__m = false;
	}
	if (set.dH_X__px <= 0){
		set.dH_X__px__userInput  = false;
		set_valid.dH_X__px = false;
	}
	if (set.dH_Y__px <= 0){
		set.dH_Y__px__userInput  = false;
		set_valid.dH_Y__px = false;
	}
    if (set.theta_X__pxm <= 0){
        set.theta_X__pxm__userInput = false;
        set_valid.theta_X__pxm = false;
	}
    if (set.theta_Y__pxm <= 0){
        set.theta_Y__pxm__userInput = false;
        set_valid.theta_Y__pxm = false;
	}
	if (set.delta_d_X__px <= 0){
		set.delta_d_X__px__userInput = false;
		set_valid.delta_d_X__px = false;
	}
	if (set.delta_d_Y__px <= 0){
		set.delta_d_Y__px__userInput = false;
		set_valid.delta_d_Y__px = false;
	}
	if (set.delta_D_X__m <= 0){
		set.delta_D_X__m__userInput = false;
		set_valid.delta_D_X__m = false;
	}
	if (set.delta_D_Y__m <= 0){
		set.delta_D_Y__m__userInput = false;
		set_valid.delta_D_Y__m = false;
	}
    if (set.d1_X__px < 0){
		set.d1_X__px__userInput = false;
		set_valid.d1_X__px = false;
	}
    if (set.d1_Y__px < 0){
		set.d1_Y__px__userInput = false;
		set_valid.d1_Y__px = false;
	}
	if (set.D1_X__m <= 0){
		set.D1_X__m__userInput = false;
		set_valid.D1_X__m = false;
	}
	if (set.D1_Y__m <= 0){
		set.D1_Y__m__userInput = false;
		set_valid.D1_Y__m = false;
	}
	if (set.d2_X__px <= 0){
		set.d2_X__px__userInput = false;
		set_valid.d2_X__px = false;
	}
	if (set.d2_Y__px <= 0){
		set.d2_Y__px__userInput = false;
		set_valid.d2_Y__px = false;
	}
	if (set.D2_X__m <= 0){
		set.D2_X__m__userInput = false;
		set_valid.D2_X__m = false;
	}
	if (set.D2_Y__m <= 0){
		set.D2_Y__m__userInput = false;
		set_valid.D2_Y__m = false;
	}
	if (set.focal_length_X__px <= 0){
		set.focal_length_X__px__userInput = false;
		set_valid.focal_length_X__px = false;
	}
	if (set.focal_length_Y__px <= 0){
		set.focal_length_Y__px__userInput = false;
		set_valid.focal_length_Y__px = false;
	}
	if (set.baseline_X__m <= 0){
		set.baseline_X__m__userInput = false;
		set_valid.baseline_X__m = false;
	}
	if (set.baseline_Y__m <= 0){
		set.baseline_Y__m__userInput = false;
		set_valid.baseline_Y__m = false;
	}
	if (set.baseline_ratio <= 0){
		set.baseline_ratio__userInput = false;
		set_valid.baseline_ratio = false;
	}
    if (set.delta_baseline__m < 0){
		set.delta_baseline__m__userInput = false;
		set_valid.delta_baseline__m = false;
	}
	if (set.focalLength__m <= 0){
		set.focalLength__m__userInput = false;
		set_valid.focalLength__m = false;
	}
    if (set.delta_focal_length__m < 0){
		set.delta_focal_length__m__userInput = false;
		set_valid.delta_focal_length__m = false;
	}
    if (set.delta_rotation__deg < 0){
        set.delta_rotation__deg__userInput = false;
        set_valid.delta_rotation__deg = false;
    }
	if (set.DoF_D_N__m <= 0){
		set.DoF_D_N__m__userInput = false;
		set_valid.DoF_D_N__m = false;
	}
        
	if (set.DoF_D_F__m <= 0){
		set.DoF_D_F__m__userInput = false;
		set_valid.DoF_D_F__m = false;
	}
    if (set.CircleofConfusion__m <= 0){
        set.CircleofConfusion__m__userInput = false;
        set_valid.CircleofConfusion__m = false;
    }  
	if (set.f_number <= 0){
		set.f_number__userInput = false;
		set_valid.f_number = false;
	}
    if (set.delta_d_inaccuracy_ST__px <= 0){
		set.delta_d_inaccuracy_ST__px__userInput = false;
		set_valid.delta_d_inaccuracy_ST__px = false;
	}  
	if (set.DoF_H__m <= 0){
		set.DoF_H__m__userInput = false;
		set_valid.DoF_H__m = false;
	} 
	if (set.DoF_subject_distance__m <= 0){
		set.DoF_subject_distance__m__userInput = false;
		set_valid.DoF_subject_distance__m = false;
	}
	if (set.DoF_DoF__m <= 0){
		set.DoF_DoF__m__userInput = false;
		set_valid.DoF_DoF__m = false;
	}
    if (set.Cam_X <= 0){
		set.Cam_X__userInput = false;
		set_valid.Cam_X = false;
	}
    if (set.Cam_Y <= 0){
		set.Cam_Y__userInput = false;
		set_valid.Cam_Y = false;
	}
}

void LFsetup::compute(){

	deleteValid();
	setValidifUserInput();
	deleteInvalidUserInputs();

    if (set.dH_X__px - set.delta_d_X__px == 0 && set_valid.dH_X__px && set_valid.delta_d_X__px) set.dH_X__px += 0.0000000000001;
    if (set.dH_Y__px - set.delta_d_Y__px == 0 && set_valid.dH_Y__px && set_valid.delta_d_Y__px) set.dH_Y__px += 0.0000000000001;

    for (int i = 0 ; i < 7 ; i++){

        set_valid.delta_D1_X_inaccuracy_ST__m = get_delta_D1_inaccuracy_ST_X__m();
        set_valid.delta_D1_Y_inaccuracy_ST__m = get_delta_D1_inaccuracy_ST_Y__m();
        set_valid.delta_D2_X_inaccuracy_ST__m = get_delta_D2_inaccuracy_ST_X__m();
        set_valid.delta_D2_Y_inaccuracy_ST__m = get_delta_D2_inaccuracy_ST_Y__m();
        set_valid.delta_DH_X_inaccuracy_ST__m = get_delta_DH_inaccuracy_ST_X__m();
        set_valid.delta_DH_Y_inaccuracy_ST__m = get_delta_DH_inaccuracy_ST_Y__m();

        set_valid.delta_D_X__m = get_delta_D_X__m();
        set_valid.delta_D_Y__m = get_delta_D_Y__m();

		set_valid.Pixelsize_X__m = get_PixelSize_X__m();
		set_valid.Pixelsize_Y__m = get_PixelSize_Y__m();
		set_valid.PixelAspectRatio = get_PixelAspectRatio();

		set_valid.resolution_X__px = get_resolution_X__px();
		set_valid.resolution_Y__px = get_resolution_Y__px();
		set_valid.AspectRatio = get_AspectRatio();

		set_valid.sensor_X__m = get_sensor_X__m();
		set_valid.sensor_Y__m = get_sensor_Y__m();

		set_valid.FramesizeDH_X__m = get_Framesize_DH_X__m();
		set_valid.FramesizeDH_Y__m = get_Framesize_DH_Y__m();

		set_valid.FramesizeD1_X__m = get_Framesize_D1_X__m();
		set_valid.FramesizeD1_Y__m = get_Framesize_D1_Y__m();

		set_valid.FramesizeD2_X__m = get_Framesize_D2_X__m();
		set_valid.FramesizeD2_Y__m = get_Framesize_D2_Y__m();

		set_valid.DH_X__m = get_DH_X__m();
		set_valid.DH_Y__m = get_DH_Y__m();

		set_valid.dH_X__px = get_dH_X__px();
		set_valid.dH_Y__px = get_dH_Y__px();

		set_valid.DHopt_X__m = get_DHopt_X__m();
		set_valid.DHopt_Y__m = get_DHopt_Y__m();

		set_valid.D1_X__m = get_D1_X__m();
		set_valid.D1_Y__m = get_D1_Y__m();

		set_valid.D2_X__m =  get_D2_X__m();
		set_valid.D2_Y__m =  get_D2_Y__m();

        set_valid.delta_d_X__px =  get_delta_d_X__px();
        set_valid.delta_d_Y__px = get_delta_d_Y__px();

        set_valid.theta_X__pxm = get_theta_X__pxm();
        set_valid.theta_Y__pxm = get_theta_Y__pxm();

		set_valid.d2_X__px = get_d2_X__px();
		set_valid.d2_Y__px = get_d2_Y__px();

		set_valid.d1_X__px = get_d1_X__px();
		set_valid.d1_Y__px = get_d1_Y__px();

		set_valid.focal_length_X__px = get_focalLength_X__px();
		set_valid.focal_length_Y__px =  get_focalLength_Y__px();

		set_valid.baseline_X__m = get_baseline_X__m();
		set_valid.baseline_Y__m = get_baseline_Y__m();
		set_valid.baseline_ratio = get_baselineRatio();

		set_valid.focalLength__m = get_focalLength__m();
		set_valid.DoF_D_N__m = get_DoF_D_N__m();
		set_valid.DoF_D_F__m = get_DoF_D_F__m();
		set_valid.DoF_H__m = get_DoF_H__m();       
		set_valid.DoF_DoF__m = get_DoF_DoF__m();

        set_valid.object_space_angle_X_degree = get_object_space_angle_X_degree();
        set_valid.object_space_angle_Y_degree = get_object_space_angle_Y_degree();

        set_valid.geometricDepthInaccuracyDH_X__m = get_geometricDepthInaccuracyDH_X__m();
        set_valid.geometricDepthInaccuracyDH_Y__m = get_geometricDepthInaccuracyDH_Y__m();
        set_valid.geometricDepthInaccuracyD2_X__m = get_geometricDepthInaccuracyD2_X__m();
        set_valid.geometricDepthInaccuracyD2_Y__m = get_geometricDepthInaccuracyD2_Y__m();
        set_valid.geometricDepthInaccuracyD1_X__m = get_geometricDepthInaccuracyD1_X__m();
        set_valid.geometricDepthInaccuracyD1_Y__m = get_geometricDepthInaccuracyD1_Y__m();
    }

    if (set.delta_D_X__m >= 10e12) set.delta_D_X__m = INFINITY;
    if (set.delta_D_Y__m >= 10e12) set.delta_D_Y__m = INFINITY;
    if (set.d1_X__px <= 10e-12) set.d1_X__px = 0;
    if (set.d1_Y__px <= 10e-12) set.d1_Y__px = 0;
    if (set.D1_X__m >= 10e12) set.D1_X__m = INFINITY;
    if (set.D1_Y__m >= 10e12) set.D1_Y__m = INFINITY;
    if (set.delta_D1_X_inaccuracy_ST__m >= 10e12) set.delta_D1_X_inaccuracy_ST__m = INFINITY;
    if (set.delta_D1_Y_inaccuracy_ST__m >= 10e12) set.delta_D1_Y_inaccuracy_ST__m = INFINITY;

//    if (set.delta_D_X__m < 0)  set.delta_D_X__m = set.D2_X__m;
//    if (set.delta_D_Y__m < 0)  set.delta_D_Y__m = set.D2_Y__m;
//    if (set.D1_X__m < 0)  set.D1_X__m = 0;
//    if (set.D1_Y__m < 0)  set.D1_Y__m = 0;

}

// functions to compute needed information

bool LFsetup::get_geometricDepthInaccuracyDH_X__m(){

	if(set_valid.baseline_X__m  && set_valid.focalLength__m && set_valid.DH_X__m && set_valid.delta_baseline__m && set_valid.delta_focal_length__m ){
        set.geometricDepthInaccuracyDH_X__m = LFsetup::_geometricDepthInaccuracy_m(set.DH_X__m,set.baseline_X__m,set.delta_baseline__m,set.focalLength__m,set.delta_focal_length__m);
		return true;
	}
	else if(set_valid.baseline_X__m  && set_valid.DH_X__m && set_valid.delta_baseline__m){
        set.geometricDepthInaccuracyDH_X__m = LFsetup::_geometricDepthInaccuracy_m(set.DH_X__m,set.baseline_X__m,set.delta_baseline__m,1,0);
		return true;
	}
    else if(set_valid.focalLength__m && set_valid.DH_X__m && set_valid.delta_focal_length__m ){
        set.geometricDepthInaccuracyDH_X__m = LFsetup::_geometricDepthInaccuracy_m(set.DH_X__m,1,0,set.focalLength__m,set.delta_focal_length__m);
		return true;
	}
	else{
		return false;
	}
}
bool LFsetup::get_geometricDepthInaccuracyDH_Y__m(){

    if(set_valid.baseline_Y__m  && set_valid.focalLength__m && set_valid.DH_Y__m && set_valid.delta_baseline__m && set_valid.delta_focal_length__m){
        set.geometricDepthInaccuracyDH_Y__m = LFsetup::_geometricDepthInaccuracy_m(set.DH_Y__m,set.baseline_Y__m,set.delta_baseline__m,set.focalLength__m,set.delta_focal_length__m);
		return true;
	}
	else if(set_valid.baseline_Y__m  && set_valid.DH_X__m && set_valid.delta_baseline__m){
        set.geometricDepthInaccuracyDH_Y__m = LFsetup::_geometricDepthInaccuracy_m(set.DH_Y__m,set.baseline_Y__m,set.delta_baseline__m,1,0);
		return true;
	}
    else if(set_valid.focalLength__m && set_valid.DH_X__m && set_valid.delta_focal_length__m ){
        set.geometricDepthInaccuracyDH_Y__m = LFsetup::_geometricDepthInaccuracy_m(set.DH_Y__m,1,0,set.focalLength__m,set.delta_focal_length__m);
		return true;
	}
	else{
		return false;
	}
}
bool LFsetup::get_geometricDepthInaccuracyD2_X__m(){

    if(set_valid.baseline_X__m  && set_valid.focalLength__m && set_valid.D2_X__m && set_valid.delta_baseline__m && set_valid.delta_focal_length__m ){
        set.geometricDepthInaccuracyD2_X__m = LFsetup::_geometricDepthInaccuracy_m(set.D2_X__m,set.baseline_X__m,set.delta_baseline__m,set.focalLength__m,set.delta_focal_length__m);
        return true;
    }
    else if(set_valid.baseline_X__m  && set_valid.D2_X__m && set_valid.delta_baseline__m){
        set.geometricDepthInaccuracyD2_X__m = LFsetup::_geometricDepthInaccuracy_m(set.D2_X__m,set.baseline_X__m,set.delta_baseline__m,1,0);
        return true;
    }
    else if(set_valid.focalLength__m && set_valid.D2_X__m && set_valid.delta_focal_length__m ){
        set.geometricDepthInaccuracyD2_X__m = LFsetup::_geometricDepthInaccuracy_m(set.D2_X__m,1,0,set.focalLength__m,set.delta_focal_length__m);
        return true;
    }
    else{
        return false;
    }
}
bool LFsetup::get_geometricDepthInaccuracyD2_Y__m(){

    if(set_valid.baseline_Y__m  && set_valid.focalLength__m && set_valid.D2_Y__m && set_valid.delta_baseline__m && set_valid.delta_focal_length__m){
        set.geometricDepthInaccuracyD2_Y__m = LFsetup::_geometricDepthInaccuracy_m(set.D2_Y__m,set.baseline_Y__m,set.delta_baseline__m,set.focalLength__m,set.delta_focal_length__m);
        return true;
    }
    else if(set_valid.baseline_Y__m  && set_valid.D2_Y__m && set_valid.delta_baseline__m){
        set.geometricDepthInaccuracyD2_Y__m = LFsetup::_geometricDepthInaccuracy_m(set.D2_Y__m,set.baseline_Y__m,set.delta_baseline__m,1,0);
        return true;
    }
    else if(set_valid.focalLength__m && set_valid.D2_Y__m && set_valid.delta_focal_length__m ){
        set.geometricDepthInaccuracyD2_Y__m = LFsetup::_geometricDepthInaccuracy_m(set.D2_Y__m,1,0,set.focalLength__m,set.delta_focal_length__m);
        return true;
    }
    else{
        return false;
    }
}
bool LFsetup::get_geometricDepthInaccuracyD1_X__m(){

    if(set_valid.baseline_X__m  && set_valid.focalLength__m && set_valid.D1_X__m && set_valid.delta_baseline__m && set_valid.delta_focal_length__m ){
        set.geometricDepthInaccuracyD1_X__m = LFsetup::_geometricDepthInaccuracy_m(set.D1_X__m,set.baseline_X__m,set.delta_baseline__m,set.focalLength__m,set.delta_focal_length__m);
        return true;
    }
    else if(set_valid.baseline_X__m  && set_valid.D1_X__m && set_valid.delta_baseline__m){
        set.geometricDepthInaccuracyD1_X__m = LFsetup::_geometricDepthInaccuracy_m(set.D1_X__m,set.baseline_X__m,set.delta_baseline__m,1,0);
        return true;
    }
    else if(set_valid.focalLength__m && set_valid.D1_X__m && set_valid.delta_focal_length__m ){
        set.geometricDepthInaccuracyD1_X__m = LFsetup::_geometricDepthInaccuracy_m(set.D1_X__m,1,0,set.focalLength__m,set.delta_focal_length__m);
        return true;
    }
    else{
        return false;
    }
}
bool LFsetup::get_geometricDepthInaccuracyD1_Y__m(){

    if(set_valid.baseline_Y__m  && set_valid.focalLength__m && set_valid.D1_Y__m && set_valid.delta_baseline__m && set_valid.delta_focal_length__m){
        set.geometricDepthInaccuracyD1_Y__m = LFsetup::_geometricDepthInaccuracy_m(set.D1_Y__m,set.baseline_Y__m,set.delta_baseline__m,set.focalLength__m,set.delta_focal_length__m);
        return true;
    }
    else if(set_valid.baseline_Y__m  && set_valid.D1_Y__m && set_valid.delta_baseline__m){
        set.geometricDepthInaccuracyD1_Y__m = LFsetup::_geometricDepthInaccuracy_m(set.D1_Y__m,set.baseline_Y__m,set.delta_baseline__m,1,0);
        return true;
    }
    else if(set_valid.focalLength__m && set_valid.D1_Y__m && set_valid.delta_focal_length__m ){
        set.geometricDepthInaccuracyD1_Y__m = LFsetup::_geometricDepthInaccuracy_m(set.D1_Y__m,1,0,set.focalLength__m,set.delta_focal_length__m);
        return true;
    }
    else{
        return false;
    }
}
bool LFsetup::get_delta_DH_inaccuracy_ST_X__m()
{
    if(set_valid.DH_X__m && set_valid.focal_length_X__px && set_valid.baseline_X__m && set_valid.delta_d_inaccuracy_ST__px){
        set.delta_DH_X_inaccuracy_ST__m = LFsetup::_compute_delta_D_inaccuracy__m(set.DH_X__m,set.focal_length_X__px,set.baseline_X__m, set.delta_d_inaccuracy_ST__px);
        return true;
	}
	else{
		if (set.DH_X__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_delta_DH_inaccuracy_ST_Y__m(){
    if(set_valid.DH_Y__m && set_valid.focal_length_Y__px && set_valid.baseline_Y__m && set_valid.delta_d_inaccuracy_ST__px){
        set.delta_DH_Y_inaccuracy_ST__m = LFsetup::_compute_delta_D_inaccuracy__m(set.DH_Y__m,set.focal_length_Y__px,set.baseline_Y__m, set.delta_d_inaccuracy_ST__px);
		return true;
	}
	else{
		if (set.DH_Y__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_delta_D2_inaccuracy_ST_X__m()
{
    if(set_valid.D2_X__m && set_valid.focal_length_X__px && set_valid.baseline_X__m && set_valid.delta_d_inaccuracy_ST__px){
		set.delta_D2_X_inaccuracy_ST__m = LFsetup::_compute_delta_D_inaccuracy__m(set.D2_X__m,set.focal_length_X__px,set.baseline_X__m, set.delta_d_inaccuracy_ST__px);
		return true;
	}
	else{
		if (set.DH_X__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_delta_D2_inaccuracy_ST_Y__m()
{
    if(set_valid.D2_Y__m && set_valid.focal_length_Y__px && set_valid.baseline_Y__m && set_valid.delta_d_inaccuracy_ST__px){
		set.delta_D2_Y_inaccuracy_ST__m = LFsetup::_compute_delta_D_inaccuracy__m(set.D2_Y__m,set.focal_length_Y__px,set.baseline_Y__m, set.delta_d_inaccuracy_ST__px);
		return true;
	}
	else{
		if (set.DH_Y__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_delta_D1_inaccuracy_ST_X__m()
{
    if(set_valid.D1_X__m && set_valid.focal_length_X__px && set_valid.baseline_X__m && set_valid.delta_d_inaccuracy_ST__px){
		set.delta_D1_X_inaccuracy_ST__m = LFsetup::_compute_delta_D_inaccuracy__m(set.D1_X__m,set.focal_length_X__px,set.baseline_X__m, set.delta_d_inaccuracy_ST__px);
		return true;
	}
	else{
		if (set.DH_X__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_delta_D1_inaccuracy_ST_Y__m()
{
    if(set_valid.D1_Y__m && set_valid.focal_length_Y__px && set_valid.baseline_Y__m && set_valid.delta_d_inaccuracy_ST__px){
		set.delta_D1_Y_inaccuracy_ST__m = LFsetup::_compute_delta_D_inaccuracy__m(set.D1_Y__m,set.focal_length_Y__px,set.baseline_Y__m, set.delta_d_inaccuracy_ST__px);
		return true;
	}
	else{
		if (set.DH_Y__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_delta_d_X__px()
{
	if(!set.delta_d_X__px__userInput)
	{
		if(set_valid.d1_X__px && set_valid.dH_X__px ){
			set.delta_d_X__px = LFsetup::_compute_delta_d__px_from_d1(set.d1_X__px,set.dH_X__px);
			return true;
		}
		else if(set_valid.d2_X__px && set_valid.dH_X__px ){
			set.delta_d_X__px = LFsetup::_compute_delta_d__px_from_d2(set.d2_X__px,set.dH_X__px);
			return true;
		}
        else if(set_valid.DH_X__m && set_valid.theta_X__pxm && set_valid.D1_X__m ){
            set.delta_d_X__px = LFsetup::_compute_delta_d__px_from_D1(set.DH_X__m,set.theta_X__pxm,set.D1_X__m);
			return true;
		}
        else if(set_valid.DH_X__m && set_valid.theta_X__pxm && set_valid.D2_X__m ){
            set.delta_d_X__px = LFsetup::_compute_delta_d__px_from_D2(set.DH_X__m,set.theta_X__pxm,set.D2_X__m);
			return true;
		}
        else if(set_valid.delta_D_X__m && set_valid.theta_X__pxm && set_valid.DH_X__m ){
            set.delta_d_X__px = LFsetup::_compute_delta_d__px(set.delta_D_X__m,set.theta_X__pxm,set.DH_X__m);
            return true;
        }
		else return false;
	}
	else
	{
        if(set_valid.d2_X__px && set_valid.dH_X__px ){
            if(1e-3 > std::abs(set.delta_d_X__px - LFsetup::_compute_delta_d__px_from_d2(set.d2_X__px,set.dH_X__px))){
                return true;}
            return false;
        }
        else if(set_valid.d1_X__px && set_valid.dH_X__px ){
            if(1e-3 > std::abs(set.delta_d_X__px - LFsetup::_compute_delta_d__px_from_d1(set.d1_X__px,set.dH_X__px))){
                return true;}
            return false;
        }
        else if(set_valid.DH_X__m && set_valid.theta_X__pxm && set_valid.D1_X__m ){
            if(1e-3 > std::abs(set.delta_d_X__px - LFsetup::_compute_delta_d__px_from_D1(set.DH_X__m,set.theta_X__pxm,set.D1_X__m))){
				return true;}
			return false;
		}
        else if(set_valid.DH_X__m && set_valid.theta_X__pxm && set_valid.D2_X__m ){
            if(1e-3 > std::abs(set.delta_d_X__px - LFsetup::_compute_delta_d__px_from_D2(set.DH_X__m,set.theta_X__pxm,set.D2_X__m))){
                return true;}
            return false;
        }
        else if(set_valid.delta_D_X__m && set_valid.theta_X__pxm && set_valid.DH_X__m ){
            if(1e-3 > std::abs(set.delta_d_X__px - LFsetup::_compute_delta_d__px(set.delta_D_X__m,set.theta_X__pxm,set.DH_X__m))){
                return true;}
            return false;
        }
		else{
			if (set.delta_d_X__px__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_delta_d_Y__px()
{
	if(!set.delta_d_Y__px__userInput)
	{
        if(set_valid.d1_Y__px && set_valid.dH_Y__px ){
            set.delta_d_Y__px = LFsetup::_compute_delta_d__px_from_d1(set.d1_Y__px,set.dH_Y__px);
            return true;
        }
        else if(set_valid.d2_Y__px && set_valid.dH_Y__px ){
            set.delta_d_Y__px = LFsetup::_compute_delta_d__px_from_d2(set.d2_Y__px,set.dH_Y__px);
            return true;
        }
        else if(set_valid.delta_D_Y__m && set_valid.theta_Y__pxm && set_valid.DH_Y__m ){
            set.delta_d_Y__px = LFsetup::_compute_delta_d__px(set.delta_D_Y__m,set.theta_Y__pxm,set.DH_Y__m);
            return true;
        }
        else if(set_valid.DH_Y__m && set_valid.theta_Y__pxm && set_valid.D1_Y__m ){
            set.delta_d_Y__px = LFsetup::_compute_delta_d__px_from_D1(set.DH_Y__m,set.theta_Y__pxm,set.D1_Y__m);
			return true;
		}
        else if(set_valid.DH_Y__m && set_valid.theta_Y__pxm && set_valid.D2_Y__m ){
            set.delta_d_Y__px = LFsetup::_compute_delta_d__px_from_D2(set.DH_Y__m,set.theta_Y__pxm,set.D2_Y__m);
			return true;
		}
		else return false;
	}
	else
	{
        if(set_valid.d1_Y__px && set_valid.dH_Y__px ){
            if(1e-3 > std::abs(set.delta_d_Y__px - LFsetup::_compute_delta_d__px_from_d1(set.d1_Y__px,set.dH_Y__px))){
                return true;}
            return false;
        }
        else if(set_valid.d2_Y__px && set_valid.dH_Y__px ){
            if(1e-3 > std::abs(set.delta_d_Y__px - LFsetup::_compute_delta_d__px_from_d2(set.d2_Y__px,set.dH_Y__px))){
                return true;}
            return false;
        }
        else if(set_valid.delta_D_Y__m && set_valid.theta_Y__pxm && set_valid.DH_Y__m ){
            if(1e-3 > std::abs(set.delta_d_Y__px - LFsetup::_compute_delta_d__px(set.delta_D_Y__m,set.theta_Y__pxm,set.DH_Y__m))){
                return true;}
            return false;
        }
        else if(set_valid.DH_Y__m && set_valid.theta_Y__pxm && set_valid.D1_Y__m ){
            if(1e-3 > std::abs(set.delta_d_Y__px - LFsetup::_compute_delta_d__px_from_D1(set.DH_Y__m,set.theta_Y__pxm,set.D1_Y__m))){
				return true;}
			return false;
		}
        else if(set_valid.DH_Y__m && set_valid.theta_Y__pxm && set_valid.D2_Y__m ){
            if(1e-3 > std::abs(set.delta_d_Y__px - LFsetup::_compute_delta_d__px_from_D2(set.DH_Y__m,set.theta_Y__pxm,set.D2_Y__m))){
				return true;}
			return false;
		}
		else{
			if (set.delta_d_Y__px__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_delta_D_X__m()
{
	if(set_valid.D1_X__m && set_valid.D2_X__m && !set.delta_D_X__m__userInput){
		set.delta_D_X__m = LFsetup::_compute_delta_D__m(set.D1_X__m,set.D2_X__m);
		return true;
	}
	if(set_valid.D1_X__m && set_valid.D2_X__m && set.delta_D_X__m__userInput){
        if(1e-3 > std::abs(set.delta_D_X__m - LFsetup::_compute_delta_D__m(set.D1_X__m,set.D2_X__m))){
			return true;}
		return false;
	}
	else{
		if (set.delta_D_X__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_delta_D_Y__m()
{
	if(set_valid.D1_Y__m && set_valid.D2_Y__m && !set.delta_D_Y__m__userInput){
		set.delta_D_Y__m = LFsetup::_compute_delta_D__m(set.D1_Y__m,set.D2_Y__m);
		return true;
	}
	if(set_valid.D1_Y__m && set_valid.D2_Y__m && set.delta_D_Y__m__userInput){
        if(1e-3 > std::abs(set.delta_D_Y__m - LFsetup::_compute_delta_D__m(set.D1_Y__m,set.D2_Y__m))){
			return true;}
		return false;
	}
	else{
		if (set.delta_D_Y__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_D2_Y__m()
{
	if(!set.D2_Y__m__userInput)
	{
        if(set_valid.theta_Y__pxm && set_valid.DH_Y__m && set_valid.delta_d_Y__px ){
            set.D2_Y__m = LFsetup::_compute_D2__m(set.theta_Y__pxm,set.DH_Y__m,set.delta_d_Y__px);
			return true;
		}
		else if(set_valid.delta_D_Y__m && set_valid.D1_Y__m ){
			set.D2_Y__m = LFsetup::_compute_D2__m(set.delta_D_Y__m,set.D1_Y__m);
			return true;
		}
		else return false;
	}
	else
	{
        if(set_valid.theta_Y__pxm && set_valid.DH_Y__m && set_valid.delta_d_Y__px ){
            if(1e-3 > std::abs(set.D2_Y__m - LFsetup::_compute_D2__m(set.theta_Y__pxm,set.DH_Y__m,set.delta_d_Y__px))){
				return true;}
			return false;
		}
		else if(set_valid.delta_D_Y__m && set_valid.D1_Y__m ){
            if(1e-3 > std::abs(set.D2_Y__m - LFsetup::_compute_D2__m(set.delta_D_Y__m,set.D1_Y__m))){
				return true;}
			return false;
		}
		else{
			if (set.D2_Y__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_D2_X__m()
{
	if(!set.D2_X__m__userInput)
	{
        if(set_valid.theta_X__pxm && set_valid.DH_X__m && set_valid.delta_d_X__px ){
            set.D2_X__m = LFsetup::_compute_D2__m(set.theta_X__pxm,set.DH_X__m,set.delta_d_X__px);
			return true;
		}
		else if(set_valid.delta_D_X__m && set_valid.D1_X__m ){
			set.D2_X__m = LFsetup::_compute_D2__m(set.delta_D_X__m,set.D1_X__m);
			return true;
		}
		else return false;
	}
	else
	{
        if(set_valid.theta_X__pxm && set_valid.DH_X__m && set_valid.delta_d_X__px){
            if(1e-3 > std::abs(set.D2_X__m - LFsetup::_compute_D2__m(set.theta_X__pxm,set.DH_X__m,set.delta_d_X__px))){
				return true;}
			return false;
		}
		else if(set_valid.delta_D_X__m && set_valid.D1_X__m ){
            if(1e-3 > std::abs(set.D2_X__m - LFsetup::_compute_D2__m(set.delta_D_X__m,set.D1_X__m))){
				return true;}
			return false;
		}
		else{
			if (set.D2_X__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_d1_X__px()
{
	if(set_valid.delta_d_X__px && set_valid.d2_X__px && !set.d1_X__px__userInput){
        set.d1_X__px = LFsetup::_compute_d1__px(set.delta_d_X__px,set.d2_X__px);
        return true;
	}
	else if(set_valid.delta_d_X__px && set_valid.dH_X__px && !set.d1_X__px__userInput){
        set.d1_X__px = LFsetup::_compute_d1__px_from_DH(set.dH_X__px,set.delta_d_X__px);
        return true;
	}
	else if(set_valid.delta_d_X__px && set_valid.d2_X__px && set.d1_X__px__userInput){
        if(1e-3 > std::abs(set.d1_X__px - LFsetup::_compute_d1__px(set.delta_d_X__px,set.d2_X__px))){
			return true;}
		return false;
	}
	else if(set_valid.delta_d_X__px && set_valid.dH_X__px && set.d1_X__px__userInput){
        if(1e-3 > std::abs(set.d1_X__px - LFsetup::_compute_d1__px_from_DH(set.dH_X__px,set.delta_d_X__px))){
			return true;}
		return false;
	}
    else if(set_valid.theta_X__pxm && set_valid.D1_X__m && set.d1_X__px__userInput){
        if(1e-3 > std::abs(set.d1_X__px - LFsetup::_compute_d1__px_from_theta(set.theta_X__pxm,set.D1_X__m))){
            return true;}
        return false;
    }
    else if(set_valid.theta_X__pxm && set_valid.D1_X__m && !set.d1_X__px__userInput){
        set.d1_X__px = LFsetup::_compute_d1__px_from_theta(set.theta_X__pxm,set.D1_X__m);
        return true;
    }
	else{
		if (set.d1_X__px__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_d1_Y__px()
{
	if(set_valid.delta_d_Y__px && set_valid.d2_Y__px && !set.d1_Y__px__userInput){
		set.d1_Y__px = LFsetup::_compute_d1__px(set.delta_d_Y__px,set.d2_Y__px);
        return true;
	}
	else if(set_valid.delta_d_Y__px && set_valid.dH_Y__px && !set.d1_Y__px__userInput){
		set.d1_Y__px = LFsetup::_compute_d1__px_from_DH(set.dH_Y__px,set.delta_d_Y__px);
        return true;
	}
	else if(set_valid.delta_d_Y__px && set_valid.d2_Y__px && set.d1_Y__px__userInput){
        if(1e-3 > std::abs(set.d1_Y__px - LFsetup::_compute_d1__px(set.delta_d_Y__px,set.d2_Y__px))){
			return true;}
		return false;
	}
	else if(set_valid.delta_d_Y__px && set_valid.dH_Y__px && set.d1_Y__px__userInput){
        if(1e-3 > std::abs(set.d1_Y__px - LFsetup::_compute_d1__px_from_DH(set.dH_Y__px,set.delta_d_Y__px))){
			return true;}
		return false;
	}
    else if(set_valid.theta_Y__pxm && set_valid.D1_Y__m && set.d1_Y__px__userInput){
        if(1e-3 > std::abs(set.d1_Y__px - LFsetup::_compute_d1__px_from_theta(set.theta_Y__pxm,set.D1_Y__m))){
            return true;}
        return false;
    }
    else if(set_valid.theta_Y__pxm && set_valid.D1_Y__m && !set.d1_Y__px__userInput){
        set.d1_Y__px = LFsetup::_compute_d1__px_from_theta(set.theta_Y__pxm,set.D1_Y__m);
        return true;
    }
	else{
		if (set.d1_Y__px__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_d2_X__px()
{
	if(set_valid.delta_d_X__px && set_valid.d1_X__px && !set.d2_X__px__userInput){
		set.d2_X__px = LFsetup::_compute_d2__px(set.delta_d_X__px,set.d1_X__px);
		return true;
	}
	else if(set_valid.delta_d_X__px && set_valid.dH_X__px && !set.d2_X__px__userInput){
		set.d2_X__px = LFsetup::_compute_d2__px_from_DH(set.dH_X__px,set.delta_d_X__px);
		return true;
	}
    else if(set_valid.theta_X__pxm && set_valid.D2_X__m && !set.d2_X__px__userInput){
        set.d2_X__px = LFsetup::_compute_d2__px_from_theta(set.theta_X__pxm,set.D2_X__m);
		return true;
	}
	else if(set_valid.delta_d_X__px && set_valid.d1_X__px && set.d2_X__px__userInput){
        if(1e-3 > std::abs(set.d2_X__px - LFsetup::_compute_d2__px(set.delta_d_X__px,set.d1_X__px))){
			return true;}
		return false;
	}
	else if(set_valid.delta_d_X__px && set_valid.dH_X__px && set.d2_X__px__userInput){
        if(1e-3 > std::abs(set.d2_X__px - LFsetup::_compute_d2__px_from_DH(set.dH_X__px,set.delta_d_X__px))){
			return true;}
		return false;
	}
    else if(set_valid.theta_X__pxm && set_valid.D2_X__m && set.d2_X__px__userInput){
        if(1e-3 > std::abs(set.d2_X__px - LFsetup::_compute_d2__px_from_theta(set.theta_X__pxm,set.D2_X__m))){
			return true;}
		return false;
	}
	else{
		if (set.d2_X__px__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_d2_Y__px()
{
	if(set_valid.delta_d_Y__px && set_valid.d1_Y__px && !set.d2_Y__px__userInput){
		set.d2_Y__px = LFsetup::_compute_d2__px(set.delta_d_Y__px,set.d1_Y__px);
		return true;
	}
	else if(set_valid.delta_d_Y__px && set_valid.dH_Y__px && !set.d2_Y__px__userInput){
		set.d2_Y__px = LFsetup::_compute_d2__px_from_DH(set.dH_Y__px,set.delta_d_Y__px);
		return true;
	}
    else if(set_valid.theta_Y__pxm && set_valid.D2_Y__m && !set.d2_Y__px__userInput){
        set.d2_Y__px = LFsetup::_compute_d2__px_from_theta(set.theta_Y__pxm,set.D2_Y__m);
		return true;
	}
	else if(set_valid.delta_d_Y__px && set_valid.d1_Y__px && set.d2_Y__px__userInput){
        if(1e-3 > std::abs(set.d2_Y__px - LFsetup::_compute_d2__px(set.delta_d_Y__px,set.d1_Y__px))){
			return true;}
		return false;
	}
	else if(set_valid.delta_d_Y__px && set_valid.dH_Y__px && set.d2_Y__px__userInput){
        if(1e-3 > std::abs(set.d2_Y__px - LFsetup::_compute_d2__px_from_DH(set.dH_Y__px,set.delta_d_Y__px))){
			return true;}
		return false;
	}
    else if(set_valid.theta_Y__pxm && set_valid.D2_Y__m && set.d2_Y__px__userInput){
        if(1e-3 > std::abs(set.d2_Y__px - LFsetup::_compute_d2__px_from_theta(set.theta_Y__pxm,set.D2_Y__m))){
			return true;}
		return false;
	}
	else{
		if (set.d2_Y__px__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_D1_X__m()
{
	if(!set.D1_X__m__userInput)
	{
        if(set_valid.theta_X__pxm && set_valid.DH_X__m && set_valid.delta_d_X__px){
            set.D1_X__m = LFsetup::_compute_D1__m(set.theta_X__pxm,set.DH_X__m,set.delta_d_X__px);
            return true;
        }
        else if(set_valid.delta_D_X__m && set_valid.D2_X__m ){
			set.D1_X__m = LFsetup::_compute_D1__m(set.delta_D_X__m,set.D2_X__m);
            return true;
		}
		else return false;
	}
	else{
        if(set_valid.theta_X__pxm && set_valid.DH_X__m && set_valid.delta_d_X__px){
            if(1e-3 > std::abs(set.D1_X__m - LFsetup::_compute_D1__m(set.theta_X__pxm,set.DH_X__m,set.delta_d_X__px))){
                return true;}
            return false;
        }
        else if(set_valid.delta_D_X__m && set_valid.D2_X__m ){
            if(1e-3 > std::abs(set.D1_X__m - LFsetup::_compute_D1__m(set.delta_D_X__m,set.D2_X__m))){
				return true;}
			return false;
		}
		else{
			if (set.D1_X__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_D1_Y__m()
{
	if(!set.D1_Y__m__userInput)
	{
		if(set_valid.delta_D_Y__m && set_valid.D2_Y__m ){
			set.D1_Y__m = LFsetup::_compute_D1__m(set.delta_D_Y__m,set.D2_Y__m);
            return true;
		}
        else if(set_valid.theta_Y__pxm && set_valid.DH_Y__m && set_valid.delta_d_Y__px ){
            set.D1_Y__m = LFsetup::_compute_D1__m(set.theta_Y__pxm,set.DH_Y__m,set.delta_d_Y__px);
            return true;
		}
		else return false;
	}
	else
	{
		if(set_valid.delta_D_Y__m && set_valid.D2_Y__m ){
            if(1e-3 > std::abs(set.D1_Y__m - LFsetup::_compute_D1__m(set.delta_D_Y__m,set.D2_Y__m))){
				return true;}
			return false;
		}
        else if(set_valid.theta_Y__pxm && set_valid.DH_Y__m && set_valid.delta_d_Y__px ){
            if(1e-3 > std::abs(set.D1_Y__m - LFsetup::_compute_D1__m(set.theta_Y__pxm,set.DH_Y__m,set.delta_d_Y__px))){
				return true;}
			return false;
		}
		else{
			if (set.D1_Y__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_dH_X__px()
{
	if (!set.dH_X__px__userInput){
        if(set_valid.theta_X__pxm && set_valid.DH_X__m ){
            set.dH_X__px = LFsetup::_compute_dH__px(set.theta_X__pxm,set.DH_X__m);
			return true;
		}
		else if(set_valid.d1_X__px && set_valid.d2_X__px ){
			set.dH_X__px = LFsetup::_compute_dH__px_from_d1d2(set.d1_X__px,set.d2_X__px);
			return true;
		}
		else return false;
	}
	else{
        if(set_valid.theta_X__pxm && set_valid.DH_X__m ){
            if(1e-3 > std::abs(set.dH_X__px - LFsetup::_compute_dH__px(set.theta_X__pxm,set.DH_X__m))){
				return true;}
			return false;
		}
		else if(set_valid.d1_X__px && set_valid.d2_X__px ){
            if(1e-3 > std::abs(set.dH_X__px - LFsetup::_compute_dH__px_from_d1d2(set.d1_X__px,set.d2_X__px))){
				return true;}
			return false;
		}
		else{
			if (set.dH_X__px__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_dH_Y__px()
{
	if (!set.dH_Y__px__userInput){
        if(set_valid.theta_Y__pxm && set_valid.DH_Y__m ){
            set.dH_Y__px = LFsetup::_compute_dH__px(set.theta_Y__pxm,set.DH_Y__m);
			return true;
		}
		else if(set_valid.d1_Y__px && set_valid.d2_Y__px ){
			set.dH_Y__px = LFsetup::_compute_dH__px_from_d1d2(set.d1_Y__px,set.d2_Y__px);
			return true;
		}
		else return false;
	}
	else
	{
        if(set_valid.theta_Y__pxm && set_valid.DH_Y__m ){
            if(1e-3 > std::abs(set.dH_Y__px - LFsetup::_compute_dH__px(set.theta_Y__pxm,set.DH_Y__m))){
				return true;}
			return false;
		}
		else if(set_valid.d1_Y__px && set_valid.d2_Y__px ){
            if(1e-3 > std::abs(set.dH_Y__px - LFsetup::_compute_dH__px_from_d1d2(set.d1_Y__px,set.d2_Y__px))){
				return true;}
			return false;
		}
		else{
			if (set.dH_Y__px__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_theta_Y__pxm()
{
    if(set_valid.focalLength__m && set_valid.baseline_Y__m && set_valid.Pixelsize_Y__m){
        set.theta_Y__pxm = LFsetup::_compute_theta__pxm(set.focalLength__m,set.baseline_Y__m,set.Pixelsize_Y__m);
        return true;
    }
    else if(set_valid.delta_D_Y__m && set_valid.DH_Y__m && set_valid.delta_d_Y__px ){
        set.theta_Y__pxm = LFsetup::_compute_theta__pxm_fromD(set.delta_D_Y__m,set.DH_Y__m,set.delta_d_Y__px);
        return true;
    }
    else if(set_valid.delta_D_Y__m && set_valid.dH_Y__px && set_valid.delta_d_Y__px){
        set.theta_Y__pxm = LFsetup::_compute_theta__pxm_from_d(set.delta_D_Y__m,set.dH_Y__px,set.delta_d_Y__px);
        return true;
    }
    else return false;

}
bool LFsetup::get_theta_X__pxm()
{
    if(set_valid.focalLength__m && set_valid.baseline_X__m && set_valid.Pixelsize_X__m){
        set.theta_X__pxm = LFsetup::_compute_theta__pxm(set.focalLength__m,set.baseline_X__m,set.Pixelsize_X__m);
        return true;
    }
    else if(set_valid.delta_D_X__m && set_valid.DH_X__m && set_valid.delta_d_X__px){
        set.theta_X__pxm = LFsetup::_compute_theta__pxm_fromD(set.delta_D_X__m,set.DH_X__m,set.delta_d_X__px);
        return true;
    }
    else if(set_valid.delta_D_X__m && set_valid.dH_X__px && set_valid.delta_d_X__px){
        set.theta_X__pxm = LFsetup::_compute_theta__pxm_from_d(set.delta_D_X__m,set.dH_X__px,set.delta_d_X__px);
        return true;
    }
    else return false;

}
bool LFsetup::get_DH_X__m()
{
	if(!set.DH_X__m__userInput)
	{
        if(set_valid.D1_X__m && set_valid.theta_X__pxm && set_valid.delta_d_X__px ){
            set.DH_X__m = LFsetup::_compute_DH__m_from_D1(set.D1_X__m,set.theta_X__pxm,set.delta_d_X__px);
			return true;
		}
        else if(set_valid.D2_X__m && set_valid.theta_X__pxm && set_valid.delta_d_X__px ){
            set.DH_X__m = LFsetup::_compute_DH__m_from_D2(set.D2_X__m,set.theta_X__pxm,set.delta_d_X__px);
			return true;
		}
        else if(set_valid.dH_X__px && set_valid.theta_X__pxm){
            set.DH_X__m = LFsetup::_compute_DH__m_from_dH(set.dH_X__px,set.theta_X__pxm);
			return true;
		}
		else return false;
	}
	else
	{
        if(set_valid.D1_X__m && set_valid.theta_X__pxm && set_valid.delta_d_X__px){
            if(1e-3 > std::abs(set.DH_X__m - LFsetup::_compute_DH__m_from_D1(set.D1_X__m,set.theta_X__pxm,set.delta_d_X__px))){
				return true;}
			return false;
		}
        else if(set_valid.D2_X__m && set_valid.theta_X__pxm && set_valid.delta_d_X__px){
            if(1e-3 > std::abs(set.DH_X__m - LFsetup::_compute_DH__m_from_D2(set.D2_X__m,set.theta_X__pxm,set.delta_d_X__px))){
				return true;}
			return false;
		}
        else if(set_valid.dH_X__px && set_valid.theta_X__pxm ){
            if(1e-3 > std::abs(set.DH_X__m - LFsetup::_compute_DH__m_from_dH(set.dH_X__px,set.theta_X__pxm))){
				return true;}
			return false;
		}
		else{
			if (set.DH_X__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_DH_Y__m()
{
	if(!set.DH_Y__m__userInput)
	{
        if(set_valid.D1_Y__m && set_valid.theta_Y__pxm && set_valid.delta_d_Y__px ){
            set.DH_Y__m = LFsetup::_compute_DH__m_from_D1(set.D1_Y__m,set.theta_Y__pxm,set.delta_d_Y__px);
			return true;
		}
        else if(set_valid.D2_Y__m && set_valid.theta_Y__pxm && set_valid.delta_d_Y__px ){
            set.DH_Y__m = LFsetup::_compute_DH__m_from_D2(set.D2_Y__m,set.theta_Y__pxm,set.delta_d_Y__px);
			return true;
		}
        else if(set_valid.dH_Y__px && set_valid.theta_Y__pxm ){
            set.DH_Y__m = LFsetup::_compute_DH__m_from_dH(set.dH_Y__px,set.theta_Y__pxm);
			return true;
		}
		else return false;
	}
	else
	{
        if(set_valid.D1_Y__m && set_valid.theta_Y__pxm && set_valid.delta_d_Y__px){
            if(1e-3 > std::abs(set.DH_Y__m - LFsetup::_compute_DH__m_from_D1(set.D1_Y__m,set.theta_Y__pxm,set.delta_d_Y__px))){
				return true;}
			return false;
		}
        else if(set_valid.D2_Y__m && set_valid.theta_Y__pxm && set_valid.delta_d_Y__px){
            if(1e-3 > std::abs(set.DH_Y__m - LFsetup::_compute_DH__m_from_D2(set.D2_Y__m,set.theta_Y__pxm,set.delta_d_Y__px))){
				return true;}
			return false;
		}
        else if(set_valid.dH_Y__px && set_valid.theta_Y__pxm ){
            if(1e-3 > std::abs(set.DH_Y__m - LFsetup::_compute_DH__m_from_dH(set.dH_Y__px,set.theta_Y__pxm))){
				return true;}
			return false;
		}
		else{
			if (set.DH_Y__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_DHopt_Y__m()
{
    if(set_valid.focal_length_Y__px && set_valid.baseline_Y__m && !set.DHopt_Y__m__userInput){
        set.DHopt_Y__m = LFsetup::_compute_DHopt__m(set.focal_length_Y__px,set.baseline_Y__m);
		return true;
	}
    else if(set_valid.focal_length_Y__px && set_valid.baseline_Y__m && set.DHopt_Y__m__userInput){
        if (1e-3 > std::abs(set.DHopt_Y__m - LFsetup::_compute_DHopt__m(set.focal_length_Y__px,set.baseline_Y__m))){
			return true;}
		return false;
	}
	else{
		if (set.DHopt_Y__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_DHopt_X__m()
{
    if(set_valid.focal_length_X__px && set_valid.baseline_X__m && !set.DHopt_X__m__userInput){
        set.DHopt_X__m = LFsetup::_compute_DHopt__m(set.focal_length_X__px,set.baseline_X__m);
		return true;
	}
    else if(set_valid.focal_length_X__px && set_valid.baseline_X__m && set.DHopt_X__m__userInput){
        if (1e-3 > std::abs(set.DHopt_X__m - LFsetup::_compute_DHopt__m(set.focal_length_X__px,set.baseline_X__m))){
			return true;}
		return false;
	}
	else{
		if (set.DHopt_X__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_Framesize_DH_X__m()
{
    if(set_valid.Cam_X && set_valid.baseline_X__m && set_valid.sensor_X__m  && set_valid.focalLength__m && set_valid.DH_X__m && !set.FramesizeDH_X__m__userInput){
            set.FramesizeDH_X__m = LFsetup::_compute_Framesize__m(set.sensor_X__m,set.focalLength__m,set.DH_X__m,set.baseline_X__m,set.Cam_X);
			return true;
	}
    else if(set_valid.Cam_X && set_valid.baseline_X__m && set_valid.sensor_X__m  && set_valid.focalLength__m && set_valid.DH_X__m && set.FramesizeDH_X__m__userInput){
            if (1e-03 > std::abs(set.FramesizeDH_X__m - LFsetup::_compute_Framesize__m(set.sensor_X__m,set.focalLength__m,set.DH_X__m,set.baseline_X__m,set.Cam_X))){
				return true;}
			return false;
	}
	else{
		if (set.FramesizeDH_X__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_Framesize_DH_Y__m()
{
    if(set_valid.Cam_Y && set_valid.baseline_Y__m && set_valid.sensor_Y__m  && set_valid.focalLength__m && set_valid.DH_Y__m && !set.FramesizeDH_Y__m__userInput){
            set.FramesizeDH_Y__m = LFsetup::_compute_Framesize__m(set.sensor_Y__m,set.focalLength__m,set.DH_Y__m,set.baseline_Y__m,set.Cam_Y);
			return true;
	}
    if(set_valid.Cam_Y && set_valid.baseline_Y__m && set_valid.sensor_Y__m  && set_valid.focalLength__m && set_valid.DH_Y__m && set.FramesizeDH_Y__m__userInput){
        if (1e-03 > std::abs(set.FramesizeDH_Y__m - LFsetup::_compute_Framesize__m(set.sensor_Y__m,set.focalLength__m,set.DH_Y__m,set.baseline_Y__m,set.Cam_Y))){
			return true;}
		return false;
	}
	else{
		if (set.FramesizeDH_Y__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_Framesize_D1_X__m()
{
    if(set_valid.Cam_X && set_valid.baseline_X__m && set_valid.sensor_X__m  && set_valid.focalLength__m && set_valid.D1_X__m && !set.FramesizeD1_X__m__userInput){
            set.FramesizeD1_X__m = LFsetup::_compute_Framesize__m(set.sensor_X__m,set.focalLength__m,set.D1_X__m,set.baseline_X__m,set.Cam_X);
                        return true;
	}
    else if(set_valid.Cam_X && set_valid.baseline_X__m && set_valid.sensor_X__m  && set_valid.focalLength__m && set_valid.D1_X__m && set.FramesizeD1_X__m__userInput){
            if (1e-03 > std::abs(set.FramesizeD1_X__m - LFsetup::_compute_Framesize__m(set.sensor_X__m,set.focalLength__m,set.D1_X__m,set.baseline_X__m,set.Cam_X))){
				return true;}
			return false;
	}
	else{
		if (set.FramesizeD1_X__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_Framesize_D1_Y__m()
{
    if(set_valid.Cam_Y && set_valid.baseline_Y__m && set_valid.sensor_Y__m  && set_valid.focalLength__m && set_valid.D1_Y__m && !set.FramesizeD1_Y__m__userInput){
            set.FramesizeD1_Y__m = LFsetup::_compute_Framesize__m(set.sensor_Y__m,set.focalLength__m,set.D1_Y__m,set.baseline_Y__m,set.Cam_Y);
			return true;
	}
    if(set_valid.Cam_Y && set_valid.baseline_Y__m && set_valid.sensor_Y__m  && set_valid.focalLength__m && set_valid.D1_Y__m && set.FramesizeD1_Y__m__userInput){
        if (1e-03 > std::abs(set.FramesizeD1_Y__m - LFsetup::_compute_Framesize__m(set.sensor_Y__m,set.focalLength__m,set.D1_Y__m,set.baseline_Y__m,set.Cam_Y))){
			return true;}
		return false;
	}
	else{
		if (set.FramesizeD1_Y__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_Framesize_D2_X__m()
{
    if(set_valid.Cam_X && set_valid.baseline_X__m && set_valid.sensor_X__m  && set_valid.focalLength__m && set_valid.D2_X__m && !set.FramesizeD2_X__m__userInput){
            set.FramesizeD2_X__m = LFsetup::_compute_Framesize__m(set.sensor_X__m,set.focalLength__m,set.D2_X__m,set.baseline_X__m,set.Cam_X);
			return true;
	}
    else if(set_valid.Cam_X && set_valid.baseline_X__m && set_valid.sensor_X__m  && set_valid.focalLength__m && set_valid.D2_X__m && set.FramesizeD2_X__m__userInput){
            if (1e-03 > std::abs(set.FramesizeD2_X__m - LFsetup::_compute_Framesize__m(set.sensor_X__m,set.focalLength__m,set.D2_X__m,set.baseline_X__m,set.Cam_X))){
				return true;}
			return false;
	}
	else{
		if (set.FramesizeD2_X__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_Framesize_D2_Y__m()
{
    if(set_valid.Cam_Y && set_valid.baseline_Y__m && set_valid.sensor_Y__m  && set_valid.focalLength__m && set_valid.D2_Y__m && !set.FramesizeD2_Y__m__userInput){
            set.FramesizeD2_Y__m = LFsetup::_compute_Framesize__m(set.sensor_Y__m,set.focalLength__m,set.D2_Y__m,set.baseline_Y__m,set.Cam_Y);
			return true;
	}
    if(set_valid.Cam_Y && set_valid.baseline_Y__m && set_valid.sensor_Y__m  && set_valid.focalLength__m && set_valid.D2_Y__m && set.FramesizeD2_Y__m__userInput){
        if (1e-03 > std::abs(set.FramesizeD2_Y__m - LFsetup::_compute_Framesize__m(set.sensor_Y__m,set.focalLength__m,set.D2_Y__m,set.baseline_Y__m,set.Cam_Y))){
			return true;}
		return false;
	}
	else{
		if (set.FramesizeD2_Y__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_focalLength_X__px()
{
		if(set_valid.focalLength__m && set_valid.sensor_X__m && set_valid.resolution_X__px  && !set.focal_length_X__px__userInput){
			set.focal_length_X__px = LFsetup::_compute_focalLength__px(set.focalLength__m,set.sensor_X__m,set.resolution_X__px);
			return true;
		}
        else if(set_valid.baseline_X__m && set_valid.theta_X__pxm && !set.focal_length_X__px__userInput){
            set.focal_length_X__px = LFsetup::_compute_focalLength__px(set.baseline_X__m,set.theta_X__pxm);
			return true;
		}
		if(set_valid.focalLength__m && set_valid.sensor_X__m && set_valid.resolution_X__px  && set.focal_length_X__px__userInput){
            if (1e-3 > std::abs(set.focal_length_X__px - LFsetup::_compute_focalLength__px(set.focalLength__m,set.sensor_X__m,set.resolution_X__px))){
				return true;}
			return false;
		}
        else if(set_valid.baseline_X__m && set_valid.theta_X__pxm && set.focal_length_X__px__userInput){
            if (1e-3 > std::abs(set.focal_length_X__px - LFsetup::_compute_focalLength__px(set.baseline_X__m,set.theta_X__pxm))){
				return true;}
			return false;
		}
		else{
			if (set.focal_length_X__px__userInput) return true;
			else return false;
		}
}
bool LFsetup::get_focalLength_Y__px()
{
	if(set_valid.focalLength__m && set_valid.sensor_Y__m && set_valid.resolution_Y__px  && !set.focal_length_Y__px__userInput){
		set.focal_length_Y__px = LFsetup::_compute_focalLength__px(set.focalLength__m,set.sensor_Y__m,set.resolution_Y__px);
		return true;
	}
    else if(set_valid.baseline_Y__m && set_valid.theta_Y__pxm && !set.focal_length_Y__px__userInput){
        set.focal_length_Y__px = LFsetup::_compute_focalLength__px(set.baseline_Y__m,set.theta_Y__pxm);
		return true;
	}
	if(set_valid.focalLength__m && set_valid.sensor_Y__m && set_valid.resolution_Y__px  && set.focal_length_Y__px__userInput){
        if (1e-3 > std::abs(set.focal_length_Y__px - LFsetup::_compute_focalLength__px(set.focalLength__m,set.sensor_Y__m,set.resolution_Y__px))){
			return true;}
		return false;
	}
    else if(set_valid.baseline_Y__m && set_valid.theta_Y__pxm && set.focal_length_Y__px__userInput ){
        if (1e-3 > std::abs(set.focal_length_Y__px - LFsetup::_compute_focalLength__px(set.baseline_Y__m,set.theta_Y__pxm))){
			return true;}
		return false;
	}
	else{
		if (set.focal_length_Y__px__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_focalLength__m()
{
        if(set_valid.theta_X__pxm && set_valid.Pixelsize_X__m && set_valid.baseline_X__m && !set.focalLength__m__userInput){
            set.focalLength__m = LFsetup::_compute_focalLength__m_from_theta(set.theta_X__pxm, set.baseline_X__m,set.Pixelsize_X__m);
			return true;
		}
		else if(set_valid.focal_length_X__px && set_valid.sensor_X__m && set_valid.resolution_X__px  && !set.focalLength__m__userInput){
			set.focalLength__m = LFsetup::_compute_focalLength__m(set.focal_length_X__px, set.sensor_X__m, set.resolution_X__px);
			return true;
		}
        else if(set_valid.theta_Y__pxm && set_valid.Pixelsize_Y__m && set_valid.baseline_Y__m && !set.focalLength__m__userInput){
            set.focalLength__m = LFsetup::_compute_focalLength__m_from_theta(set.theta_Y__pxm, set.baseline_Y__m,set.Pixelsize_Y__m);
			return true;
		}
		else if(set_valid.focal_length_Y__px && set_valid.sensor_Y__m && set_valid.resolution_Y__px   && !set.focalLength__m__userInput){
			set.focalLength__m = LFsetup::_compute_focalLength__m(set.focal_length_Y__px, set.sensor_Y__m, set.resolution_Y__px);
			return true;
		}
        else if(set_valid.theta_X__pxm && set_valid.Pixelsize_X__m && set_valid.baseline_X__m && set.focalLength__m__userInput){
            if (1e-3 > std::abs(set.focalLength__m - LFsetup::_compute_focalLength__m_from_theta(set.theta_X__pxm, set.baseline_X__m,set.Pixelsize_X__m))){
				return true;}
			return false;
		}
		else if(set_valid.focal_length_X__px && set_valid.sensor_X__m && set_valid.resolution_X__px  && set.focalLength__m__userInput){
            if (1e-3 > std::abs(set.focalLength__m - LFsetup::_compute_focalLength__m(set.focal_length_X__px, set.sensor_X__m, set.resolution_X__px))){
				return true;}
			return false;
		}
        else if(set_valid.theta_Y__pxm && set_valid.Pixelsize_Y__m && set_valid.baseline_Y__m && set.focalLength__m__userInput){
            if (1e-3 > std::abs(set.focalLength__m - LFsetup::_compute_focalLength__m_from_theta(set.theta_X__pxm, set.baseline_Y__m,set.Pixelsize_Y__m))){
				return true;}
			return false;
		}
		else if(set_valid.focal_length_Y__px && set_valid.sensor_Y__m && set_valid.resolution_Y__px   && set.focalLength__m__userInput){
            if (1e-3 > std::abs(set.focalLength__m - LFsetup::_compute_focalLength__m(set.focal_length_Y__px, set.sensor_Y__m, set.resolution_Y__px))){
				return true;}
			return false;
		}
		else{
			if (set.focalLength__m__userInput) return true;
			else return false;
		}
}
bool LFsetup::get_baseline_Y__m()
{
        if(set_valid.theta_Y__pxm && set_valid.Pixelsize_Y__m && set_valid.focalLength__m && !set.baseline_Y__m__userInput){
            set.baseline_Y__m = LFsetup::_compute_baseline__m(set.theta_Y__pxm, set.focalLength__m,set.Pixelsize_Y__m);
			return true;
		}
        else if (set_valid.baseline_X__m && set_valid.baseline_ratio && !set.baseline_Y__m__userInput){
					set.baseline_Y__m = LFsetup::_compute_baseline_Y__m(set.baseline_ratio,set.baseline_X__m);
					return true;
				}
		else if (set_valid.baseline_X__m && set_valid.baseline_ratio&& set.baseline_Y__m__userInput){
            if (1e-3 > std::abs(set.baseline_Y__m - LFsetup::_compute_baseline_Y__m(set.baseline_ratio,set.baseline_X__m))){
				return true;}
			return false;
		}
        else if(set_valid.theta_Y__pxm && set_valid.Pixelsize_Y__m && set_valid.focalLength__m  && set.baseline_Y__m__userInput){
            if (1e-3 > std::abs(set.baseline_Y__m - LFsetup::_compute_baseline__m(set.theta_Y__pxm, set.focalLength__m,set.Pixelsize_Y__m))){
				return true;}
			return false;
		}
		else{
			if (set.baseline_Y__m__userInput) return true;
			else return false;
		}
}
bool LFsetup::get_baseline_X__m()
{
        if(set_valid.theta_X__pxm && set_valid.Pixelsize_X__m && set_valid.focalLength__m && !set.baseline_X__m__userInput){
            set.baseline_X__m = LFsetup::_compute_baseline__m(set.theta_X__pxm, set.focalLength__m,set.Pixelsize_X__m);
			return true;
		}
		else if (set_valid.baseline_Y__m && set_valid.baseline_ratio&& !set.baseline_X__m__userInput){
			set.baseline_X__m = LFsetup::_compute_baseline_X__m(set.baseline_ratio,set.baseline_Y__m);
			return true;
		}
		else if (set_valid.baseline_Y__m && set_valid.baseline_ratio&& set.baseline_X__m__userInput){
            if (1e-3 > std::abs(set.baseline_X__m - LFsetup::_compute_baseline_X__m(set.baseline_ratio,set.baseline_Y__m))){
				return true;}
			return false;
		}
        else if(set_valid.theta_X__pxm && set_valid.Pixelsize_X__m && set_valid.focalLength__m  && set.baseline_X__m__userInput){
            if (1e-3 > std::abs(set.baseline_X__m - LFsetup::_compute_baseline__m(set.theta_X__pxm, set.focalLength__m, set.Pixelsize_X__m))){
				return true;}
			return false;
		}
		else{
			if (set.baseline_X__m__userInput) return true;
			else return false;
		}
}
bool LFsetup::get_sensor_X__m()
{
	if (!set.sensor_X__m__userInput)
	{
		if(set_valid.Pixelsize_X__m && set_valid.resolution_X__px ){
			set.sensor_X__m = LFsetup::_compute_sensor_X__m(set.resolution_X__px,set.Pixelsize_X__m);
			return true;
		}
        else if(set_valid.delta_D_X__m && set_valid.theta_X__pxm && set_valid.resolution_X__px && set_valid.delta_d_X__px && set_valid.DH_X__m ){
            set.sensor_X__m = LFsetup::_compute_sensor__m(set.delta_D_X__m,set.theta_X__pxm,set.resolution_X__px,set.delta_d_X__px,set.DH_X__m,set.Pixelsize_X__m);
			return true;
		}
        else if(set_valid.D1_X__m && set_valid.theta_X__pxm && set_valid.resolution_X__px && set_valid.delta_d_X__px && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            set.sensor_X__m = LFsetup::_compute_sensor__m_from_D1(set.DH_X__m,set.theta_X__pxm,set.resolution_X__px,set.delta_d_X__px,set.D1_X__m,set.Pixelsize_X__m);
			return true;
		}
        else if(set_valid.D2_X__m && set_valid.theta_X__pxm && set_valid.resolution_X__px && set_valid.delta_d_X__px && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            set.sensor_X__m = LFsetup::_compute_sensor__m_from_D2(set.DH_X__m,set.theta_X__pxm,set.resolution_X__px,set.delta_d_X__px,set.D2_X__m,set.Pixelsize_X__m);
			return true;
		}
		else return false;
	}
	else
	{
		if(set_valid.Pixelsize_X__m && set_valid.resolution_X__px ){
            if(1e-3 > std::abs(set.sensor_X__m - LFsetup::_compute_sensor_X__m(set.resolution_X__px,set.Pixelsize_X__m))){
				return true;}
			return false;
		}
        else if(set_valid.delta_D_X__m && set_valid.theta_X__pxm && set_valid.resolution_X__px && set_valid.delta_d_X__px && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            if(1e-3 > std::abs(set.sensor_X__m - LFsetup::_compute_sensor__m(set.delta_D_X__m,set.theta_X__pxm,set.resolution_X__px,set.delta_d_X__px,set.DH_X__m,set.Pixelsize_X__m))){
				return true;}
			return false;
		}
        else if(set_valid.D1_X__m && set_valid.theta_X__pxm && set_valid.resolution_X__px && set_valid.delta_d_X__px && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            if(1e-3 > std::abs(set.sensor_X__m - LFsetup::_compute_sensor__m_from_D1(set.DH_X__m,set.theta_X__pxm,set.resolution_X__px,set.delta_d_X__px,set.D1_X__m,set.Pixelsize_X__m))){
				return true;}
			return false;
		}
        else if(set_valid.D2_X__m && set_valid.theta_X__pxm && set_valid.resolution_X__px && set_valid.delta_d_X__px && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            if(1e-3 > std::abs(set.sensor_X__m - LFsetup::_compute_sensor__m_from_D1(set.DH_X__m,set.theta_X__pxm,set.resolution_X__px,set.delta_d_X__px,set.D2_X__m,set.Pixelsize_X__m))){
				return true;}
			return false;
		}
		else{
			if (set.sensor_X__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_sensor_Y__m()
{
	if (!set.sensor_Y__m__userInput)
	{
		if(set_valid.Pixelsize_Y__m  && set_valid.resolution_Y__px ){
			set.sensor_Y__m = LFsetup::_compute_sensor_Y__m(set.resolution_Y__px,set.Pixelsize_Y__m);
			return true;
		}
        else if(set_valid.delta_D_Y__m && set_valid.theta_Y__pxm && set_valid.resolution_Y__px && set_valid.delta_d_Y__px && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            set.sensor_Y__m = LFsetup::_compute_sensor__m(set.delta_D_Y__m,set.theta_Y__pxm,set.resolution_Y__px,set.delta_d_Y__px,set.DH_Y__m,set.Pixelsize_Y__m);
			return true;
		}
        else if(set_valid.D1_Y__m && set_valid.theta_Y__pxm && set_valid.resolution_Y__px && set_valid.delta_d_Y__px && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            set.sensor_Y__m = LFsetup::_compute_sensor__m_from_D1(set.DH_Y__m,set.theta_Y__pxm,set.resolution_Y__px,set.delta_d_Y__px,set.D1_Y__m,set.Pixelsize_Y__m);
			return true;
		}
        else if(set_valid.D2_Y__m && set_valid.theta_Y__pxm && set_valid.resolution_Y__px && set_valid.delta_d_Y__px && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            set.sensor_Y__m = LFsetup::_compute_sensor__m_from_D1(set.DH_Y__m,set.theta_Y__pxm,set.resolution_Y__px,set.delta_d_Y__px,set.D2_Y__m,set.Pixelsize_Y__m);
			return true;
		}
		else return false;
	}
	else
	{
		if(set_valid.Pixelsize_Y__m && set_valid.resolution_Y__px ){
            if(1e-3 > std::abs(set.sensor_Y__m - LFsetup::_compute_sensor_Y__m(set.resolution_Y__px,set.Pixelsize_Y__m))){
				return true;}
			return false;
		}
        else if(set_valid.delta_D_Y__m && set_valid.theta_Y__pxm && set_valid.resolution_Y__px && set_valid.delta_d_Y__px && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            if(1e-3 > std::abs(set.sensor_Y__m - LFsetup::_compute_sensor__m(set.delta_D_Y__m,set.theta_Y__pxm,set.resolution_Y__px,set.delta_d_Y__px,set.DH_Y__m,set.Pixelsize_Y__m))){
				return true;}
			return false;
		}
        else if(set_valid.D1_Y__m && set_valid.theta_Y__pxm& set_valid.resolution_Y__px && set_valid.delta_d_Y__px  && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            if(1e-3 > std::abs(set.sensor_Y__m - LFsetup::_compute_sensor__m_from_D1(set.DH_Y__m,set.theta_Y__pxm,set.resolution_Y__px,set.delta_d_Y__px,set.D1_Y__m,set.Pixelsize_Y__m))){
				return true;}
			return false;
		}
        else if(set_valid.D2_Y__m  && set_valid.theta_Y__pxm && set_valid.resolution_Y__px && set_valid.delta_d_Y__px  && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            if(1e-3 > std::abs(set.sensor_Y__m - LFsetup::_compute_sensor__m_from_D1(set.DH_Y__m,set.theta_Y__pxm,set.resolution_Y__px,set.delta_d_Y__px,set.D2_Y__m,set.Pixelsize_Y__m))){
				return true;}
			return false;
		}
		else{
			if (set.sensor_Y__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_PixelAspectRatio()
{
	if(set_valid.Pixelsize_Y__m && set_valid.Pixelsize_X__m && !set.PixelAspectRatio__userInput){
		set.PixelAspectRatio = LFsetup::_compute_PixelAspectRatio(set.Pixelsize_X__m,set.Pixelsize_Y__m);
		return true;
	}
	else if(set_valid.Pixelsize_Y__m && set_valid.Pixelsize_X__m && set.PixelAspectRatio__userInput){

        if (1e-3 > std::abs(set.PixelAspectRatio - LFsetup::_compute_PixelAspectRatio(set.Pixelsize_X__m,set.Pixelsize_Y__m))){
			return true;}
		return false;
	}
	else{
		if (set.PixelAspectRatio__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_PixelSize_X__m()
{
	if(set_valid.resolution_X__px && set_valid.sensor_X__m && !set.Pixelsize_X__m__userInput){
		set.Pixelsize_X__m = LFsetup::_compute_PixelSize__m_from_sensor(set.resolution_X__px, set.sensor_X__m);
		return true;
	}
	else if(set_valid.Pixelsize_Y__m && set_valid.PixelAspectRatio && !set.Pixelsize_X__m__userInput){
		set.Pixelsize_X__m = LFsetup::_compute_PixelSize_X__m(set.PixelAspectRatio,set.Pixelsize_Y__m);
		return true;
	}
    else if(set_valid.theta_X__pxm && set_valid.baseline_X__m && set_valid.focalLength__m  && !set.Pixelsize_X__m__userInput){
        set.Pixelsize_X__m = LFsetup::_compute_Pixelsize__m(set.theta_X__pxm, set.focalLength__m, set.baseline_X__m);
        return true;
    }
	else if(set_valid.Pixelsize_Y__m && set_valid.PixelAspectRatio && set.Pixelsize_X__m__userInput){
        if(1e-3 > std::abs(set.Pixelsize_X__m - LFsetup::_compute_PixelSize_X__m(set.PixelAspectRatio,set.Pixelsize_Y__m))){
			return true;}
		return false;
	}
	else if(set_valid.resolution_X__px && set_valid.sensor_X__m && set.Pixelsize_X__m__userInput){
        if (1e-3 > std::abs(set.Pixelsize_X__m - LFsetup::_compute_PixelSize__m_from_sensor(set.resolution_X__px, set.sensor_X__m))){
			return true;}
		return false;
	}
    else if(set_valid.theta_X__pxm && set_valid.baseline_X__m && set_valid.focalLength__m  && set.Pixelsize_X__m__userInput){
        if (1e-3 > std::abs(set.Pixelsize_X__m - LFsetup::_compute_Pixelsize__m(set.theta_X__pxm, set.focalLength__m, set.baseline_X__m))){
            return true;}
        return false;
    }
	else{
		if (set.Pixelsize_X__m__userInput) return true;
		else return false;
	}

}
bool LFsetup::get_PixelSize_Y__m()
{
	if(set_valid.resolution_Y__px && set_valid.sensor_Y__m && !set.Pixelsize_Y__m__userInput){
		set.Pixelsize_Y__m = LFsetup::_compute_PixelSize__m_from_sensor(set.resolution_Y__px, set.sensor_Y__m);
		return true;
	}
	else if(set_valid.Pixelsize_X__m && set_valid.PixelAspectRatio && !set.Pixelsize_Y__m__userInput){
		set.Pixelsize_Y__m = LFsetup::_compute_PixelSize_Y__m(set.PixelAspectRatio,set.Pixelsize_X__m);
		return true;
	}
    else if(set_valid.theta_Y__pxm && set_valid.baseline_Y__m && set_valid.focalLength__m  && !set.Pixelsize_Y__m__userInput){
        set.Pixelsize_Y__m = LFsetup::_compute_Pixelsize__m(set.theta_Y__pxm, set.focalLength__m, set.baseline_Y__m);
        return true;
    }
	else if(set_valid.Pixelsize_X__m  && set_valid.PixelAspectRatio && set.Pixelsize_Y__m__userInput){

        if(1e-3 > std::abs(set.Pixelsize_Y__m - LFsetup::_compute_PixelSize_Y__m(set.PixelAspectRatio,set.Pixelsize_X__m))){
			return true;}
		return false;
	}
	else if(set_valid.resolution_Y__px && set_valid.sensor_Y__m && set.Pixelsize_Y__m__userInput){
        if(1e-3 > std::abs(set.Pixelsize_Y__m - LFsetup::_compute_PixelSize__m_from_sensor(set.resolution_Y__px, set.sensor_Y__m))){
			return true;}
		return false;
	}
    else if(set_valid.theta_Y__pxm && set_valid.baseline_Y__m && set_valid.focalLength__m  && set.Pixelsize_Y__m__userInput){
        if (1e-3 > std::abs(set.Pixelsize_Y__m - LFsetup::_compute_Pixelsize__m(set.theta_Y__pxm, set.focalLength__m, set.baseline_Y__m))){
            return true;}
        return false;
    }
	else{
		if (set.Pixelsize_Y__m__userInput) return true;
		else return false;
	}
}
bool LFsetup::get_resolution_Y__px()
{
	if (!set.resolution_Y__px__userInput)
	{
		if(set_valid.AspectRatio && set_valid.resolution_X__px ){
			set.resolution_Y__px = LFsetup::_compute_resolution_Y__m(set.AspectRatio,set.resolution_X__px);
			return true;
		}
		else if(set_valid.sensor_Y__m && set_valid.Pixelsize_Y__m ){
			set.resolution_X__px = LFsetup::_compute_resolution_from_Sen_and_Pix__px(set.sensor_Y__m,set.Pixelsize_Y__m);
			return true;
		}
        else if(set_valid.delta_D_Y__m && set_valid.theta_Y__pxm && set_valid.sensor_Y__m && set_valid.delta_d_Y__px && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            set.resolution_Y__px = LFsetup::_compute_resolution__px(set.delta_D_Y__m,set.theta_Y__pxm,set.sensor_Y__m,set.delta_d_Y__px,set.DH_Y__m,set.Pixelsize_Y__m);
			return true;
		}
        else if(set_valid.delta_D_Y__m && set_valid.theta_Y__pxm && set_valid.sensor_Y__m && set_valid.D1_Y__m && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            set.resolution_Y__px = LFsetup::_compute_resolution__px_from_D1(set.DH_Y__m,set.theta_Y__pxm,set.delta_D_Y__m,set.sensor_Y__m,set.D1_Y__m,set.Pixelsize_Y__m);
			return true;
		}
        else if(set_valid.delta_D_Y__m && set_valid.theta_Y__pxm && set_valid.sensor_Y__m && set_valid.D2_Y__m && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            set.resolution_Y__px = LFsetup::_compute_resolution__px_from_D2(set.DH_Y__m,set.theta_Y__pxm,set.delta_D_Y__m,set.sensor_Y__m,set.D2_Y__m,set.Pixelsize_Y__m);
			return true;
		}
		else{
			return false;
		}
	}
	else
	{
		if(set_valid.AspectRatio && set_valid.resolution_X__px ){
            if (1e-3 > std::abs(set.resolution_Y__px - LFsetup::_compute_resolution_Y__m(set.AspectRatio,set.resolution_X__px))){
				return true;}
			return false;
		}
		else if(set_valid.sensor_Y__m && set_valid.Pixelsize_Y__m ){
            if (1e-3 > std::abs(set.resolution_Y__px - LFsetup::_compute_resolution_from_Sen_and_Pix__px(set.sensor_Y__m,set.Pixelsize_Y__m))){
				return true;}
			return false;
		}
        else if(set_valid.delta_D_Y__m && set_valid.theta_Y__pxm && set_valid.sensor_Y__m && set_valid.delta_d_Y__px && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m ){
            if (1e-3 > std::abs(set.resolution_Y__px - LFsetup::_compute_resolution__px(set.delta_D_Y__m,set.theta_Y__pxm,set.sensor_Y__m,set.delta_d_Y__px,set.DH_Y__m,set.Pixelsize_Y__m))){
				return true;}
			return false;
		}
        else if(set_valid.delta_D_Y__m && set_valid.theta_Y__pxm && set_valid.sensor_Y__m && set_valid.D1_Y__m && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            if (1e-3 > std::abs(set.resolution_Y__px - LFsetup::_compute_resolution__px_from_D1(set.DH_Y__m,set.theta_Y__pxm,set.delta_D_Y__m,set.sensor_Y__m,set.D1_Y__m,set.Pixelsize_Y__m))){
				return true;}
			return false;
		}
        else if(set_valid.delta_D_Y__m && set_valid.theta_Y__pxm && set_valid.sensor_Y__m && set_valid.D2_Y__m && set_valid.DH_Y__m && set_valid.Pixelsize_Y__m){
            if (1e-3 > std::abs(set.resolution_Y__px - LFsetup::_compute_resolution__px_from_D2(set.DH_Y__m,set.theta_Y__pxm,set.delta_D_Y__m,set.sensor_Y__m,set.D2_Y__m,set.Pixelsize_Y__m))){
				return true;}
			return false;
		}
		else{
			if (set.resolution_Y__px__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_resolution_X__px()
{
	if (!set.resolution_X__px__userInput)
	{
		if(set_valid.AspectRatio && set_valid.resolution_Y__px ){
			set.resolution_X__px = LFsetup::_compute_resolution_X__m(set.AspectRatio,set.resolution_Y__px);
			return true;
		}
		else if(set_valid.sensor_X__m && set_valid.Pixelsize_X__m ){
			set.resolution_X__px = LFsetup::_compute_resolution_from_Sen_and_Pix__px(set.sensor_X__m,set.Pixelsize_X__m);
			return true;
		}
        else if(set_valid.delta_D_X__m && set_valid.theta_X__pxm && set_valid.sensor_X__m && set_valid.delta_d_X__px && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            set.resolution_X__px = LFsetup::_compute_resolution__px(set.delta_D_X__m,set.theta_X__pxm,set.sensor_X__m,set.delta_d_X__px,set.DH_X__m,set.Pixelsize_X__m);
			return true;
		}
        else if(set_valid.delta_D_X__m && set_valid.theta_X__pxm && set_valid.sensor_X__m && set_valid.D1_X__m && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            set.resolution_X__px = LFsetup::_compute_resolution__px_from_D1(set.DH_X__m,set.theta_X__pxm,set.delta_D_X__m,set.sensor_X__m,set.D1_X__m,set.Pixelsize_X__m);
			return true;
		}
        else if(set_valid.delta_D_X__m && set_valid.theta_X__pxm && set_valid.sensor_X__m && set_valid.D2_X__m && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            set.resolution_X__px = LFsetup::_compute_resolution__px_from_D2(set.DH_X__m,set.theta_X__pxm,set.delta_D_X__m,set.sensor_X__m,set.D2_X__m,set.Pixelsize_X__m);
			return true;
		}
		else{
			return false;
		}
	}
	else
	{
		if(set_valid.AspectRatio && set_valid.resolution_Y__px ){
            if (1e-3 > std::abs(set.resolution_X__px - LFsetup::_compute_resolution_X__m(set.AspectRatio,set.resolution_Y__px))){
				return true;}
			return false;
		}
		else if(set_valid.sensor_X__m && set_valid.Pixelsize_X__m ){
            if (1e-3 > std::abs(set.resolution_X__px - LFsetup::_compute_resolution_from_Sen_and_Pix__px(set.sensor_X__m,set.Pixelsize_X__m))){
				return true;}
			return false;
		}
        else if(set_valid.delta_D_X__m && set_valid.theta_X__pxm && set_valid.sensor_X__m && set_valid.delta_d_X__px && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            if (1e-3 > std::abs(set.resolution_X__px - LFsetup::_compute_resolution__px(set.delta_D_X__m,set.theta_X__pxm,set.sensor_X__m,set.delta_d_X__px,set.DH_X__m,set.Pixelsize_X__m))){
				return true;}
			return false;
		}
        else if(set_valid.delta_D_X__m && set_valid.theta_X__pxm & set_valid.sensor_X__m && set_valid.D1_X__m && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            if (1e-3 > std::abs(set.resolution_X__px - LFsetup::_compute_resolution__px_from_D1(set.DH_X__m,set.theta_X__pxm,set.delta_D_X__m,set.sensor_X__m,set.D1_X__m,set.Pixelsize_X__m))){
				return true;}
			return false;
		}
        else if(set_valid.delta_D_X__m && set_valid.theta_X__pxm && set_valid.sensor_X__m && set_valid.D2_X__m && set_valid.DH_X__m && set_valid.Pixelsize_X__m){
            if (1e-3 > std::abs(set.resolution_X__px - LFsetup::_compute_resolution__px_from_D2(set.DH_X__m,set.theta_X__pxm,set.delta_D_X__m,set.sensor_X__m,set.D2_X__m,set.Pixelsize_X__m))){
				return true;}
			return false;
		}
		else{
			if (set.resolution_X__px__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_AspectRatio()
{
	if(!set.AspectRatio__userInput){
		if(set_valid.resolution_X__px && set_valid.resolution_Y__px ){
			set.AspectRatio = LFsetup::_compute_AspectRatio(set.resolution_X__px,set.resolution_Y__px);
			return true;}
		return false;

	}
	else{
		if(set_valid.resolution_X__px && set_valid.resolution_Y__px ){
            if (1e-3 > std::abs(set.AspectRatio - LFsetup::_compute_AspectRatio(set.resolution_X__px,set.resolution_Y__px))){
				return true;}
			return false;
		}
		else{
			if (set.AspectRatio__userInput) return true;
			else return false;
		}
	}

}
bool LFsetup::get_baselineRatio()
{
	if(!set.baseline_ratio__userInput){
		if(set_valid.baseline_X__m && set_valid.baseline_Y__m ){
			set.baseline_ratio = LFsetup::_compute_AspectRatio(set.baseline_X__m,set.baseline_Y__m);
			return true;}
		return false;

	}
	else{
		if(set_valid.baseline_X__m && set_valid.baseline_Y__m ){
            if (1e-3 > std::abs(set.baseline_ratio - LFsetup::_compute_AspectRatio(set.baseline_X__m,set.baseline_Y__m))){
				return true;}
			return false;
		}
		else{
			if (set.baseline_ratio__userInput) return true;
			else return false;
		}
	}

}
bool LFsetup::get_DoF_D_N__m()
{
	if(!set.DoF_D_N__m__userInput)
	{
		if(set_valid.DoF_H__m && set_valid.DoF_subject_distance__m && set_valid.focalLength__m ){
			set.DoF_D_N__m = LFsetup::_compute_DoF_D_N__m(set.DoF_H__m,set.DoF_subject_distance__m,set.focalLength__m);
			return true;
		}
		else{
			return false;
		}
	}
	else
	{
		if(set_valid.DoF_H__m && set_valid.DoF_subject_distance__m && set_valid.focalLength__m ){
            if (1e-3 > std::abs(set.DoF_D_N__m - LFsetup::_compute_DoF_D_N__m(set.DoF_H__m,set.DoF_subject_distance__m,set.focalLength__m))){
				return true;}
			return false;
		}
		else{
			if (set.DoF_D_N__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_DoF_D_F__m()
{
	if(!set.DoF_D_F__m__userInput)
	{
		if(set_valid.DoF_H__m && set_valid.DoF_subject_distance__m && set_valid.focalLength__m ){
			set.DoF_D_F__m = LFsetup::_compute_DoF_D_F__m(set.DoF_H__m,set.DoF_subject_distance__m,set.focalLength__m);
			if (set.DoF_D_F__m < 0) set.DoF_D_F__m=INFINITY;
			return true;
		}
		else{
			return false;
		}
	}
	else
	{
		if(set_valid.DoF_H__m && set_valid.DoF_subject_distance__m && set_valid.focalLength__m ){
            if (1e-3 > std::abs(set.DoF_D_F__m - LFsetup::_compute_DoF_D_F__m(set.DoF_H__m,set.DoF_subject_distance__m,set.focalLength__m))){
				return true;}
			return false;
		}
		else{
			if (set.DoF_D_F__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_DoF_H__m()
{
	if(!set.DoF_H__m__userInput){
        if(set_valid.focalLength__m && set_valid.f_number && set_valid.CircleofConfusion__m ){
            set.DoF_H__m = LFsetup::_compute_DoF_H__m(set.focalLength__m,set.f_number,set.CircleofConfusion__m);
			return true;}
		return false;
	}
	if (set.DoF_H__m__userInput) return true;
	else return false;
}
bool LFsetup::get_DoF_DoF__m()
{
	if(!set.DoF_DoF__m__userInput)
	{
		if(set_valid.DoF_D_F__m && set_valid.DoF_D_N__m ){
			set.DoF_DoF__m = LFsetup::_compute_DoF_DoF__m(set.DoF_D_N__m,set.DoF_D_F__m);
			return true;
		}
		else{
			return false;
		}
	}
	else
	{
		if(set_valid.DoF_D_F__m && set_valid.DoF_D_N__m ){
            if (1e-3 > std::abs(set.DoF_DoF__m - LFsetup::_compute_DoF_DoF__m(set.DoF_D_N__m,set.DoF_D_F__m))){
				return true;}
			return false;
		}
		else{
			if (set.DoF_DoF__m__userInput) return true;
			else return false;
		}
	}
}
bool LFsetup::get_object_space_angle_X_degree()
{
    if(set_valid.sensor_X__m  && set_valid.focalLength__m){
            set.object_space_angle_X_degree = LFsetup::_object_space_angle_degree(set.sensor_X__m,set.focalLength__m);
            return true;
    }
    else{
        return false;
    }
}
bool LFsetup::get_object_space_angle_Y_degree()
{
    if(set_valid.sensor_Y__m  && set_valid.focalLength__m){
            set.object_space_angle_Y_degree = LFsetup::_object_space_angle_degree(set.sensor_Y__m,set.focalLength__m);
            return true;
    }
    else{
        return false;
    }
}





// basic equations, implemented as inline function


inline double LFsetup::_compute_D1__m(double theta__pxm,double DH__m,double delta_d__px)
{
    return ((theta__pxm*DH__m)/(theta__pxm- delta_d__px*DH__m));
}

inline double LFsetup::_compute_D2__m(double theta__pxm,double DH__m,double delta_d__px)
{
    return ((theta__pxm*DH__m)/(theta__pxm+ delta_d__px*DH__m));
}

inline double LFsetup::_compute_theta__pxm_fromD(double delta_D__m,double DH__m,double delta_d__px)
{
    return ((delta_d__px * DH__m * DH__m) + (delta_d__px*DH__m * std::sqrt(DH__m*DH__m + delta_D__m * delta_D__m)))/(delta_D__m);
}

inline double LFsetup::_compute_theta__pxm_from_d(double delta_D__m,double dH__px,double delta_d__px)
{
    return ((delta_D__m / (delta_d__px * 2) * dH__px * dH__px) - ((delta_d__px * 2)*delta_D__m / 4));
}

inline double LFsetup::_compute_theta__pxm(double focalLength__m, double baseline__m, double PixelSize__m)
{
    return (focalLength__m * baseline__m / PixelSize__m );
}

inline double LFsetup::_compute_DH__m_from_D1(double D1__m, double theta__pxm, double delta_d__px)
{
    return (D1__m*theta__pxm)/(theta__pxm+ delta_d__px*D1__m);
}

inline double LFsetup::_compute_DH__m_from_D2(double D2__m, double theta__pxm, double delta_d__px)
{
    return (D2__m*theta__pxm)/(theta__pxm- delta_d__px*D2__m);
}

inline double LFsetup::_compute_DH__m_from_dH(double dH__px, double theta__pxm)
{
    return (theta__pxm)/(dH__px);
}

inline double LFsetup::_compute_DHopt__m(double focal_length__px,double baseline__m)
{
    return std::sqrt(focal_length__px*baseline__m);
}

inline double LFsetup::_compute_delta_d__px_from_d2(double d2__px, double dH__px)
{
	return (d2__px - dH__px);
}

inline double LFsetup::_compute_delta_d__px_from_d1(double d1__px, double dH__px)
{
	return (dH__px - d1__px);
}

inline double LFsetup::_compute_delta_D__m(double D1__m, double D2__m)
{
	return (D1__m - D2__m);
}

inline double LFsetup::_compute_D1__m(double delta_D_m, double D2__px)
{
	return (delta_D_m + D2__px);
}

inline double LFsetup::_compute_D2__m(double delta_D_m, double D1__px)
{
	return (D1__px - delta_D_m);
}

inline double LFsetup::_compute_d2__px(double delta_d__px, double d1__px)
{
	return (double)2.00000*delta_d__px + d1__px;
}

inline double LFsetup::_compute_d1__px(double delta_d__px, double d2__px)
{
	return d2__px - (double)2.00000*delta_d__px;
}

inline double LFsetup::_compute_d2__px_from_DH(double dH__px, double delta_d__px)
{
	return delta_d__px + dH__px;
}

inline double LFsetup::_compute_d1__px_from_DH(double dH__px, double delta_d__px)
{
	return dH__px - delta_d__px;
}

inline double LFsetup::_compute_resolution__px_from_D1(double DH__m, double theta__pxm,double delta_D__m,double sensor__m,double D1__m,double PixelSize__m)
{
    return (D1__m*DH__m*delta_D__m*sensor__m)/(PixelSize__m*theta__pxm*(D1__m-DH__m));
}

inline double LFsetup::_compute_resolution__px_from_D2(double DH__m, double theta__pxm,double delta_D__m,double sensor__m,double D2__m,double PixelSize__m)
{
    return (D2__m*DH__m*delta_D__m*sensor__m)/(PixelSize__m*theta__pxm*(DH__m-D2__m));
}

inline double LFsetup::_compute_sensor__m_from_D1(double DH__m, double theta__pxm,double resolution__m,double delta_d__px,double D1__m,double PixelSize__m)
{
    return ((theta__pxm*(D1__m-DH__m)*resolution__m*PixelSize__m)/(DH__m*D1__m*delta_d__px));
}

inline double LFsetup::_compute_sensor__m_from_D2(double DH__m, double theta__pxm,double resolution__m,double delta_d__px,double D2__m,double PixelSize__m)
{
    return ((theta__pxm*(DH__m-D2__m)*resolution__m*PixelSize__m)/(DH__m*D2__m*delta_d__px));
}

inline double LFsetup::_compute_delta_d__px_from_D2(double DH__m, double theta__pxm,double D2__m)
{
    return ((theta__pxm*(DH__m-D2__m))/(DH__m*D2__m));
}

inline double LFsetup::_compute_delta_d__px_from_D1(double DH__m, double theta__pxm,double D1__m)
{
    return ((theta__pxm*(D1__m-DH__m))/(DH__m*D1__m));
}

inline double LFsetup::_compute_delta_d__px(double delta_D__m, double theta__pxm,double DH__m)
{
    return ((theta__pxm*delta_D__m)/((DH__m*DH__m + DH__m * std::sqrt(DH__m*DH__m+delta_D__m*delta_D__m))));
}

inline double LFsetup::_compute_sensor__m(double delta_D__m, double theta__pxm,double resolution__m,double delta_d__px,double DH__m, double PixelSize__m)
{
    return ((theta__pxm*delta_D__m*resolution__m*PixelSize__m)/(delta_d__px*(DH__m*DH__m + DH__m * std::sqrt(DH__m*DH__m+delta_D__m*delta_D__m))));
}

inline double LFsetup::_compute_resolution__px(double delta_D__m, double theta__pxm,double sensor__px,double delta_d__m,double DH__m, double PixelSize__m)
{
    return ( ( (delta_d__m*sensor__px*DH__m*DH__m) + (delta_d__m*sensor__px*DH__m * std::sqrt( DH__m * DH__m + delta_D__m * delta_D__m) ) ) / ( delta_D__m * theta__pxm*  PixelSize__m ) );
}

inline double LFsetup::_compute_Framesize__m(double sensor__m, double focalLength__m,double DH__m, double baseline__m, double cams)
{
    return ((sensor__m*DH__m/focalLength__m) - baseline__m*(cams-1));
}

inline double LFsetup::_compute_sensor_X__m(double resolution_X__px, double resolution_Y__px,double sensor_Y__m)
{
	return (resolution_X__px*sensor_Y__m/resolution_Y__px);
}

inline double LFsetup::_compute_sensor_Y__m(double resolution_X__px, double resolution_Y__px,double sensor_X__m)
{
	return (resolution_Y__px*sensor_X__m/resolution_X__px);
}

inline double LFsetup::_compute_resolution_X__m(double AspectRatio, double resolution_Y__px)
{
	return (AspectRatio*resolution_Y__px);
}

inline double LFsetup::_compute_resolution_Y__m(double AspectRatio, double resolution_X__px)
{
	return (resolution_X__px/AspectRatio);
}

inline double LFsetup::_compute_baseline_X__m(double AspectRatio, double baseline_Y__m)
{
	return (AspectRatio*baseline_Y__m);
}

inline double LFsetup::_compute_baseline_Y__m(double AspectRatio, double baseline_X__m)
{
	return (baseline_X__m/AspectRatio);
}

inline double LFsetup::_compute_AspectRatio(double resolution_X__px, double resolution_Y__px)
{
	return (resolution_X__px/resolution_Y__px);
}

inline double LFsetup::_compute_sensor_X__m(double resolution_X__px, double PixelSize_X__m)
{
	return (resolution_X__px*PixelSize_X__m);
}

inline double LFsetup::_compute_sensor_Y__m(double resolution_Y__px, double PixelSize_Y__m)
{
	return (resolution_Y__px*PixelSize_Y__m);
}

inline double LFsetup::_compute_PixelAspectRatio(double PixelSize_X__m, double PixelSize_Y__m)
{
	return (PixelSize_X__m/PixelSize_Y__m);
}

inline double LFsetup::_compute_PixelSize_X__m(double PixelAspectRatio, double PixelSize_Y__m)
{
	return (PixelAspectRatio * PixelSize_Y__m);
}

inline double LFsetup::_compute_PixelSize__m_from_sensor(double resolution__px, double sensor__m)
{
	return (sensor__m / resolution__px);
}

inline double LFsetup::_compute_Pixelsize__m(double theta__pxm, double focalLength__m, double baseline__m)
{
    return (focalLength__m * baseline__m / theta__pxm);
}

inline double LFsetup::_compute_PixelSize_Y__m(double PixelAspectRatio, double PixelSize_X__m)
{
	return (PixelSize_X__m/ PixelAspectRatio );
}

inline double LFsetup::_compute_focalLength__px(double focalLength__m, double sensor__m, double resolution__px)
{
	return (focalLength__m * resolution__px /  sensor__m);
}

inline double LFsetup::_compute_focalLength__px(double baseline__m, double theta__pxm)
{
    return (theta__pxm / baseline__m );
}

inline double LFsetup::_compute_d2__px_from_theta(double theta__pxm, double D2__m)
{
    return (theta__pxm / D2__m);
}
inline double LFsetup::_compute_d1__px_from_theta(double theta__pxm, double D1__m)
{
    return (theta__pxm / D1__m);
}

inline double LFsetup::_compute_dH__px_from_d1d2(double d1__px, double d2__px)
{
	return ((d1__px + d2__px)/2);
}

inline double LFsetup::_compute_dH__px(double theta__pxm, double DH__m)
{
    return ( (theta__pxm) /  (DH__m ) );
}

inline double LFsetup::_compute_focalLength__m_from_theta(double theta__pxm, double baseline__m, double PixelSize__m)
{
    return (theta__pxm *PixelSize__m /  baseline__m);
}

inline double LFsetup::_compute_focalLength__m(double focal_length__px, double sensor__m, double resolution__px)
{
	return (focal_length__px * sensor__m / resolution__px);
}

inline double LFsetup::_compute_baseline__m(double theta__pxm, double focalLength__m, double PixelSize__m)
{
    return (theta__pxm * PixelSize__m /  focalLength__m);
}

inline double LFsetup::_compute_delta_D_inaccuracy__m(double D__m, double focalLength__px, double baseline__m, double delta_d_inaccuracy__px)
{
	return ( (D__m * D__m * delta_d_inaccuracy__px) /  (focalLength__px * baseline__m) );
}

inline double LFsetup::_compute_resolution_from_Sen_and_Pix__px(double sensor__m,double Pixelsize__m)
{
	return (sensor__m/Pixelsize__m);
}

inline double LFsetup::_compute_DoF_H__m(double focalLength__m, double f_number, double CircleofConfusion__m)
{
    return (focalLength__m*focalLength__m)/(f_number*CircleofConfusion__m) + focalLength__m;
}

inline double LFsetup::_compute_DoF_D_N__m(double DoF_D_F__m, double DoF_DoF__m)
{
	return DoF_D_F__m - DoF_DoF__m;
}

inline double LFsetup::_compute_DoF_D_N__m(double DoF_H__m, double DoF_subject_distance__m, double focalLength__m)
{
    return ((DoF_H__m - focalLength__m)  * DoF_subject_distance__m)/(DoF_H__m + (DoF_subject_distance__m - 2*focalLength__m));
}

inline double LFsetup::_compute_DoF_D_F__m(double DoF_D_N__m, double DoF_DoF__m)
{
	return DoF_D_N__m + DoF_DoF__m;
}

inline double LFsetup::_compute_DoF_D_F__m(double DoF_H__m, double DoF_subject_distance__m, double focalLength__m)
{
    return ((DoF_H__m - focalLength__m)  * DoF_subject_distance__m)/(DoF_H__m - DoF_subject_distance__m );
}

inline double LFsetup::_compute_DoF_DoF__m(double DoF_D_N__m, double DoF_D_F__m)
{
	return DoF_D_F__m - DoF_D_N__m;
}

inline double LFsetup::_geometricDepthInaccuracy_m(double DH__m,double baseline__m, double delta_baseline__m,double focal_length__m, double delta_focal_length__m)
{
    return sqrt( ((DH__m*delta_baseline__m)/baseline__m)*((DH__m*delta_baseline__m)/baseline__m) + ((DH__m*delta_focal_length__m)/focal_length__m)*((DH__m*delta_focal_length__m)/focal_length__m) ) ;
}

inline double LFsetup::_object_space_angle_degree(double sensor__m, double focal_length__m){

    return 180/3.14*2*std::atan((sensor__m)/(2*focal_length__m));
}

