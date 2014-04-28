#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QFileDialog>
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QMdiArea>
#include <QListWidget>
#include <QPrintDialog>
#include <QPrinter>

#include <QtGui>

//#include <lightfield/Lightfield.hpp>

// Grafic Frontends
namespace Ui{
    class MainWindow;
}

class LF_Viewer : public QMainWindow
 {
    Q_OBJECT

public:
    LF_Viewer();

private slots:
    void open();
    void save();
    void saveAs();
    void print();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void info();

private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *infoAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *ImageMenu;
    QMenu *LFMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;

    QListWidget *List1;
    QListWidget *ParameterList;

    QMdiArea *mdiArea;

};

#endif // VIEWER_H

