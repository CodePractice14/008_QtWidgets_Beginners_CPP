#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("Voidrealms");
    a.setOrganizationDomain("http://www.voidrealms.com");
    a.setApplicationName("Cool App");
    a.setApplicationDisplayName("My Cool Application");
    a.setApplicationVersion("0.1.15 Beta");

    MainWindow w;
    w.show();
    return a.exec();
}
