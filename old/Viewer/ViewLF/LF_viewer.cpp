#include "LF_viewer.h"

LF_Viewer::LF_Viewer()
 {
    is_Clicked = false;
    lf = NULL;
    dock = NULL;
    dock2 = NULL;

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox();


    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    //vbox->addWidget(view);
    //vbox->setContentsMargins(20,20,1000,1000);
    //vbox->setSpacing(0);

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

    setWindowTitle(tr("Light Field Viewer"));

}



void LF_Viewer::createMenus()
 {
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(popOutAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(helpMenu);

    viewMenu = menuBar()->addMenu(tr("&View"));
}


void LF_Viewer::createToolBars()
 {
    //ToolBar defined in source code
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(infoAct);
    fileToolBar->addAction(closeAct);
    fileToolBar->addAction(exitAct);

    //QSpinBox *spinBox = new QSpinBox;
    fileToolBar->addSeparator();
    fileToolBar->addAction(popOutAct);
    fileToolBar->addSeparator();
    fileToolBar->addWidget(spinBox);
    fileToolBar->addWidget(slider);
    spinBox->setToolTip("Horoptor");
    slider->setToolTip("Horoptor");
    slider->setEnabled(false);
    spinBox->setEnabled(false);
    slider->setFixedWidth(400);
    spinBox->setRange(0, 30);
    slider->setRange(0, 30);

    fileToolBar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
}

void LF_Viewer::createStatusBar()
 {
    statusBar()->showMessage(tr("Ready"));
}








