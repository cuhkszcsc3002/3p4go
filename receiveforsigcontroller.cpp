#include "receiveforsigcontroller.h"
#include "game.h"

ReceiveForSigController::ReceiveForSigController(QObject* parent)
    : HttpRequestHandler(parent)
{
    // empty
}

void ReceiveForSigController::service(HttpRequest &request, HttpResponse &response)
{

    QByteArray data = request.getBody();
    QJsonDocument doc= QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    QString newMoveChainStr=obj.take("moveChain").toString();
    MoveChain newMoveChain (newMoveChainStr);
    qDebug()<<"receive movechain: "<<newMoveChain.toJsonString();
//    game->checkNewmove(newMoveChain,response);
//    game->checkNewMove(newMoveChain, response);

}
