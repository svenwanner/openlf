#include "LF_viewer.h"
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include "LF_viewer_child.h"



void LF_Viewer::print()
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

void LF_Viewer::zoomIn()
 {
    scaleImage(1.25);
}

void LF_Viewer::zoomOut()
 {
    scaleImage(0.8);
}

void LF_Viewer::normalSize()
 {
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void LF_Viewer::fitToWindow()
 {
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)  {
        normalSize();
    }
    updateActions();
}

void LF_Viewer::about()
 {
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
               "and QScrollArea to display an image. QLabel is typically used "
               "for displaying a text, but it can also display an image. "
               "QScrollArea provides a scrolling view around another widget. "
               "If the child widget exceeds the size of the frame, QScrollArea "
               "automatically provides scroll bars. </p><p>The example "
               "demonstrates how QLabel's ability to scale its contents "
               "(QLabel::scaledContents), and QScrollArea's ability to "
               "automatically resize its contents "
               "(QScrollArea::widgetResizable), can be used to implement "
               "zooming and scaling features. </p><p>In addition the example "
               "shows how to use QPainter to print an image.</p>"));
}

void LF_Viewer::updateActions()
 {
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void LF_Viewer::scaleImage(double factor)
 {
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void LF_Viewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
 {
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
void LF_Viewer::info()
 {
       QMessageBox::about(this, tr("Light Field Properies"),
               tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
                  "and QScrollArea to display an image. QLabel is typically used "
                  "for displaying a text, but it can also display an image. "
                  "QScrollArea provides a scrolling view around another widget. "
                  "If the child widget exceeds the size of the frame, QScrollArea "
                  "automatically provides scroll bars. </p><p>The example "
                  "demonstrates how QLabel's ability to scale its contents "
                  "(QLabel::scaledContents), and QScrollArea's ability to "
                  "automatically resize its contents "
                  "(QScrollArea::widgetResizable), can be used to implement "
                  "zooming and scaling features. </p><p>In addition the example "
                  "shows how to use QPainter to print an image.</p>"));
}
void LF_Viewer::save()
 {
}

void LF_Viewer::saveAs()
 {
}


void LF_Viewer::open_as_Subwidget()
{
  LF_Viewer_Child *test = new LF_Viewer_Child();
  mdiArea->addSubWindow(test->scrollArea);
  //if (activeMdiChild()) cout << "test" << endl;
  test->open();
}

void LF_Viewer::open_as_Widget()
 {
   LF_Viewer_Child *test = new LF_Viewer_Child();
   test->open();
}


/*void LF_Viewer::openLightField() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.lf *.h5)"));
    ui->debugLabel->setText(QString("Try to open file: ")+fileName);

    lf = new OpenLF::lightfield::Lightfield(fileName.toStdString());

    int w = lf->width();
    int h = lf->height();
    int ch = lf->cams_h();
    int cv = lf->cams_v();

    QString dbg = "loaded LightField of size: ("+QString::number(ch)+","+QString::number(cv)+","+QString::number(w)+","+QString::number(h)+")";
    ui->debugLabel->setText(dbg);
}*/
