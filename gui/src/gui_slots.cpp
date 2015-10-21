#include "gui_toolbox.h"

//#ifdef _MSC_VER
//#include "ui_gui_windows.h"
//#elif __GNUC__
//#include "ui_gui_linux.h"
//#endif
#include "ui_toolbox_ui.h"

#ifndef __APPLE__
	#include <omp.h>
#endif


/*************************************************************
 *                              Slots
 *************************************************************/

void GUI_Toolbox::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>LF Image Viewer</b> displays EPIs and LF animations"));
}

void GUI_Toolbox::OpenLFCamConfigurator(){

	LFCamConfigurator *LFCC = new LFCamConfigurator();
	LFCC->show();
}

void GUI_Toolbox::showNode()
{
	QNEMainWindow *_QNEMW = new QNEMainWindow();
	_QNEMW->show();

}

void GUI_Toolbox::showViewer()
{
	QNEMainWindow *_QNEMW = new QNEMainWindow();
	_QNEMW->show();

}

void GUI_Toolbox::showAnimator()
{
	QNEMainWindow *_QNEMW = new QNEMainWindow();
	_QNEMW->show();

}



