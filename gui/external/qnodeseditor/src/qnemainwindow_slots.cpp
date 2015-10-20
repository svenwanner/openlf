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

#include "openlf.hpp"

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

void QNEMainWindow::new_circuit_viewer()
{
	_circuitViewer = new Circuit_Viewer(mdiArea, this);
        newCircuit(_circuitViewer->circuit());
	connect(_circuitViewer, SIGNAL(newCircuit(DspCircuit*)), this, SLOT(newCircuit(DspCircuit*)));
	connect(_circuitViewer, SIGNAL(activated(QWidget*)), this, SLOT(activate(QWidget*)));
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
  
  if (comp) {
    comp = comp->clone();

    _circuitViewer->addComponent(comp);
  }
  else {
    if (!it->text().compare("Circuit Input"))
      _circuitViewer->addInputComponent();
    else if (!it->text().compare("Circuit Output"))
      _circuitViewer->addOutputComponent();
  }
}

void QNEMainWindow::showCompSettings(DspComponent *comp)
{
  _settings->attach(comp);
}

void QNEMainWindow::showCompSettings(QNEBlock *block)
{
  _settings->attach(block);
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

        //populate component list
        QListWidgetItem *item;
        item = new QListWidgetItem("Circuit Input");
        List1->addItem(item);
        item = new QListWidgetItem("Circuit Output");
        List1->addItem(item);
        
        std::vector<DspComponent*> comps = OpenLF::componentList();
        for(auto it=comps.begin();it!=comps.end();++it) {
          item = new QListWidgetItem((*it)->getTypeName().c_str());
          item->setData(Qt::UserRole, QVP<DspComponent>::asQVariant(*it));
          List1->addItem(item);
        }

	connect(List1, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(addComponent(QListWidgetItem*)));

	docks.push_back(dock);
	// ******************************************************************
        

        QDockWidget *settings_dock = new QDockWidget(tr("Component Settings:"), this);
	settings_dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	_settings = new QNESettings(settings_dock);
	settings_dock->setWidget(_settings);
	addDockWidget(Qt::RightDockWidgetArea, settings_dock);
        
        _circuit_dock = new QDockWidget(tr("Circuit Settings:"), this);
	_circuit_dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        QWidget *box = new QWidget(_circuit_dock);
        settings_dock->setWidget(box);
	QFormLayout *layout = new QFormLayout(_circuit_dock);
        box->setLayout(layout);
        _c_name_ed = new QLineEdit(_circuit_dock);
        connect(_c_name_ed, SIGNAL(textChanged(QString)), this, SLOT(circuitNameChanged(QString)));
        _c_name_ed->setText(_circuitViewer->circuit()->GetComponentName().c_str());
        layout->addRow(tr("&Name"), _c_name_ed);   
        
	addDockWidget(Qt::RightDockWidgetArea, _circuit_dock);
}



void QNEMainWindow::newCircuit(DspCircuit* c)
{
  _circuits.push_back(c);
}


void QNEMainWindow::circuitNameChanged(QString name)
{
  _circuitViewer->circuit()->SetComponentName(name.toUtf8().constData());
}
