#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);

    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openLightField()));
}

Viewer::~Viewer()
{
    delete ui;
}


void Viewer::openLightField() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.lf *.h5)"));
    ui->debugLabel->setText(QString("Try to open file: ")+fileName);

    lf = OpenLF::lightfield::Lightfield(fileName.toStdString());

    int w = lf.width();
    int h = lf.height();
    int ch = lf.cams_h();
    int cv = lf.cams_v();

    QString dbg = "loaded LightField of size: ("+QString::number(ch)+","+QString::number(cv)+","+QString::number(w)+","+QString::number(h)+")";
    ui->debugLabel->setText(dbg);
}
