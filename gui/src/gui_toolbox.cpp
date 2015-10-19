#include "gui_toolbox.h"

#ifdef _MSC_VER
#include "ui_gui_windows.h"
#elif __GNUC__
#include "ui_gui_linux.h"
#endif

#include <iostream>
#include <vector>
#include <iomanip>





/*************************************************************
 *                     Constructor
 *************************************************************/
GUI_Toolbox::GUI_Toolbox(QWidget *parent) : QMainWindow(parent), ui(new Ui::GUI_Toolbox){

    ui->setupUi(this);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    createUIActions();

    ui->Slider_selectHoropter->setEnabled(false);
    ui->Button_ApplyHoropter->setEnabled(false);
    ui->lineEdit_cut_X->setEnabled(false);
    ui->lineEdit_cut_Y->setEnabled(false);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    //setWindowTitle(tr("Light Field Toolbox"));
}
/*************************************************************
 *                     Destructor
 *************************************************************/
GUI_Toolbox::~GUI_Toolbox(){
    delete ui;
}
/*************************************************************
 *                Define Menubar without UI
 *************************************************************/
void GUI_Toolbox::createMenus(){
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);
    menuBar()->setNativeMenuBar(false);
}
/*************************************************************
 *                Define Toolbar without UI
 *************************************************************/
void GUI_Toolbox::createToolBars(){
//    ToolBar defined in source code
    fileToolBar = addToolBar(tr("Tools"));
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveAsAct);
    fileToolBar->addAction(exitAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(showMainAct);
    fileToolBar->addAction(showAct);
	fileToolBar->addSeparator();
	fileToolBar->addAction(showAct_Node);

}
/*************************************************************
 *                Define Statusbar without UI
 *************************************************************/
void GUI_Toolbox::createStatusBar(){
    statusBar()->showMessage(tr("Ready"));
}


