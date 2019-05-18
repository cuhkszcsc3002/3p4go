#include "receivenewmovecontroller.h"
#include "game.h"

ReceiveNewMoveController::ReceiveNewMoveController(QObject* parent)
    : HttpRequestHandler(parent) {
    // empty
}

void ReceiveNewMoveController::service(HttpRequest &request, HttpResponse &response) {

    QByteArray data = request.getBody();

    qDebug()<<data;

    QJsonDocument doc= QJsonDocument::fromJson(data);

    qDebug()<<doc;

    QJsonObject obj = doc.object();

    qDebug()<<obj;

    QString newMoveChainStr=obj.take("moveChain").toString();

    qDebug()<<newMoveChainStr;

    MoveChain newMoveChain (newMoveChainStr);

    game->checkNewmove(newMoveChain,response);


}
