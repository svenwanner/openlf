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

#ifndef CIRCUITVIEWER_H
#define CIRCUITVIEWER_H

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

#include "qnesettings.h"
#include "qneblock.h"

#include "DspCircuit.h"

class QNodesEditor;
class Circuit_Viewer;
class Circuit_Thread;

class Circuit_Viewer : public QMainWindow

{
  Q_OBJECT
  
public:
  Circuit_Viewer(QMdiArea *mdiArea = 0, QMainWindow *parent = 0, DspCircuit *circuit = 0);
  ~Circuit_Viewer();
  
  void addComponent(DspComponent *comp, bool gui_only = false);
  void addInputComponent(int pads = 1, QPointF *pos = NULL);
  void addOutputComponent(int pads = 1, QPointF *pos = NULL);
  DspCircuit *circuit();
  bool processing();
  
  
  //void open(const QString &title);
  //void setImage(const QString &title, QPixmap *pxmap);
  //void enableEPI(bool enable);
  
  //QString userFriendlyCurrentFile();
  //QString currentFile()  { return curFile; }
  
  //QScrollArea *scrollArea;
  
signals:
  void compSelected(DspComponent *comp);
  void compSelected(QNEBlock *block);
  void portSelected(QNEPort *port);
  
  void focusChanged();
  
  void activated(QWidget* w);
  void newCircuit(DspCircuit* c);
  void circuitChanged(DspCircuit* new_c, DspCircuit* old, Circuit_Viewer *v);
  void state_changed(Circuit_Viewer *v);
  
public slots:

  void configure();
  
protected:
  virtual bool event(QEvent* e);
  virtual void closeEvent(QCloseEvent *event);
  
private slots:
  
  void save();
  void saveAs();
  void load();
  void show(DspCircuit *c);
  void zoomIn();
  void zoomOut();
  void fitToWindow();
  void onCompSelected(DspComponent *comp);
  void onCompSelected(QNEBlock *block);
  void onPortSelected(QNEPort *port);
  void on_action_Pop_Out_triggered();
  void on_action_Pop_In_triggered();
  void tick();
  void thread_finished();
  
  
private:
  int event_memory;
  
  QMdiArea *mdiArea;
  QWidget *popInpopOutWidget;
  
  // member variable to store click position
  QPoint m_lastPoint;
  // member variable - flag of click beginning
  bool m_mouseClick;
  
  void scaleImage(double factor);
  void adjustScrollBar(QScrollBar *scrollBar, double factor);
  void createToolbar();
  void createActions();
  void createMenus();
  void check_add_circuit();
  
  QAction *MousePosition;
  //QAction *saveAct;
  //QAction *saveAsAct;
  //QAction *loadAct;
  QAction *exitAct;
  QAction *infoAct;
  QAction *zoomInAct;
  QAction *zoomOutAct;
  QAction *fitToWindowAct;
  QAction *popInAct;
  QAction *popOutAct;
  QAction *tickAct;
  
  const int ToolBar_Height = 40;
  QToolBar *ToolBar = std::nullptr_t();
  QMenu *circuitMenu = std::nullptr_t();
  
  
  //QVBoxLayout* vbox;
  
  //QMenuBar *menuBar;
  //QMainWindow *inner;
  //QMenu *viewMenu;
  
  //QToolBar *fileToolBar;
  
  
  //double scaleFactor;
  
  //void setCurrentFile(const QString &fileName);
  //QString strippedName(const QString &fullFileName);
  
  //QString curFile;
  //bool isUntitled;
  
  DspCircuit *_circuit;
  QGraphicsScene *_scene;
  QGraphicsView *_view;
  QNodesEditor *_editor;
  std::vector<QNEBlock*> _blocks;
  
  QNEBlock *_input_block = NULL;
  QNEBlock *_output_block = NULL;
  
  bool _extra_window = false;
  QPointF _leftmost, _rightmost;
  
  bool _processing = false;
  
  Circuit_Thread  *_circuitThread = NULL;
  QThread *_thread = NULL;
};

#endif