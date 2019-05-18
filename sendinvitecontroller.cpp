#include "sendinvitecontroller.h"
#include "game.h"

SendInviteController::SendInviteController(QObject* parent)
    : HttpRequestHandler(parent)
{

}

void SendInviteController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray data = request.getBody();
    QJsonDocument doc= QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QString inviteIP=obj.take("IP").toString();
    QString invitePort=obj.take("port").toString();
    QString inviteKey=obj.take("key").toString();



//    MoveChain newMoveChain (newMoveChainStr);
//    qDebug()<<"receive movechain: "<<newMoveChain.toJsonString();
    //    game->checkNewmove(newMoveChain,response);
    //    game->checkNewMove(newMoveChain, response);

}
