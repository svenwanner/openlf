#include "gui_toolbox.h"
#include <QApplication>

#include <iostream>
#include <vector>
#include <iomanip>



int main(int argc, char *argv[])
{
    QApplication LightFieldToolbox(argc, argv);

    LightFieldToolbox.setOrganizationName("HCI");
    LightFieldToolbox.setApplicationName("Light Field Toolbox");

	QNEMainWindow *_QNEMW = new QNEMainWindow();
	_QNEMW->showMaximized();

//     Prints welcome message...
    std::cout << "Welcome to Light-Field Nodes Editor" << std::endl;

    // Prints arguments...
    if (argc > 1) {
        std::cout << std::endl << "Arguments:" << std::endl;
        for (int i = 1; i < argc; i++) {
            std::cout << i << ": " << argv[i] << std::endl;
        }
    }

    return LightFieldToolbox.exec();
}
