#ifndef LF_VIEWER_CHILD_H
#define LF_VIEWER_CHILD_H

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
#include <QPrintDialog>
#include <QPrinter>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>

class LF_Viewer_Child : public QWidget
 {
    Q_OBJECT

public:
    LF_Viewer_Child();

    void open();
    QPixmap *pxmap;
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();
    QString currentFile()  { return curFile; }

    QScrollArea *scrollArea;

//protected:

private slots:

    void print();
    void zoomOut();
    void zoomIn();


private:


#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void createToolBars();
    void createMenus();
    void normalSize();
    void createActions();

    QAction *infoAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

    QMenuBar *menuBar;
    QMainWindow *inner;
    QToolBar *fileToolBar;
    QMenu *fileMenu;
    QMenu *ImageMenu;


    QLabel *imageLabel;

    double scaleFactor;

    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QString curFile;
    bool isUntitled;
};

#endif // LF_VIEWER_CHILD_H
