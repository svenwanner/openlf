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
#ifndef CLASS_LFSETUP_H_
#define CLASS_LFSETUP_H_

#include "ConfigParser.h"


#endif /* CLASS_LFSETUP_H_ */

class LFsetup{

public:

struct LFvalid{

		bool delta_D_X__m; // Depth range

		bool delta_D_Y__m; // Depth range

		bool D1_X__m; // depth further away of the camera

		bool D1_Y__m; // depth further away of the camera

		bool D2_X__m; // depth closer to the camera

		bool D2_Y__m; // depth closer to the camera

		bool delta_d_X__px; // Disparity range

		bool delta_d_Y__px; // Disparity range

        bool theta_X__pxm; // multiplication of the focal length and the baseline

        bool theta_Y__pxm; // multiplication of the focal length and the baseline

		bool DH_X__m; // Depth of Horoptor

		bool DH_Y__m; // Depth of Horoptor

		bool DHopt_X__m; //Depth of optimal positioned Horoptor

		bool DHopt_Y__m; //Depth of optimal positioned Horoptor

		bool focalLength__m;

		bool focal_length_X__px;

		bool focal_length_Y__px;

		bool baseline_X__m;

		bool baseline_Y__m;

		bool baseline_ratio;

		bool sensor_X__m; // sensor length sh

		bool sensor_Y__m; // sensor wide sv

		bool resolution_X__px; // Nh

		bool resolution_Y__px; //Nv

		bool d1_X__px; //Disparity of depth further away

		bool d1_Y__px; //Disparity of depth further away

		bool d2_X__px; //Disparity of closer depth

		bool d2_Y__px; //Disparity of closer depth

		bool dH_X__px; // Disparity of Horoptor

		bool dH_Y__px; // Disparity of Horoptor

		bool FramesizeDH_X__m; //Size of the camera image area in space

		bool FramesizeDH_Y__m; //Size of the camera image area in space

		bool FramesizeD1_X__m; //Size of the camera image area in space

		bool FramesizeD1_Y__m; //Size of the camera image area in space

		bool FramesizeD2_X__m; //Size of the camera image area in space

		bool FramesizeD2_Y__m; //Size of the camera image area in space

		bool AspectRatio;

		bool Pixelsize_X__m; // tilde(sh)

		bool Pixelsize_Y__m; // tilde(sv)

		bool PixelAspectRatio;

		bool delta_d_inaccuracy_ST__px;

		bool delta_D1_X_inaccuracy_ST__m;

		bool delta_D2_X_inaccuracy_ST__m;

		bool delta_DH_X_inaccuracy_ST__m;

		bool delta_D1_Y_inaccuracy_ST__m;

		bool delta_D2_Y_inaccuracy_ST__m;

		bool delta_DH_Y_inaccuracy_ST__m;

		bool DoF_D_N__m; // closest distance for which the object is still sharp

		bool DoF_D_F__m; // farest distance for which the object is still sharp

		bool f_number;

		bool DoF_H__m; // auxiliary variable (Hyperfocal distance)

		bool DoF_subject_distance__m; // distance for which the object would be perfectly focused

		bool DoF_DoF__m; // Depth of field

        bool CircleofConfusion__m;

		bool geometricDepthInaccuracyDH_X__m;

		bool geometricDepthInaccuracyDH_Y__m;

        bool geometricDepthInaccuracyD1_X__m;

        bool geometricDepthInaccuracyD1_Y__m;

        bool geometricDepthInaccuracyD2_X__m;

        bool geometricDepthInaccuracyD2_Y__m;

        bool object_space_angle_X_degree;

        bool object_space_angle_Y_degree;

		bool delta_focal_length__m;

        bool delta_rotation__deg;

		bool delta_baseline__m;

        bool Cam_X;
        bool Cam_Y;

	}set_valid;

struct LFparameter{

	double delta_D_X__m; // Depth range
	bool delta_D_X__m__userInput;

	double delta_D_Y__m; // Depth range
	bool delta_D_Y__m__userInput;

	double D1_X__m; // depth further away of the camera
	bool D1_X__m__userInput;

	double D1_Y__m; // depth further away of the camera
	bool D1_Y__m__userInput;

	double D2_X__m; // depth closer to the camera
	bool D2_X__m__userInput;

	double D2_Y__m; // depth closer to the camera
	bool D2_Y__m__userInput;

	double delta_d_X__px; // Disparity range
	bool delta_d_X__px__userInput;

	double delta_d_Y__px; // Disparity range
	bool delta_d_Y__px__userInput;

    double theta_X__pxm; // multiplication of the focal length and the baseline
    bool theta_X__pxm__userInput;

    double theta_Y__pxm; // multiplication of the focal length and the baseline
    bool theta_Y__pxm__userInput;

	double DH_X__m; // Depth of Horoptor
	bool DH_X__m__userInput;

	double DH_Y__m; // Depth of Horoptor
	bool DH_Y__m__userInput;

	double DHopt_X__m; //Depth of optimal positioned Horoptor
	bool DHopt_X__m__userInput;

	double DHopt_Y__m; //Depth of optimal positioned Horoptor
	bool DHopt_Y__m__userInput;

	double focalLength__m;
	bool focalLength__m__userInput;

	double delta_focal_length__m;
	bool delta_focal_length__m__userInput;

    double delta_rotation__deg;
    bool delta_rotation__deg__userInput;

	double focal_length_X__px;
	bool focal_length_X__px__userInput;

	double focal_length_Y__px;
	bool focal_length_Y__px__userInput;

	double baseline_X__m;
	bool baseline_X__m__userInput;

	double delta_baseline__m;
	bool delta_baseline__m__userInput;
    bool delta_baseline_X_tagged;
    bool delta_baseline_Y_tagged;
    bool delta_baseline_Z_tagged;

    bool delta_rotation_X_tagged;
    bool delta_rotation_Y_tagged;
    bool delta_rotation_Z_tagged;


	double baseline_Y__m;
	bool baseline_Y__m__userInput;

	double baseline_ratio;
	bool baseline_ratio__userInput;

	double sensor_X__m; // sensor length sh
	bool sensor_X__m__userInput;

	double sensor_Y__m; // sensor wide sv
	bool sensor_Y__m__userInput;

	double resolution_X__px; // Nh
	bool resolution_X__px__userInput;

	double resolution_Y__px; //Nv
	bool resolution_Y__px__userInput;

	double d1_X__px; //Disparity of depth further away
	bool d1_X__px__userInput;

	double d1_Y__px; //Disparity of depth further away
	bool d1_Y__px__userInput;

	double d2_X__px; //Disparity of closer depth
	bool d2_X__px__userInput;

	double d2_Y__px; //Disparity of closer depth
	bool d2_Y__px__userInput;

	double dH_X__px; // Disparity of Horoptor
	bool dH_X__px__userInput;

	double dH_Y__px; // Disparity of Horoptor
	bool dH_Y__px__userInput;

	double FramesizeDH_X__m; //Size of the camera image area in space
	bool FramesizeDH_X__m__userInput;

	double FramesizeDH_Y__m; //Size of the camera image area in space
	bool FramesizeDH_Y__m__userInput;

	double FramesizeD1_X__m; //Size of the camera image area in space
	bool FramesizeD1_X__m__userInput;

	double FramesizeD1_Y__m; //Size of the camera image area in space
	bool FramesizeD1_Y__m__userInput;

	double FramesizeD2_X__m; //Size of the camera image area in space
	bool FramesizeD2_X__m__userInput;

	double FramesizeD2_Y__m; //Size of the camera image area in space
	bool FramesizeD2_Y__m__userInput;

	double AspectRatio;
	bool AspectRatio__userInput;

	double Pixelsize_X__m; // tilde(sh)
	bool Pixelsize_X__m__userInput;

	double Pixelsize_Y__m; // tilde(sv)
	bool Pixelsize_Y__m__userInput;

	double PixelAspectRatio;
	bool PixelAspectRatio__userInput;

	double delta_d_inaccuracy_ST__px;//ST = Structure tensor inaccuracy, geometrical inaccuracy is additional error.
	bool delta_d_inaccuracy_ST__px__userInput;

	double DoF_D_N__m; // closest distance for which the object is still sharp
	bool DoF_D_N__m__userInput;

	double DoF_D_F__m; // farest distance for which the object is still sharp
	bool DoF_D_F__m__userInput;

	double f_number;
	bool f_number__userInput;

	double DoF_H__m; // auxiliary variable (Hyperfocal distance)
	bool DoF_H__m__userInput;

	double DoF_subject_distance__m;	// distance for which the object would be perfectly focused
	bool DoF_subject_distance__m__userInput;

	double DoF_DoF__m;
	bool DoF_DoF__m__userInput;

    double CircleofConfusion__m;
    bool CircleofConfusion__m__userInput;

    double Cam_X;
	double Cam_Y;
	bool Cam_X__userInput;
	bool Cam_Y__userInput;

	double delta_D1_X_inaccuracy_ST__m;

	double delta_D2_X_inaccuracy_ST__m;

	double delta_DH_X_inaccuracy_ST__m;

	double delta_D1_Y_inaccuracy_ST__m;

	double delta_D2_Y_inaccuracy_ST__m;

	double delta_DH_Y_inaccuracy_ST__m;

	double geometricDepthInaccuracyDH_X__m;

	double geometricDepthInaccuracyDH_Y__m;

    double geometricDepthInaccuracyD1_X__m;

    double geometricDepthInaccuracyD1_Y__m;

    double geometricDepthInaccuracyD2_X__m;

    double geometricDepthInaccuracyD2_Y__m;

    double object_space_angle_X_degree;

    double object_space_angle_Y_degree;

}set;

    void load(ConfigParser &cfg);
	void deleteValid();
	void setValidifUserInput();
	void deleteInvalidUserInputs();
	void changeParameter(int number,double value);
    void save(std::string);
    void expBlender(std::string);
    void expLF_Framework(std::string);
	void compute();
	void console_program();
	void test_parameter_computation();
	bool get_AspectRatio();
	bool get_PixelAspectRatio();
	bool get_PixelSize_X__m();
	bool get_PixelSize_Y__m();
	bool get_resolution_X__px();
	bool get_resolution_Y__px();
	bool get_sensor_X__m();
	bool get_sensor_Y__m();
	bool get_Framesize_DH_X__m();
	bool get_Framesize_DH_Y__m();
	bool get_Framesize_D1_X__m();
	bool get_Framesize_D1_Y__m();
	bool get_Framesize_D2_X__m();
	bool get_Framesize_D2_Y__m();
	bool get_DH_X__m();
	bool get_DH_Y__m();
	bool get_DHopt_X__m();
	bool get_DHopt_Y__m();
	bool get_D1_X__m();
	bool get_D1_Y__m();
	bool get_D2_X__m();
	bool get_D2_Y__m();
	bool get_delta_D_X__m();
	bool get_delta_D_Y__m();
	bool get_delta_d_X__px();
	bool get_delta_d_Y__px();
    bool get_theta_X__pxm();
    bool get_theta_Y__pxm();
	bool get_d2_X__px();
	bool get_d2_Y__px();
	bool get_d1_X__px();
	bool get_d1_Y__px();
	bool get_dH_X__px();
	bool get_dH_Y__px();
	bool get_focalLength_X__px();
	bool get_focalLength_Y__px();
	bool get_focalLength__m();
	bool get_baseline_X__m();
	bool get_baseline_Y__m();
	bool get_baselineRatio();
	bool get_delta_D1_inaccuracy_ST_X__m();
	bool get_delta_D2_inaccuracy_ST_X__m();
	bool get_delta_DH_inaccuracy_ST_X__m();
	bool get_delta_D1_inaccuracy_ST_Y__m();
    bool get_delta_D2_inaccuracy_ST_Y__m();
	bool get_delta_DH_inaccuracy_ST_Y__m();
	bool get_DoF_D_N__m();
	bool get_DoF_D_F__m();
	bool get_f_number();
	bool get_DoF_H__m();
	bool get_DoF_subject_distance__m();
	bool get_DoF_DoF__m();
	bool get_geometricDepthInaccuracyDH_X__m();
	bool get_geometricDepthInaccuracyDH_Y__m();
    bool get_geometricDepthInaccuracyD1_X__m();
    bool get_geometricDepthInaccuracyD1_Y__m();
    bool get_geometricDepthInaccuracyD2_X__m();
    bool get_geometricDepthInaccuracyD2_Y__m();
    bool get_object_space_angle_X_degree();
    bool get_object_space_angle_Y_degree();


//Constructor
LFsetup(ConfigParser & cfg){

		set.delta_D_X__m = cfg.delta_D_X__m; // Depth range
		set.delta_D_X__m__userInput = true;
		set.delta_D_Y__m = cfg.delta_D_Y__m; // Depth range
		set.delta_D_Y__m__userInput = true;
		set.D1_Y__m = cfg.D1_Y__m; // depth further away of the camera
		set.D1_Y__m__userInput = true;
		set.D1_X__m = cfg.D1_X__m; // depth further away of the camera
		set.D1_X__m__userInput = true;
		set.D2_X__m = cfg.D2_X__m; // depth closer to the camera
		set.D2_X__m__userInput = true;
		set.D2_Y__m = cfg.D2_Y__m; // depth closer to the camera
		set.D2_Y__m__userInput = true;
		set.delta_d_X__px = cfg.delta_d_X__px; // Disparity range
		set.delta_d_X__px__userInput = true;
		set.delta_d_Y__px = cfg.delta_d_Y__px; // Disparity range
		set.delta_d_Y__px__userInput = true;
        set.theta_X__pxm = cfg.theta_X__pxm; // multiplication of the focal length and the baseline
        set.theta_X__pxm__userInput = true;
        set.theta_Y__pxm = cfg.theta_Y__pxm; // multiplication of the focal length and the baseline
        set.theta_Y__pxm__userInput = true;
		set.DH_X__m = cfg.DH_X__m; // Depth of Horoptor
		set.DH_X__m__userInput = true;
		set.DH_Y__m = cfg.DH_Y__m; // Depth of Horoptor
		set.DH_Y__m__userInput = true;
		set.focalLength__m = cfg.focalLength__m;
		set.focalLength__m__userInput = true;
		set.focal_length_X__px = cfg.focal_length_X__px;
		set.focal_length_X__px__userInput = true;
		set.focal_length_Y__px = cfg.focal_length_Y__px;
		set.focal_length_Y__px__userInput = true;
		set.baseline_X__m = cfg.baseline_X__m;
		set.baseline_X__m__userInput = true;
		set.baseline_Y__m = cfg.baseline_Y__m;
		set.baseline_Y__m__userInput = true;
		set.baseline_ratio = cfg.baseline_ratio;
		set.baseline_ratio__userInput = true;
		set.sensor_X__m = cfg.sensor_X__m; // sensor length sh
		set.sensor_X__m__userInput = true;
		set.sensor_Y__m = cfg.sensor_Y__m; // sensor wide sv
		set.sensor_Y__m__userInput = true;
		set.resolution_X__px = cfg.resolution_X__px; // Nh
		set.resolution_X__px__userInput = true;
		set.resolution_Y__px = cfg.resolution_Y__px; //Nv
		set.resolution_Y__px__userInput = true;
		set.d1_X__px = cfg.d1_X__px; //Disparity of depth further away
		set.d1_X__px__userInput = true;
		set.d1_Y__px = cfg.d1_Y__px; //Disparity of depth further away
		set.d1_Y__px__userInput = true;
		set.d2_X__px = cfg.d2_X__px; //Disparity of closer depth
		set.d2_X__px__userInput = true;
		set.d2_Y__px = cfg.d2_Y__px; //Disparity of closer depth
		set.d2_Y__px__userInput = true;
		set.dH_X__px = cfg.dH_X__px; // Disparity of Horoptor
		set.dH_X__px__userInput = true;
		set.dH_Y__px = cfg.dH_Y__px; // Disparity of Horoptor
		set.dH_Y__px__userInput = true;
		set.AspectRatio = cfg.AspectRatio;
		set.AspectRatio__userInput = true;
		set.Pixelsize_X__m = cfg.Pixelsize_X__m; // tilde(sh)
		set.Pixelsize_X__m__userInput = true;
		set.Pixelsize_Y__m = cfg.Pixelsize_Y__m; // tilde(sv)
		set.Pixelsize_Y__m__userInput = true;
		set.PixelAspectRatio = cfg.PixelAspectRatio;
		set.PixelAspectRatio__userInput = true;
		set.DoF_D_N__m = cfg.DoF_D_N__m; // closest distance for which the object is still sharp
		set.DoF_D_N__m__userInput = true;
		set.DoF_D_F__m = cfg.DoF_D_F__m; // farest distance for which the object is still sharp
		set.DoF_D_F__m__userInput = true;
		set.f_number = cfg.f_number;
		set.f_number__userInput = true;
		set.DoF_H__m = cfg.DoF_H__m;				// auxiliary variable (Hyperfocal distance)
		set.DoF_H__m__userInput = true;
		set.DoF_subject_distance__m = cfg.DoF_subject_distance__m;	// distance for which the object would be perfectly focused
		set.DoF_subject_distance__m__userInput = true;
		set.DoF_DoF__m = cfg.DoF_DoF__m;
		set.DoF_DoF__m__userInput = true;
        set.Cam_X = cfg.CamX;
        set.Cam_Y = cfg.CamY;
        set.Cam_X__userInput = true;
        set.Cam_Y__userInput = true;
        set.delta_d_inaccuracy_ST__px = cfg.delta_d_inaccuracy_ST__px;
        set.delta_d_inaccuracy_ST__px__userInput = true;
        set.delta_baseline__m = cfg.delta_b__m;
		set.delta_focal_length__m = cfg.delta_f__m;
		set.delta_baseline__m__userInput = true;
		set.delta_focal_length__m__userInput = true;

                
// Initialize non input parameter;
		set.FramesizeDH_X__m = 0;
		set.FramesizeDH_Y__m = 0;
		set.FramesizeDH_X__m__userInput = false;
		set.FramesizeDH_Y__m__userInput = false;
		set_valid.FramesizeDH_X__m = false;
		set_valid.FramesizeDH_Y__m = false;
		set.FramesizeD1_X__m = 0;
		set.FramesizeD1_Y__m = 0;
		set.FramesizeD1_X__m__userInput = false;
		set.FramesizeD1_Y__m__userInput = false;
		set_valid.FramesizeD1_X__m = false;
		set_valid.FramesizeD1_Y__m = false;
		set.FramesizeD2_X__m = 0;
		set.FramesizeD2_Y__m = 0;
		set.FramesizeD2_X__m__userInput = false;
		set.FramesizeD2_Y__m__userInput = false;
		set_valid.FramesizeD2_X__m = false;
		set_valid.FramesizeD2_Y__m = false;
		set.DHopt_X__m = 0;
		set.DHopt_X__m__userInput = false;
		set_valid.DHopt_X__m = false;
		set.DHopt_Y__m = 0;
		set.DHopt_Y__m__userInput = false;
		set_valid.DHopt_Y__m = false;
		set.geometricDepthInaccuracyDH_X__m = 0;
		set.geometricDepthInaccuracyDH_Y__m = 0;
		set_valid.geometricDepthInaccuracyDH_X__m = false;
		set_valid.geometricDepthInaccuracyDH_Y__m = false;
        set.object_space_angle_X_degree = 0;
        set.object_space_angle_Y_degree = 0;
        set_valid.object_space_angle_X_degree = false;
        set_valid.object_space_angle_Y_degree = false;
        set.delta_baseline_X_tagged = true;
        set.delta_baseline_Y_tagged = true;
        set.delta_baseline_Z_tagged = true;
        set.delta_d_inaccuracy_ST__px = 0.01;
        set.delta_d_inaccuracy_ST__px__userInput = true;

        set.geometricDepthInaccuracyD1_X__m = 0;
        set.geometricDepthInaccuracyD2_X__m = 0;
        set.geometricDepthInaccuracyDH_X__m = 0;
        set.geometricDepthInaccuracyD1_Y__m = 0;
        set.geometricDepthInaccuracyD2_Y__m = 0;
        set.geometricDepthInaccuracyDH_Y__m = 0;

        set.delta_D1_X_inaccuracy_ST__m = 0;
        set.delta_D2_X_inaccuracy_ST__m = 0;
        set.delta_DH_X_inaccuracy_ST__m = 0;
        set.delta_D1_Y_inaccuracy_ST__m = 0;
        set.delta_D2_Y_inaccuracy_ST__m = 0;
        set.delta_DH_Y_inaccuracy_ST__m = 0;

}

LFsetup(){

    set.object_space_angle_X_degree = 0;
    set.object_space_angle_Y_degree = 0;
    set_valid.object_space_angle_X_degree = false;
    set_valid.object_space_angle_Y_degree = false;
	set_valid.geometricDepthInaccuracyDH_X__m = false;
	set_valid.geometricDepthInaccuracyDH_Y__m = false;
	set.delta_baseline__m = 0;
	set.delta_focal_length__m = 0;
	set.delta_baseline__m__userInput = false;
	set.delta_focal_length__m__userInput = false;
	set_valid.delta_baseline__m = false;
	set_valid.delta_focal_length__m = false;

	set.delta_D_X__m = 0;
	set.delta_D_X__m__userInput = false;
	set_valid.delta_D_X__m = false;
	set.delta_D_Y__m = 0;
	set.delta_D_Y__m__userInput = false;
	set_valid.delta_D_Y__m = false;
	set.D1_Y__m = 0;
	set.D1_Y__m__userInput = false;
	set_valid.D1_Y__m = false;
	set.D1_X__m = 0;
	set.D1_X__m__userInput = false;
	set_valid.D1_X__m = false;
	set.D2_X__m = 0;
	set.D2_X__m__userInput = false;
	set_valid.D2_X__m = false;
	set.D2_Y__m = 0;
	set.D2_Y__m__userInput = false;
	set_valid.D2_Y__m = false;
	set.delta_d_X__px = 0;
	set.delta_d_X__px__userInput = false;
	set_valid.delta_d_X__px = false;
	set.delta_d_Y__px = 0;
	set.delta_d_Y__px__userInput = false;
	set_valid.delta_d_Y__px = false;
    set.theta_X__pxm = 0;
    set.theta_X__pxm__userInput = false;
    set_valid.theta_X__pxm = false;
    set.theta_Y__pxm = 0;
    set.theta_Y__pxm__userInput = false;
    set_valid.theta_Y__pxm = false;
	set.DH_X__m = 0;
	set.DH_X__m__userInput = false;
	set_valid.DH_X__m = false;
	set.DH_Y__m = 0;
	set.DH_Y__m__userInput = false;
	set_valid.DH_Y__m = false;
	set.DHopt_X__m = 0;
	set.DHopt_X__m__userInput = false;
	set_valid.DHopt_X__m = false;
	set.DHopt_Y__m = 0;
	set.DHopt_Y__m__userInput = false;
	set_valid.DHopt_Y__m = false;
	set.focalLength__m = 0;
	set.focalLength__m__userInput = false;
	set_valid.focalLength__m = false;
	set.focal_length_X__px = 0;
	set.focal_length_X__px__userInput = false;
	set_valid.focal_length_X__px = false;
	set.focal_length_Y__px = 0;
	set.focal_length_Y__px__userInput = false;
	set_valid.focal_length_Y__px = false;
	set.baseline_X__m = 0;
	set.baseline_X__m__userInput = false;
	set_valid.baseline_X__m = false;
	set.baseline_Y__m = 0;
	set.baseline_Y__m__userInput = false;
	set_valid.baseline_Y__m = false;
	set.baseline_ratio = 0;
	set.baseline_ratio__userInput = false;
	set_valid.baseline_ratio = false;
	set.sensor_X__m = 0;
	set.sensor_X__m__userInput = false;
	set_valid.sensor_X__m = false;
	set.sensor_Y__m = 0;
	set.sensor_Y__m__userInput = false;
	set_valid.sensor_Y__m = false;
	set.resolution_X__px= 0;
	set.resolution_X__px__userInput = false;
	set_valid.resolution_X__px = false;
	set.resolution_Y__px = 0;
	set.resolution_Y__px__userInput = false;
	set_valid.resolution_Y__px = false;
	set.d1_X__px = 0;
	set.d1_X__px__userInput = false;
	set_valid.d1_X__px = false;
	set.d1_Y__px = 0;
	set.d1_Y__px__userInput = false;
	set_valid.d1_Y__px = false;
	set.d2_X__px = 0;
	set.d2_X__px__userInput = false;
	set_valid.d2_X__px = false;
	set.d2_Y__px = 0;
	set.d2_Y__px__userInput = false;
	set_valid.d2_Y__px = false;
	set.dH_X__px = 0;
	set.dH_X__px__userInput = false;
	set_valid.dH_X__px = false;
	set.dH_Y__px = 0;
	set.dH_Y__px__userInput = false;
	set_valid.dH_Y__px = false;
	set.AspectRatio = 0;
	set.AspectRatio__userInput = false;
	set_valid.AspectRatio = false;
	set.Pixelsize_X__m = 0;
	set.Pixelsize_X__m__userInput = false;
	set_valid.Pixelsize_X__m = false;
	set.Pixelsize_Y__m = 0;
	set.Pixelsize_Y__m__userInput = false;
	set_valid.Pixelsize_Y__m = false;
	set.PixelAspectRatio = 0;
	set.PixelAspectRatio__userInput = false;
	set_valid.PixelAspectRatio = false;
	set.DoF_D_N__m = 0;
	set.DoF_D_N__m__userInput = false;
	set_valid.DoF_D_N__m = false;
	set.DoF_D_F__m = 0;
	set.DoF_D_F__m__userInput = false;
	set_valid.DoF_D_F__m = false;
	set.f_number = 0;
	set.f_number__userInput = false;
	set_valid.f_number = false;
	set.DoF_H__m = 0;
	set.DoF_H__m__userInput = false;
	set_valid.DoF_H__m = false;
	set.DoF_subject_distance__m = 0;
	set.DoF_subject_distance__m__userInput = false;
	set_valid.DoF_subject_distance__m = false;
	set.DoF_DoF__m = 0;
	set.DoF_DoF__m__userInput = false;
	set_valid.DoF_DoF__m = false;
	set.FramesizeDH_X__m = 0;
	set.FramesizeDH_Y__m = 0;
	set.FramesizeDH_X__m__userInput = false;
	set.FramesizeDH_Y__m__userInput = false;
	set_valid.FramesizeDH_X__m = false;
	set_valid.FramesizeDH_Y__m = false;
	set.FramesizeD1_X__m = 0;
	set.FramesizeD1_Y__m = 0;
	set.FramesizeD1_X__m__userInput = false;
	set.FramesizeD1_Y__m__userInput = false;
	set_valid.FramesizeD1_X__m = false;
	set_valid.FramesizeD1_Y__m = false;
	set.FramesizeD2_X__m = 0;
	set.FramesizeD2_Y__m = 0;
	set.FramesizeD2_X__m__userInput = false;
	set.FramesizeD2_Y__m__userInput = false;
	set_valid.FramesizeD2_X__m = false;
	set_valid.FramesizeD2_Y__m = false;
    set.Cam_X = 0;
	set.Cam_Y = 0;
	set.Cam_X__userInput = false;
	set.Cam_Y__userInput = false;
	set_valid.Cam_X = false;
	set_valid.Cam_Y = false;
    set.delta_d_inaccuracy_ST__px = 0;
    set.delta_d_inaccuracy_ST__px__userInput = false;
    set_valid.delta_d_inaccuracy_ST__px = false;
    set.delta_baseline_X_tagged = true;
    set.delta_baseline_Y_tagged = true;
    set.delta_baseline_Z_tagged = true;
    set.delta_d_inaccuracy_ST__px = 0.01;
    set.delta_d_inaccuracy_ST__px__userInput = true;
    set_valid.delta_d_inaccuracy_ST__px = true;
    set.geometricDepthInaccuracyD1_X__m = 0;
    set.geometricDepthInaccuracyD2_X__m = 0;
    set.geometricDepthInaccuracyDH_X__m = 0;
    set.geometricDepthInaccuracyD1_Y__m = 0;
    set.geometricDepthInaccuracyD2_Y__m = 0;
    set.geometricDepthInaccuracyDH_Y__m = 0;
    set.delta_D1_X_inaccuracy_ST__m = 0;
    set.delta_D2_X_inaccuracy_ST__m = 0;
    set.delta_DH_X_inaccuracy_ST__m = 0;
    set.delta_D1_Y_inaccuracy_ST__m = 0;
    set.delta_D2_Y_inaccuracy_ST__m = 0;
    set.delta_DH_Y_inaccuracy_ST__m = 0;
}

private:

    inline double _compute_focalLength__m_from_theta(double theta__pxm, double baseline__m, double PixelSize__m);
    inline double _compute_focalLength__m(double focal_length__px, double sensor__m, double resolution__px);

    inline double _compute_baseline__m(double theta__pxm, double focalLength_m, double PixelSize__m);

	inline double _compute_baseline_X__m(double AspectRatio, double baseline_Y__m);
	inline double _compute_baseline_Y__m(double AspectRatio, double baseline_X__m);

    inline double _compute_D1__m(double theta__m_m,double DH__m,double delta_d__px);
    inline double _compute_D2__m(double theta__m_m,double DH__m,double delta_d__px);

    inline double _compute_theta__pxm_fromD(double delta_D__m,double DH__m,double delta_d__px);
    inline double _compute_theta__pxm_from_d(double delta_D__m,double dH__m,double delta_d__px);
    inline double _compute_theta__pxm(double focalLength__m, double baseline__m, double PixelSize__m);

    inline double _compute_DH__m_from_D1(double D1__m, double theta__pxm, double delta_d__px);
    inline double _compute_DH__m_from_D2(double D2__m, double theta__pxm, double delta_d__px);
    inline double _compute_DH__m_from_dH(double dH__px, double theta__pxm);

    inline double _compute_dH__px(double theta__pxm, double DH__m);

    inline double _compute_DHopt__m(double focalLength__px,double baseline__m);

    inline double _compute_resolution__px(double delta_D__m, double theta__pxm,double sensor__px,double delta_d__m,double DH__m, double PixelSize__m);
    inline double _compute_resolution__px_from_D1(double DH__m, double theta__pxm,double delta_D__m,double sensor__px,double D1__m, double PixelSize__m);
    inline double _compute_resolution__px_from_D2(double DH__m, double theta__pxm,double delta_D__m,double sensor__px,double D2__m, double PixelSize__m);

	inline double _compute_d2__px(double delta_d__px, double d1__px);
	inline double _compute_d1__px(double delta_d__px, double d2__px);

	inline double _compute_d2__px_from_DH(double dH__px, double delta_d__px);
	inline double _compute_d1__px_from_DH(double dH__px, double delta_d__px);

	inline double _compute_delta_d__px_from_d2(double d2__px, double dH__px);
	inline double _compute_delta_d__px_from_d1(double d1__px, double dH__px);
    inline double _compute_delta_d__px(double delta_D__m, double theta__pxm,double DH__m);
    inline double _compute_delta_d__px_from_D1(double DH__m, double theta__pxm,double D1__m);
    inline double _compute_delta_d__px_from_D2(double DH__m, double theta__pxm,double D2__m);

	inline double _compute_delta_D__m(double D1__m, double D2__m);
	inline double _compute_D1__m(double delta_D_m, double D2__px);
	inline double _compute_D2__m(double delta_D_m, double D1__px);

    inline double _compute_Framesize__m(double sensor_X__m, double focalLength__m,double DH__m,double baseline__m,double cams);

	inline double _compute_resolution_X__m(double AspectRatio, double resolution_Y__px);
	inline double _compute_resolution_Y__m(double AspectRatio, double resolution_X__px);

	inline double _compute_AspectRatio(double resolution_X__px, double resolution_Y__px);
	inline double _compute_PixelAspectRatio(double PixelSize_X__m, double PixelSize_Y__m);

    inline double _compute_sensor__m(double delta_D__m, double theta__pxm,double resolution__m,double delta_d__px,double DH__m, double PixelSize__m);
    inline double _compute_sensor__m_from_D1(double DH__m, double theta__pxm,double resolution__m,double delta_d__px,double D1__m, double PixelSize__m);
    inline double _compute_sensor__m_from_D2(double DH__m, double theta__pxm,double resolution__m,double delta_d__px,double D2__m, double PixelSize__m);

	inline double _compute_sensor_X__m(double resolution_X__px, double resolution_Y__px,double sensor_Y__m);
	inline double _compute_sensor_Y__m(double resolution_X__px, double resolution_Y__px,double sensor_X__m);
	inline double _compute_sensor_X__m(double resolution_X__px, double PixelSize_X__m);
	inline double _compute_sensor_Y__m(double resolution_Y__px, double PixelSize_Y__m);

	inline double _compute_PixelSize_X__m(double PixelAspectRatio, double PixelSize_Y__m);
	inline double _compute_PixelSize_Y__m(double PixelAspectRatio, double PixelSize_X__m);
	inline double _compute_PixelSize__m_from_sensor(double resolution__px, double sensor__m);
    inline double _compute_Pixelsize__m(double theta__pxm, double focalLength__m, double baseline__m);

	inline double _compute_focalLength__px(double focalLength__m, double sensor__m, double resolution__px);
    inline double _compute_focalLength__px(double baseline__m, double theta__pxm);

    inline double _compute_d2__px_from_theta(double theta__pxm, double D2__m);
    inline double _compute_d1__px_from_theta(double theta__pxm, double D1__m);
	inline double _compute_dH__px_from_d1d2(double d1__px, double d2__px);

	inline double _compute_delta_D_inaccuracy__m(double D__m, double focalLength__px, double baseline__m, double delta_d_inaccuracy__px);
	inline double _compute_resolution_from_Sen_and_Pix__px(double sensor__m,double Pixelsize__m);

	inline double _compute_DoF_H__m(double focalLength__m, double f_number, double PixelSize__m);

	inline double _compute_DoF_D_N__m(double DoF_D_F__m, double DoF_DoF__m);
	inline double _compute_DoF_D_N__m(double DoF_H__m, double DoF_subject_distance__m, double focalLength__m);

	inline double _compute_DoF_D_F__m(double DoF_D_N__m, double DoF_DoF__m);
	inline double _compute_DoF_D_F__m(double DoF_H__m, double DoF_subject_distance__m, double focalLength__m);

	inline double _compute_DoF_DoF__m(double DoF_D_N__m, double DoF_D_F__m);

	inline double _geometricDepthInaccuracy_m(double DH__m,double baseline__m, double delta_baseline__m,double focal_length__m, double delta_focal_length__m);

    inline double _object_space_angle_degree(double sensor__m, double focal_length__m);

};



