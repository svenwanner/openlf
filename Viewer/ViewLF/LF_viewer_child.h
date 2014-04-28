#ifndef LF_VIEWER_CHILD_H
#define LF_VIEWER_CHILD_H

#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QtGui>

#include <QScrollArea>
#include <QLabel>

class MdiChild : public QWidget
 {
    Q_OBJECT

public:
    MdiChild();


    QPixmap *pxmap;
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();
    QString currentFile()  { return curFile; }

//protected:

//private slots:


private:

    QLabel *imageLabel;
    QScrollArea *scrollArea;

    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QString curFile;
    bool isUntitled;
};

#endif // LF_VIEWER_CHILD_H
