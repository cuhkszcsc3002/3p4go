#include "receiveinvitecontroller.h"
#include "game.h"

ReceiveInviteController::ReceiveInviteController(QObject* parent)
    : HttpRequestHandler(parent)
{

}

void ReceiveInviteController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray data = request.getBody();
    QJsonDocument doc= QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    IP inviteIP(obj.take("IP").toString());
    int invitePort=obj.take("port").toString().toInt();
    QString inviteKey=obj.take("key").toString();

//    game->receiveInvite(inviteIP);

//    MoveChain newMoveChain (newMoveChainStr);
//    qDebug()<<"receive movechain: "<<newMoveChain.toJsonString();
    //    game->checkNewmove(newMoveChain,response);
    //    game->checkNewMove(newMoveChain, response);

}
