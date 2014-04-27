#include "LF_viewer.h"
#include "ui_MainWindow.h"
#include <QDockWidget>

void LF_Viewer::createDockWindows()
 {
    QDockWidget *dock = new QDockWidget(tr("Light Field Channels:"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    List1 = new QListWidget(dock);
    List1->addItems(QStringList()
            << "Channel1"
            << "Channel2"
            << "Channel3"
            << "Channel4"
            << "Channel5");
    dock->setWidget(List1);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("Light Field Properies:"), this);
    ParameterList = new QListWidget(dock);
    ParameterList->addItems(QStringList()
            << "Parameter 1."
            << "Parameter 2 "
            << "Parameter 3 "
            << "Parameter 4 ");
    dock->setWidget(ParameterList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

}


