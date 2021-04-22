#include "notepad.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Call the application object
    QApplication a(argc, argv);

    // Create the main application object and display it on the screen
    Notepad w;
    w.show();

    // Puts the application into a loop in which events are handled
    return a.exec();
}
