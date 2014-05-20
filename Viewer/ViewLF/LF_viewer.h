#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QFileDialog>
#include "ui_MainWindow.h"
#include <QDockWidget>
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
    void openLightField();

    void about();
    void info();

    void openChannel(const QString &name);

private:

    OpenLF::lightfield::Lightfield *lf;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);


    QDockWidget *dock;
    QDockWidget *dock2;

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    LF_Viewer_Child *activeMdiChild();
    QMdiSubWindow *findMdiChild(const QString &fileName);


#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QString path;

    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *infoAct;
    QAction *toggleInsideOutAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;

    QToolBar *fileToolBar;

    QListWidget *ChannelList;
    QListWidget *ParameterList;

    QMdiArea *mdiArea;

};

#endif // VIEWER_H

