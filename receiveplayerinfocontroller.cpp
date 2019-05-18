#include "receiveplayerinfocontroller.h"
#include "game.h"

ReceivePlayerInfoController::ReceivePlayerInfoController(QObject* parent)
    : HttpRequestHandler(parent)
{

}

void ReceivePlayerInfoController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray data = request.getBody();

    qDebug()<<data;

    QJsonDocument doc= QJsonDocument::fromJson(data);

    qDebug()<<doc;

    QJsonObject obj = doc.object();

    qDebug()<<obj;

    IP inviteIP(obj.take("IP").toString());

    qDebug()<<inviteIP;

    int invitePort=obj.take("port").toString().toInt();

    qDebug()<<invitePort;


    QString inviteKey=obj.take("key").toString();

    qDebug()<<inviteKey;

    game->updatePlayerInfo(inviteIP,inviteIP,inviteIP);



//    qDebug()<<"receive movechain: "<<newMoveChain.toJsonString();
}
