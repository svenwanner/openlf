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

class QNESettings : public QWidget
{
  Q_OBJECT
  
public:
  QNESettings(QWidget *parent = 0) : QWidget(parent) { setLayout(&_layout); };
  
  void attach(DspComponent *comp);
  
protected:
  
private:
  QVBoxLayout _layout;
  
  DspComponent *_component = NULL;
  QWidget *_layout_w = NULL;
  
private slots:
  void textSettingChanged(QString text);
  void selFileClicked();
  void floatSettingChanged(double val);
  void intSettingChanged(int val);
};

#endif