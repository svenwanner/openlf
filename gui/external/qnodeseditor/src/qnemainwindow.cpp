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

#include "qnemainwindow.h"
#include "userinterface_qnemainwindow.h"

#include "qneblock.h"
#include "qnodeseditor.h"

#include <QGraphicsScene>
#include <QFileDialog>

#include "qneport.h"
#include "qneconnection.h"

#include <iostream>

#include "circuitviewer.h"


QNEMainWindow::QNEMainWindow(QWidget *parent)  :  QMainWindow(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle(tr("Circuit Toolbox"));
  
  
  mdiArea = new QMdiArea;
  mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mdiArea->setViewMode(QMdiArea::TabbedView);
  mdiArea->setTabsClosable(true);
  setCentralWidget(mdiArea);
  
  createActions();
  createMenus();
  createDockWindows();
  createToolBars();  
  
  new_circuit_viewer();
  
  this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  
}
QNEMainWindow::~QNEMainWindow()
{
  mdiArea->closeAllSubWindows();
}

void QNEMainWindow::activate(QWidget* wid){
  
  _circuitViewer = (Circuit_Viewer*)wid;
  
  if (_c_name_ed && _circuitViewer->circuit())
    _c_name_ed->setText(_circuitViewer->circuit()->GetComponentName().c_str());
};

void QNEMainWindow::createMenus()
{
  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(loadAct);
  //fileMenu->addAction(saveAct);
  fileMenu->addAction(newAct);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAct);
  
  viewMenu = new QMenu(tr("&View"), this);
  viewMenu->addAction(tabViewAct);
  
  //helpMenu = new QMenu(tr("&Help"), this);
  
  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(viewMenu);
  //menuBar()->addMenu(helpMenu);
  //menuBar()->addMenu(viewMenu);
}


void QNEMainWindow::createToolBars()
{
  //ToolBar defined in source code
  fileToolBar = addToolBar(tr("File"));
  fileToolBar->addAction(loadAct);
  fileToolBar->addAction(saveAct);
  fileToolBar->addAction(newAct);
  fileToolBar->addSeparator();
  fileToolBar->addAction(quitAct);
  //fileToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

/*void QNEMainWindow::createToolBars()
printf("start client\n");
      _client_socket = new QLocalSocket(this);
      
      connect(_client_socket, SIGNAL(connected()), this, SLOT(showFileClientConnected()));
      connect(_client_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(showFileClientError(QLocalSocket::LocalSocketError)));
      
      _client_socket->connectToServer("clifview_showfile", QIODevice::ReadWrite);*/
