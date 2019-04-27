#include "mainwindow.h"
#include <QApplication>
#include "client.h"
#include "ip.h"
#include "move.h"
#include "rsa.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"Testing...";
    return a.exec();
}
