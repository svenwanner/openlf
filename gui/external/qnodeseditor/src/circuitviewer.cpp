/* Copyright (c) 2012, Maximilian Diebold
			 Hendrik Siedelmann
			 Sven Wanner
All rights reserved.

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

#include "circuitviewer.h"

#include "qnemainwindow.h"
#include "userinterface_qnemainwindow.h"

#include "qneblock.h"
#include "qnodeseditor.h"

#include <QGraphicsScene>
#include <QFileDialog>

#include "qneport.h"
#include "qneconnection.h"
#include "qnodesthreads.h"

#include <iostream>
#include <assert.h>

#include "openlf.hpp"


Circuit_Viewer::Circuit_Viewer(QMdiArea *mdiArea, QMainWindow *parent, DspCircuit *circuit) : QMainWindow(parent), mdiArea(mdiArea)
{
  this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  
  //setAttribute(Qt::WA_DeleteOnClose);
  setMouseTracking(true);
  
  //scrollArea = new QScrollArea;
  //scrollArea->setBackgroundRole(QPalette::Dark);  
  
  _scene = new QGraphicsScene();
  
  if (circuit)
    _circuit = circuit;
  else
    _circuit = new DspCircuit();
  
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
  
  show(_circuit);
}

Circuit_Viewer::~Circuit_Viewer(){
}

void Circuit_Viewer::createActions()
{
//  saveAct = new QAction(QIcon(":/circuit_save.png"), tr("&Save"), this);
//  saveAct->setShortcuts(QKeySequence::Save);
//  saveAct->setStatusTip(tr("Save Circuit to disk"));
//  connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
  
//  saveAsAct = new QAction(QIcon(":/circuit_save.png"), tr("Save &As..."), this);
//  saveAsAct->setShortcuts(QKeySequence::SaveAs);
//  saveAsAct->setStatusTip(tr("Save the document under a new name"));
//  connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
  
 // loadAct = new QAction(QIcon(":/circuit_load.png"), tr("&Load"), this);
//  loadAct->setShortcuts(QKeySequence::Open);
//  loadAct->setStatusTip(tr("Load Circuit from disk"));
//  connect(loadAct, SIGNAL(triggered()), this, SLOT(load()));
  
  zoomInAct = new QAction(QIcon(":/Zoom-In.png"), tr("Zoom &In (25%)"), this);
  zoomInAct->setShortcut(tr("Ctrl++"));
  connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
  
  zoomOutAct = new QAction(QIcon(":/Zoom-Out.png"), tr("Zoom &Out (25%)"), this);
  zoomOutAct->setShortcut(tr("Ctrl+-"));
  connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
  
  fitToWindowAct = new QAction(QIcon(":/fittowindow.png"), tr("&Fit to Window"), this);
  fitToWindowAct->setCheckable(true);
  fitToWindowAct->setShortcut(tr("Ctrl+F"));
  connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
  
  popInAct = new QAction(QIcon(":/arrow_down.png"), tr("Rettach"), this);
  popInAct->setStatusTip(tr("reattach subwindow to main window."));
  popInAct->setDisabled(true);
  connect(popInAct, SIGNAL(triggered()), this, SLOT(on_action_Pop_In_triggered()));
  
  popOutAct = new QAction(QIcon(":/arrow_up.png"), tr("Pop Out"), this);
  popOutAct->setStatusTip(tr("pop out subwindow as extra window."));
  connect(popOutAct, SIGNAL(triggered()), this, SLOT(on_action_Pop_Out_triggered()));
  
  tickAct = new QAction(QIcon(":/clock.png"), tr("Tick"), this);
  tickAct->setStatusTip(tr("Tick Circuit."));
  if (_circuit->hasError())
    tickAct->setDisabled(true);
  connect(tickAct, SIGNAL(triggered()), this, SLOT(tick()));
  
  connect(_editor, SIGNAL(compSelected(DspComponent*)), this, SLOT(onCompSelected(DspComponent*)));
  connect(_editor, SIGNAL(compSelected(QNEBlock*)), this, SLOT(onCompSelected(QNEBlock*)));
  connect(_editor, SIGNAL(portSelected(QNEPort*)), this, SLOT(onPortSelected(QNEPort*)));
  connect(_editor, SIGNAL(circuitChanged()), this, SLOT(configure()));
}

bool Circuit_Viewer::event(QEvent* e)
{
  bool res = QMainWindow::event(e);
  if (_extra_window) {
    if (isActiveWindow())
      emit activated(this);
  }
  else {
    QMdiSubWindow *subwin = mdiArea->activeSubWindow();
    if (subwin && subwin->widget() == this)
      emit activated(this);
  }
  return res;
}

void Circuit_Viewer::closeEvent(QCloseEvent *event)
{
  emit circuitChanged(NULL, circuit(),this);
  
  QMainWindow::closeEvent(event);
}

void Circuit_Viewer::createToolbar()
{
  ToolBar = addToolBar(tr("File"));
  //toolBar->setFixedHeight(ToolBar_Height);
  //ToolBar->addAction(loadAct);
  //ToolBar->addAction(saveAct);
  //ToolBar->addSeparator();
  ToolBar->addAction(tickAct);
  ToolBar->addSeparator();
  ToolBar->addAction(zoomInAct);
  ToolBar->addAction(zoomOutAct);
  ToolBar->addAction(fitToWindowAct);
  ToolBar->addSeparator();
  ToolBar->addAction(popInAct);
  ToolBar->addAction(popOutAct);

  //ToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  
}

void Circuit_Viewer::createMenus()
{
  
  circuitMenu = new QMenu(tr("&Circuit"), this);
  circuitMenu->addAction(tickAct);
  circuitMenu->addSeparator();
  //circuitMenu->addAction(saveAct);
  circuitMenu->addAction(zoomInAct);
  circuitMenu->addAction(zoomOutAct);
  circuitMenu->addAction(fitToWindowAct);
  circuitMenu->addSeparator();
  circuitMenu->addAction(popInAct);
  circuitMenu->addAction(popOutAct);
  
  menuBar()->addMenu(circuitMenu);
  
}

void Circuit_Viewer::zoomIn(){
  scaleImage(1.25); 
}
void Circuit_Viewer::zoomOut(){ 
  scaleImage(0.8); 
}
void Circuit_Viewer::scaleImage(double factor){
  _view->scale(factor, factor);
}

void Circuit_Viewer::fitToWindow()
{
  _view->fitInView(_scene->sceneRect(), Qt::KeepAspectRatio);
  fitToWindowAct->setChecked(false);
}

void Circuit_Viewer::onCompSelected(DspComponent *comp)
{
  emit compSelected(comp);
}

void Circuit_Viewer::onCompSelected(QNEBlock *block)
{
  emit compSelected(block);
}

void Circuit_Viewer::onPortSelected(QNEPort *port)
{
  emit portSelected(port);
}


void Circuit_Viewer::addComponent(DspComponent *comp, bool gui_only)
{
  char buf[64];
  for(int i=0;;i++) {
    sprintf(buf, "%s_%d", comp->getTypeName().c_str(), i);
    if (!_circuit->GetComponent<DspComponent>(buf))
      break;
  }
  
  if (!gui_only) {
    bool success = _circuit->AddComponent(comp, buf);
    assert(success);
  }
  
  _blocks.push_back(new QNEBlock(comp, _scene));
  
  QMetaObject::invokeMethod(this, "configure", Qt::QueuedConnection);
}

//FIXME delete old input comp if already existing!
void Circuit_Viewer::addInputComponent(int pads, QPointF *pos)
{
  char buf[64];
  
  for(int i=0;i<pads;i++) {
    sprintf(buf, "input_%d", i);
    _circuit->AddInput(buf);
  }
  
  _input_block = new QNEBlock(_circuit, _scene, QNEBlock::BlockType::Source, pos);
  _blocks.push_back(_input_block);
  emit circuitChanged(_circuit, NULL, this);
}

void Circuit_Viewer::addOutputComponent(int pads, QPointF *pos)
{   
  char buf[64];
  
  for(int i=0;i<pads;i++) {
    sprintf(buf, "output_%d", i);
    _circuit->AddOutput(buf);
  }
  
  _output_block = new QNEBlock(_circuit, _scene, QNEBlock::BlockType::Sink, pos);
  _blocks.push_back(_output_block);
  emit circuitChanged(_circuit, NULL, this);
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

void Circuit_Viewer::load()
{
  QString path = QFileDialog::getOpenFileName(this, tr("select filename of circuit"));
  
  DspCircuit *new_circuit = DspCircuit::load(path.toUtf8().constData(), &OpenLF::getComponent);
  if (!new_circuit)
    //FIXME error msg
    return;
  
  emit newCircuit(new_circuit);
  
  show(new_circuit);
}

void Circuit_Viewer::show(DspCircuit *c)
{
  DspCircuit *old = _circuit;
  _circuit = c;
  _circuit->configure();
  
  emit circuitChanged(_circuit, old, this);
  emit activated(this);
  
  _scene->clear();
  _blocks.resize(0);
  _input_block = NULL;
  _output_block = NULL;
  
  if (_circuit->hasError())
    tickAct->setDisabled(true);
  else
    tickAct->setDisabled(false);
  
  _rightmost = QPointF(-1000000,0);
  _leftmost = QPointF(1000000,0);
  
  for(int i=0;i<_circuit->GetComponentCount();i++)
    addComponent(_circuit->GetComponent(i), true);
  
  for(int i=0;i<_blocks.size();i++) {
    QNEBlock *block = _blocks[i];
    if (block->component && block->component->x-200 < _leftmost.x() - 200)
      _leftmost = QPointF(block->component->x-200, block->component->y);
    if (block->component && block->component->x+200 > _rightmost.x()+200)
      _rightmost = QPointF(block->component->x+200, block->component->y);
    DspComponent *comp = _blocks[i]->component;
    DspWireBus *inputs = comp->GetInputWires();
    
    for(int j=0;j<inputs->GetWireCount();j++) {
      DspWire *input = inputs->GetWire(j);
      int src_idx = input->fromSignalIndex;
      int sink_idx = input->toSignalIndex;
      DspComponent *source_comp = input->linkedComponent;
      QNEBlock *source_block = NULL;
      
      for(int n=0;n<_blocks.size();n++) {
        if (source_comp == _blocks[n]->component) {
          source_block = _blocks[n];
          break;
        }
      }
      
      QNEPort *p1 = source_block->getPortByIdx(src_idx, true);
      QNEPort *p2 = block->getPortByIdx(sink_idx, false);
      
      QNEConnection *conn = new QNEConnection();
      _scene->addItem(conn);
      conn->setPort1(p1, true);
      conn->setPort2(p2, true);
      conn->setPos1(p1->scenePos());
      conn->setPos2(p2->scenePos());
      conn->updatePath();
    }
  }
  
  //FIXME add input output count stuff
  if (_circuit->GetInputCount()) {
    addInputComponent(_circuit->GetInputCount(), &_leftmost);
    
    DspWireBus *inputs = _circuit->GetInToInWires();
    for(int i=0;i<inputs->GetWireCount();i++) {
      DspWire *input = inputs->GetWire(i);
      int src_idx = input->fromSignalIndex;
      int sink_idx = input->toSignalIndex;
      DspComponent *target_comp = input->linkedComponent;
      QNEBlock *target_block = NULL;
      
      for(int n=0;n<_blocks.size();n++)
        if (target_comp == _blocks[n]->component) {
          target_block = _blocks[n];
          break;
        }
        assert(target_block);
      
      QNEPort *p1 = _input_block->getPortByIdx(src_idx, true);
      QNEPort *p2 = target_block->getPortByIdx(sink_idx, false);
      
      QNEConnection *conn = new QNEConnection();
      _scene->addItem(conn);
      conn->setPort1(p1, true);
      conn->setPort2(p2, true);
      conn->setPos1(p1->scenePos());
      conn->setPos2(p2->scenePos());
      conn->updatePath();
    }
  }
  
  if (_circuit->GetOutputCount()) {
    addOutputComponent(_circuit->GetOutputCount(), &_rightmost);    
    
    DspWireBus *outputs = _circuit->GetOutToOutWires();
    for(int i=0;i<outputs->GetWireCount();i++) {
      DspWire *output = outputs->GetWire(i);
      int src_idx = output->fromSignalIndex;
      int sink_idx = output->toSignalIndex;
      DspComponent *source_comp = output->linkedComponent;
      QNEBlock *source_block = NULL;
      
      for(int n=0;n<_blocks.size();n++)
        if (source_comp == _blocks[n]->component) {
          source_block = _blocks[n];
          break;
        }
        assert(source_block);
      
      QNEPort *p1 = source_block->getPortByIdx(src_idx, true);
      QNEPort *p2 = _output_block->getPortByIdx(sink_idx, false);
      
      QNEConnection *conn = new QNEConnection();
      _scene->addItem(conn);
      conn->setPort1(p1, true);
      conn->setPort2(p2, true);
      conn->setPos1(p1->scenePos());
      conn->setPos2(p2->scenePos());
      conn->updatePath();
    }
  }
}


void Circuit_Viewer::tick()
{
  assert(!_circuitThread && !_processing);
  
  tickAct->setDisabled(true);
  _processing = true;
  emit state_changed(this);
  
  Circuit_Thread  *_circuitThread = new Circuit_Thread(_circuit);
  QThread *_thread = new QThread;
  _circuitThread->moveToThread(_thread);
  connect(_thread, SIGNAL(started()), _circuitThread, SLOT(run()));
  connect(_circuitThread, SIGNAL(done()), this, SLOT(thread_finished()));
  _thread->start();
  
}

void Circuit_Viewer::thread_finished()
{
  _processing = false;
  emit state_changed(this);
  
  tickAct->setDisabled(false);
  
  delete _thread;
  delete _circuitThread;
  
  _thread = NULL;
  _circuitThread = NULL;
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
    _extra_window = true;
    popInAct->setDisabled(false);
    popOutAct->setDisabled(true);
  }
}

void Circuit_Viewer::on_action_Pop_In_triggered()
{
  //if (! mdiArea->activeSubWindow()){
    mdiArea->addSubWindow(popInpopOutWidget);
    popInpopOutWidget->showMaximized();
    mdiArea->update();
    _extra_window = false;
    popInAct->setDisabled(true);
    popOutAct->setDisabled(false);
  //}
}


bool Circuit_Viewer::processing()
{
  return _processing;
}

void Circuit_Viewer::configure()
{  
  _circuit->configure();
  QList<QGraphicsItem*> items = _scene->items();
  
  foreach(QGraphicsItem *item, items)
  { 
    if (item->type() == QNEBlock::Type)
      (dynamic_cast<QNEBlock*>(item))->checkError();
  }
  
  if (_circuit->hasError())
    tickAct->setDisabled(true);
  else
    tickAct->setDisabled(false);
}

DspCircuit *Circuit_Viewer::circuit()
{
  return _circuit;
}
