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

class QNodesEditor;
class Circuit_Viewer;

class QNEMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit QNEMainWindow(QWidget *parent = 0);
	~QNEMainWindow();

private slots:
	void saveFile();
	void loadFile();
	void addBlock();
	void on_action_Pop_Out_triggered();
	void createDockWindows();
	void addComponent(QListWidgetItem *it);
        
signals:
	void itemDoubleClicked();

private:

	QMdiArea *mdiArea = std::nullptr_t();

	QMenu *fileMenu = std::nullptr_t();
	QMenu *helpMenu = std::nullptr_t();
	QMenu *viewMenu = std::nullptr_t();

	QToolBar *fileToolBar;

	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	
	std::vector<QDockWidget*> docks;

	QNodesEditor *nodesEditor = std::nullptr_t();
	QGraphicsView *view = std::nullptr_t();
	QGraphicsScene *scene = std::nullptr_t();

	QAction *quitAct = std::nullptr_t();
	QAction *loadAct = std::nullptr_t();
	QAction *saveAct = std::nullptr_t();
	QAction *addAct = std::nullptr_t();
	QAction *popOutAct = std::nullptr_t();

	QListWidget *List1 = std::nullptr_t();
	QListWidget *List2 = std::nullptr_t();

	QDockWidget *dock = std::nullptr_t();
	QDockWidget *dock2 = std::nullptr_t();

	QSlider *slider = std::nullptr_t();
	QSpinBox *spinBox = std::nullptr_t();
        
        Circuit_Viewer *_circuitViewer = NULL;
};

#endif // QNEMAINWINDOW_H


















class Circuit_Viewer : public QWidget
{
	Q_OBJECT

public:
	Circuit_Viewer(QWidget *parent = 0);

        void addComponent(DspComponent *comp);
        
	//void open(const QString &title);
	//void setImage(const QString &title, QPixmap *pxmap);
	//void enableEPI(bool enable);

	//QString userFriendlyCurrentFile();
	//QString currentFile()  { return curFile; }

	QScrollArea *scrollArea;

protected:
	//void mousePressEvent(QMouseEvent * e);
	//void mouseMoveEvent(QMouseEvent* event);


private slots:

	void save();
	void saveAs();
	void zoomIn();
	void zoomOut();
	void normalSize();
	void fitToWindow();


private:

	// member variable to store click position
	QPoint m_lastPoint;
	// member variable - flag of click beginning
	bool m_mouseClick;

	void scaleImage(double factor);
	void adjustScrollBar(QScrollBar *scrollBar, double factor);
	void createToolbar();
	void createActions();

	QAction *MousePosition;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *exitAct;
	QAction *infoAct;
	QAction *zoomInAct;
	QAction *zoomOutAct;
	QAction *normalSizeAct;
	QAction *fitToWindowAct;

	const int ToolBar_Height = 40;

	//QVBoxLayout* vbox;

	//QMenuBar *menuBar;
	//QMainWindow *inner;
	QMenu *viewMenu;

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
};

