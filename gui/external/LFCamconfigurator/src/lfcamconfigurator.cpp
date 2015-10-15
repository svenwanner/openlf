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

#include "ConfigParser.h"
#include <QApplication>
#include <QtGui>

HelpDialog::HelpDialog()
{
    label = new QLabel(this);
    label->setBackgroundRole(QPalette::Base);
    label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    label->setScaledContents(true);
    pxmap = new QPixmap(":/Hilfe.png");

    label->setPixmap(*pxmap);
    label->resize(0.8*label->pixmap()->size());

}

void LFCamConfigurator::createMenus(){
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(ResetAct);
    fileMenu->addAction(ExportBlenderAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(HelpAct);
//    helpMenu->addAction(aboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);
    menuBar()->setNativeMenuBar(false);
}

LFCamConfigurator::LFCamConfigurator(QWidget *parent) : QMainWindow(parent),ui(new Ui::LFCamConfigurator) {

    ui->setupUi(this);
    createActions();
    createMenus();
    //disable lineEdit

    ui->lineEdit_D_N->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_D_F->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_H_DoF->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_DoF->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_Framesize_Y_at_DH->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_DHopt_X->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_theta_X->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_theta_Y->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_Framesize_X_at_DH->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_DHopt_Y->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_AperturAngle_X->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_AperturAngle_Y->setStyleSheet( "background-color: gray; color : black;" );

    ui->lineEdit_geoH1->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_geoH2->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_geoHH->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_geoV1->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_geoVH->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_geoV2->setStyleSheet( "background-color: gray; color : black;" );

    ui->lineEdit_stH1->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_stH2->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_stHH->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_stV1->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_stVH->setStyleSheet( "background-color: gray; color : black;" );
    ui->lineEdit_stV2->setStyleSheet( "background-color: gray; color : black;" );

    ui->lineEdit_stprecision->setStyleSheet( "background-color: green; color : black;" );

    ui->lineEdit_DHopt_X->setEnabled(false);
    ui->lineEdit_DHopt_Y->setEnabled(false);
    ui->lineEdit_AperturAngle_X->setEnabled(false);
    ui->lineEdit_AperturAngle_Y->setEnabled(false);
    ui->lineEdit_Framesize_X_at_DH->setEnabled(false);
    ui->lineEdit_Framesize_Y_at_DH->setEnabled(false);
    ui->lineEdit_H_DoF->setEnabled(false);
    ui->lineEdit_D_N->setEnabled(false);
    ui->lineEdit_D_F->setEnabled(false);
    ui->lineEdit_DoF->setEnabled(false);
    ui->lineEdit_theta_X->setEnabled(false);
    ui->lineEdit_theta_Y->setEnabled(false);

    ui->lineEdit_geoH1->setEnabled(false);
    ui->lineEdit_geoHH->setEnabled(false);
    ui->lineEdit_geoH2->setEnabled(false);
    ui->lineEdit_geoV1->setEnabled(false);
    ui->lineEdit_geoVH->setEnabled(false);
    ui->lineEdit_geoV2->setEnabled(false);
    ui->lineEdit_stH1->setEnabled(false);
    ui->lineEdit_stHH->setEnabled(false);
    ui->lineEdit_stH2->setEnabled(false);
    ui->lineEdit_stV1->setEnabled(false);
    ui->lineEdit_stVH->setEnabled(false);
    ui->lineEdit_stV2->setEnabled(false);


    setWindowTitle("LFCam Configurator");

    setup = new LFsetup();
    helpDialog = new HelpDialog();

    userinput = false;
    justChanged = false;
    HiddenFlag = false;


    /****************************************************************************************************
     *                                      Signals from the User Interface
     ****************************************************************************************************/
    connect_signals();


   resetUI();

}


LFCamConfigurator::~LFCamConfigurator()
{

    delete ui;
    delete setup;
}

