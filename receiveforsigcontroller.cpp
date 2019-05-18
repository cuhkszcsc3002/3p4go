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

    qDebug()<<data;

    QJsonDocument doc= QJsonDocument::fromJson(data);

    qDebug()<<doc;

    QJsonObject obj = doc.object();

    qDebug()<<obj;

    QString newMoveChainStr=obj.take("moveChain").toString();

    qDebug()<<newMoveChainStr;

    MoveChain newMoveChain (newMoveChainStr);

    qDebug()<<"receive movechain: "<<newMoveChain.toJsonString();

    game->validateForSig(newMoveChain,1,response);

}
