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
#include <LF_viewer_child.h>

#include <QtGui>
#include <OpenLF/lightfield/Lightfield.hpp>

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
    void open_as_Subwidget();
    void open_as_Widget();
    //void openLightField();
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

    //OpenLF::lightfield::Lightfield *lf;
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

    LF_Viewer_Child *activeMdiChild();
    QMdiSubWindow *findMdiChild(const QString &fileName);


#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *infoAct;
    QAction *toggleInsideOutAct;
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

