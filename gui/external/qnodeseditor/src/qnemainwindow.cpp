/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Modified by: Maximilian Diebold
			 Hendrik Siedelmann
			 Sven Wanner

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/

#include "comp_epi.hpp"
#include "comp_lfread.hpp"
#include "comp_lfwrite.hpp"
#include "operators.hpp"

#include "qnemainwindow.h"
#include "userinterface_qnemainwindow.h"

#include "qneblock.h"
#include "qnodeseditor.h"

#include <QGraphicsScene>
#include <QFileDialog>

#include "qneport.h"
#include <iostream>


template <class T> class QVP
{  
public:
    static T* asPtr(QVariant v) { return  (T *) v.value<void *>(); }
    static QVariant asQVariant(T* ptr) { return qVariantFromValue((void *) ptr); }
};

QNEMainWindow::QNEMainWindow(QWidget *parent)  :  QMainWindow(parent)
{
	mdiArea = new QMdiArea;
	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setCentralWidget(mdiArea);

	slider = new QSlider(Qt::Horizontal);
	spinBox = new QSpinBox();


	createActions();
	createMenus();
	createToolBars();
	createDockWindows();

	_circuitViewer = new Circuit_Viewer();
	mdiArea->addSubWindow(_circuitViewer);
	_circuitViewer->setObjectName("circuitViewer");
	_circuitViewer->show();

	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

}
QNEMainWindow::~QNEMainWindow()
{
	mdiArea->closeAllSubWindows();
}

void QNEMainWindow::on_action_Pop_Out_triggered()
{
	if (mdiArea->activeSubWindow()){
		QMdiSubWindow *sub = mdiArea->activeSubWindow();
		QWidget *wid = sub->widget();
		wid->hide();
		sub->deleteLater();
		mdiArea->removeSubWindow(wid);
		wid->show();
	}
}


void QNEMainWindow::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(addAct);
	fileMenu->addAction(loadAct);
	fileMenu->addAction(saveAct);
	//fileMenu->addSeparator();
	fileMenu->addAction(quitAct);

	helpMenu = new QMenu(tr("&Help"), this);

	viewMenu = new QMenu(tr("&File"), this);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(helpMenu);
	menuBar()->addMenu(viewMenu);

	

}


void QNEMainWindow::createToolBars()
{
	//ToolBar defined in source code
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(addAct);
	fileToolBar->addAction(loadAct);
	fileToolBar->addAction(saveAct);
	fileToolBar->addAction(popOutAct);
	fileToolBar->addSeparator();
	fileToolBar->addAction(quitAct);


	fileToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}


/*

SIGNALS

*/

void QNEMainWindow::createActions()
{
	quitAct = new QAction(QIcon(":/images/exit.png"), tr("&Quit"), this);
	quitAct->setShortcuts(QKeySequence::Quit);
	quitAct->setStatusTip(tr("Quit the application"));
	connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

	loadAct = new QAction(QIcon(":/images/open.png"), tr("&Load"), this);
	loadAct->setShortcuts(QKeySequence::Open);
	loadAct->setStatusTip(tr("Open a file"));
	connect(loadAct, SIGNAL(triggered()), this, SLOT(loadFile()));

	saveAct = new QAction(QIcon(":/images/arrow.png"), tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save a file"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

	addAct = new QAction(QIcon(":/images/arrow.png"), tr("&Add"), this);
	addAct->setStatusTip(tr("Add a block"));
	connect(addAct, SIGNAL(triggered()), this, SLOT(addBlock()));

	popOutAct = new QAction(QIcon(":/images/arrow.png"), tr("popOut"), this);
	popOutAct->setStatusTip(tr("Pop Out Subwindow as own Window."));
	connect(popOutAct, SIGNAL(triggered()), this, SLOT(on_action_Pop_Out_triggered()));

}


/*

SLOTS

*/


void QNEMainWindow::saveFile()
{
	QString fname = QFileDialog::getSaveFileName();
	if (fname.isEmpty())
		return;

	QFile f(fname);
	f.open(QFile::WriteOnly);
	QDataStream ds(&f);
	nodesEditor->save(ds);
}

void QNEMainWindow::loadFile()
{
	QString fname = QFileDialog::getOpenFileName();
	if (fname.isEmpty())
		return;

	QFile f(fname);
	f.open(QFile::ReadOnly);
	QDataStream ds(&f);
	nodesEditor->load(ds);
}

void QNEMainWindow::addBlock()
{
    QNEBlock *b = new QNEBlock(0);

    scene->addItem(b);
	static const char* names[] = {"Vin", "Voutsadfasdf", "Imin", "Imax", "mul", "add", "sub", "div", "Conv", "FFT"};
	for (int i = 0; i < 4 + rand() % 3; i++)
	{
		b->addPort(names[rand() % 10], rand() % 2, 0, 0);
        b->setPos(view->sceneRect().center().toPoint());
	}
}



void QNEMainWindow::addComponent(QListWidgetItem *it)
{
  DspComponent *comp = QVP<DspComponent>::asPtr(it->data(Qt::UserRole));
  
  comp = comp->clone();

  _circuitViewer->addComponent(comp);
}


void QNEMainWindow::createDockWindows()
{
	mdiArea->closeAllSubWindows();

	if (dock != NULL){
		delete dock;
	}

	dock = new QDockWidget(tr("Light Field Channels:"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	List1 = new QListWidget(dock);
	dock->setWidget(List1);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	viewMenu->addAction(dock->toggleViewAction());

	// populate the items of the list
	//for (int i = 0; i < 10; i++)
	//{
        QListWidgetItem *it;
        it = new QListWidgetItem("LF reader");
        it->setData(Qt::UserRole, QVP<DspComponent>::asQVariant(new COMP_LFRead()));
        List1->addItem(it);
        
        it = new QListWidgetItem("LF writer");
        it->setData(Qt::UserRole, QVP<DspComponent>::asQVariant(new COMP_LFWrite()));
        List1->addItem(it);
        
        it = new QListWidgetItem("EPI");
        it->setData(Qt::UserRole, QVP<DspComponent>::asQVariant(new COMP_Epi()));
        List1->addItem(it);
        
        it = new QListWidgetItem("GAUSCH");
        it->setData(Qt::UserRole, QVP<DspComponent>::asQVariant(new OP_VigraGauss()));
        List1->addItem(it);
	//}

	connect(List1, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(addComponent(QListWidgetItem*)));

	docks.push_back(dock);
	// ******************************************************************
}












Circuit_Viewer::Circuit_Viewer(QWidget *parent) : QWidget(parent)
{
  
  this->setMinimumSize(600,600);
  //this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  setAttribute(Qt::WA_DeleteOnClose);
  setMouseTracking(true);
  
  scrollArea = new QScrollArea;
  scrollArea->setBackgroundRole(QPalette::Dark);
  
  createActions();
  createToolbar();
  
  _circuit = new DspCircuit();
  
  
  _scene = new QGraphicsScene();
  
  
  _view = new QGraphicsView(this);
  _view->setScene(_scene);
  //_view->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  _view->setMinimumSize(600,600);
  
  _view->setRenderHint(QPainter::Antialiasing, true);
  
  _editor = new QNodesEditor(this);
  _editor->install(_scene);
  
  
  QNEBlock *b = new QNEBlock(0);
  _scene->addItem(b);
  b->addPort("test", 0, QNEPort::NamePort);
  b->addPort("TestBlock", 0, QNEPort::TypePort);
  b->addInputPort("in1");
  b->addInputPort("in2");
  b->addInputPort("in3");
  b->addOutputPort("out1");
  b->addOutputPort("out2");
  b->addOutputPort("out3");
  
  b = b->clone();
  b->setPos(150, 0);
  
  b = b->clone();
  b->setPos(150, 150);
}

void Circuit_Viewer::createActions()
{
	saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	saveAsAct = new QAction(tr("Save &As..."), this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

	zoomInAct = new QAction(QIcon(":/images/Zoom-In.png"), tr("Zoom &In (25%)"), this);
	zoomInAct->setShortcut(tr("Ctrl++"));
	connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

	zoomOutAct = new QAction(QIcon(":/images/Zoom-Out.png"), tr("Zoom &Out (25%)"), this);
	zoomOutAct->setShortcut(tr("Ctrl+-"));
	connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

	normalSizeAct = new QAction(tr("&Normal Size"), this);
	normalSizeAct->setShortcut(tr("Ctrl+S"));
	connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

	fitToWindowAct = new QAction(tr("&Fit to Window"), this);
	fitToWindowAct->setCheckable(true);
	fitToWindowAct->setShortcut(tr("Ctrl+F"));
	connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
}

void Circuit_Viewer::createToolbar()
{
	QToolBar* toolBar = new QToolBar(this);
	toolBar->setFixedHeight(ToolBar_Height);
	toolBar->addAction(saveAct);
	toolBar->addAction(zoomInAct);
	toolBar->addAction(zoomOutAct);
	toolBar->addAction(normalSizeAct);
	toolBar->addAction(fitToWindowAct);

	QVBoxLayout* vbox = new QVBoxLayout(this);

	vbox->addWidget(toolBar);
	vbox->addWidget(scrollArea);
	vbox->setContentsMargins(0, 0, 0, 0);
	vbox->setSpacing(0);
}

void Circuit_Viewer::normalSize()
{
}

void Circuit_Viewer::zoomIn()
{
	scaleImage(1.25);
}

void Circuit_Viewer::zoomOut()
{
	scaleImage(0.8);
}

void Circuit_Viewer::fitToWindow()
{
	bool fitToWindow = fitToWindowAct->isChecked();
	scrollArea->setWidgetResizable(fitToWindow);
	if (!fitToWindow) {
		normalSize();
	}
	zoomInAct->setEnabled(!fitToWindowAct->isChecked());
	zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
}

static int counter = 0;

void Circuit_Viewer::addComponent(DspComponent *comp)
{
  char buf[64];
  sprintf(buf, "whatefer%d", counter++);
  bool success = _circuit->AddComponent(comp, buf);
  assert(success);
    
  new QNEBlock(comp, _scene);
}

void Circuit_Viewer::scaleImage(double factor)
{
	//Q_ASSERT(imageLabel->pixmap());
	//scaleFactor *= factor;
	//imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

	adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
	adjustScrollBar(scrollArea->verticalScrollBar(), factor);

	zoomInAct->setEnabled(factor < 3.0);
	zoomOutAct->setEnabled(factor > 0.333);
}
void Circuit_Viewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
	scrollBar->setValue(int(factor * scrollBar->value()	+ ((factor - 1) * scrollBar->pageStep() / 2)));
}
void Circuit_Viewer::save()
{
}

void Circuit_Viewer::saveAs()
{
}