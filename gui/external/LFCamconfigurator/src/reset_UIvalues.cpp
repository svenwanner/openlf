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

void LFCamConfigurator::resetUI(){

    ui->lineEdit_Resolution_X__px->setText(QString::number(0));
    ui->lineEdit_AspectRatio->setText(QString::number(0));
    ui->lineEdit_PixelSize_X->setText(QString::number(0));
    ui->lineEdit_PixelAspectRatio->setText(QString::number(0));
    ui->lineEdit_SensorSize_X->setText(QString::number(0));
    ui->lineEdit_Framesize_X_at_DH->setText(QString::number(0, 'g', 5));
    ui->lineEdit_focalLength->setText(QString::number(0));
    ui->lineEdit_baseline_X->setText(QString::number(0));
    ui->lineEdit_theta_X->setText(QString::number(0, 'g', 5));
    ui->lineEdit_D1_X->setText(QString::number(0));
    ui->lineEdit_d1_X->setText(QString::number(0));
    ui->lineEdit_D2_X->setText(QString::number(0));
    ui->lineEdit_d2_X->setText(QString::number(0));
    ui->lineEdit_DH_X->setText(QString::number(0));
    ui->lineEdit_dH_X->setText(QString::number(0));
    ui->lineEdit_DHopt_X->setText(QString::number(0, 'g', 5));
    ui->lineEdit_delta_D_X->setText(QString::number(0));
    ui->lineEdit_delta_d_X->setText(QString::number(0));
    ui->lineEdit_D_N->setText(QString::number(0, 'g', 5));
    ui->lineEdit_D_F->setText(QString::number(0, 'g', 5));
    ui->lineEdit_f_number->setText(QString::number(0));
    ui->lineEdit_H_DoF->setText(QString::number(0, 'g', 5));
    ui->lineEdit_subject_distance->setText(QString::number(0));
    ui->lineEdit_DoF->setText(QString::number(0, 'g', 5));
    ui->lineEdit_Resolution_Y__px->setText(QString::number(0));
    ui->lineEdit_PixelSize_Y->setText(QString::number(0));
    ui->lineEdit_SensorSize_Y->setText(QString::number(0));
    ui->lineEdit_Framesize_Y_at_DH->setText(QString::number(0, 'g', 5));
    ui->lineEdit_baseline_Y->setText(QString::number(0));
    ui->lineEdit_theta_Y->setText(QString::number(0, 'g', 5));
    ui->lineEdit_D1_Y->setText(QString::number(0));
    ui->lineEdit_d1_Y->setText(QString::number(0));
    ui->lineEdit_D2_Y->setText(QString::number(0));
    ui->lineEdit_d2_Y->setText(QString::number(0));
    ui->lineEdit_DH_Y->setText(QString::number(0));
    ui->lineEdit_dH_Y->setText(QString::number(0));
    ui->lineEdit_DHopt_Y->setText(QString::number(0, 'g', 5));
    ui->lineEdit_delta_D_Y->setText(QString::number(0));
    ui->lineEdit_delta_d_Y->setText(QString::number(0));
    ui->lineEdit_Cam_X->setText(QString::number(0));
    ui->lineEdit_Cam_Y->setText(QString::number(0));
    ui->lineEdit_coc->setText(QString::number(0));
    ui->lineEdit_stprecision->setText(QString::number(0.01));

    ui->lineEdit_geoH1->setText(QString::number(0, 'g', 4));
    ui->lineEdit_geoV1->setText(QString::number(0, 'g', 4));
    ui->lineEdit_geoH2->setText(QString::number(0, 'g', 4));
    ui->lineEdit_geoV2->setText(QString::number(0, 'g', 4));
    ui->lineEdit_geoHH->setText(QString::number(0, 'g', 4));
    ui->lineEdit_geoVH->setText(QString::number(0, 'g', 4));

    ui->lineEdit_stH1->setText(QString::number(0, 'g', 4));
    ui->lineEdit_stV1->setText(QString::number(0, 'g', 4));
    ui->lineEdit_stH2->setText(QString::number(0, 'g', 4));
    ui->lineEdit_stV2->setText(QString::number(0, 'g', 4));
    ui->lineEdit_stHH->setText(QString::number(0, 'g', 4));
    ui->lineEdit_stVH->setText(QString::number(0, 'g', 4));



    ui->checkBox_Resolution_X__px->setChecked(false);
    ui->checkBox_AspectRatio->setChecked(false);
    ui->checkBox_PixelSize_X->setChecked(false);
    ui->checkBox_PixelAspectRatio->setChecked(false);
    ui->checkBox_SensorSize_X->setChecked(false);
    ui->checkBox_focalLength->setChecked(false);
    ui->checkBox_baseline_X->setChecked(false);
    ui->checkBox_D1_X->setChecked(false);
    ui->checkBox_d1_X->setChecked(false);
    ui->checkBox_d2_X->setChecked(false);
    ui->checkBox_d2_X->setChecked(false);
    ui->checkBox_DH_X->setChecked(false);
    ui->checkBox_dH_X->setChecked(false);
    ui->checkBox_delta_D_X->setChecked(false);
    ui->checkBox_delta_d_X->setChecked(false);
    ui->checkBox_f_number->setChecked(false);
    ui->checkBox_subject_distance->setChecked(false);
    ui->checkBox_Resolution_Y->setChecked(false);
    ui->checkBox_PixelSize_Y->setChecked(false);
    ui->checkBox_SensorSize_Y->setChecked(false);
    ui->checkBox_baseline_Y->setChecked(false);
    ui->checkBox_D1_Y->setChecked(false);
    ui->checkBox_d1_Y->setChecked(false);
    ui->checkBox_D2_Y->setChecked(false);
    ui->checkBox_d2_Y->setChecked(false);
    ui->checkBox_DH_Y->setChecked(false);
    ui->checkBox_dH_Y->setChecked(false);
    ui->checkBox_delta_D_Y->setChecked(false);
    ui->checkBox_delta_d_Y->setChecked(false);
    ui->checkBox_camX->setChecked(false);
    ui->checkBox_camY->setChecked(false);
    ui->checkBox_coc->setChecked(false);
    ui->checkBox_stprecision->setChecked(true);

    ui->horizontalSlider_focalLength->setValue(33);
    ui->horizontalSlider_baseline_X->setValue(33);
    ui->horizontalSlider_baseline_Y->setValue(33);
    ui->horizontalSlider_dH_X->setValue(33);
    ui->horizontalSlider_dH_Y->setValue(33);
    ui->horizontalSlider_subject_distance->setValue(33);

    ui->lineEdit_Resolution_X__px->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_AspectRatio->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_PixelSize_X->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_PixelAspectRatio->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_SensorSize_X->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_focalLength->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_baseline_X->setStyleSheet( "background-color: red; color : black;" );
    if(HiddenFlag == false){
        ui->lineEdit_D1_X->setStyleSheet( "background-color: red; color : black;" );
        ui->lineEdit_d1_X->setStyleSheet( "background-color: red; color : black;" );
        ui->lineEdit_D2_X->setStyleSheet( "background-color: red; color : black;" );
        ui->lineEdit_d2_X->setStyleSheet( "background-color: red; color : black;" );
    }
    ui->lineEdit_DH_X->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_dH_X->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_delta_D_X->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_delta_d_X->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_f_number->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_subject_distance->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_coc->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_Resolution_Y__px->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_PixelSize_Y->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_SensorSize_Y->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_baseline_Y->setStyleSheet( "background-color: red; color : black;" );
    if(HiddenFlag == false){
        ui->lineEdit_D1_Y->setStyleSheet( "background-color: red; color : black;" );
        ui->lineEdit_d1_Y->setStyleSheet( "background-color: red; color : black;" );
        ui->lineEdit_D2_Y->setStyleSheet( "background-color: red; color : black;" );
        ui->lineEdit_d2_Y->setStyleSheet( "background-color: red; color : black;" );
    }
    ui->lineEdit_DH_Y->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_dH_Y->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_delta_D_Y->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_delta_d_Y->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_Cam_X->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_Cam_Y->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_baseline_jitter->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_focallength_jitter->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_rotation_jitter->setStyleSheet( "background-color: red; color : black;" );
    ui->lineEdit_stprecision->setStyleSheet( "background-color: green; color : black;" );

}
