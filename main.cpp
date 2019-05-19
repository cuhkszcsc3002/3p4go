#include <QApplication>
//#include "client.h"
#include "game.h"
//#include "rsa2.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QCoreApplication serverApp(argc, argv);
//    serverApp.exec();
//    testServer(a);
//    qDebug()<<"Testing...";
    Game g(&a);
    g.init();
//    testRSA2();
//    testClient();
//    testIP();
//    testClient();
    return a.exec();
}
