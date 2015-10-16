#include "gui_toolbox.h"

#ifdef _MSC_VER
#include "ui_gui_windows.h"
#elif __GNUC__
#include "ui_gui_linux.h"
#endif

//#include "tools/LFCamConfigurator/includes/lfcamconfigurator.h"

#ifndef __APPLE__
	#include <omp.h>
#endif



/*************************************************************
 *                              Slots
 *************************************************************/

void GUI_Toolbox::OpenLFCamConfigurator(){

    LFCamConfigurator *LFCC = new LFCamConfigurator();
	LFCC->show();
}

void GUI_Toolbox::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>LF Image Viewer</b> displays EPIs and LF animations"));
}

void GUI_Toolbox::showNode()
{
	QNEMainWindow *QNEMW = new QNEMainWindow();
	QNEMW->show();
}


