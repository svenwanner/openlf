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

#include <assert.h>

#include "qnemainwindow.h"
#include "userinterface_qnemainwindow.h"

#include "qneblock.h"
#include "qnodeseditor.h"

#include "circuitviewer.h"

#include <iostream>

template <class T> class QVP
{
public:
	static T* asPtr(QVariant v) { return  (T *)v.value<void *>(); }
	static QVariant asQVariant(T* ptr) { return qVariantFromValue((void *)ptr); }
};

/*

SLOTS

*/

void QNEMainWindow::new_circuit_viewer(DspCircuit *c)
{
  Circuit_Viewer *v;
  
  v = new Circuit_Viewer(mdiArea, this, c);
  
  mdiArea->addSubWindow(v);
  v->setObjectName("circuitViewer");
  //WARNING this causes activate events from last active Circuit_Viewer, therfore set _circuitViewer only afterwards
  v->showMaximized();
  _circuitViewer = v;
  
  connect(v, SIGNAL(newCircuit(DspCircuit*)), this, SLOT(newCircuit(DspCircuit*)));
  connect(v, SIGNAL(activated(QWidget*)), this, SLOT(activate(QWidget*)));
  connect(v, SIGNAL(circuitChanged(DspCircuit*,DspCircuit*)), this, SLOT(viewer_circuit_changed(DspCircuit*,DspCircuit*)));
  connect(v, SIGNAL(compSelected(DspComponent*)), this, SLOT(showCompSettings(DspComponent*)));
  connect(v, SIGNAL(compSelected(QNEBlock*)), this, SLOT(showCompSettings(QNEBlock*)));
    
  if (!_viewers.count(v->circuit()))
    newCircuit(v->circuit(), v);
  else
    viewer_circuit_changed(v->circuit(), NULL);
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

void QNEMainWindow::show_circuit(QListWidgetItem *it)
{
  
  DspCircuit *c = QVP<DspCircuit>::asPtr(it->data(Qt::UserRole));
  
  assert(_viewers.count(c));
  
  Circuit_Viewer *v = std::get<0>(_viewers[c]);
  
  if (v) {
    v->hide();
    v->QWidget::show();
  }
  else
    new_circuit_viewer(c);
}

void QNEMainWindow::showCompSettings(DspComponent *comp)
{
  _settings->attach(comp, _circuits);
  //FIXME is this the right circuit viewer?
  connect(_settings, SIGNAL(settingChanged()), _circuitViewer, SLOT(configure()));
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
	//viewMenu->addAction(dock->toggleViewAction());

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
        _circuit_dock->setWidget(box);
	QFormLayout *layout = new QFormLayout(_circuit_dock);
        box->setLayout(layout);
        _c_name_ed = new QLineEdit(_circuit_dock);
        connect(_c_name_ed, SIGNAL(textChanged(QString)), this, SLOT(circuitNameChanged(QString)));
        if (_circuitViewer)
          _c_name_ed->setText(_circuitViewer->circuit()->GetComponentName().c_str());
        layout->addRow(tr("&Name"), _c_name_ed);   
        
	addDockWidget(Qt::RightDockWidgetArea, _circuit_dock);
        
        
  assert(_viewers.size() == 0);
        
  _circuit_list_dock = new QDockWidget(tr("Circuit list:"), this);
  _circuit_list_dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  _circuit_list_w = new QListWidget(_circuit_list_dock);
  _circuit_list_dock->setWidget(_circuit_list_w);
  addDockWidget(Qt::LeftDockWidgetArea, _circuit_list_dock);

  connect(_circuit_list_w, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(show_circuit(QListWidgetItem*)));
}

void QNEMainWindow::newCircuit(DspCircuit* c)
{
  Circuit_Viewer *v = dynamic_cast<Circuit_Viewer*>(sender());
  
  newCircuit(c, v);
}

void QNEMainWindow::newCircuit(DspCircuit* c, Circuit_Viewer *v)
{
  _circuits.push_back(c);
  
  std::string name = c->GetComponentName();
  if (!name.size())
    name = "(unnamed)";
  QListWidgetItem *item = new QListWidgetItem(name.c_str());
  item->setData(Qt::UserRole, QVP<DspCircuit>::asQVariant(c));
  _circuit_list_w->addItem(item);
  
  if (v) {
    assert(v->circuit() == c);
    v->setWindowTitle(name.c_str());
    _viewers[c] = std::make_tuple(v,item);
  }
}

void QNEMainWindow::circuitNameChanged(QString name)
{
  if (!_circuitViewer)
    return;
  
  _circuitViewer->circuit()->SetComponentName(name.toUtf8().constData());
  viewer_circuit_changed(_circuitViewer->circuit(), NULL);
  
  
  std::string std_name = _circuitViewer->circuit()->GetComponentName();
  if (!std_name.size())
    std_name = "(unnamed)";

  _circuitViewer->setWindowTitle(std_name.c_str());
}

void QNEMainWindow::view_mode_changed(bool tabbed)
{
  if (tabbed)
    mdiArea->setViewMode(QMdiArea::TabbedView);
  else
    mdiArea->setViewMode(QMdiArea::SubWindowView);
}

void QNEMainWindow::viewer_circuit_changed(DspCircuit* new_c, DspCircuit* old)
{
  if (old)
    std::get<0>(_viewers[old]) = NULL;
  
  Circuit_Viewer *v = dynamic_cast<Circuit_Viewer*>(sender());
  
  if (new_c) {
    std::string name = new_c->GetComponentName();
    if (!name.size())
      name = "(unnamed)";
    
    if (v) {
      std::get<0>(_viewers[new_c]) = v;
      v->setWindowTitle(name.c_str());
    }
    
    QListWidgetItem *item = std::get<1>(_viewers[new_c]);
    if (item) {
      item->listWidget()->blockSignals(true);
      item->setText(name.c_str());
      item->setSelected(true);
      item->listWidget()->blockSignals(false);
    }
  }
}
