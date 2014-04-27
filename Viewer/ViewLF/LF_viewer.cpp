#include "LF_viewer.h"
#include "ui_MainWindow.h"
#include <QDockWidget>


LF_Viewer::LF_Viewer()
 {
    ui->setupUi(this);

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    //setCentralWidget(scrollArea);

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    mdiArea->addSubWindow(scrollArea);


    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    setWindowTitle(tr("Image Viewer"));
    //resize(500, 400);
}



void LF_Viewer::createMenus()
 {
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&View"));

    ImageMenu = new QMenu(tr("&Image"), this);
    ImageMenu->addAction(zoomInAct);
    ImageMenu->addAction(zoomOutAct);
    ImageMenu->addAction(normalSizeAct);
    ImageMenu->addSeparator();
    ImageMenu->addAction(fitToWindowAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    //menuBar()->addSeparator();
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(ImageMenu);
    menuBar()->addMenu(helpMenu);
}


void LF_Viewer::createToolBars()
 {
    //First Toolbar generated in Forms
    ui->toolBar->addAction(openAct);
    ui->toolBar->addAction(saveAct);


    //Second ToolBar defined in source code
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(printAct);
    fileToolBar->addAction(zoomInAct);
    fileToolBar->addAction(zoomOutAct);
    fileToolBar->addAction(infoAct);
    fileToolBar->addAction(exitAct);

}

void LF_Viewer::createStatusBar()
 {
    statusBar()->showMessage(tr("Ready"));
}



























/*
LF_Viewer::LF_Viewer(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    //
    //QWidget *popup = new QWidget();
    //mdiArea->addSubWindow(popup);
    //popup->show();
    MdiChild *child = createMdiChild();
    child->show();

    setWindowTitle(tr("LF_Viewer"));
    setUnifiedTitleAndToolBarOnMac(true);
}



void LF_Viewer::createMenus()
 {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addSeparator();
    QAction *action = fileMenu->addAction(tr("Switch layout direction"));
    connect(action, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));
    fileMenu->addAction(exitAct);

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    windowMenu = menuBar()->addMenu(tr("&Window"));
    //updateWindowMenu();
    //connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    menuBar()->addSeparator();

    LFMenu = menuBar()->addMenu((tr("&Light Field")));
    LFMenu->addAction(infoAct);
    LFMenu->addAction(printAct);
    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void LF_Viewer::createToolBars()
 {
    //First Toolbar generated in Forms
    ui->toolBar->addAction(openAct);
    ui->toolBar->addAction(saveAct);

    //Second ToolBar defined in source code
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(printAct);
    fileToolBar->addAction(infoAct);
    fileToolBar->addAction(exitAct);

}

void LF_Viewer::createStatusBar()
 {
    statusBar()->showMessage(tr("Ready"));
}










*/
