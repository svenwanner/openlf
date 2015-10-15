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

/****************************************************************************************************
 *                                      S L O T S
 ****************************************************************************************************/


void LFCamConfigurator::SimpleButtonPressed() {

    if(HiddenFlag == false){
        HiddenFlag = true;

        ui->lineEdit_AperturAngle_Y->setHidden(true);
        ui->label_AperturAngle_Y->setHidden(true);
        ui->label_AperturAngle_Y_2->setHidden(true);

        ui->SimpleMode->setText("Extended Mode");
        ui->horizontalSlider_baseline_Y->setHidden(true);
        ui->checkBox_Lock_baseline->setHidden(true);
        ui->checkBox_AspectRatio->setHidden(true);
        ui->label_AspectRatio->setHidden(true);
        ui->lineEdit_AspectRatio->setHidden(true);

        ui->label_dH_X->setText("Horoptor Disp. d  ");
        ui->label_DH_X->setText("Horoptor Depth Z  ");

        ui->label_baseline_X->setText("Baseline");
        ui->lineEdit_baseline_Y->setHidden(true);
        ui->checkBox_baseline_Y->setHidden(true);
        ui->label_baselineY_Unit->setHidden(true);
        ui->label_baseline_Y->setHidden(true);

        ui->lineEdit_PixelAspectRatio->setHidden(true);
        ui->checkBox_PixelAspectRatio->setHidden(true);
        ui->label_PixelAspectRatio->setHidden(true);

        ui->lineEdit_PixelSize_Y->setHidden(true);
        ui->checkBox_PixelSize_Y->setHidden(true);
        ui->label_PixelSize_Y->setHidden(true);
        ui->label_PixelSize_YUnit->setHidden(true);

        ui->label_sensorsizeY->setHidden(true);
        ui->label_sensorsizeYUnit->setHidden(true);
        ui->lineEdit_SensorSize_Y->setHidden(true);
        ui->checkBox_SensorSize_Y->setHidden(true);

        ui->lineEdit_theta_Y->setHidden(true);
        ui->label_thetaY->setHidden(true);
        ui->label_thetaYUnit->setHidden(true);

        ui->lineEdit_D1_X->setStyleSheet( "background-color: gray; color : black;" );
        ui->lineEdit_d1_X->setStyleSheet( "background-color: gray; color : black;" );
        ui->lineEdit_D2_X->setStyleSheet( "background-color: gray; color : black;" );
        ui->lineEdit_d2_X->setStyleSheet( "background-color: gray; color : black;" );

        ui->lineEdit_D1_X->setEnabled(false);
        ui->lineEdit_d1_X->setEnabled(false);
        ui->lineEdit_D2_X->setEnabled(false);
        ui->lineEdit_d2_X->setEnabled(false);

        ui->checkBox_D1_X->setHidden(true);
        ui->checkBox_D1_X->setChecked(false);
        ui->checkBox_D2_X->setHidden(true);
        ui->checkBox_D2_X->setChecked(false);
        ui->checkBox_d1_X->setHidden(true);
        ui->checkBox_d1_X->setChecked(false);
        ui->checkBox_d2_X->setHidden(true);
        ui->checkBox_d2_X->setChecked(false);

        ui->checkBox_D1_Y->setHidden(true);
        ui->checkBox_D1_Y->setChecked(false);
        ui->checkBox_D2_Y->setHidden(true);
        ui->checkBox_D2_Y->setChecked(false);
        ui->checkBox_d1_Y->setHidden(true);
        ui->checkBox_d1_Y->setChecked(false);
        ui->checkBox_d2_Y->setHidden(true);
        ui->checkBox_d2_Y->setChecked(false);

        ui->lineEdit_D1_Y->setHidden(true);
        ui->lineEdit_D2_Y->setHidden(true);
        ui->lineEdit_d1_Y->setHidden(true);
        ui->lineEdit_d2_Y->setHidden(true);

        ui->label_D1_Y->setHidden(true);
        ui->label_D1_Y_small->setHidden(true);
        ui->label_D2_Y->setHidden(true);
        ui->label_D2_Y_small->setHidden(true);
        ui->label_d1_Y->setHidden(true);
        ui->label_d1_Y_small->setHidden(true);
        ui->label_d2_Y->setHidden(true);
        ui->label_d2_Y_small->setHidden(true);

        ui->label_D1_YUnit->setHidden(true);
        ui->label_D2_YUnit->setHidden(true);
        ui->label_d1_YUnit->setHidden(true);
        ui->label_d2_YUnit->setHidden(true);

        ui->label_delta_D_Y->setHidden(true);
        ui->label_delta_D_YUnit->setHidden(true);
        ui->label_delta_d_Y->setHidden(true);
        ui->label_delta_d_YUnit->setHidden(true);
        ui->lineEdit_delta_D_Y->setHidden(true);
        ui->lineEdit_delta_d_Y->setHidden(true);
        ui->checkBox_delta_D_Y->setHidden(true);
        ui->checkBox_delta_d_Y->setHidden(true);
//////////////
        ui->horizontalSlider_dH_Y->setHidden(true);
        ui->horizontalSlider_DH_Y->setHidden(true);
        ui->checkBox_Lock_dH->setHidden(true);
        ui->checkBox_Lock_DH->setHidden(true);
///////////////
        ui->label_DH_Y->setHidden(true);
        ui->label_DH_Y_small->setHidden(true);
        ui->label_dH_Y_small->setHidden(true);
        ui->label_dH_Y->setHidden(true);
        ui->lineEdit_DH_Y->setHidden(true);
        ui->lineEdit_dH_Y->setHidden(true);
        ui->checkBox_DH_Y->setHidden(true);
        ui->checkBox_dH_Y->setHidden(true);
        ui->label_DH_YUnit->setHidden(true);
        ui->label_dH_YUnit->setHidden(true);

        ui->lineEdit_DHopt_Y->setHidden(true);
        ui->lineEdit_Framesize_Y_at_DH->setHidden(true);
        ui->label_DHopt_Y->setHidden(true);
        ui->label_Framesize_Y_at_DH->setHidden(true);
        ui->label_Framesize_Y_at_DH_small->setHidden(true);
        ui->label_DHopt_YUnit->setHidden(true);
        ui->label_Framesize_Y_at_DHUnit->setHidden(true);

        ui->label_Unit_19->setHidden(true);
        ui->label_Unit_20->setHidden(true);
        ui->label_Unit_22->setHidden(true);
        ui->label_Unit_24->setHidden(true);

        ui->lineEdit_geoV1->setHidden(true);
        ui->lineEdit_geoV2->setHidden(true);
        ui->lineEdit_geoVH->setHidden(true);

        ui->lineEdit_stV1->setHidden(true);
        ui->lineEdit_stV2->setHidden(true);
        ui->lineEdit_stVH->setHidden(true);

        ui->checkBox_dH_Y->setChecked(false);
        ui->checkBox_DH_Y->setChecked(false);
        ui->checkBox_Lock_dH->setChecked(false);
        ui->checkBox_Lock_DH->setChecked(false);

    }

    else{
        HiddenFlag = false;
        ui->SimpleMode->setText("Simple Mode");
        ui->horizontalSlider_baseline_Y->setHidden(false);
        ui->checkBox_Lock_baseline->setHidden(false);
        ui->checkBox_AspectRatio->setHidden(false);
        ui->label_AspectRatio->setHidden(false);
        ui->lineEdit_AspectRatio->setHidden(false);

        ui->label_baseline_X->setText("Baseline (hori)");
        ui->label_dH_X->setText("Horoptor Disp. d   (hori)");
        ui->label_DH_X->setText("Horoptor Depth Z   (hori)");

        ui->lineEdit_AperturAngle_Y->setHidden(false);
        ui->label_AperturAngle_Y->setHidden(false);
        ui->label_AperturAngle_Y_2->setHidden(false);

        ui->lineEdit_baseline_Y->setHidden(false);
        ui->label_baselineY_Unit->setHidden(false);
        ui->label_baseline_Y->setHidden(false);
        ui->checkBox_baseline_Y->setHidden(false);

        ui->lineEdit_PixelAspectRatio->setHidden(false);
        ui->checkBox_PixelAspectRatio->setHidden(false);
        ui->label_PixelAspectRatio->setHidden(false);

        ui->lineEdit_PixelSize_Y->setHidden(false);
        ui->checkBox_PixelSize_Y->setHidden(false);
        ui->label_PixelSize_Y->setHidden(false);
        ui->label_PixelSize_YUnit->setHidden(false);

        ui->label_sensorsizeY->setHidden(false);
        ui->label_sensorsizeYUnit->setHidden(false);
        ui->lineEdit_SensorSize_Y->setHidden(false);
        ui->checkBox_SensorSize_Y->setHidden(false);

        ui->lineEdit_theta_Y->setHidden(false);
        ui->label_thetaY->setHidden(false);
        ui->label_thetaYUnit->setHidden(false);

        if(setup->set_valid.D1_X__m){ui->lineEdit_D1_X->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_D1_X->setStyleSheet( "background-color: red; color : black;" );}
        if(setup->set_valid.d1_X__px){ui->lineEdit_d1_X->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_d1_X->setStyleSheet( "background-color: red; color : black;" );}
        if(setup->set_valid.D2_X__m){ui->lineEdit_D2_X->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_D2_X->setStyleSheet( "background-color: red; color : black;" );}
        if(setup->set_valid.d2_X__px){ui->lineEdit_d2_X->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_d2_X->setStyleSheet( "background-color: red; color : black;" );}

        ui->checkBox_D1_X->setHidden(false);
        ui->checkBox_D2_X->setHidden(false);
        ui->checkBox_d1_X->setHidden(false);
        ui->checkBox_d2_X->setHidden(false);

        ui->lineEdit_D1_X->setEnabled(true);
        ui->lineEdit_d1_X->setEnabled(true);
        ui->lineEdit_D2_X->setEnabled(true);
        ui->lineEdit_d2_X->setEnabled(true);

        ui->checkBox_D1_Y->setHidden(false);
        ui->checkBox_D2_Y->setHidden(false);
        ui->checkBox_d1_Y->setHidden(false);
        ui->checkBox_d2_Y->setHidden(false);

        ui->lineEdit_D1_Y->setHidden(false);
        ui->lineEdit_D2_Y->setHidden(false);
        ui->lineEdit_d1_Y->setHidden(false);
        ui->lineEdit_d2_Y->setHidden(false);

        ui->label_D1_Y->setHidden(false);
        ui->label_D1_Y_small->setHidden(false);
        ui->label_D2_Y->setHidden(false);
        ui->label_D2_Y_small->setHidden(false);
        ui->label_d1_Y->setHidden(false);
        ui->label_d1_Y_small->setHidden(false);
        ui->label_d2_Y->setHidden(false);
        ui->label_d2_Y_small->setHidden(false);

        ui->label_D1_YUnit->setHidden(false);
        ui->label_D2_YUnit->setHidden(false);
        ui->label_d1_YUnit->setHidden(false);
        ui->label_d2_YUnit->setHidden(false);

        ui->label_delta_D_Y->setHidden(false);
        ui->label_delta_D_YUnit->setHidden(false);
        ui->label_delta_d_Y->setHidden(false);
        ui->label_delta_d_YUnit->setHidden(false);
        ui->lineEdit_delta_D_Y->setHidden(false);
        ui->lineEdit_delta_d_Y->setHidden(false);
        ui->checkBox_delta_D_Y->setHidden(false);
        ui->checkBox_delta_d_Y->setHidden(false);
///////////////////

        if (!ui->checkBox_Lock_dH->isChecked()) ui->horizontalSlider_dH_Y->setHidden(false);
        if (!ui->checkBox_Lock_DH->isChecked()) ui->horizontalSlider_DH_Y->setHidden(false);
        ui->checkBox_Lock_dH->setHidden(false);
        ui->checkBox_Lock_DH->setHidden(false);
///////////////////
        ui->label_DH_Y->setHidden(false);
        ui->label_DH_Y_small->setHidden(false);
        ui->label_dH_Y_small->setHidden(false);
        ui->label_dH_Y->setHidden(false);
        ui->lineEdit_DH_Y->setHidden(false);
        ui->lineEdit_dH_Y->setHidden(false);
        ui->checkBox_DH_Y->setHidden(false);
        ui->checkBox_dH_Y->setHidden(false);
        ui->label_DH_YUnit->setHidden(false);
        ui->label_dH_YUnit->setHidden(false);

        ui->lineEdit_DHopt_Y->setHidden(false);
        ui->lineEdit_Framesize_Y_at_DH->setHidden(false);
        ui->label_DHopt_Y->setHidden(false);
        ui->label_Framesize_Y_at_DH->setHidden(false);
        ui->label_Framesize_Y_at_DH_small->setHidden(false);
        ui->label_DHopt_YUnit->setHidden(false);
        ui->label_Framesize_Y_at_DHUnit->setHidden(false);

        if (setup->set_valid.baseline_X__m==true) ui->checkBox_Lock_baseline->setChecked(true);
        if (ui->checkBox_DH_X->isChecked()){
            ui->checkBox_Lock_DH->setChecked(true);
            ui->checkBox_DH_Y->setChecked(true);
        }
        if (ui->checkBox_dH_X->isChecked()){
            ui->checkBox_Lock_dH->setChecked(true);
            ui->checkBox_dH_Y->setChecked(true);
        }

        if(setup->set_valid.delta_d_X__px){
            ui->lineEdit_delta_d_Y->setText(ui->lineEdit_delta_d_X->text());
            ui->checkBox_delta_d_Y->setChecked(true);
        }

        if(setup->set_valid.Pixelsize_X__m==true) {
            ui->lineEdit_PixelSize_Y->setText(ui->lineEdit_PixelSize_X->text());
            ui->checkBox_PixelSize_Y->setChecked(true);
        }
        ui->label_Unit_19->setHidden(false);
        ui->label_Unit_20->setHidden(false);
        ui->label_Unit_22->setHidden(false);
        ui->label_Unit_24->setHidden(false);

        ui->lineEdit_geoV1->setHidden(false);
        ui->lineEdit_geoV2->setHidden(false);
        ui->lineEdit_geoVH->setHidden(false);

        ui->lineEdit_stV1->setHidden(false);
        ui->lineEdit_stV2->setHidden(false);
        ui->lineEdit_stVH->setHidden(false);

        update();
    }


}


void LFCamConfigurator::CoC() {
    if(userinput){
    userinput=false;
    ui->checkBox_coc->setChecked(true);
    update();
}
}
void LFCamConfigurator::resolution_XChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_Resolution_X__px->setChecked(true);
    update();
}
}
void LFCamConfigurator::AspectRatioChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_AspectRatio->setChecked(true);
    update();
}
}
void LFCamConfigurator::PixelSize_XChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_PixelSize_X->setChecked(true);
    update();
}
}
void LFCamConfigurator::PixelAspectRatioChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_PixelAspectRatio->setChecked(true);
    update();
}
}
void LFCamConfigurator::SensorSize_XChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_SensorSize_X->setChecked(true);
    update();
}
}

void LFCamConfigurator::focalLengthChanged() {
    if(userinput){
        userinput=false;
        justChanged = true;
        ui->horizontalSlider_focalLength->setValue(33);
        ui->checkBox_focalLength->setChecked(true);
        update();
        focalLengthSliderSave=ui->lineEdit_focalLength->text().toDouble();
    }
}

void LFCamConfigurator::baseline_XChanged() {
    if(userinput){
    userinput=false;
    justChanged = true;
    ui->horizontalSlider_baseline_X->setValue(33);
    ui->checkBox_baseline_X->setChecked(true);
    if(ui->checkBox_Lock_baseline->isChecked()){
        ui->lineEdit_baseline_Y->setText(ui->lineEdit_baseline_X->text());
        ui->checkBox_baseline_Y->setChecked(true);
    }
    update();
    baseline_XSliderSave=ui->lineEdit_baseline_X->text().toDouble();
}
}
void LFCamConfigurator::D1_XChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_D1_X->setChecked(true);
    update();
}
}
void LFCamConfigurator::d1_XChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_d1_X->setChecked(true);
    update();
}
}
void LFCamConfigurator::D2_XChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_D2_X->setChecked(true);
    update();
}
}
void LFCamConfigurator::d2_XChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_d2_X->setChecked(true);
    update();
}
}
void LFCamConfigurator::dH_XChanged() {
    if(userinput){
        userinput=false;
        justChanged = true;
        ui->horizontalSlider_dH_X->setValue(33);
        ui->checkBox_dH_X->setChecked(true);
        if(ui->checkBox_Lock_dH->isChecked()){
            ui->lineEdit_dH_Y->setText(ui->lineEdit_dH_X->text());
            ui->checkBox_dH_Y->setChecked(true);
        }
        update();
        dH_XSliderSave=ui->lineEdit_dH_X->text().toDouble();
        if(ui->checkBox_Lock_subjectDistance->isChecked()){
            ui->checkBox_subject_distance->setChecked(false);
            ui->lineEdit_subject_distance->setText(ui->lineEdit_DH_X->text());
            ui->checkBox_subject_distance->setChecked(true);
        }
    }
}
void LFCamConfigurator::DHopt_XChanged() {
    if(userinput){
    userinput=false;
    update();
}
}
void LFCamConfigurator::delta_D_XChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_delta_D_X->setChecked(true);
    update();
}
}
void LFCamConfigurator::delta_d_XChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_delta_d_X->setChecked(true);
    update();
}
}

void LFCamConfigurator::f_numberChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_f_number->setChecked(true);
    update();
}
}

void LFCamConfigurator::subject_distanceChanged() {
    if(userinput){
    userinput=false;
    justChanged = true;
    ui->horizontalSlider_subject_distance->setValue(33);
    ui->checkBox_subject_distance->setChecked(true);
    update();
    subject_distanceSliderSave=ui->lineEdit_subject_distance->text().toDouble();
}
}

void LFCamConfigurator::resolution_YChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_Resolution_Y->setChecked(true);
    update();
}
}
void LFCamConfigurator::PixelSize_YChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_PixelSize_Y->setChecked(true);
    update();
}
}
void LFCamConfigurator::SensorSize_YChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_SensorSize_Y->setChecked(true);
    update();
}
}

void LFCamConfigurator::baseline_YChanged() {
    if(userinput){
        userinput=false;
        justChanged = true;
        ui->horizontalSlider_baseline_Y->setValue(33);
        ui->checkBox_baseline_Y->setChecked(true);
        update();
        baseline_YSliderSave=ui->lineEdit_baseline_Y->text().toDouble();
    }
}
void LFCamConfigurator::D1_YChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_D1_Y->setChecked(true);
    update();
}
}
void LFCamConfigurator::d1_YChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_d1_Y->setChecked(true);
    update();
}
}
void LFCamConfigurator::D2_YChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_D2_Y->setChecked(true);
    update();
}
}
void LFCamConfigurator::d2_YChanged() {
    if(userinput){
    userinput=false;
    ui->checkBox_d2_Y->setChecked(true);
    update();
}
}

void LFCamConfigurator::DH_XChanged() {
    if(userinput){

        userinput=false;
        justChanged = true;
        ui->horizontalSlider_DH_X->setValue(33);
        ui->checkBox_DH_X->setChecked(true);

        if(ui->checkBox_Lock_dH->isChecked()){
            ui->lineEdit_DH_Y->setText(ui->lineEdit_DH_X->text());
        }
        if(ui->checkBox_Lock_subjectDistance->isChecked()){
            ui->checkBox_subject_distance->setChecked(false);
            ui->lineEdit_subject_distance->setText(ui->lineEdit_DH_X->text());
            ui->checkBox_subject_distance->setChecked(true);
            subject_distanceSliderSave=ui->lineEdit_DH_X->text().toDouble();
        }

        update();
        DH_XSliderSave=ui->lineEdit_DH_X->text().toDouble();
    }
}
void LFCamConfigurator::DH_YChanged() {
    if(userinput){

        userinput=false;
        ui->horizontalSlider_DH_Y->setValue(33);
        ui->checkBox_DH_Y->setChecked(true);
        update();
        DH_YSliderSave=ui->lineEdit_DH_Y->text().toDouble();
    }
}


void LFCamConfigurator::dH_YChanged() {
    if(userinput){
        userinput=false;
        ui->horizontalSlider_dH_Y->setValue(33);
        ui->checkBox_dH_Y->setChecked(true);
        update();
        dH_YSliderSave=ui->lineEdit_dH_Y->text().toDouble();
    }
}
void LFCamConfigurator::DHopt_YChanged() {
    if(userinput){
        userinput=false;
        update();
    }
}
void LFCamConfigurator::delta_D_YChanged() {
    if(userinput){
        userinput=false;
        ui->checkBox_delta_D_Y->setChecked(true);
        update();
    }
}
void LFCamConfigurator::delta_d_YChanged() {
    if(userinput){
        userinput=false;
        ui->checkBox_delta_d_Y->setChecked(true);
        update();
    }
}
void LFCamConfigurator::camX_Changed() {
    if(userinput){
        userinput=false;
        ui->checkBox_camX->setChecked(true);
        update();
    }
}
void LFCamConfigurator::camY_Changed() {
    if(userinput){
        userinput=false;
        ui->checkBox_camY->setChecked(true);
        update();
    }
}

void LFCamConfigurator::stprecision_Changed() {
    if(userinput){
        userinput=false;
        ui->checkBox_stprecision->setChecked(true);
        update();
    }
}

void LFCamConfigurator::setUserInput(QString){
    userinput=true;
}

void LFCamConfigurator::Slot_update(bool) {
    update();
}


void LFCamConfigurator::DH_XBoxChanged(bool) {
    DH_XSliderSave = ui->lineEdit_DH_X->text().toDouble();
    update();
}
void LFCamConfigurator::dH_XBoxChanged(bool) {
    dH_XSliderSave = ui->lineEdit_dH_X->text().toDouble();
    update();
}


void LFCamConfigurator::DH_YBoxChanged(bool) {
    DH_YSliderSave = ui->lineEdit_DH_Y->text().toDouble();
    update();
}
void LFCamConfigurator::dH_YBoxChanged(bool) {
    dH_YSliderSave = ui->lineEdit_dH_Y->text().toDouble();
    update();
}


void LFCamConfigurator::baselineJitter_text(QString){
    userinput=true;
}
void LFCamConfigurator::baselineJitter_edit() {
    if(userinput){
        userinput=false;
        ui->checkBox_baseline_jitter->setChecked(true);
        update();
    }
}

void LFCamConfigurator::rotationJitter_text(QString){
    userinput=true;
}
void LFCamConfigurator::rotationJitter_edit() {
    if(userinput){
        userinput=false;
        ui->checkBox_rotation_jitter->setChecked(true);
        update();
    }
}

void LFCamConfigurator::focallengthJitter_text(QString){
    userinput=true;
}
void LFCamConfigurator::focallengthJitter_edit() {
    if(userinput){
        userinput=false;
        ui->checkBox_focallength_jitter->setChecked(true);
        update();
    }
}


//SLIDER-SLOTS
void LFCamConfigurator::focalLengthSlider(int value){
    if(justChanged){
        justChanged=false;
    }
    else{

        ui->lineEdit_focalLength->setText(QString::number(((double)value*0.015+0.5)*focalLengthSliderSave));
        update();
    }
}
void LFCamConfigurator::baseline_XSlider(int value){
    if(justChanged){justChanged=false;}else{
        ui->lineEdit_baseline_X->setText(QString::number(((double)value*0.015+0.5)*baseline_XSliderSave));
        update();
        if(ui->checkBox_Lock_baseline->isChecked()){
            ui->lineEdit_baseline_Y->setText(ui->lineEdit_baseline_X->text());
            ui->checkBox_baseline_Y->setChecked(true);
            update();
        }
    }
}
void LFCamConfigurator::baseline_YSlider(int value){
    if(justChanged){justChanged=false;}else{
        ui->lineEdit_baseline_Y->setText(QString::number(((double)value*0.015+0.5)*baseline_YSliderSave));
        update();
    }
}
void LFCamConfigurator::dH_XSlider(int value){
    if(justChanged){justChanged=false;}else{
        ui->lineEdit_dH_X->setText(QString::number(((double)value*0.015+0.5)*dH_XSliderSave));
        update();
        if(ui->checkBox_Lock_dH->isChecked()){
            ui->lineEdit_dH_Y->setText(ui->lineEdit_dH_X->text());
            ui->checkBox_dH_X->setChecked(true);
            ui->checkBox_dH_Y->setChecked(true);
            update();
        }
    }
    if(ui->checkBox_Lock_subjectDistance->isChecked()){
        ui->checkBox_subject_distance->setChecked(false);
        ui->lineEdit_subject_distance->setText(ui->lineEdit_DH_X->text());
        ui->checkBox_subject_distance->setChecked(true);
    }
}
void LFCamConfigurator::dH_YSlider(int value){
    if(justChanged){justChanged=false;}else{
        ui->lineEdit_dH_Y->setText(QString::number(((double)value*0.015+0.5)*dH_YSliderSave));
        update();
    }
}

void LFCamConfigurator::DH_XSlider(int value){
    if(justChanged){justChanged=false;}else{
        ui->lineEdit_DH_X->setText(QString::number(((double)value*0.015+0.5)*DH_XSliderSave));
        update();
        if(ui->checkBox_Lock_DH->isChecked()){
            ui->lineEdit_DH_Y->setText(ui->lineEdit_DH_X->text());
            ui->checkBox_DH_X->setChecked(true);
            ui->checkBox_DH_Y->setChecked(true);
        }
        update();
    }
    if(ui->checkBox_Lock_subjectDistance->isChecked()){
        ui->checkBox_subject_distance->setChecked(false);
        ui->lineEdit_subject_distance->setText(ui->lineEdit_DH_X->text());
        ui->checkBox_subject_distance->setChecked(true);
    }
}
void LFCamConfigurator::DH_YSlider(int value){
    if(justChanged){justChanged=false;}else{
        ui->lineEdit_DH_Y->setText(QString::number(((double)value*0.015+0.5)*DH_YSliderSave));
        update();
    }
}

void LFCamConfigurator::subject_distanceSlider(int value){
    if(justChanged){justChanged=false;}else{
        ui->lineEdit_subject_distance->setText(QString::number(((double)value*0.015+0.5)*subject_distanceSliderSave));
        update();
    }
}

void LFCamConfigurator::Lock_baseline(int value){
    if(value==0){
        ui->horizontalSlider_baseline_Y->setVisible(true);
        ui->checkBox_baseline_Y->setChecked(false);
    }
    else{
        ui->horizontalSlider_baseline_Y->setVisible(false);
        ui->lineEdit_baseline_Y->setText(ui->lineEdit_baseline_X->text());
        ui->checkBox_baseline_Y->setChecked(true);
        update();
    }
}
void LFCamConfigurator::Lock_dh(int value){
    if(value==0){
        ui->horizontalSlider_dH_Y->setVisible(true);
        ui->checkBox_dH_Y->setChecked(false);
    }
    else{
        ui->horizontalSlider_dH_Y->setVisible(false);
        ui->lineEdit_dH_Y->setText(ui->lineEdit_dH_X->text());
        ui->checkBox_dH_X->setChecked(true);
        ui->checkBox_dH_Y->setChecked(true);
        update();
    }
}

void LFCamConfigurator::Lock_Dh(int value){
    if(value==0){
        ui->horizontalSlider_DH_Y->setVisible(true);
        ui->checkBox_DH_Y->setChecked(false);
    }
    else{
        ui->horizontalSlider_DH_Y->setVisible(false);
        ui->lineEdit_DH_Y->setText(ui->lineEdit_DH_X->text());
        ui->checkBox_DH_X->setChecked(true);
        ui->checkBox_DH_Y->setChecked(true);
        update();
    }
}
void LFCamConfigurator::Lock_subjectDistance(int value){
    if(value==0){
        ui->horizontalSlider_subject_distance->setVisible(true);
        ui->checkBox_subject_distance->setChecked(false);
        ui->checkBox_subject_distance->setHidden(false);
        subject_distanceSliderSave=ui->lineEdit_DH_X->text().toDouble();
    }
    else{
        ui->horizontalSlider_subject_distance->setVisible(false);
        ui->lineEdit_subject_distance->setText(ui->lineEdit_DH_X->text());
        ui->checkBox_subject_distance->setChecked(true);
        ui->checkBox_subject_distance->setHidden(true);
        update();
    }
}





void LFCamConfigurator::save(){
    SimpleButtonPressed();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/home", tr(".ini File (*.ini)"));
    if (fileName.trimmed().isEmpty()){
        std::cout << "nothing to load" << std::endl;
    }
    else{
        setup->save(fileName.toStdString());
    }
}
void LFCamConfigurator::expBlender(){
    SimpleButtonPressed();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export to Blender"),"/home", tr(".ini File (*.ini)"));
    if (fileName.trimmed().isEmpty()){
        std::cout << "nothing to load" << std::endl;
    }
    else{
        setup->expBlender(fileName.toStdString());
    }
}
void LFCamConfigurator::expFramework(){
    SimpleButtonPressed();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export to LF Framework"),"/home", tr(".ini File (*.ini)"));
    if (fileName.trimmed().isEmpty()){
        std::cout << "nothing to load" << std::endl;
    }
    else{
        setup->expLF_Framework(fileName.toStdString());
    }
}

void LFCamConfigurator::help(){
    helpDialog->show();

}


/****************************************************************************************************
 *                                      U P D A T E
 ****************************************************************************************************/

void LFCamConfigurator::update() {

    get_UIvalues();

    setup->compute();

    set_UIvalues();

    if(setup->set_valid.resolution_X__px){ui->lineEdit_Resolution_X__px->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_Resolution_X__px->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.AspectRatio){ui->lineEdit_AspectRatio->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_AspectRatio->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.Pixelsize_X__m){ui->lineEdit_PixelSize_X->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_PixelSize_X->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.PixelAspectRatio){ui->lineEdit_PixelAspectRatio->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_PixelAspectRatio->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.sensor_X__m){ui->lineEdit_SensorSize_X->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_SensorSize_X->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.focalLength__m){ui->lineEdit_focalLength->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_focalLength->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.baseline_X__m){ui->lineEdit_baseline_X->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_baseline_X->setStyleSheet( "background-color: red; color : black;" );}


    if(HiddenFlag == false){
        if(setup->set_valid.D1_X__m){ui->lineEdit_D1_X->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_D1_X->setStyleSheet( "background-color: red; color : black;" );}
        if(setup->set_valid.d1_X__px){ui->lineEdit_d1_X->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_d1_X->setStyleSheet( "background-color: red; color : black;" );}
        if(setup->set_valid.D2_X__m){ui->lineEdit_D2_X->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_D2_X->setStyleSheet( "background-color: red; color : black;" );}
        if(setup->set_valid.d2_X__px){ui->lineEdit_d2_X->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_d2_X->setStyleSheet( "background-color: red; color : black;" );}
    }
    else{
        ui->lineEdit_D1_X->setStyleSheet( "background-color: gray; color : black;" );
        ui->lineEdit_d1_X->setStyleSheet( "background-color: gray; color : black;" );
        ui->lineEdit_D2_X->setStyleSheet( "background-color: gray; color : black;" );
        ui->lineEdit_d2_X->setStyleSheet( "background-color: gray; color : black;" );
    }

    if(setup->set_valid.DH_X__m){ui->lineEdit_DH_X->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_DH_X->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.dH_X__px){ui->lineEdit_dH_X->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_dH_X->setStyleSheet( "background-color: red; color : black;" );}



    if(setup->set_valid.delta_D_X__m){ui->lineEdit_delta_D_X->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_delta_D_X->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.delta_d_X__px){ui->lineEdit_delta_d_X->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_delta_d_X->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.f_number){ui->lineEdit_f_number->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_f_number->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.DoF_subject_distance__m){ui->lineEdit_subject_distance->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_subject_distance->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.CircleofConfusion__m){ui->lineEdit_coc->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_coc->setStyleSheet( "background-color: red; color : black;" );}


    if(setup->set_valid.resolution_Y__px){ui->lineEdit_Resolution_Y__px->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_Resolution_Y__px->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.Pixelsize_Y__m){ui->lineEdit_PixelSize_Y->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_PixelSize_Y->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.sensor_Y__m){ui->lineEdit_SensorSize_Y->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_SensorSize_Y->setStyleSheet( "background-color: red; color : black;" );}

    if(setup->set_valid.baseline_Y__m){ui->lineEdit_baseline_Y->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_baseline_Y->setStyleSheet( "background-color: red; color : black;" );}

    if(HiddenFlag == false){
        if(setup->set_valid.D1_Y__m){ui->lineEdit_D1_Y->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_D1_Y->setStyleSheet( "background-color: red; color : black;" );}
        if(setup->set_valid.d1_Y__px){ui->lineEdit_d1_Y->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_d1_Y->setStyleSheet( "background-color: red; color : black;" );}
        if(setup->set_valid.D2_Y__m){ui->lineEdit_D2_Y->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_D2_Y->setStyleSheet( "background-color: red; color : black;" );}
        if(setup->set_valid.d2_Y__px){ui->lineEdit_d2_Y->setStyleSheet( "background-color: green; color : black;" );}
        else{ui->lineEdit_d2_Y->setStyleSheet( "background-color: red; color : black;" );}
    }
    else{
            ui->lineEdit_D1_Y->setStyleSheet( "background-color: gray; color : black;" );
            ui->lineEdit_d1_Y->setStyleSheet( "background-color: gray; color : black;" );
            ui->lineEdit_D2_Y->setStyleSheet( "background-color: gray; color : black;" );
            ui->lineEdit_d2_Y->setStyleSheet( "background-color: gray; color : black;" );
        }

    if(setup->set_valid.DH_Y__m){ui->lineEdit_DH_Y->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_DH_Y->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.dH_Y__px){ui->lineEdit_dH_Y->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_dH_Y->setStyleSheet( "background-color: red; color : black;" );}

    if(setup->set_valid.delta_D_Y__m){ui->lineEdit_delta_D_Y->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_delta_D_Y->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.delta_d_Y__px){ui->lineEdit_delta_d_Y->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_delta_d_Y->setStyleSheet( "background-color: red; color : black;" );}

    if(setup->set_valid.Cam_X){ui->lineEdit_Cam_X->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_Cam_X->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.Cam_Y){ui->lineEdit_Cam_Y->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_Cam_Y->setStyleSheet( "background-color: red; color : black;" );}


    if(setup->set_valid.delta_baseline__m){ui->lineEdit_baseline_jitter->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_baseline_jitter->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.delta_focal_length__m){ui->lineEdit_focallength_jitter->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_focallength_jitter->setStyleSheet( "background-color: red; color : black;" );}
    if(setup->set_valid.delta_rotation__deg){ui->lineEdit_rotation_jitter->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_rotation_jitter->setStyleSheet( "background-color: red; color : black;" );}

    if(setup->set_valid.delta_d_inaccuracy_ST__px){ui->lineEdit_stprecision->setStyleSheet( "background-color: green; color : black;" );}
    else{ui->lineEdit_stprecision->setStyleSheet( "background-color: red; color : black;" );}


}

