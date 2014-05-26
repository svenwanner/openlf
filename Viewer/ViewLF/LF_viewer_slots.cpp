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





//void LF_Viewer::open_as_Subwidget()
//{
//  LF_Viewer_Child *test = new LF_Viewer_Child();
//  mdiArea->addSubWindow(test->scrollArea);
//  //if (activeMdiChild()) cout << "test" << endl;
//  test->open();
//}

//void LF_Viewer::open_as_Widget()
// {
//   LF_Viewer_Child *test = new LF_Viewer_Child();
//   test->open();
//}


void LF_Viewer::openLightField() {

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), path , tr("All files (*.*) ;; LF (*.lf) ;; HDF5 (*.h5 *.hdf5)"));
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
    else{
// generate Child as subwindow
        LF_Viewer_Child *test = new LF_Viewer_Child();
        mdiArea->addSubWindow(test);
        QImage OutputImage(lf->width(),lf->height(),QImage::Format_RGB888);

        if(name == "Color")
        {
            makeCOLORImage(OutputImage);
        }
        else if(name == "r" || name == "g" || name == "b"){
            makeCHANNELImage(name.toStdString(),OutputImage);
        }
        else{

        }

        QPixmap pixmap = QPixmap::fromImage(OutputImage);
    //Transfer Image to Child and show child
        test->setImage(name,&pixmap);
        test->show();


        QString dbg = "Show Channel: " + name;
        statusBar()->showMessage(dbg,3000);
    }
}

void LF_Viewer::openView(const QString &name)
{
    if (name.isEmpty())
        return;

// generate Child as subwindow
    LF_Viewer_Child *test = new LF_Viewer_Child();
// if this isn't there the window will be generated as own window
    mdiArea->addSubWindow(test);

//Extract numbers XX from names of singe viewXX
    std::string tmp = name.toStdString();
    const char firstNumber_char = tmp[4];
    int firstNumber_int = atoi(&firstNumber_char);
    const char secondNumber_char = tmp[5];
    int secondNumber_int = atoi(&secondNumber_char);
    //std::cout << first_int << second_string << std::endl;

//get Image related to the view number
    vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> > img;
    lf->getImage(firstNumber_int,secondNumber_int,img);

//convert image to pixmap
    QImage img1((uchar*)img.data(), img.width(), img.height(), QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img1);

//Transfer Image to Child and show child
    test->setImage(name,&pixmap);
    test->show();

//Show in status bar that image is loaded from LF
    QString dbg = "Show View: " + name;
    statusBar()->showMessage(dbg,3000);

}


//Functions to get either a color image or a gray of for each channel an Image

void LF_Viewer::makeCOLORImage(QImage &A){

    float* red = lf->channel_ptr("r");
    float* green = lf->channel_ptr("g");
    float* blue = lf->channel_ptr("b");;

    for(int i = 0; i<lf->height();i++){
         for(int j = 0; j<lf->width();j++){
        //std::cout << *channel << std::endl;
            QRgb value = qRgb((uchar)((float)255.0 * *red),(uchar)((float)255.0 * *green),(uchar)((float)255.0 * *blue));
            red++;
            green++;
            blue++;
            //std::cout << value << std::endl;
            A.setPixel(j,i,value);
         }
    }
}

void LF_Viewer::makeGRAYImage(std::string name,QImage &A){

    float* channel = lf->channel_ptr(name);

    for(int i = 0; i<lf->height();i++){
         for(int j = 0; j<lf->width();j++){
        //std::cout << *channel << std::endl;
            QRgb value = qRgb((uchar)((float)255.0 * *channel),(uchar)((float)255.0 * *channel),(uchar)((float)255.0 * *channel));
            channel++;
            //std::cout << value << std::endl;
            A.setPixel(j,i,value);
         }
    }
}

void LF_Viewer::makeCHANNELImage(std::string name,QImage &A){

    float* channel = lf->channel_ptr(name);

    for(int i = 0; i<lf->height();i++){
         for(int j = 0; j<lf->width();j++){
             uchar tmp = (uchar)((float)255.0 * *channel);
            channel++;
        //std::cout << *channel << std::endl;
            QRgb value;
            if (name == "r") value = qRgb(tmp,0,0);
            if (name == "g") value = qRgb(0,tmp,0);
            if (name == "b") value = qRgb(0,0,tmp);

            //std::cout << value << std::endl;
            A.setPixel(j,i,value);
         }
    }
}
