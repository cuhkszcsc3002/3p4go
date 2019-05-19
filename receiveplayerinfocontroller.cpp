#include "receiveplayerinfocontroller.h"
#include "game.h"

ReceivePlayerInfoController::ReceivePlayerInfoController(Game *g, QObject* parent)
    : HttpRequestHandler(parent)
{
    game = g;
}

/*
 * Method: ReceivePlayerInfoController::service(HttpRequest &request, HttpResponse &response)
 * Usage: Called automatically
 * ------------------------------------------------
 * This method is use to decode the Json from client and pass the data after decode to
 * the game by calling updatePlayerInfo function with the required parameter type.
 */

void ReceivePlayerInfoController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray data = request.getBody();

    qDebug()<<data;

    QJsonDocument doc= QJsonDocument::fromJson(data);

    qDebug()<<doc;

    QJsonArray array = doc.array();

    qDebug()<<array;

    QList<IP> IPArray;
    IP newIP;

    for (QJsonValue value: array)
    {
        QJsonObject obj = value.toObject();
        QString address = obj.take("IP").toString();
        int port = obj.take("port").toInt();
        Key2 newKey = Key2::decode(obj.take("key").toString());
        newIP = IP(address, port);
        newIP.setPublicKey(newKey);
        IPArray.append(newIP);
    }
    qDebug() << IPArray;
//    Q_ASSERT(IPArray.length()==3);
    game->updatePlayerInfo(IPArray.at(0), IPArray.at(1), IPArray.at(2));

    response.write("1", true);
    qDebug() << "ReceivePlayerInfo Complete.";

//    QEventLoop eventLoop;

//    QObject::connect(game->server, SIGNAL(receivePlayerInfoFinish()), &eventLoop, SLOT(quit()));

//    eventLoop.exec();

//    qDebug()<<"receive movechain: "<<newMoveChain.toJsonString();
}
