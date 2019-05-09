#include "server.h"

Server::Server()
{

}

void Server::init(Game * g)
{
    game = g;
}

//int Server::receiveInvite(IP players_Ip, int p)
//{

//}

int testServer(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Load the configuration file
    QString configFileName="/Users/TY/Downloads/QtWebApp/MyFirstWebApp/etc/webapp1.ini";
    qDebug()<<configFileName;
    // Session store
    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    sessionSettings->beginGroup("sessions");
    RequestMapper::sessionStore=new HttpSessionStore(sessionSettings,&app);

    // Start the HTTP server
    QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat, &app);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings,new RequestMapper(&app),&app);

    return app.exec();
}
