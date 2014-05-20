#include <QtGui>
#include <QPixmap>
#include "LF_viewer_child.h"



LF_Viewer_Child::LF_Viewer_Child(QWidget *parent)
    : QWidget(parent)
 {

    setAttribute(Qt::WA_DeleteOnClose);

    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);

    createActions();
    createToolbar();

    setWindowTitle(tr("Image Viewer"));
}

void LF_Viewer_Child::createActions()
 {
    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    printAct = new QAction(QIcon(":/images/print.png"), tr("&Print..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    zoomInAct = new QAction(QIcon(":/images/Zoom-In.png"),tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(QIcon(":/images/Zoom-Out.png"),tr("Zoom &Out (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Normal Size"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));


}


void LF_Viewer_Child::createToolbar()
 {

    QToolBar* toolBar = new QToolBar(this);
    toolBar->addAction(saveAct);
    toolBar->addAction(zoomInAct);
    toolBar->addAction(zoomOutAct);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(toolBar);
    //vbox->addWidget(view);
    vbox->addWidget(scrollArea);
    vbox->setContentsMargins(0,0,0,0);
    vbox->setSpacing(0);
    this->setMinimumSize(300,300);
    //setLayout(vbox);

}



void LF_Viewer_Child::open()
 {
    QPixmap *pxmap = new QPixmap(":images/lenna.png");
    imageLabel->setPixmap(*pxmap);
    imageLabel->resize(imageLabel->pixmap()->size());
    scaleFactor = 1.0;

}

void LF_Viewer_Child::setImage(QPixmap *pxmap)
 {
    imageLabel->setPixmap(*pxmap);
    imageLabel->resize(imageLabel->pixmap()->size());
    scaleFactor = 1.0;

}

void LF_Viewer_Child::save()
 {
}

void LF_Viewer_Child::saveAs()
 {
}

void LF_Viewer_Child::print()
 {
    Q_ASSERT(imageLabel->pixmap());
#ifndef QT_NO_PRINTER
    QPrintDialog dialog(&printer, this);
    if (dialog.exec())  {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}

void LF_Viewer_Child::normalSize()
 {
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void LF_Viewer_Child::zoomIn()
 {
    scaleImage(1.25);
}

void LF_Viewer_Child::zoomOut()
 {
    scaleImage(0.8);
}

void LF_Viewer_Child::updateActions()
 {
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
}

void LF_Viewer_Child::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}

void LF_Viewer_Child::scaleImage(double factor)
 {
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void LF_Viewer_Child::adjustScrollBar(QScrollBar *scrollBar, double factor)
 {
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

