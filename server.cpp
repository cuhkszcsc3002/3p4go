#include "game.h"

Server::Server()
{

}

void Server::init(Game * g)
{
    game = g;
}

void Server::run()
{

};


int Server::receiveInvite()
{

    QString url="http://127.0.0.1:8080/sendInvite";

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl qurl = QUrl(url);

    QByteArray dataArray = QJsonDocument().toJson(QJsonDocument::Compact);

    request.setUrl(url);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply * reply = manager->post(request, dataArray);

    QEventLoop eventLoop;

    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray ipAddress = reply->readAll();

    qDebug()<<ipAddress;
    bool ok;
    int result=ipAddress.toInt(&ok,10);
    return result;

//    return replyData;
}

int Server::replyInvite()
{

}

QString Server::receivePlayerInfo()
{
    QString url="http://127.0.0.1:8080/sendPlayerInfo";

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl qurl = QUrl(url);

    QByteArray dataArray = QJsonDocument().toJson(QJsonDocument::Compact);

    request.setUrl(url);

    QNetworkReply * reply = manager->post(request, dataArray);

    QEventLoop eventLoop;

    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray playerInfo = reply->readAll();
    QString stringInfo=playerInfo;

    qDebug()<<stringInfo;

    return stringInfo;


}

MoveChain Server::receiveSigReq()
{
    QString url="http://127.0.0.1:8080/sendPlayerInfo";

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkRequest request;
    QUrl qurl = QUrl(url);

    QByteArray dataArray = QJsonDocument().toJson(QJsonDocument::Compact);

    request.setUrl(url);

    QNetworkReply * reply = manager->post(request, dataArray);

    QEventLoop eventLoop;

    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray arraySig = reply->readAll();

    QString stringSig=arraySig;

    MoveChain chainSig=stringSig;

    qDebug()<<stringSig;

    return chainSig;

}

void Server::rejectSig(HttpResponse & response)
{
    response.write("0", true);

}

void Server::acceptSig(HttpResponse &response)
{
    response.write("1",true);
}



MoveChain Server::receiveNewMove()
{
    QString url="http://127.0.0.1:8080/boardcastNewMove";

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl qurl = QUrl(url);

    QByteArray dataArray = QJsonDocument().toJson(QJsonDocument::Compact);

    request.setUrl(url);

    QNetworkReply * reply = manager->post(request, dataArray);

    QEventLoop eventLoop;

    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray arrayMove = reply->readAll();

    QString stringMove=arrayMove;

    MoveChain chainMove=stringMove;

    qDebug()<<stringMove;

    return chainMove;

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
    QString runPath = QCoreApplication::applicationDirPath();
    qDebug()<<runPath;
    QString configFileName="/Users/TY/3p4go/webapp1.ini";
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
