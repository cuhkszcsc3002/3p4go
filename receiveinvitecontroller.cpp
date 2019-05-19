#include "receiveinvitecontroller.h"
#include "game.h"

ReceiveInviteController::ReceiveInviteController(Game* g, QObject* parent)
    : HttpRequestHandler(parent)
{
    game = g;
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
    qDebug() << "Server.rceiveInviteController service";
    QByteArray data = request.getBody();

    qDebug()<<data;

    QJsonDocument doc= QJsonDocument::fromJson(data);

    qDebug()<<doc;

    QJsonObject obj = doc.object();

    qDebug()<<obj;
    int port = obj.take("port").toInt();
    qDebug() << "port:" << port;
    IP inviteIP = IP(obj.take("IP").toString(), port);


//    inviteIP.setPort(invitePort);

    qDebug()<<inviteIP;

    QString inviteKey=obj.take("key").toString();


    game->receiveInvite(inviteIP,response);

    QEventLoop eventLoop;
    QObject::connect(game->gui->invite, SIGNAL(inviteAccept()), &eventLoop, SLOT(quit()));
    QObject::connect(game->gui->invite, SIGNAL(inviteReject()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    qDebug() << "Loop End";

}
