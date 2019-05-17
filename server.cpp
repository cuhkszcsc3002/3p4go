#include "game.h"

Server::Server()
{

}

void Server::init(Game * g)
{
    game = g;
}

int Server::receiveInvite(IP players_Ip, int p)
{

}

int Server::receivePlayerInfo()
{

}

int Server::receiveSigReq(int request)
{

}

int Server::rejectSig()
{

}

int Server::acceptSig()
{

}

int Server::receiveNewMove()
{

}

void Server::finish()
{

}

void testServer(QCoreApplication& app)
{
//    QCoreApplication app(argc, argv);

    // Load the configuration file
    QString runPath = QCoreApplication::applicationDirPath();
    qDebug()<<runPath;
    QString configFileName="/Users/TY/Desktop/3p4go 2/webapp1.ini";
    //    QString configFileName="./webapp1.ini";

    qDebug()<<configFileName;

    // Session store
    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    sessionSettings->beginGroup("sessions");
    RequestMapper::sessionStore=new HttpSessionStore(sessionSettings,&app);

    // Start the HTTP server
    QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat, &app);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings,new RequestMapper(&app),&app);

//    return app.exec();
}
