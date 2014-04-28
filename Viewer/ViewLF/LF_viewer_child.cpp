#include <QtGui>

#include "LF_viewer_child.h"

MdiChild::MdiChild()
 {
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
    static int sequenceNumber = 1;
    curFile = tr("document%1.jpg").arg(sequenceNumber++);
    setWindowTitle(curFile + "[*]");

    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    pxmap = new QPixmap(":/lenna.png");
    imageLabel->setPixmap(*pxmap);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);



}





bool MdiChild::save()
 {
    if (isUntitled)  {
        return saveAs();
    } else  {
        return saveFile(curFile);
    }
}

bool MdiChild::saveAs()
 {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool MdiChild::saveFile(const QString &fileName)
 {

    return true;
}


void MdiChild::setCurrentFile(const QString &fileName)
 {

}

QString MdiChild::userFriendlyCurrentFile()
 {
    return strippedName(curFile);
}


QString MdiChild::strippedName(const QString &fullFileName)
 {
    return QFileInfo(fullFileName).fileName();
}
