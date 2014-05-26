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
#include <QToolBar>
#include <QVBoxLayout>


class LF_Viewer_Child : public QWidget
 {
    Q_OBJECT

public:
    LF_Viewer_Child(QWidget *parent = 0);

    void open(const QString &title);
    void setImage(const QString &title,QPixmap *pxmap);

    QString userFriendlyCurrentFile();
    QString currentFile()  { return curFile; }

    QScrollArea *scrollArea;

protected:
    void mouseReleaseEvent ( QMouseEvent * e );
    void mousePressEvent ( QMouseEvent * e );

signals:
    void mouseClick();


private slots:

    void save();
    void saveAs();
    void print();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();

private:

    // member variable to store click position
    QPoint m_lastPoint;
    // member variable - flag of click beginning
    bool m_mouseClick;


#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void createToolbar();
    void createActions();

    QAction *MousePosition;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *infoAct;
    QAction *printAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;



    QVBoxLayout* vbox;

    QMenuBar *menuBar;
    QMainWindow *inner;
    QMenu *viewMenu;

    QToolBar *fileToolBar;

    QPixmap *pxmap;

    QLabel *imageLabel;

    double scaleFactor;

    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QString curFile;
    bool isUntitled;
};

#endif // LF_VIEWER_CHILD_H
