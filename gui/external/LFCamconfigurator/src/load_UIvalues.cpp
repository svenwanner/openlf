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

#include "lfcamconfigurator.h"

#ifdef _MSC_VER
#include "ui_lfcamconfigurator_windows.h"
#elif __GNUC__
#include "ui_lfcamconfigurator_linux.h"
#endif

#include <iostream>

void LFCamConfigurator::load() {



   QString fileName = QFileDialog::getOpenFileName(this, tr("Open Configuration File"), "/home", tr(".ini Files (*.ini)"));
   if (fileName.trimmed().isEmpty()){
       std::cout << "nothing to load" << std::endl;
   }
   else{
       ConfigParser cfg(fileName.toStdString());
       setup->load(cfg);

       resetUI();
       set_UIvalues();

       ui->horizontalSlider_focalLength->setValue(33);
       ui->horizontalSlider_baseline_X->setValue(33);
       ui->horizontalSlider_baseline_Y->setValue(33);
       ui->horizontalSlider_dH_X->setValue(33);
       ui->horizontalSlider_dH_Y->setValue(33);
       ui->horizontalSlider_subject_distance->setValue(33);

       update();
   }

}

void LFsetup::load(ConfigParser & cfg){

        set.delta_D_X__m = cfg.delta_D_X__m; // Depth range
        set.delta_D_X__m__userInput = true;
        set.delta_D_Y__m = cfg.delta_D_Y__m; // Depth range
        set.delta_D_Y__m__userInput = true;
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
        set.dH_X__px = cfg.dH_X__px; // Disparity of Horoptor
        std::cout << set.dH_X__px << std::endl;
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
        set.CircleofConfusion__m = cfg.CircleofConfusion__m;
        set.CircleofConfusion__m__userInput = true;
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
        set.delta_rotation__deg = cfg.delta_rot__deg;
        set.delta_rotation__deg__userInput = true;
        set.delta_d_inaccuracy_ST__px = cfg.delta_d_inaccuracy_ST__px;
        set.delta_d_inaccuracy_ST__px__userInput = true;


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
        set.sensor_Y__m = 0;

        deleteValid();
        setValidifUserInput();
        deleteInvalidUserInputs();
}
