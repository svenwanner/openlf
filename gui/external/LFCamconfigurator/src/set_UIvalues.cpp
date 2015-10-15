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



void LFCamConfigurator::set_UIvalues(){


    ui->lineEdit_Resolution_X__px->setText(QString::number(roundf(setup->set.resolution_X__px* 1000000)/1000000, 'g', 6));
    ui->lineEdit_AspectRatio->setText(QString::number(roundf(setup->set.AspectRatio* 1000000)/1000000, 'g', 6));
    ui->lineEdit_PixelSize_X->setText(QString::number((double)1000000*roundf(setup->set.Pixelsize_X__m* 1000000000)/1000000000, 'g', 6));
    ui->lineEdit_PixelAspectRatio->setText(QString::number(roundf(setup->set.PixelAspectRatio* 1000000)/1000000, 'g', 6));
    ui->lineEdit_SensorSize_X->setText(QString::number((double)1000*roundf(setup->set.sensor_X__m* 1000000000)/1000000000, 'g', 6));
    ui->lineEdit_Framesize_X_at_DH->setText(QString::number(roundf(setup->set.FramesizeDH_X__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_focalLength->setText(QString::number((double)1000*roundf(setup->set.focalLength__m * 1000000000)/1000000000, 'g', 6));
    ui->lineEdit_baseline_X->setText(QString::number((double)1000*roundf(setup->set.baseline_X__m* 1000000000)/1000000000, 'g', 6));
    ui->lineEdit_theta_X->setText(QString::number(roundf(setup->set.theta_X__pxm* 1000000)/1000000, 'g', 6));
    ui->lineEdit_D1_X->setText(QString::number(roundf(setup->set.D1_X__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_d1_X->setText(QString::number(roundf(setup->set.d1_X__px* 1000000)/1000000, 'g', 6));
    ui->lineEdit_D2_X->setText(QString::number(roundf(setup->set.D2_X__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_d2_X->setText(QString::number(roundf(setup->set.d2_X__px* 1000000)/1000000, 'g', 6));
    ui->lineEdit_DH_X->setText(QString::number(roundf(setup->set.DH_X__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_dH_X->setText(QString::number(roundf(setup->set.dH_X__px* 1000000)/1000000, 'g', 6));
    ui->lineEdit_DHopt_X->setText(QString::number(roundf(setup->set.DHopt_X__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_delta_D_X->setText(QString::number(roundf(setup->set.delta_D_X__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_delta_d_X->setText(QString::number((double)2*roundf(setup->set.delta_d_X__px* 1000000)/1000000, 'g', 6));
    ui->lineEdit_D_N->setText(QString::number(roundf(setup->set.DoF_D_N__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_D_F->setText(QString::number(roundf(setup->set.DoF_D_F__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_f_number->setText(QString::number(roundf(setup->set.f_number* 1000000)/1000000, 'g', 6));
    ui->lineEdit_H_DoF->setText(QString::number(roundf(setup->set.DoF_H__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_subject_distance->setText(QString::number(roundf(setup->set.DoF_subject_distance__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_DoF->setText(QString::number(roundf(setup->set.DoF_DoF__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_coc->setText(QString::number((double)1000000*roundf(setup->set.CircleofConfusion__m* 1000000000)/1000000000, 'g', 6));
    ui->lineEdit_Resolution_Y__px->setText(QString::number(roundf(setup->set.resolution_Y__px* 1000000)/1000000, 'g', 6));
    ui->lineEdit_PixelSize_Y->setText(QString::number((double)1000000*roundf(setup->set.Pixelsize_Y__m* 1000000000)/1000000000, 'g', 6));
    ui->lineEdit_SensorSize_Y->setText(QString::number((double)1000*roundf(setup->set.sensor_Y__m* 1000000000)/1000000000, 'g', 6));
    ui->lineEdit_Framesize_Y_at_DH->setText(QString::number(roundf(setup->set.FramesizeDH_Y__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_baseline_Y->setText(QString::number((double)1000*roundf(setup->set.baseline_Y__m* 1000000000)/1000000000, 'g', 6));
    ui->lineEdit_theta_Y->setText(QString::number(roundf(setup->set.theta_Y__pxm* 1000000)/1000000, 'g', 6));
    ui->lineEdit_D1_Y->setText(QString::number(roundf(setup->set.D1_Y__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_d1_Y->setText(QString::number(roundf(setup->set.d1_Y__px* 1000000)/1000000, 'g', 6));
    ui->lineEdit_D2_Y->setText(QString::number(roundf(setup->set.D2_Y__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_d2_Y->setText(QString::number(roundf(setup->set.d2_Y__px* 1000000)/1000000, 'g', 6));
    ui->lineEdit_DH_Y->setText(QString::number(roundf(setup->set.DH_Y__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_dH_Y->setText(QString::number(roundf(setup->set.dH_Y__px* 1000000)/1000000, 'g', 6));
    ui->lineEdit_DHopt_Y->setText(QString::number(roundf(setup->set.DHopt_Y__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_delta_D_Y->setText(QString::number(roundf(setup->set.delta_D_Y__m* 1000000)/1000000, 'g', 6));
    ui->lineEdit_delta_d_Y->setText(QString::number((double)2*roundf(setup->set.delta_d_Y__px* 1000000)/1000000, 'g', 6));
    ui->lineEdit_Cam_X->setText(QString::number(roundf(setup->set.Cam_X* 1000000)/1000000, 'g', 6));
    ui->lineEdit_Cam_Y->setText(QString::number(roundf(setup->set.Cam_Y* 1000000)/1000000, 'g', 6));
    ui->lineEdit_AperturAngle_X->setText(QString::number(roundf(setup->set.object_space_angle_X_degree* 1000000)/1000000, 'g', 6));
    ui->lineEdit_AperturAngle_Y->setText(QString::number(roundf(setup->set.object_space_angle_Y_degree* 1000000)/1000000, 'g', 6));
    ui->lineEdit_stprecision->setText(QString::number(roundf(setup->set.delta_d_inaccuracy_ST__px* 1000000)/1000000, 'g', 6));

    ui->lineEdit_geoH1->setText(QString::number(roundf(setup->set.geometricDepthInaccuracyD1_X__m*100000.0)/100000.0, 'g', 6));
    ui->lineEdit_geoV1->setText(QString::number(roundf(setup->set.geometricDepthInaccuracyD1_Y__m*100000.0)/100000.0, 'g', 6));
    ui->lineEdit_geoH2->setText(QString::number(roundf(setup->set.geometricDepthInaccuracyD2_X__m*100000.0)/100000.0, 'g', 6));
    ui->lineEdit_geoV2->setText(QString::number(roundf(setup->set.geometricDepthInaccuracyD2_Y__m*100000.0)/100000.0, 'g', 6));
    ui->lineEdit_geoHH->setText(QString::number(roundf(setup->set.geometricDepthInaccuracyDH_X__m*100000.0)/100000.0, 'g', 6));
    ui->lineEdit_geoVH->setText(QString::number(roundf(setup->set.geometricDepthInaccuracyDH_Y__m*100000.0)/100000.0, 'g', 6));

    ui->lineEdit_stH1->setText(QString::number(roundf(setup->set.delta_D1_X_inaccuracy_ST__m*100000.0)/100000.0, 'g', 6));
    ui->lineEdit_stV1->setText(QString::number(roundf(setup->set.delta_D1_Y_inaccuracy_ST__m*100000.0)/100000.0, 'g', 6));
    ui->lineEdit_stH2->setText(QString::number(roundf(setup->set.delta_D2_X_inaccuracy_ST__m*100000.0)/100000.0, 'g', 6));
    ui->lineEdit_stV2->setText(QString::number(roundf(setup->set.delta_D2_Y_inaccuracy_ST__m*100000.0)/100000.0, 'g', 6));
    ui->lineEdit_stHH->setText(QString::number(roundf(setup->set.delta_DH_X_inaccuracy_ST__m*100000.0)/100000.0, 'g', 6));
    ui->lineEdit_stVH->setText(QString::number(roundf(setup->set.delta_DH_Y_inaccuracy_ST__m*100000.0)/100000.0, 'g', 6));

    ui->checkBox_Resolution_X__px->setChecked(setup->set.resolution_X__px__userInput);
    ui->checkBox_AspectRatio->setChecked(setup->set.AspectRatio__userInput);
    ui->checkBox_PixelSize_X->setChecked(setup->set.Pixelsize_X__m__userInput);
    ui->checkBox_PixelAspectRatio->setChecked(setup->set.PixelAspectRatio__userInput);
    ui->checkBox_SensorSize_X->setChecked(setup->set.sensor_X__m__userInput);
    ui->checkBox_focalLength->setChecked(setup->set.focalLength__m__userInput);
    ui->checkBox_baseline_X->setChecked(setup->set.baseline_X__m__userInput);
    ui->checkBox_D1_X->setChecked(setup->set.D1_X__m__userInput);
    ui->checkBox_d1_X->setChecked(setup->set.d1_X__px__userInput);
    ui->checkBox_D2_X->setChecked(setup->set.D2_X__m__userInput);
    ui->checkBox_d2_X->setChecked(setup->set.d2_X__px__userInput);
    ui->checkBox_DH_X->setChecked(setup->set.DH_X__m__userInput);
    ui->checkBox_dH_X->setChecked(setup->set.dH_X__px__userInput);
    ui->checkBox_coc->setChecked(setup->set.CircleofConfusion__m__userInput);

    ui->checkBox_delta_D_X->setChecked(setup->set.delta_D_X__m__userInput);
    ui->checkBox_delta_d_X->setChecked((double)2*setup->set.delta_d_X__px__userInput);
    ui->checkBox_f_number->setChecked(setup->set.f_number__userInput);
    ui->checkBox_subject_distance->setChecked(setup->set.DoF_subject_distance__m__userInput);
    ui->checkBox_Resolution_Y->setChecked(setup->set.resolution_Y__px__userInput);
    ui->checkBox_PixelSize_Y->setChecked(setup->set.Pixelsize_Y__m__userInput);
    ui->checkBox_SensorSize_Y->setChecked(setup->set.sensor_Y__m__userInput);
    ui->checkBox_baseline_Y->setChecked(setup->set.baseline_Y__m__userInput);
    ui->checkBox_D1_Y->setChecked(setup->set.D1_Y__m__userInput);
    ui->checkBox_d1_Y->setChecked(setup->set.d1_Y__px__userInput);
    ui->checkBox_D2_Y->setChecked(setup->set.D2_Y__m__userInput);
    ui->checkBox_d2_Y->setChecked(setup->set.d2_Y__px__userInput);
    ui->checkBox_DH_Y->setChecked(setup->set.DH_Y__m__userInput);
    ui->checkBox_dH_Y->setChecked(setup->set.dH_Y__px__userInput);
    ui->checkBox_delta_D_Y->setChecked(setup->set.delta_D_Y__m__userInput);
    ui->checkBox_delta_d_Y->setChecked((double)2*setup->set.delta_d_Y__px__userInput);
    ui->checkBox_camX->setChecked(setup->set.Cam_X__userInput);
    ui->checkBox_camY->setChecked(setup->set.Cam_Y__userInput);

    ui->checkBox_baseline_jitter_X->setChecked(setup->set.delta_baseline_X_tagged);
    ui->checkBox_baseline_jitter_Y->setChecked(setup->set.delta_baseline_Y_tagged);
    ui->checkBox_baseline_jitter_Z->setChecked(setup->set.delta_baseline_Z_tagged);

    ui->checkBox_rotation_jitter_X->setChecked(setup->set.delta_rotation_X_tagged);
    ui->checkBox_rotation_jitter_Y->setChecked(setup->set.delta_rotation_Y_tagged);
    ui->checkBox_rotation_jitter_Z->setChecked(setup->set.delta_rotation_Z_tagged);

    ui->checkBox_stprecision->setChecked(setup->set.delta_d_inaccuracy_ST__px__userInput);

    ui->lineEdit_baseline_jitter->setText(QString::number(1000*setup->set.delta_baseline__m));
    ui->lineEdit_focallength_jitter->setText(QString::number(1000*setup->set.delta_focal_length__m));
    ui->lineEdit_rotation_jitter->setText(QString::number((double)180/(double)3.14*setup->set.delta_rotation__deg));

    ui->checkBox_baseline_jitter->setChecked(setup->set.delta_baseline__m__userInput);
    ui->checkBox_focallength_jitter->setChecked( setup->set.delta_focal_length__m__userInput);
    ui->checkBox_rotation_jitter->setChecked(setup->set.delta_rotation__deg__userInput);



}




