#include "LF_viewer.h"
#include <QtGui>

void LF_Viewer::createActions()
 {
    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openLightField())) ;

    //toggleInsideOutAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    //toggleInsideOutAct->setShortcut(tr("Ctrl+O"));
    //connect(toggleInsideOutAct, SIGNAL(triggered()), this, SLOT(open_as_Subwidget()));

    exitAct = new QAction(QIcon(":/images/exit.png"),tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    infoAct = new QAction(QIcon(":/images/info.png"),tr("Info"), this);
    infoAct->setStatusTip(tr("Infos about loaded light field"));
    connect(infoAct, SIGNAL(triggered()), this, SLOT(info()));




}


