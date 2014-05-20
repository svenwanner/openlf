#include "LF_viewer.h"
#include "ui_MainWindow.h"
#include <QDockWidget>
#include <string>

void LF_Viewer::createDockWindows()
 {

    dock = new QDockWidget(tr("Light Field Channels:"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    ChannelList = new QListWidget(dock);
    dock->setWidget(ChannelList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    //viewMenu->addAction(dock->toggleViewAction());

    dock2 = new QDockWidget(tr("Light Field Properies:"), this);
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    ParameterList = new QListWidget(dock2);
    dock2->setWidget(ParameterList);
    addDockWidget(Qt::RightDockWidgetArea, dock2);
    //viewMenu->addAction(dock2->toggleViewAction());



// Load Items to dock
    std::string *channel_list = new std::string[40];
    channel_list[0]="Color";
    channel_list[1]="r";
    channel_list[2]="g";
    channel_list[3]="b";

    int No_of_Channels = 4;

    for (int i = 0 ; i < No_of_Channels ; i++ ){
        ChannelList->addItems(QStringList()
                << channel_list[i].c_str());
    }


// Load Items to dock2
    std::stringstream view;
    for (int i = 0 ; i<lf->cams_h();i++)
    {
        for (int j = 0 ; j<lf->cams_v();j++)
        {
            view << "view" << i << j;
            ParameterList->addItems(QStringList()
                    << view.str().c_str());
            view.str("");
        }
    }

    connect(ChannelList, SIGNAL(currentTextChanged(QString)),
           this, SLOT(openChannel(QString)));
    connect(ParameterList, SIGNAL(currentTextChanged(QString)),
         this, SLOT(openView(QString)));


}




