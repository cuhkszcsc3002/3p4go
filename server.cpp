#include "game.h"
#include "QDir"
Server::Server()
{

}

void Server::init(Game * g,int avaliablePort)
{
    game = g;
//    int arg = 0;
//    char argv[10][10];
//    this->serverApp = new QCoreApplication(arg, argv);
    qDebug() << "Server Init Success.";

    run(avaliablePort);

}

void Server::run(int avaliablePort)
{
//    QString runPath = QCoreApplication::applicationDirPath();
    qDebug() << "Server Init at port: "<< avaliablePort;
//    QString configFileName="C:/Users/fsxgc/Documents/qt/3P4Go_Git/3p4go/webapp1.ini";
//    QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat,game->app);
//    listenerSettings->setValue("port", avaliablePort);

//    listenerSettings->beginGroup("listener");


    QSettings* settings = new QSettings("3P4GO", "Server");
    settings->beginGroup("listener");
    settings->setValue("port", avaliablePort);
    settings->setValue("minThreads", 4);
    settings->setValue("maxThreads", 100);
    settings->setValue("cleanupInterval", 6000000);
    settings->setValue("readTimeout", 6000000);
    settings->setValue("maxRequestSize", 16000000);
    settings->setValue("maxMultiPartSize", 1000000000);

    QSettings* listenerSettings=settings;


//    qDebug() << "listenerSettings:" << listenerSettings->allKeys();
//    listenerSettings->beginGroup("listener");
//    listenerSettings->setValue("port", avaliablePort);
    qDebug() << "listenerSettings:" << listenerSettings->allKeys();


    new HttpListener(listenerSettings, new RequestMapper(game->app, game), game->app);
//    new HttpListener(listenerSettings, new RequestMapper(nullptr, game));
};


int Server::replyInvite(HttpResponse * response,int result)
{
    qDebug() << "Server.replyInvite() invoked.";
    if (result==1)
    {
        QJsonObject result;
        result.insert("result", 1);
        result.insert("key", game->myIP.getPublicKey().toString());
        QJsonDocument doc(result);

        response->write(doc.toJson(), true);
    }
    else
    {
        QJsonObject result;
        result.insert("result", 0);
        QJsonDocument doc(result);

        response->write(doc.toJson(), true);
    }
}


void Server::rejectSig(HttpResponse & response)
{
    response.write("0", true);

    emit receiveForSigFinish();

}


void Server::acceptSig(HttpResponse &response)
{
    response.write("1",true);

    emit receiveForSigFinish();
}


void Server::acceptNewMove(HttpResponse &response)
{
    response.write("1",true);
    qDebug() << "Server.acceptNewMove";

    emit receiveNewMoveFinish();
}


void Server::rejectNewMove(HttpResponse &response)
{
    response.write("0",true);

    emit receiveNewMoveFinish();
}


void Server::finish()
{

}

