/* Copyright (c) 2012, STANISLAW ADASZEWSKI
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
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef QNEMAINWINDOW_H
#define QNEMAINWINDOW_H

#include <tuple>

#include <QMainWindow>
#include <QtWidgets>
#include <QMdiArea>
#include <QSpinBox>
#include <QDockWidget>

#include <QTextEdit>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QtGui>
#include <QScrollBar>
#include <QScrollArea>
#include <QLabel>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QToolBar>
#include <QVBoxLayout>
#include <QLineEdit>

#include <unordered_map>

#include "qnesettings.h"
#include "qneblock.h"

#include "DspCircuit.h"

class QNodesEditor;
class Circuit_Viewer;

namespace openlf { class LF; }
namespace clif { class Mat; }

class QNEMainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit QNEMainWindow(QWidget *parent = 0);
  ~QNEMainWindow();
  
private slots:
  void newComponent(DspComponent *comp);
  void new_circuit_viewer(DspCircuit *c = NULL);
  void onApplicationFocusChanged();
  void createDockWindows();
  void addComponent(QListWidgetItem *it);
  void showCompSettings(DspComponent *comp);
  void showCompSettings(QNEBlock *comp);
  void activate(QWidget* wid);
  void newCircuit(DspCircuit* c);
  void newCircuit(DspCircuit* c, Circuit_Viewer *v);
  void viewer_circuit_changed(DspCircuit* new_c = NULL, DspCircuit* old = NULL, Circuit_Viewer *v = NULL);
  void circuitNameChanged(QString name);
  void circuitTypeChanged(QString name);
  void view_mode_changed(bool tabbed);
  void show_circuit(QListWidgetItem *it);
  void check_viewer_state(Circuit_Viewer *v);
  void showPortProps(QNEPort *port);
  void open_clif_viewer();
  
signals:
  void itemDoubleClicked();
  
private:
  
  QMdiArea *mdiArea = std::nullptr_t();
  
  QMenu *fileMenu = std::nullptr_t();
  QMenu *helpMenu = std::nullptr_t();
  QMenu *viewMenu = std::nullptr_t();
  
  QToolBar *fileToolBar = std::nullptr_t();
  
  void createActions();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  
  QNodesEditor *nodesEditor = std::nullptr_t();
  QGraphicsView *view = std::nullptr_t();
  QGraphicsScene *scene = std::nullptr_t();
  
  QAction *quitAct = std::nullptr_t();
  QAction *loadAct = std::nullptr_t();
  QAction *saveAct = std::nullptr_t();
  QAction *newAct = std::nullptr_t();
  QAction *tabViewAct = NULL;
  
  QListWidget *List1 = std::nullptr_t();
  QListWidget *List2 = std::nullptr_t();
  
  QDockWidget *_comp_list_dock = NULL;
  QDockWidget *_settings_dock = NULL;
  QDockWidget *_circuit_dock = NULL;
  QDockWidget *_circuit_list_dock = NULL;
  QDockWidget *_port_dock = NULL;
  
  QPushButton *_open_clif_btn = NULL;
  
  QLineEdit *_c_name_ed = NULL;
  QLineEdit *_c_type_ed = NULL;
  
  Circuit_Viewer *_circuitViewer = NULL;
  QNESettings *_settings = NULL;
  QListWidget *_circuit_list_w = NULL;
  
  openlf::LF *_lf_selected = NULL;
  clif::Mat *_mat_selected = NULL;
  
  QListWidget *_comp_list = NULL;
  std::unordered_map<DspComponent*,QListWidgetItem*> _comp_map;
  
  std::vector<QThread*> threads;
  std::vector<DspCircuit*> _circuits;
  std::unordered_map<DspCircuit*,std::tuple<Circuit_Viewer*,QListWidgetItem*>> _viewers;
};

#endif // QNEMAINWINDOW_H

