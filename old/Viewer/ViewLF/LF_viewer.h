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
#include <QSpinBox>

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
    //virtual bool event(QEvent *);

private slots:

    void openLightField();
    void info();

    void openChannel(const QString &name);
    void openView(const QString &name);
    void close();
    void closeAll();
    void setValue(int value);
    void showEPI(QPoint position);
    void on_action_Pop_Out_triggered();

signals:
    void test();

private:

    bool is_Clicked;
    double scaleFactor;

    OpenLF::lightfield::Lightfield *lf;

    void makeGRAYImage(std::string name,QImage &A);
    void makeCOLORImage(QImage &A);
    void makeCHANNELImage(std::string name,QImage &A);

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

    LF_Viewer_Child *activeMdiChild();
    QMdiSubWindow *findMdiChild(const QString &fileName);


    QString path;

    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *infoAct;
    QAction *closeAct;
    QAction *exitAct;
    QAction *popOutAct;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;

    QToolBar *fileToolBar;
    QSlider *slider;
    QSpinBox *spinBox;

    QListWidget *ChannelList;
    QListWidget *ParameterList;

    QMdiArea *mdiArea;

};

#endif // VIEWER_H

