#include "receiveplayerinfocontroller.h"
#include "game.h"

ReceivePlayerInfoController::ReceivePlayerInfoController(QObject* parent)
    : HttpRequestHandler(parent)
{

}

void ReceivePlayerInfoController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray data = request.getBody();
    QJsonDocument doc= QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    IP inviteIP(obj.take("IP").toString());
    int invitePort=obj.take("port").toString().toInt();
    QString inviteKey=obj.take("key").toString();


//    qDebug()<<"receive movechain: "<<newMoveChain.toJsonString();
}
