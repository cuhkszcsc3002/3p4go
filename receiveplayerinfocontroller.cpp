#include "receiveplayerinfocontroller.h"
#include "game.h"

ReceivePlayerInfoController::ReceivePlayerInfoController(Game *g, QObject* parent)
    : HttpRequestHandler(parent)
{
    game = g;
}

/*
 * Method: ReceivePlayerInfoController::service(HttpRequest &request, HttpResponse &response)
 * Usage: Called automatically
 * ------------------------------------------------
 * This method is use to decode the Json from client and pass the data after decode to
 * the game by calling updatePlayerInfo function with the required parameter type.
 */

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

//    TODO
    game->updatePlayerInfo(inviteIP,inviteIP,inviteIP);

    response.write("1", true);

//    QEventLoop eventLoop;

//    QObject::connect(game->server, SIGNAL(receivePlayerInfoFinish()), &eventLoop, SLOT(quit()));

//    eventLoop.exec();

//    qDebug()<<"receive movechain: "<<newMoveChain.toJsonString();
}
