#include "game.h"

Server::Server()
{

}

void Server::init(Game * g)
{
    game = g;
}

int Server::receiveInvite()
{
    /*
     * A smart handler:
     * If http:// is lacked, add it automatically as default.
     */
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

QString Server::receiveSigReq()
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

    qDebug()<<stringSig;

    return stringSig;

}

int sigRequestFromGame()
{

}



QString Server::receiveNewMove()
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

    qDebug()<<stringMove;

    return stringMove;

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
