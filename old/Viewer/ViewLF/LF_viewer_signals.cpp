#include "LF_viewer.h"
#include <QtGui>

void LF_Viewer::createActions()
 {
    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openLightField())) ;

    exitAct = new QAction(QIcon(":/images/exit.png"),tr("Close Light Field"), this);
    exitAct->setShortcut(tr("Ctrl+Alt+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    closeAct = new QAction(QIcon(":/images/exit.png"),tr("Close Windows"), this);
    closeAct->setShortcut(tr("Ctrl+Q"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(closeAll()));

    infoAct = new QAction(QIcon(":/images/info.png"),tr("Info"), this);
    infoAct->setStatusTip(tr("Infos about loaded light field"));
    connect(infoAct, SIGNAL(triggered()), this, SLOT(info()));

    popOutAct = new QAction(QIcon(":/images/arrow.png"),tr("popOut"), this);
    popOutAct->setStatusTip(tr("Pop Out Subwindow as own Window."));
    connect(popOutAct, SIGNAL(triggered()), this, SLOT(on_action_Pop_Out_triggered()));

    connect(spinBox, SIGNAL(valueChanged(int)),slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)),spinBox, SLOT(setValue(int)));
}


