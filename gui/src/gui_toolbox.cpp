#include "gui_toolbox.h"

//#ifdef _MSC_VER
//#include "ui_gui_windows.h"
//#elif __GNUC__
//#include "ui_gui_linux.h"
//#endif
#include "ui_toolbox_ui.h"

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
//    createToolBars();
    createStatusBar();

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
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
    
    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);
    menuBar()->setNativeMenuBar(false);
}

/*************************************************************
 *                Define Statusbar without UI
 *************************************************************/
void GUI_Toolbox::createStatusBar(){
    statusBar()->showMessage(tr("Ready"));
}


