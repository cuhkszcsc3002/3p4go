#include "game.h"
#include "QDir"
Server::Server()
{

}

void Server::init(Game * g,int avaliablePort=8080)
{
    game = g;
//    int arg = 0;
//    char argv[10][10];
//    this->serverApp = new QCoreApplication(arg, argv);
    qDebug() << "Server Init Success.";

    run(avaliablePort);

}

void Server::run(int avaliablePort=8080)
{
//    QString runPath = QCoreApplication::applicationDirPath();
    qDebug() << "Server Init at port: "<< avaliablePort;
    QSettings settings("3P4GO", "Server"), settings2("3P4Go", "Server");
    settings.beginGroup("listener");
    settings.setValue("port",avaliablePort);
    settings.setValue("minThreads",4);
    settings.setValue("maxThreads",100);
    settings.setValue("cleanupInterval",60000);
    settings.setValue("readTimeout",60000);
    settings.setValue("maxRequestSize",16000);
    settings.setValue("maxMultiPartSize",10000000);
    settings.endGroup();
    settings.beginGroup("sessions");
    settings.setValue("expirationTime",3600000);
    settings.setValue("cookieName","sessionid");
    settings.setValue("cookiePath","/");
    settings.setValue("cookieComment","Identifies the user");
    settings.endGroup();

    settings2.beginGroup("listener");
    settings2.setValue("port",avaliablePort);
    settings2.setValue("minThreads",4);
    settings2.setValue("maxThreads",100);
    settings2.setValue("cleanupInterval",60000);
    settings2.setValue("readTimeout",60000);
    settings2.setValue("maxRequestSize",16000);
    settings2.setValue("maxMultiPartSize",10000000);
    settings2.endGroup();

    settings2.beginGroup("sessions");
    settings2.setValue("expirationTime",3600000);
    settings2.setValue("cookieName","sessionid");
    settings2.setValue("cookiePath","/");
    settings2.setValue("cookieComment","Identifies the user");
    settings2.endGroup();

    QSettings * sessionSettings = &settings;
    qDebug() << "SessionSettings:" << sessionSettings->allKeys();

    sessionSettings->beginGroup("sessions");

    RequestMapper::sessionStore=new HttpSessionStore(sessionSettings, game->app);

    QSettings* listenerSettings=&settings2;
    qDebug() << "listenerSettings:" << listenerSettings->allKeys();

    listenerSettings->beginGroup("listener");

    new HttpListener(listenerSettings, new RequestMapper(game->app, game),game->app);
};


int Server::replyInvite(HttpResponse & response,int result)
{
    if (result==1)
    {
        response.write("1",true);
    }
    else
    {
        response.write("0",true);
    }
}


void Server::rejectSig(HttpResponse & response)
{
    response.write("0", true);

}


void Server::acceptSig(HttpResponse &response)
{
    response.write("1",true);
}


void Server::acceptNewMove(HttpResponse &response)
{
    response.write("1",true);
}


void Server::rejectNewMove(HttpResponse &response)
{
    response.write("0",true);
}


void Server::finish()
{

}

