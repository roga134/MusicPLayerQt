#include "musicplayerpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    musicplayerpage w;
    w.show();
    return a.exec();
}
