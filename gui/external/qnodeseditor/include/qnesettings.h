#ifndef _QNESETTINGS_H
#define _QNESETTINGS_H

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

#include "DspCircuit.h"

#include "qneblock.h"

class Circuit_Viewer;

class QNESettings : public QWidget
{
  Q_OBJECT
  
public:
  QNESettings(QWidget *parent = 0) : QWidget(parent) { setLayout(&_layout); };
  
  void attach(Circuit_Viewer *viewer, DspComponent *comp, std::vector<DspCircuit*> &circuits);
  void attach(QNEBlock *block);
  
public slots:
  void reload();
  
signals:
  void settingChanged();
  
protected:
  
private:
  QVBoxLayout _layout;
  
  DspComponent *_component = NULL;
  QWidget *_layout_w = NULL;
  Circuit_Viewer *_viewer = NULL;
  std::vector<DspCircuit*> _circuits;
  
private slots:
  void settingOnOffReset();
  void textSettingChanged(QString text);
  void aliasChanged(QString text);
  void selFileClicked();
  void floatSettingChanged(double val);
  void intSettingChanged(int val);
  void portCountChanged(int val);
  void circuitSelected(int val);
  void boolChanged(int val);
  void slot_treedoubleclicked(QTreeWidgetItem *item, int column);
};

#endif
