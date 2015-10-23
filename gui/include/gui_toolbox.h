#ifndef GUI_TOOLBOX_H
#define GUI_TOOLBOX_H


#include "qnodeseditor/include/qnemainwindow.h"
#include "LFCamconfigurator/include/lfcamconfigurator.h"

#include <iostream>
#include <string>
#include <QMainWindow>
#include <QObject>
#include <QFileDialog>
#include <QLabel>
#include <QScrollArea>
#include <QtGui>
#include <QMessageBox>
#include <QDockWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QScrollBar>
#include <QAction>
#include <QMenu>
#include <QVBoxLayout>
#include <QStatusBar>


namespace Ui {
    class GUI_Toolbox;
}

class GUI_Toolbox : public QMainWindow
{
    Q_OBJECT

public:
    explicit GUI_Toolbox(QWidget *parent = 0);
    ~GUI_Toolbox();

private slots:
    //void OpenLFCamConfigurator();

    void about();
	void showNode();
        void showViewer();
        void showAnimator();
	void OpenLFCamConfigurator();

private:
    Ui::GUI_Toolbox *ui;

    void createActions();
    void createUIActions();
    void createMenus();
    void createStatusBar();

    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *aboutAct;
    QAction *showAct;
	QAction *showAct_Node;
    QAction *showMainAct;

    QString path;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;

    QToolBar *fileToolBar;

	QNEMainWindow *QNEMW = std::nullptr_t();
	LFCamConfigurator *LFCC = std::nullptr_t();

	std::vector<QThread*> threads;


};

#endif // GUI_TOOLBOX_H
