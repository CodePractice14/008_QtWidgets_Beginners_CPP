#include "dialog.h"

#include <QApplication>

/*
    Absolute Layouts should be avoided at all costs
    Controls get set on their exact position (they do not scale)

*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
