#include "game.h"
#include "QDir"
Server::Server()
{

}

void Server::init(Game * g)
{
    game = g;

}

void Server::run()
{
    QString runPath = QCoreApplication::applicationDirPath();

    qDebug()<<runPath;

    QString configFileName="/Users/TY/3p4go/webapp1.ini";
//    QString configFileName="./3p4go/webapp1.ini";

    qDebug()<<configFileName;

    // Session store
    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,game->app);
    sessionSettings->beginGroup("sessions");
    RequestMapper::sessionStore=new HttpSessionStore(sessionSettings, game->app);

    // Start the HTTP server
    QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat, game->app);
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
