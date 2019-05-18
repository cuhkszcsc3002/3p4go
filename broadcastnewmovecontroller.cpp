#include "broadcastnewmovecontroller.h"
#include "game.h"

BroadcastNewMoveController::BroadcastNewMoveController(QObject* parent)
    : HttpRequestHandler(parent) {
    // empty
}

void BroadcastNewMoveController::service(HttpRequest &request, HttpResponse &response) {
    QByteArray data = request.getBody();
    QJsonDocument doc= QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QString newMoveChainStr=obj.take("moveChain").toString();
    MoveChain newMoveChain (newMoveChainStr);

}
