#include <QtGui>
#include <QPixmap>
#include "LF_viewer_child.h"

LF_Viewer_Child::LF_Viewer_Child()
 {

    setAttribute(Qt::WA_DeleteOnClose);

    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
}

void LF_Viewer_Child::open()
 {
    //QString fileName = QFileDialog::getOpenFileName(this,
      //                              tr("Open File"), QDir::currentPath());
    //if (!fileName.isEmpty())  {
      //  QImage image(fileName);
      //  if (image.isNull())  {
      //      QMessageBox::information(this, tr("IErrorMessage"),
      //                               tr("Cannot load %1.").arg(fileName));
      //      return;
      //  }

        //imageLabel->setPixmap(QPixmap::fromImage(image));
        QPixmap *pxmap = new QPixmap(":images/lenna.png");
        imageLabel->setPixmap(*pxmap);
        imageLabel->resize(imageLabel->pixmap()->size());
        scaleFactor = 1.0;
   // }
//To show it externally
    scrollArea->show();
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
