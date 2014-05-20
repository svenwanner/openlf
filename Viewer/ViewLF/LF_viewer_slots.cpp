#include "LF_viewer.h"
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include "LF_viewer_child.h"
#include <iostream>






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


void LF_Viewer::openLightField() {

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), path , tr("LF (*.lf) ;; HDF5 (*.h5 *.hdf5) ;; All files (*.*)"));
    path = QFileInfo(fileName).path(); // store path for next time

    lf = new OpenLF::lightfield::Lightfield(fileName.toStdString());

    int w = lf->width();
    int h = lf->height();
    int ch = lf->cams_h();
    int cv = lf->cams_v();

    QString dbg = "loaded LightField of size: ("+QString::number(ch)+","+QString::number(cv)+","+QString::number(w)+","+QString::number(h)+")";
    statusBar()->showMessage(dbg,3000);

    createDockWindows();
}

void LF_Viewer::openChannel(const QString &name)
{
    if (name.isEmpty())
        return;
    std::cout << name.toStdString() << std::endl;
    LF_Viewer_Child *test = new LF_Viewer_Child();
    mdiArea->addSubWindow(test);

    QImage img((uchar*)lf->data(), lf->width(), lf->height(), QImage::Format_RGB32);
    QPixmap pixmap = QPixmap::fromImage(img);

    test->setImage(&pixmap);
    test->show();
    //test->open();

    QString dbg = "Show Channel: " + name;
    statusBar()->showMessage(dbg,3000);

}

//void LF_Viewer::openChannel(const QString &name)
//{
//    if (name.isEmpty())
//        return;
//    std::cout << name.toStdString() << std::endl;
//    LF_Viewer_Child *test = new LF_Viewer_Child();
//    mdiArea->addSubWindow(test->scrollArea);
//    //if (activeMdiChild()) cout << "test" << endl;
//    test->open();

//}
