#include "LF_viewer.h"
#include <QMessageBox>
#include "LF_viewer_child.h"
#include <iostream>
#include <QMdiSubWindow>

void LF_Viewer::setValue(int value){

    slider->setValue(value);
    spinBox->setValue(value);





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



void LF_Viewer::openLightField() {

    if (lf != NULL){
        delete lf;
        lf=NULL;
        mdiArea->closeAllSubWindows();
    }

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), path , tr("All files (*.*) ;; LF (*.lf) ;; HDF5 (*.h5 *.hdf5)"));
    path = QFileInfo(fileName).path(); // store path for next time
    QFileInfo info(fileName);

    QString EXTENSION = info.suffix();
    QString MODIFIED_DATE = info.lastModified().toString();

    if (fileName.isEmpty())
        return;

<<<</*<<< Updated upstream
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), path , tr("All files (*.*) ;; LF (*.lf) ;; HDF5 (*.h5 *.hdf5)"));
    path = QFileInfo(fileName).path(); // store path for next time
=======*/
    if (EXTENSION.toStdString() != "hdf5" && EXTENSION.toStdString() != "h5" && EXTENSION.toStdString() != "lf" && EXTENSION.toStdString() != "h5")
        return;
//>>>>>>> Stashed changes

    lf = new OpenLF::lightfield::Lightfield(fileName.toStdString());




    int w = lf->width();
    int h = lf->height();
    int ch = lf->cams_h();
    int cv = lf->cams_v();

    QString dbg = "loaded LightField of size: ("+QString::number(ch)+","+QString::number(cv)+","+QString::number(w)+","+QString::number(h)+")";
    statusBar()->showMessage(dbg,3000);

    slider->setEnabled(true);
    spinBox->setEnabled(true);

    createDockWindows();
}

void LF_Viewer::openChannel(const QString &name)
{
    if (name.isEmpty())
        return;
//<<<<<<< Updated upstream
//    else{
//// generate Child as subwindow
//        LF_Viewer_Child *test = new LF_Viewer_Child();
//        mdiArea->addSubWindow(test);
//        QImage OutputImage(lf->width(),lf->height(),QImage::Format_RGB888);

//        if(name == "Color")
//        {
//            makeCOLORImage(OutputImage);
//        }
//        else if(name == "r" || name == "g" || name == "b"){
//            makeCHANNELImage(name.toStdString(),OutputImage);
//        }
//        else{

//        }

//        QPixmap pixmap = QPixmap::fromImage(OutputImage);
//    //Transfer Image to Child and show child
//        test->setImage(name,&pixmap);
//        test->show();


//        QString dbg = "Show Channel: " + name;
//        statusBar()->showMessage(dbg,3000);
//    }
//=======

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
    else if(name == "bw" ){
        makeGRAYImage(name.toStdString(),OutputImage);
    }
    else{
    // Todo: Discuss about representation of result channels
    }

    QPixmap pixmap = QPixmap::fromImage(OutputImage);
//Transfer Image to Child and show child
    test->setImage(name,&pixmap);
    test->setObjectName(name);
    test->show();

//>>>>>>> Stashed changes
}

void LF_Viewer::openView(const QString &name)
{
    if (name.isEmpty())
        return;

// generate Child as subwindow
    LF_Viewer_Child *test = new LF_Viewer_Child();
    test->enableEPI(true);
    connect(test, SIGNAL(mouseClick(QPoint)), this , SLOT(showEPI(QPoint)));

// if this isn't there the window will be generated as own window
    mdiArea->addSubWindow(test);

//Extract numbers XX from names of singe viewXX
    std::string tmp = name.toStdString();
    const char firstNumber_char = tmp[0];
    int firstNumber_int = atoi(&firstNumber_char);
    const char secondNumber_char = tmp[1];
    int secondNumber_int = atoi(&secondNumber_char);
    std::cout << firstNumber_int << secondNumber_int << std::endl;

//get Image related to the view number
    vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> > img;
    lf->getImage(firstNumber_int,secondNumber_int,img);

//convert image to pixmap
    QImage img1((uchar*)img.data(), img.width(), img.height(), QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img1);

//Transfer Image to Child and show child
    test->setImage(name,&pixmap);
    test->setObjectName(name);
    test->show();
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
//<<<<<<< Updated upstream
//    }
//}

//void LF_Viewer::makeGRAYImage(std::string name,QImage &A){
//=======
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
//>>>>>>> Stashed changes

    float* channel = lf->channel_ptr(name);

    for(int i = 0; i<lf->height();i++){
         for(int j = 0; j<lf->width();j++){
//<<<<<<< Updated upstream
//        //std::cout << *channel << std::endl;
//            QRgb value = qRgb((uchar)((float)255.0 * *channel),(uchar)((float)255.0 * *channel),(uchar)((float)255.0 * *channel));
//            channel++;
//            //std::cout << value << std::endl;
//=======
             uchar tmp = (uchar)((float)255.0 * *channel);
            channel++;
            QRgb value;
            if (name == "r") value = qRgb(tmp,0,0);
            if (name == "g") value = qRgb(0,tmp,0);
            if (name == "b") value = qRgb(0,0,tmp);
//>>>>>>> Stashed changes
            A.setPixel(j,i,value);
         }
    }
}
//<<<<<<< Updated upstream

//void LF_Viewer::makeCHANNELImage(std::string name,QImage &A){

//    float* channel = lf->channel_ptr(name);

//    for(int i = 0; i<lf->height();i++){
//         for(int j = 0; j<lf->width();j++){
//             uchar tmp = (uchar)((float)255.0 * *channel);
//            channel++;
//        //std::cout << *channel << std::endl;
//            QRgb value;
//            if (name == "r") value = qRgb(tmp,0,0);
//            if (name == "g") value = qRgb(0,tmp,0);
//            if (name == "b") value = qRgb(0,0,tmp);

//            //std::cout << value << std::endl;
//            A.setPixel(j,i,value);
//         }
//    }
//=======

void LF_Viewer::close(){
    mdiArea->closeAllSubWindows();
    delete dock;
    delete dock2;
    delete lf;
    lf = NULL;
    dock = NULL;
    dock2 = NULL;
    slider->setEnabled(false);
    spinBox->setEnabled(false);
}
void LF_Viewer::closeAll(){
    mdiArea->closeAllSubWindows();
}

void LF_Viewer::showEPI(QPoint position){
    const int ToolBar_Height = 40;
    qDebug() << "Position: (" << QString::number( position.x()-1 ) <<"."<< QString::number(position.y()-ToolBar_Height-1) <<")";
    qDebug() << "Horoptor: " << QString::number(spinBox->value());

//generate EPI horizontal
    LF_Viewer_Child *test = new LF_Viewer_Child();
//get Image related to the view number
    vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> > img;
    lf->getHorizontalEpi(position.y()-ToolBar_Height-1,(int)round(lf->cams_h()/2-1),spinBox->value(),img);

    mdiArea->addSubWindow(test);

//convert image to pixmap
    QImage img1((uchar*)img.data(), img.width(), img.height(), QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img1);

//Transfer Image to Child and show child
    QString name = "EPI_H YPosition:" + QString::number(position.y()-ToolBar_Height-1) + " Horoptor: " + QString::number(spinBox->value());
    test->setImage(name,&pixmap);
    test->setObjectName(name);
    test->show();

//generate EPI vertical
    test = new LF_Viewer_Child();

//get Image related to the view number
    vigra::MultiArray<2,vigra::RGBValue<vigra::UInt8> > img2;
    lf->getVerticalEpi(position.x()-1,(int)round(lf->cams_v()/2-1),spinBox->value(),img2);

    mdiArea->addSubWindow(test);

//convert image to pixmap
    QImage img11((uchar*)img2.data(), img2.width(), img2.height(), QImage::Format_RGB888);
    QPixmap pixmap2 = QPixmap::fromImage(img11);

//Transfer Image to Child and show child
    QString name1 = "EPI_V XPosition:" + QString::number(position.x()-1) + " Horoptor: " + QString::number(spinBox->value());
    test->setImage(name1,&pixmap2);
    test->setObjectName(name);
    test->show();

}

void LF_Viewer::on_action_Pop_Out_triggered()
{
    if (mdiArea->activeSubWindow()){
        QMdiSubWindow *sub = mdiArea->activeSubWindow();
        QWidget *wid = sub->widget();
        wid->hide();
        sub->deleteLater();
        mdiArea->removeSubWindow(wid);
        wid->show();
    }

//    QListWidget* list = new QListWidget();
//    list->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

//    //Add SubWindows List to QListWidget Here
//    foreach(QMdiSubWindow* window , mdiArea->subWindowList())
//    {
//      list->addItem(window->objectName());
//      std::cout << window->objectName().toStdString() << std::endl;
//    }


//>>>>>>> Stashed changes
}
