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

    GUI_Toolbox gui;
//    LFgui.loadConfigini(config_path);
    gui.show();

//     Prints welcome message...
    std::cout << "Welcome to Light-Field GUI" << std::endl;

    // Prints arguments...
    if (argc > 1) {
        std::cout << std::endl << "Arguments:" << std::endl;
        for (int i = 1; i < argc; i++) {
            std::cout << i << ": " << argv[i] << std::endl;
        }
    }

    return LightFieldToolbox.exec();
}
