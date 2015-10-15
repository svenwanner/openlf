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

#include <lfcamconfigurator.h>
#ifdef _MSC_VER
#include "ui_lfcamconfigurator_windows.h"
#elif __GNUC__
#include "ui_lfcamconfigurator_linux.h"
#endif

void LFCamConfigurator::get_UIvalues(){

    setup->set.resolution_X__px = ui->lineEdit_Resolution_X__px->text().toDouble();
    setup->set.AspectRatio = ui->lineEdit_AspectRatio->text().toDouble();
    setup->set.Pixelsize_X__m = (ui->lineEdit_PixelSize_X->text().toDouble())/(double)1000000;
    setup->set.PixelAspectRatio = ui->lineEdit_PixelAspectRatio->text().toDouble();
    setup->set.sensor_X__m = (ui->lineEdit_SensorSize_X->text().toDouble())/(double)1000;
    setup->set.focalLength__m = (ui->lineEdit_focalLength->text().toDouble())/(double)1000;
    setup->set.baseline_X__m = (ui->lineEdit_baseline_X->text().toDouble())/(double)1000;

    setup->set.theta_X__pxm = ui->lineEdit_theta_X->text().toDouble();

    setup->set.D1_X__m = ui->lineEdit_D1_X->text().toDouble();
    setup->set.d1_X__px = ui->lineEdit_d1_X->text().toDouble();
    setup->set.D2_X__m = ui->lineEdit_D2_X->text().toDouble();
    setup->set.d2_X__px = ui->lineEdit_d2_X->text().toDouble();
    setup->set.DH_X__m = ui->lineEdit_DH_X->text().toDouble();
    setup->set.dH_X__px = ui->lineEdit_dH_X->text().toDouble();
    setup->set.delta_D_X__m = ui->lineEdit_delta_D_X->text().toDouble();
    setup->set.delta_d_X__px = ui->lineEdit_delta_d_X->text().toDouble()/(double)2;
    setup->set.DoF_D_N__m = ui->lineEdit_D_N->text().toDouble();
    setup->set.DoF_D_F__m = ui->lineEdit_D_F->text().toDouble();
    setup->set.f_number = ui->lineEdit_f_number->text().toDouble();
    setup->set.DoF_H__m = ui->lineEdit_H_DoF->text().toDouble();
    setup->set.DoF_subject_distance__m = ui->lineEdit_subject_distance->text().toDouble();
    setup->set.DoF_DoF__m = ui->lineEdit_DoF->text().toDouble();
    setup->set.CircleofConfusion__m = ui->lineEdit_coc->text().toDouble()/(double)1000000;
    setup->set.resolution_Y__px = ui->lineEdit_Resolution_Y__px->text().toDouble();
    setup->set.Pixelsize_Y__m = ui->lineEdit_PixelSize_Y->text().toDouble()/(double)1000000;
    setup->set.sensor_Y__m = ui->lineEdit_SensorSize_Y->text().toDouble()/(double)1000;
    setup->set.baseline_Y__m = (ui->lineEdit_baseline_Y->text().toDouble())/(double)1000;

    setup->set.theta_Y__pxm = ui->lineEdit_theta_Y->text().toDouble();

    setup->set.D1_Y__m = ui->lineEdit_D1_Y->text().toDouble();
    setup->set.d1_Y__px = ui->lineEdit_d1_Y->text().toDouble();
    setup->set.D2_Y__m = ui->lineEdit_D2_Y->text().toDouble();
    setup->set.d2_Y__px = ui->lineEdit_d2_Y->text().toDouble();
    setup->set.DH_Y__m = ui->lineEdit_DH_Y->text().toDouble();
    setup->set.dH_Y__px = ui->lineEdit_dH_Y->text().toDouble();
    setup->set.delta_D_Y__m = ui->lineEdit_delta_D_Y->text().toDouble();
    setup->set.delta_d_Y__px = ui->lineEdit_delta_d_Y->text().toDouble()/(double)2;
    setup->set.Cam_X = ui->lineEdit_Cam_X->text().toDouble();
    setup->set.Cam_Y = ui->lineEdit_Cam_Y->text().toDouble();
    setup->set.delta_d_inaccuracy_ST__px = ui->lineEdit_stprecision->text().toDouble();

    setup->set.resolution_X__px__userInput = ui->checkBox_Resolution_X__px->isChecked();
    setup->set.AspectRatio__userInput = ui->checkBox_AspectRatio->isChecked();
    setup->set.Pixelsize_X__m__userInput = ui->checkBox_PixelSize_X->isChecked();
    setup->set.PixelAspectRatio__userInput = ui->checkBox_PixelAspectRatio->isChecked();
    setup->set.sensor_X__m__userInput = ui->checkBox_SensorSize_X->isChecked();
    setup->set.focalLength__m__userInput = ui->checkBox_focalLength->isChecked();
    setup->set.baseline_X__m__userInput = ui->checkBox_baseline_X->isChecked();
    setup->set.D1_X__m__userInput = ui->checkBox_D1_X->isChecked();
    setup->set.d1_X__px__userInput = ui->checkBox_d1_X->isChecked();
    setup->set.D2_X__m__userInput = ui->checkBox_D2_X->isChecked();
    setup->set.d2_X__px__userInput = ui->checkBox_d2_X->isChecked();
    setup->set.DH_X__m__userInput = ui->checkBox_DH_X->isChecked();
    setup->set.dH_X__px__userInput = ui->checkBox_dH_X->isChecked();
    setup->set.delta_D_X__m__userInput = ui->checkBox_delta_D_X->isChecked();
    setup->set.delta_d_X__px__userInput = ui->checkBox_delta_d_X->isChecked();
    setup->set.f_number__userInput = ui->checkBox_f_number->isChecked();
    setup->set.DoF_subject_distance__m__userInput = ui->checkBox_subject_distance->isChecked();
    setup->set.CircleofConfusion__m__userInput = ui->checkBox_coc->isChecked();
    setup->set.resolution_Y__px__userInput = ui->checkBox_Resolution_Y->isChecked();
    setup->set.Pixelsize_Y__m__userInput = ui->checkBox_PixelSize_Y->isChecked();
    setup->set.sensor_Y__m__userInput = ui->checkBox_SensorSize_Y->isChecked();
    setup->set.baseline_Y__m__userInput = ui->checkBox_baseline_Y->isChecked();
    setup->set.D1_Y__m__userInput = ui->checkBox_D1_Y->isChecked();
    setup->set.d1_Y__px__userInput = ui->checkBox_d1_Y->isChecked();
    setup->set.D2_Y__m__userInput = ui->checkBox_D2_Y->isChecked();
    setup->set.d2_Y__px__userInput = ui->checkBox_d2_Y->isChecked();
    setup->set.DH_Y__m__userInput = ui->checkBox_DH_Y->isChecked();
    setup->set.dH_Y__px__userInput = ui->checkBox_dH_Y->isChecked();
    setup->set.delta_D_Y__m__userInput = ui->checkBox_delta_D_Y->isChecked();
    setup->set.delta_d_Y__px__userInput = ui->checkBox_delta_d_Y->isChecked();
    setup->set.Cam_X__userInput = ui->checkBox_camX->isChecked();
    setup->set.Cam_Y__userInput = ui->checkBox_camY->isChecked();
    setup->set.delta_d_inaccuracy_ST__px__userInput = ui->checkBox_stprecision->isChecked();

    setup->set.delta_baseline_X_tagged = ui->checkBox_baseline_jitter_X->isChecked();
    setup->set.delta_baseline_Y_tagged = ui->checkBox_baseline_jitter_Y->isChecked();
    setup->set.delta_baseline_Z_tagged = ui->checkBox_baseline_jitter_Z->isChecked();

    setup->set.delta_rotation_X_tagged = ui->checkBox_rotation_jitter_X->isChecked();
    setup->set.delta_rotation_Y_tagged = ui->checkBox_rotation_jitter_Y->isChecked();
    setup->set.delta_rotation_Z_tagged = ui->checkBox_rotation_jitter_Z->isChecked();

    setup->set.delta_baseline__m = ui->lineEdit_baseline_jitter->text().toDouble()/(double)1000;
    setup->set.delta_focal_length__m = ui->lineEdit_focallength_jitter->text().toDouble()/(double)1000;

    setup->set.delta_baseline__m__userInput = ui->checkBox_baseline_jitter->isChecked();
    setup->set.delta_focal_length__m__userInput =  ui->checkBox_focallength_jitter->isChecked();

    setup->set.delta_rotation__deg = ui->lineEdit_rotation_jitter->text().toDouble()*(double)3.14/(double)180;
    setup->set.delta_rotation__deg__userInput =  ui->checkBox_rotation_jitter->isChecked();
}
