#include "TransportWidget.h"
#include <QApplication>
#include <QDebug>
#include <QTextStream>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TransportWidget w;
    w.show();

    return a.exec();
}
