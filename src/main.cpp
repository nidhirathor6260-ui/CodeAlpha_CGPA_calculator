#include <QApplication>
#include "mainwindow.h"

// ============================================================
// main.cpp — Application Entry Point
//
// Creates the Qt application, launches the main window.
// ============================================================
int main(int argc, char* argv[]) {

    // QApplication manages app-wide resources and event loop
    QApplication app(argc, argv);

    // Set application metadata (shown in task managers, About dialogs)
    QApplication::setApplicationName("CGPA Calculator");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("CollegeProject");

    // Create and show the main window
    MainWindow window;
    window.show();

    // Start the Qt event loop — runs until the window is closed
    return app.exec();
}
