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
#include "comp_dispwrite.hpp"
#include "operators.hpp"

#include "qnemainwindow.h"
#include "userinterface_qnemainwindow.h"

#include "qneblock.h"
#include "qnodeseditor.h"

#include <QGraphicsScene>
#include <QFileDialog>

#include "qneport.h"
#include <iostream>


QNEMainWindow::QNEMainWindow(QWidget *parent)  :  QMainWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	mdiArea = new QMdiArea;
	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setCentralWidget(mdiArea);

	slider = new QSlider(Qt::Horizontal);
	spinBox = new QSpinBox();

	_circuitViewer = new Circuit_Viewer(mdiArea, this);
        
	createActions();
	createMenus();
	createDockWindows();
	createToolBars();
        
	mdiArea->addSubWindow(_circuitViewer);
	_circuitViewer->setObjectName("circuitViewer");
	_circuitViewer->showMaximized();
        
        
	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

}
QNEMainWindow::~QNEMainWindow()
{
	mdiArea->closeAllSubWindows();
}



void QNEMainWindow::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(addAct);
	fileMenu->addAction(loadAct);
	fileMenu->addAction(saveAct);
	fileMenu->addSeparator();
	fileMenu->addAction(quitAct);
        
    QMenu *circuitMenu = new QMenu(tr("&Circuit"), this);
	circuitMenu->addAction(tickAct);

	//helpMenu = new QMenu(tr("&Help"), this);

	viewMenu = new QMenu(tr("&View"), this);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(circuitMenu);
	//menuBar()->addMenu(helpMenu);
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
	fileToolBar->addAction(tickAct);
	fileToolBar->addSeparator();
	fileToolBar->addAction(quitAct);
	fileToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}










Circuit_Viewer::Circuit_Viewer(QMdiArea *mdiArea, QMainWindow *parent) : QMainWindow(parent), mdiArea(mdiArea)
{
  this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  setAttribute(Qt::WA_DeleteOnClose);
  setMouseTracking(true);
  
  //scrollArea = new QScrollArea;
  //scrollArea->setBackgroundRole(QPalette::Dark);
  
  

  _circuit = new DspCircuit();
  
  
  _scene = new QGraphicsScene();
  
  
  _view = new QGraphicsView(this);
  _view->setScene(_scene);
  _view->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  //_view->setMinimumSize(600,600);
  
  setCentralWidget(_view);
  
  _view->setRenderHint(QPainter::Antialiasing, true);
  
  _editor = new QNodesEditor(this);
  _editor->install(_scene);  

  createActions();
  createToolbar();
  createMenus();
}
Circuit_Viewer::~Circuit_Viewer(){
}

void Circuit_Viewer::createActions()
{
	saveAct = new QAction(QIcon(":/save.png"), tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	saveAsAct = new QAction(QIcon(":/saveAs.png"), tr("Save &As..."), this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

	zoomInAct = new QAction(QIcon(":/Zoom-In.png"), tr("Zoom &In (25%)"), this);
	zoomInAct->setShortcut(tr("Ctrl++"));
	connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

	zoomOutAct = new QAction(QIcon(":/Zoom-Out.png"), tr("Zoom &Out (25%)"), this);
	zoomOutAct->setShortcut(tr("Ctrl+-"));
	connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

	normalSizeAct = new QAction(QIcon(":/normalView.png"), tr("&Normal Size"), this);
	normalSizeAct->setShortcut(tr("Ctrl+S"));
	connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

	fitToWindowAct = new QAction(QIcon(":/fittowindow.png"), tr("&Fit to Window"), this);
	fitToWindowAct->setCheckable(true);
	fitToWindowAct->setShortcut(tr("Ctrl+F"));
	connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

	popInAct = new QAction(QIcon(":/arrow_up.png"), tr("popOut"), this);
	popInAct->setStatusTip(tr("Pop Out Subwindow as own Window."));
	connect(popInAct, SIGNAL(triggered()), this, SLOT(on_action_Pop_In_triggered()));

	popOutAct = new QAction(QIcon(":/arrow_down.png"), tr("popOut"), this);
	popOutAct->setStatusTip(tr("Pop Out Subwindow as own Window."));
	connect(popOutAct, SIGNAL(triggered()), this, SLOT(on_action_Pop_Out_triggered()));
        
    connect(_editor, SIGNAL(compSelected(DspComponent*)), this, SLOT(onCompSelected(DspComponent*)));
}

void Circuit_Viewer::createToolbar()
{
	ToolBar = addToolBar(tr("File"));
	//toolBar->setFixedHeight(ToolBar_Height);
	ToolBar->addAction(saveAct);
	ToolBar->addAction(zoomInAct);
	ToolBar->addAction(zoomOutAct);
	ToolBar->addAction(normalSizeAct);
	ToolBar->addAction(fitToWindowAct);
	ToolBar->addAction(popInAct);
	ToolBar->addAction(popOutAct);
	

}

void Circuit_Viewer::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(zoomInAct);
	fileMenu->addAction(zoomOutAct);
	fileMenu->addAction(normalSizeAct);
	fileMenu->addAction(fitToWindowAct);
	fileMenu->addAction(popInAct);
	fileMenu->addAction(popOutAct);
	menuBar()->addMenu(fileMenu);
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
	/*bool fitToWindow = fitToWindowAct->isChecked();
	scrollArea->setWidgetResizable(fitToWindow);
	if (!fitToWindow) {
		normalSize();
	}
	zoomInAct->setEnabled(!fitToWindowAct->isChecked());
	zoomOutAct->setEnabled(!fitToWindowAct->isChecked());*/
        _view->fitInView(_scene->sceneRect(), Qt::KeepAspectRatio);
}

void Circuit_Viewer::onCompSelected(DspComponent *comp)
{
  emit compSelected(comp);
}

static int counter = 0;

void Circuit_Viewer::addComponent(DspComponent *comp)
{
  char buf[64];
  sprintf(buf, "component_%d", counter++);
  bool success = _circuit->AddComponent(comp, buf);
  assert(success);
    
  new QNEBlock(comp, _scene);
}

void Circuit_Viewer::scaleImage(double factor)
{
	//Q_ASSERT(imageLabel->pixmap());
	//scaleFactor *= factor;
	//imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

	/*adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
	adjustScrollBar(scrollArea->verticalScrollBar(), factor);

	zoomInAct->setEnabled(factor < 3.0);
	zoomOutAct->setEnabled(factor > 0.333);*/
}
void Circuit_Viewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
	/*scrollBar->setValue(int(factor * scrollBar->value()	+ ((factor - 1) * scrollBar->pageStep() / 2)));*/
}
void Circuit_Viewer::save()
{
  saveAs();
}

void Circuit_Viewer::saveAs()
{
  QString path = QFileDialog::getSaveFileName(this, tr("select filename of circuit"));
  
  _circuit->save(path.toUtf8().constData());
}


void Circuit_Viewer::tick()
{
  _circuit->Tick();
  _circuit->Reset();
}


void Circuit_Viewer::on_action_Pop_Out_triggered()
{
	if (mdiArea->activeSubWindow()){
		QMdiSubWindow *sub = mdiArea->activeSubWindow();
		popInpopOutWidget = sub->widget();
		popInpopOutWidget->adjustSize();
		popInpopOutWidget->move(QApplication::desktop()->screen()->rect().center() - popInpopOutWidget->rect().center());
		popInpopOutWidget->hide();
		mdiArea->removeSubWindow(popInpopOutWidget);
		sub->close();
		popInpopOutWidget->show();
	}
}

void Circuit_Viewer::on_action_Pop_In_triggered()
{
	if (! mdiArea->activeSubWindow()){
		std::cout << "hello" << std::endl;
		mdiArea->addSubWindow(popInpopOutWidget);
		popInpopOutWidget->show();
		mdiArea->update();
	}
}