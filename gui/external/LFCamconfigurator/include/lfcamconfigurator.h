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

#ifndef LFCAMCONFIGURATOR_H
#define LFCAMCONFIGURATOR_H

#include <iostream>
#include <string>
#include <QMainWindow>
#include <QObject>
#include <ConfigParser.h>
#include <QFileDialog>
#include <QLabel>
#include <QScrollArea>
#include "class_LFsetup.h"


using namespace std;


class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    HelpDialog();

private:
    QLabel *label;
    QPixmap *pxmap;
};


namespace Ui {

class LFCamConfigurator;

}

class LFCamConfigurator : public QMainWindow
{
    Q_OBJECT

public:
    void update();
    explicit LFCamConfigurator(QWidget *parent = 0);
    ~LFCamConfigurator();

public slots:

    void SimpleButtonPressed();
    void resolution_XChanged();
    void AspectRatioChanged();
    void PixelSize_XChanged();
    void PixelAspectRatioChanged();
    void SensorSize_XChanged();
    void focalLengthChanged();
    void baseline_XChanged();
    void D1_XChanged();
    void d1_XChanged();
    void D2_XChanged();
    void d2_XChanged();
    void DH_XChanged();
    void dH_XChanged();
    void DHopt_XChanged();
    void delta_D_XChanged();
    void delta_d_XChanged();
    void f_numberChanged();
    void subject_distanceChanged();
    void resolution_YChanged();
    void PixelSize_YChanged();
    void SensorSize_YChanged();
    void baseline_YChanged();
    void D1_YChanged();
    void d1_YChanged();
    void D2_YChanged();
    void d2_YChanged();
    void DH_YChanged();
    void dH_YChanged();
    void DHopt_YChanged();
    void delta_D_YChanged();
    void delta_d_YChanged();
    void camX_Changed();
    void camY_Changed();
    void CoC();
    void stprecision_Changed();

    void setUserInput(QString);
    void Slot_update(bool);

    void DH_XBoxChanged(bool);
    void dH_XBoxChanged(bool);
    void DH_YBoxChanged(bool);
    void dH_YBoxChanged(bool);


    void focallengthJitter_text(QString);
    void focallengthJitter_edit();
    void baselineJitter_text(QString);
    void baselineJitter_edit();
    void rotationJitter_text(QString);
    void rotationJitter_edit();

    void focalLengthSlider(int);
    void baseline_XSlider(int);
    void baseline_YSlider(int);
    void dH_XSlider(int);
    void dH_YSlider(int);
    void DH_XSlider(int);
    void DH_YSlider(int);
    void subject_distanceSlider(int);

    void Lock_baseline(int);
    void Lock_dh(int);
    void Lock_Dh(int);
    void Lock_subjectDistance(int);

    void resetUI();
    void load();
    void save();
    void expBlender();
    void expFramework();
    void help();

    void get_UIvalues();
    void set_UIvalues();
    void connect_signals();


//    void baselineChanged(int);
//    void baselineChanged(QString);
//    void focalLengthChanged(int);
//    void focalLengthChanged(QString);
//    void horopterChanged(int);
//    void horopterChanged(QString);
//    void sensorChanged(QString);
//    void imgwidthChanged(QString);
//    void dlowChanged(QString);
//    void dhighChanged(QString);

private:
    Ui::LFCamConfigurator *ui;
    LFsetup *setup;

    void createActions();
    void createMenus();

    QAction *openAct;
    QAction *saveAsAct;
    QAction *ResetAct;
    QAction *ExportBlenderAct;
    QAction *aboutAct;
    QAction *HelpAct;
    QAction *exitAct;


    QMenu *fileMenu;
    QMenu *helpMenu;

    QScrollArea *scrollArea;

    bool HiddenFlag;

    //hilfsvariablen
    double focalLengthSliderSave;
    double baseline_XSliderSave;
    double baseline_YSliderSave;
    double dH_XSliderSave;
    double dH_YSliderSave;
    double DH_XSliderSave;
    double DH_YSliderSave;
    double subject_distanceSliderSave;
    bool justChanged;
    HelpDialog *helpDialog;
    bool userinput;

};

#endif // LFCAMCONFIGURATOR_H
