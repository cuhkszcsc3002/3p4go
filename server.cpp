#include "game.h"
#include "QDir"
Server::Server()
{

}

void Server::init(Game * g,int avaliablePort=8080)
{
    game = g;

    run(avaliablePort);

}

void Server::run(int avaliablePort=8080)
{
    QString runPath = QCoreApplication::applicationDirPath();

    QSettings settings;
    settings.beginGroup("listener");
    settings.setValue("port",avaliablePort);
    settings.setValue("minThreads",4);
    settings.setValue("maxThreads",100);
    settings.setValue("cleanupInterval",60000);
    settings.setValue("readTimeout",60000);
    settings.setValue("maxRequestSize",16000);
    settings.setValue("maxMultiPartSize",10000000);

    settings.beginGroup("sessions");
    settings.setValue("expirationTime",3600000);
    settings.setValue("cookieName","sessionid");
    settings.setValue("cookiePath","/");
    settings.setValue("cookieComment","Identifies the user");

//    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,game->app);

    QSettings* sessionSettings=&settings;


    sessionSettings->beginGroup("sessions");

    RequestMapper::sessionStore=new HttpSessionStore(sessionSettings, game->app);

    // Start the HTTP server
//    QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat, game->app);

    QSettings* listenerSettings=&settings;


    listenerSettings->beginGroup("listener");

    new HttpListener(listenerSettings,new RequestMapper(game->app, game),game->app);
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


void testServer(QCoreApplication& app)
{
    // Load the configuration file


//    return app.exec();
}
