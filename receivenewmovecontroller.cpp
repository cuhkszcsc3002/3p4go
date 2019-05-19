#include "receivenewmovecontroller.h"
#include "game.h"

ReceiveNewMoveController::ReceiveNewMoveController(Game *g, QObject* parent)
    : HttpRequestHandler(parent) {
    game = g;
}

/*
 * Method: ReceiveNewMoveController::service(HttpRequest &request, HttpResponse &response)
 * Usage: Called automatically
 * ------------------------------------------------
 * This method is use to decode the Json from client and pass the data after decode to
 * the game by calling checkNewmove function with the required parameter type.
 */

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
