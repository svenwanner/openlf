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





template <class T> class QVP
{
public:
	static T* asPtr(QVariant v) { return  (T *)v.value<void *>(); }
	static QVariant asQVariant(T* ptr) { return qVariantFromValue((void *)ptr); }
};

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

void QNEMainWindow::new_circuit()
{
	_circuitViewer = new Circuit_Viewer(mdiArea, this);
	mdiArea->addSubWindow(_circuitViewer);
	_circuitViewer->setObjectName("circuitViewer");
	_circuitViewer->showMaximized();
}
void QNEMainWindow::onApplicationFocusChanged(){
	std::cout << "hello" << std::endl;
}

void QNEMainWindow::addComponent(QListWidgetItem *it)
{
  DspComponent *comp = QVP<DspComponent>::asPtr(it->data(Qt::UserRole));
  
  comp = comp->clone();

  _circuitViewer->addComponent(comp);
}

void QNEMainWindow::showCompSettings(DspComponent *comp)
{
  _settings->attach(comp);
}

void QNEMainWindow::createDockWindows()
{
	mdiArea->closeAllSubWindows();

	if (dock != NULL){
		delete dock;
	}

	dock = new QDockWidget(tr("Component list:"), this);
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
        
        it = new QListWidgetItem("Write Mesh");
        it->setData(Qt::UserRole, QVP<DspComponent>::asQVariant(new COMP_DispWrite()));
        List1->addItem(it);
	//}

	connect(List1, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(addComponent(QListWidgetItem*)));

	docks.push_back(dock);
	// ******************************************************************
        
        QDockWidget *settings_dock = new QDockWidget(tr("Settings:"), this);
	settings_dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	_settings = new QNESettings(settings_dock);
	settings_dock->setWidget(_settings);
	addDockWidget(Qt::RightDockWidgetArea, settings_dock);
}
