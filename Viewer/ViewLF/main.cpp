#include "LF_viewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication LightFieldViewer(argc, argv);

    LightFieldViewer.setOrganizationName("HCI");
    LightFieldViewer.setApplicationName("Light Field Viewer");

    LF_Viewer w;
    w.show();
    
    return LightFieldViewer.exec();
}
