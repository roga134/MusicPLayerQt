#include "musicplayerpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    musicplayerpage w;
    w.setinformation(argv[1],argv[2],argv[3],argv[4]);
    w.show();
    return a.exec();
}
