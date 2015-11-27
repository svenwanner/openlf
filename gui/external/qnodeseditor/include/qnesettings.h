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

class QNESettings : public QWidget
{
  Q_OBJECT
  
public:
  QNESettings(QWidget *parent = 0) : QWidget(parent) { setLayout(&_layout); };
  
  void attach(DspComponent *comp, std::vector<DspCircuit*> &circuits);
  void attach(QNEBlock *block);
  
signals:
  void settingChanged();
  
protected:
  
private:
  QVBoxLayout _layout;
  
  DspComponent *_component = NULL;
  QWidget *_layout_w = NULL;
  
private slots:
  void textSettingChanged(QString text);
  void aliasChanged(QString text);
  void selFileClicked();
  void floatSettingChanged(double val);
  void intSettingChanged(int val);
  void portCountChanged(int val);
  void circuitSelected(int val);
};

#endif