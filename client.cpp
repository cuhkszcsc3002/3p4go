#include "client.h"

Client::Client()
{

}

IP Client::getLocalIP()
{
    QString ipAddress = getLocalIPAddress();
    IP local;
    local.setAddressFromString(ipAddress);
    QList<Key2> keys = RSA2::generateKey();
    local.setPublicKey(keys[0]);
    local.setPrivateKey(keys[1]);
    return local;
}

QString Client::getLocalIPAddress()
{
    QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
    QNetworkInterface eth;

    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);

    foreach(QHostAddress address, info.addresses())

    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol) {
            qDebug() << "Loading Local IP:" <<address.toString();
            return address.toString();
         }
    }
    return NULL;
}


void Client::init(Game * g)
{
    game = g;

    // 1. Use getLocalIP and set the local IP and keys.

}

QString Client::postRequest(QString url, QJsonDocument data)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl qurl = QUrl(url);

    QByteArray dataArray = data.toJson(QJsonDocument::Compact);

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply * reply = manager->post(request, dataArray);

    QEventLoop eventLoop;

    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray replyData = reply->readAll();
    qDebug()<<replyData;
    return replyData;
}


int Client::sendInvite(IP &ip)
{
    // 1. Based on the IP, get the IP address.

    // 2. Send the request for invitation.

    // 3. Received feedback, and save the publicKey in ip.


    return 1;

}

int Client::sendPlayerInfo()
{
    // 1. Encode the playerInfo in a json.


    // 2. Send the json to the other two players.


    // 3. Return

    return 1;
}

int Client::sendForSig()
{
    // 1. Fetch the whole MoveChain and encode.

    // 2. Send the whole MoveChain to the next player.

    // 3. Return

    return 1;
}

int Client::boardcastNewMove()
{
    // 1. Fetch the whole MoveChain and enocde.

    // 2. Send the whole MoveChain to the other players.

    // 3. Return

    return 1;
}

void Client::finish()
{

}

void testClient()
{
    Client client;
    qDebug() << client.getLocalIPAddress();
    client.postRequest("http://www.baidu.com", QJsonDocument());

}
