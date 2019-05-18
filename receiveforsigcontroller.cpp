#include "receiveforsigcontroller.h"
#include "game.h"

ReceiveForSigController::ReceiveForSigController(QObject* parent)
    : HttpRequestHandler(parent)
{
    // empty
}

/*
 * Method: ReceiveForSigController::service(HttpRequest &request, HttpResponse &response)
 * Usage: Called automatically
 * ------------------------------------------------
 * This method is use to decode the Json from client and pass the data after decode to
 * the game by calling validateForSig function with the required parameter type.
 */

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


    //TODO
    game->validateForSig(newMoveChain,1,response);

}
