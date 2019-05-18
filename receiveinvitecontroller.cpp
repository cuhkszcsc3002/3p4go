#include "receiveinvitecontroller.h"
#include "game.h"

ReceiveInviteController::ReceiveInviteController(QObject* parent)
    : HttpRequestHandler(parent)
{

}

/*
 * Method: ReceiveInviteController::service(HttpRequest &request, HttpResponse &response)
 * Usage: Called automatically
 * ------------------------------------------------
 * This method is use to decode the Json from client and pass the data after decode to
 * the game by calling receiveInvite function with the required parameter type.
 */

void ReceiveInviteController::service(HttpRequest &request, HttpResponse &response)
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

    game->receiveInvite(inviteIP,response);

}
