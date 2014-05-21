#include "LF_viewer.h"

LF_Viewer::LF_Viewer()
 {
    is_Clicked = false;

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();


    //vbox->addWidget(view);
    //vbox->setContentsMargins(20,20,1000,1000);
    //vbox->setSpacing(0);

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);



    setWindowTitle(tr("Light Field Viewer"));
    //resize(500, 400);
}



void LF_Viewer::createMenus()
 {
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    //menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);
}


void LF_Viewer::createToolBars()
 {
    //ToolBar defined in source code
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(infoAct);
    //fileToolBar->addAction(aboutAct);
    fileToolBar->addAction(exitAct);

}

void LF_Viewer::createStatusBar()
 {
    statusBar()->showMessage(tr("Ready"));
}








