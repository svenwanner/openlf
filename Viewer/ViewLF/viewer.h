#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QFileDialog>

#include <lightfield/Lightfield.hpp>

namespace Ui {
class Viewer;
}

class Viewer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();
    
private slots:
    void openLightField();

private:
    Ui::Viewer *ui;
    OpenLF::lightfield::Lightfield lf;
};

#endif // VIEWER_H
