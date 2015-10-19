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


void LFCamConfigurator::connect_signals(){



//Simple Mode Button
    connect(ui->SimpleMode,SIGNAL(clicked()),this,SLOT(SimpleButtonPressed()));

    //setup signal slots
    connect(ui->lineEdit_Resolution_X__px,SIGNAL(editingFinished()),this,SLOT(resolution_XChanged()));
    connect(ui->lineEdit_Resolution_Y__px,SIGNAL(editingFinished()),this,SLOT(resolution_YChanged()));

    connect(ui->lineEdit_AspectRatio,SIGNAL(editingFinished()),this,SLOT(AspectRatioChanged()));

    connect(ui->lineEdit_PixelSize_X,SIGNAL(editingFinished()),this,SLOT(PixelSize_XChanged()));
    connect(ui->lineEdit_PixelSize_Y,SIGNAL(editingFinished()),this,SLOT(PixelSize_YChanged()));

    connect(ui->lineEdit_PixelAspectRatio,SIGNAL(editingFinished()),this,SLOT(PixelAspectRatioChanged()));

    connect(ui->lineEdit_SensorSize_X,SIGNAL(editingFinished()),this,SLOT(SensorSize_XChanged()));
    connect(ui->lineEdit_SensorSize_Y,SIGNAL(editingFinished()),this,SLOT(SensorSize_YChanged()));

    connect(ui->lineEdit_focalLength,SIGNAL(editingFinished()),this,SLOT(focalLengthChanged()));

    connect(ui->lineEdit_baseline_X,SIGNAL(editingFinished()),this,SLOT(baseline_XChanged()));
    connect(ui->lineEdit_baseline_Y,SIGNAL(editingFinished()),this,SLOT(baseline_YChanged()));

    connect(ui->lineEdit_D1_X,SIGNAL(editingFinished()),this,SLOT(D1_XChanged()));
    connect(ui->lineEdit_d1_X,SIGNAL(editingFinished()),this,SLOT(d1_XChanged()));
    connect(ui->lineEdit_D1_Y,SIGNAL(editingFinished()),this,SLOT(D1_YChanged()));
    connect(ui->lineEdit_d1_Y,SIGNAL(editingFinished()),this,SLOT(d1_YChanged()));

    connect(ui->lineEdit_D2_X,SIGNAL(editingFinished()),this,SLOT(D2_XChanged()));
    connect(ui->lineEdit_d2_X,SIGNAL(editingFinished()),this,SLOT(d2_XChanged()));
    connect(ui->lineEdit_D2_Y,SIGNAL(editingFinished()),this,SLOT(D2_YChanged()));
    connect(ui->lineEdit_d2_Y,SIGNAL(editingFinished()),this,SLOT(d2_YChanged()));

    connect(ui->lineEdit_DH_X,SIGNAL(editingFinished()),this,SLOT(DH_XChanged()));
    connect(ui->lineEdit_dH_X,SIGNAL(editingFinished()),this,SLOT(dH_XChanged()));
    connect(ui->lineEdit_DH_Y,SIGNAL(editingFinished()),this,SLOT(DH_YChanged()));
    connect(ui->lineEdit_dH_Y,SIGNAL(editingFinished()),this,SLOT(dH_YChanged()));

    connect(ui->lineEdit_delta_D_X,SIGNAL(editingFinished()),this,SLOT(delta_D_XChanged()));
    connect(ui->lineEdit_delta_D_Y,SIGNAL(editingFinished()),this,SLOT(delta_D_YChanged()));
    connect(ui->lineEdit_delta_d_X,SIGNAL(editingFinished()),this,SLOT(delta_d_XChanged()));
    connect(ui->lineEdit_delta_d_Y,SIGNAL(editingFinished()),this,SLOT(delta_d_YChanged()));

    connect(ui->lineEdit_f_number,SIGNAL(editingFinished()),this,SLOT(f_numberChanged()));
    connect(ui->lineEdit_subject_distance,SIGNAL(editingFinished()),this,SLOT(subject_distanceChanged()));
    connect(ui->lineEdit_coc,SIGNAL(editingFinished()),this,SLOT(CoC()));

    connect(ui->lineEdit_Cam_X,SIGNAL(editingFinished()),this,SLOT(camX_Changed()));
    connect(ui->lineEdit_Cam_Y,SIGNAL(editingFinished()),this,SLOT(camY_Changed()));

    connect(ui->lineEdit_stprecision,SIGNAL(editingFinished()),this,SLOT(stprecision_Changed()));


    connect(ui->lineEdit_Cam_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_Cam_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_Resolution_X__px,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_Resolution_Y__px,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_AspectRatio,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_PixelSize_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_PixelSize_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_PixelAspectRatio,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_SensorSize_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_focalLength,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_baseline_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_baseline_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_D1_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_d1_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_D2_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_d2_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_DH_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_dH_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_D1_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_d1_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_D2_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_d2_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_DH_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_dH_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_delta_D_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_delta_d_X,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_delta_D_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_delta_d_Y,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_D_N,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_D_F,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_f_number,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_H_DoF,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_subject_distance,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_DoF,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_coc,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));
    connect(ui->lineEdit_stprecision,SIGNAL(textChanged(QString)),this,SLOT(setUserInput(QString)));

    connect(ui->lineEdit_focallength_jitter,SIGNAL(textChanged(QString)),this,SLOT(focallengthJitter_text(QString)));
    connect(ui->lineEdit_baseline_jitter,SIGNAL(textChanged(QString)),this,SLOT(baselineJitter_text(QString)));
    connect(ui->lineEdit_rotation_jitter,SIGNAL(textChanged(QString)),this,SLOT(rotationJitter_text(QString)));





    connect(ui->checkBox_camX,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_camY,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_Resolution_X__px, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_Resolution_Y, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_AspectRatio, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_PixelSize_X, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_PixelSize_Y, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_PixelAspectRatio, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_SensorSize_X, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_focalLength, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_baseline_X, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_baseline_Y,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_D1_X, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_d1_X, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_D2_X, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_d2_X, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));

    connect(ui->checkBox_DH_X, SIGNAL(clicked(bool)), this, SLOT(DH_XBoxChanged(bool)));
    connect(ui->checkBox_dH_X, SIGNAL(clicked(bool)), this, SLOT(dH_XBoxChanged(bool)));

    connect(ui->checkBox_D1_Y,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_d1_Y,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_D2_Y,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_d2_Y,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));

    connect(ui->checkBox_DH_Y,SIGNAL(clicked(bool)),this,SLOT(DH_YBoxChanged(bool)));
    connect(ui->checkBox_dH_Y,SIGNAL(clicked(bool)),this,SLOT(dH_YBoxChanged(bool)));

    connect(ui->checkBox_baseline_jitter_X,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_baseline_jitter_Y,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_baseline_jitter_Z,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));

    connect(ui->checkBox_rotation_jitter_X,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_rotation_jitter_Y,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_rotation_jitter_Z,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));

    connect(ui->checkBox_delta_D_X, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_delta_d_X, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_delta_D_Y,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_delta_d_Y,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));

    connect(ui->lineEdit_baseline_jitter,SIGNAL(editingFinished()),this,SLOT(baselineJitter_edit()));
    connect(ui->lineEdit_focallength_jitter,SIGNAL(editingFinished()),this,SLOT(focallengthJitter_edit()));
    connect(ui->lineEdit_rotation_jitter,SIGNAL(editingFinished()),this,SLOT(rotationJitter_edit()));

    connect(ui->checkBox_baseline_jitter,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_focallength_jitter,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));
    connect(ui->checkBox_rotation_jitter,SIGNAL(clicked(bool)),this,SLOT(Slot_update(bool)));

    connect(ui->checkBox_f_number, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_subject_distance, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));
    connect(ui->checkBox_coc, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));

    connect(ui->checkBox_stprecision, SIGNAL(clicked(bool)), this, SLOT(Slot_update(bool)));





// Sliders

    connect(ui->horizontalSlider_focalLength, SIGNAL(valueChanged(int)), this, SLOT(focalLengthSlider(int)));
    ui->horizontalSlider_focalLength->setValue(33);
    focalLengthSliderSave=0.0;

    connect(ui->horizontalSlider_baseline_X, SIGNAL(valueChanged(int)), this, SLOT(baseline_XSlider(int)));
    ui->horizontalSlider_baseline_X->setValue(33);
    baseline_XSliderSave=0.0;

    connect(ui->horizontalSlider_baseline_Y, SIGNAL(valueChanged(int)), this, SLOT(baseline_YSlider(int)));
    ui->horizontalSlider_baseline_Y->setValue(33);
    baseline_YSliderSave=0.0;

    connect(ui->horizontalSlider_dH_X, SIGNAL(valueChanged(int)), this, SLOT(dH_XSlider(int)));
    ui->horizontalSlider_dH_X->setValue(33);
    dH_XSliderSave=0.0;

    connect(ui->horizontalSlider_dH_Y, SIGNAL(valueChanged(int)), this, SLOT(dH_YSlider(int)));
    ui->horizontalSlider_dH_Y->setValue(33);
    dH_YSliderSave=0.0;

    connect(ui->horizontalSlider_subject_distance, SIGNAL(valueChanged(int)), this, SLOT(subject_distanceSlider(int)));
    ui->horizontalSlider_subject_distance->setValue(33);
    subject_distanceSliderSave=0.0;

    connect(ui->horizontalSlider_DH_X, SIGNAL(valueChanged(int)), this, SLOT(DH_XSlider(int)));
    ui->horizontalSlider_DH_X->setValue(33);
    DH_XSliderSave=0.0;

    connect(ui->horizontalSlider_DH_Y, SIGNAL(valueChanged(int)), this, SLOT(DH_YSlider(int)));
    ui->horizontalSlider_DH_Y->setValue(33);
    DH_YSliderSave=0.0;

    connect(ui->checkBox_Lock_baseline,SIGNAL(stateChanged(int)),this,SLOT(Lock_baseline(int)));
    connect(ui->checkBox_Lock_dH,SIGNAL(stateChanged(int)),this,SLOT(Lock_dh(int)));
    connect(ui->checkBox_Lock_DH,SIGNAL(stateChanged(int)),this,SLOT(Lock_Dh(int)));
    connect(ui->checkBox_Lock_subjectDistance,SIGNAL(stateChanged(int)),this,SLOT(Lock_subjectDistance(int)));


}

void LFCamConfigurator::createActions(){

    openAct = new QAction(QIcon(":/open.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setToolTip(tr("Open image sequence"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(load())) ;

    saveAsAct = new QAction(QIcon(":/saveAs.png"), tr("&SaveAs"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setToolTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(save()));

    ResetAct = new QAction(QIcon(":/reset.png"),tr("&Reset"), this);
    ResetAct->setToolTip(tr("Reset"));
    connect(ResetAct, SIGNAL(triggered()), this, SLOT(resetUI()));

    ExportBlenderAct = new QAction(QIcon(":/blender.png"),tr("&Export to Blender"), this);
    ExportBlenderAct->setToolTip(tr("Export to Blender"));
    connect(ExportBlenderAct, SIGNAL(triggered()), this, SLOT(expBlender()));

//    aboutAct = new QAction(tr("&About"), this);
//    connect(aboutAct, SIGNAL(triggered()), this, SLOT(close()));

    HelpAct = new QAction(QIcon(":/help.png"),tr("&Help"), this);
    connect(HelpAct, SIGNAL(triggered()), this, SLOT(help()));

    exitAct = new QAction(QIcon(":/exit.png"),tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}
