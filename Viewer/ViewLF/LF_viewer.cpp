#include "LF_viewer.h"
#include "ui_MainWindow.h"
#include <QDockWidget>
#include "LF_viewer_child.h"

LF_Viewer::LF_Viewer()
 {
    ui->setupUi(this);

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    setWindowTitle(tr("Image Viewer"));
    //resize(500, 400);
}



void LF_Viewer::createMenus()
 {
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&View"));

    ImageMenu = new QMenu(tr("&Image"), this);
    ImageMenu->addAction(zoomInAct);
    ImageMenu->addAction(zoomOutAct);
    ImageMenu->addAction(normalSizeAct);
    ImageMenu->addSeparator();
    ImageMenu->addAction(fitToWindowAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    //menuBar()->addSeparator();
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(ImageMenu);
    menuBar()->addMenu(helpMenu);
}


void LF_Viewer::createToolBars()
 {
    //First Toolbar generated in Forms
    ui->toolBar->addAction(openAct);
    ui->toolBar->addAction(saveAct);


    //Second ToolBar defined in source code
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(printAct);
    fileToolBar->addAction(zoomInAct);
    fileToolBar->addAction(zoomOutAct);
    fileToolBar->addAction(infoAct);
    //fileToolBar->addAction(toggleInsideOutAct);
    fileToolBar->addAction(exitAct);

}

void LF_Viewer::createStatusBar()
 {
    statusBar()->showMessage(tr("Ready"));
}

/*
MdiChild *MainWindow::activeMdiChild()
 {
    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return 0;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName)
 {
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    foreach (QMdiSubWindow *window, mdiArea->subWindowList())  {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return window;
    }
    return 0;
}
*/






















/*
LF_Viewer::LF_Viewer(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    //
    //QWidget *popup = new QWidget();
    //mdiArea->addSubWindow(popup);
    //popup->show();
    MdiChild *child = createMdiChild();
    child->show();

    setWindowTitle(tr("LF_Viewer"));
    setUnifiedTitleAndToolBarOnMac(true);
}



void LF_Viewer::createMenus()
 {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addSeparator();
    QAction *action = fileMenu->addAction(tr("Switch layout direction"));
    connect(action, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));
    fileMenu->addAction(exitAct);

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    windowMenu = menuBar()->addMenu(tr("&Window"));
    //updateWindowMenu();
    //connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    menuBar()->addSeparator();

    LFMenu = menuBar()->addMenu((tr("&Light Field")));
    LFMenu->addAction(infoAct);
    LFMenu->addAction(printAct);
    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void LF_Viewer::createToolBars()
 {
    //First Toolbar generated in Forms
    ui->toolBar->addAction(openAct);
    ui->toolBar->addAction(saveAct);

    //Second ToolBar defined in source code
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(printAct);
    fileToolBar->addAction(infoAct);
    fileToolBar->addAction(exitAct);

}

void LF_Viewer::createStatusBar()
 {
    statusBar()->showMessage(tr("Ready"));
}










*/
