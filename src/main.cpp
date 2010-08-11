#include "photo_viewer.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Photo_Viewer w;
    w.show();
    return a.exec();
}
