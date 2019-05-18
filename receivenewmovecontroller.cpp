#include "receivenewmovecontroller.h"
#include "game.h"

ReceiveNewMoveController::ReceiveNewMoveController(QObject* parent)
    : HttpRequestHandler(parent) {
    // empty
}

void ReceiveNewMoveController::service(HttpRequest &request, HttpResponse &response) {
    QByteArray data = request.getBody();
    QJsonDocument doc= QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QString newMoveChainStr=obj.take("moveChain").toString();
    MoveChain newMoveChain (newMoveChainStr);

//    game->checkNewmove(newMoveChain);

}
