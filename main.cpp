#include "mainwindow.h"
#include <QApplication>
//#include "client.h"
#include "game.h"
//#include "rsa2.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"Testing...";
//    Game g;
//    g.init();
//    testRSA2();
//    testClient();
    testIP();
    return a.exec();
}
