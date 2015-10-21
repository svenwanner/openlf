#include "gui_toolbox.h"

//#ifdef _MSC_VER
//#include "ui_gui_windows.h"
//#elif __GNUC__
//#include "ui_gui_linux.h"
//#endif
#include "ui_toolbox_ui.h"


/*************************************************************
 *                              Signal
 *************************************************************/
void GUI_Toolbox::createActions(){
    openAct = new QAction(QIcon(":/open.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setToolTip(tr("Open image sequence"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(about()));

    saveAct = new QAction(QIcon(":/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setToolTip(tr("Save the document to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(about()));

    saveAsAct = new QAction(QIcon(":/saveAs.png"), tr("&SaveAs"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setToolTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(about()));

    exitAct = new QAction(QIcon(":/exit.png"),tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    showMainAct = new QAction(QIcon(":/main.png"),tr("&Show"), this);
    showMainAct->setToolTip(tr("Show light-field with EPIs"));
	connect(showMainAct, SIGNAL(triggered()), this, SLOT(about()));

    showAct = new QAction(QIcon(":/Show.png"),tr("&Show"), this);
    showAct->setToolTip(tr("Show animated light-field"));
	connect(showAct, SIGNAL(triggered()), this, SLOT(about()));

	showAct_Node = new QAction(QIcon(":/circuit.png"), tr("&ShowNode"), this);
	showAct_Node->setToolTip(tr("Show workflow"));
	connect(showAct_Node, SIGNAL(triggered()), this, SLOT(showNode()));

}

void GUI_Toolbox::createUIActions(){

	connect(ui->Button_LFCamConfigurator, SIGNAL(clicked()),this, SLOT(OpenLFCamConfigurator()));

}
