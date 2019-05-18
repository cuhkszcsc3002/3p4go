#include "game.h"

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
    qDebug() << info.addresses();
    QString localIPAddress = "";
    QList<QHostAddress> listAddress = QNetworkInterface::allAddresses();
    for(int j = 0; j < listAddress.size(); j++){
      if(!listAddress.at(j).isNull()
          && listAddress.at(j).protocol() == QAbstractSocket::IPv4Protocol
          && listAddress.at(j) != QHostAddress::LocalHost){
              localIPAddress = listAddress.at(j).toString();
              return localIPAddress;
      }
    }
    qDebug() << "Get local IP address fail.";
    return NULL;

//    foreach(QHostAddress address, info.addresses())

//    {
//         if(address.protocol() == QAbstractSocket::IPv4Protocol) {
//            qDebug() << "Loading Local IP:" <<address.toString();
//            return address.toString();
//         }
//    }
//    return NULL;

}


void Client::init(Game * g)
{
    game = g;
}

QString Client::postRequest(QString url, QJsonDocument data)
{
    /*
     * A smart handler:
     * If http:// is lacked, add it automatically as default.
     */

    if (!url.startsWith("http") || !url.startsWith("https"))
    {
        url = "http://" + url;
    }

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


int Client::sendInvite(int playerIndex)
{
    // 1. Based on the IP, get the IP address.
    IP &ip = game->players[playerIndex];
    QString url = ip.getAddress() + ":" + QString::number(ip.getPort()) + "/sendInvite";

    // 2. Send the request for invitation.
    IP &myIP = game->myIP;
    QJsonObject data;
    data.insert("IP", myIP.getAddress());
    data.insert("port", myIP.getPort());

    qDebug() << "Send Invite: url:" << url << endl << "data:" << data;
    QJsonDocument document(data);

    // 3. Received feedback, and save the publicKey in ip.
    QString resultString = postRequest(url, document);
    QJsonObject result = QJsonDocument::fromJson(resultString.toUtf8().data()).object();
    if (!result.contains("result"))
    {
        qDebug() << "NO RESULT ERROR.";
        return -1;
    }
    else if (result.take("result")=="0")
    {
        qDebug() << "Invitation Rejected.";
        return 0;
    }
    else if (!result.contains("key")) {
        qDebug() << "Invitation Accepted, but NO KEY ERROR!";
        return -1;
    }
    else {
        QString keyString = result.take("key").toString();
        qDebug()<<"Invitation Accepted. Receive Key String:"<<keyString;
        Key2 newKey = Key2::decode(keyString);
        ip.setPublicKey(newKey);
        return 1;
    }
}

int Client::sendPlayerInfo()
{
    // 1. Encode the playerInfo in a json.
    QJsonArray array;
    for (IP &player: game->players) {
        QJsonObject obj;
        obj.insert("IP", player.getAddress());
        obj.insert("port", player.getPort());
        obj.insert("key", player.getPublicKey().encode());
        array.append(obj);
    }
    QJsonDocument document(array);

    // 2. Send the json to the other two players.
    for (int i=1; i<=2; i++)
    {
        IP & player = game->players[i];
        QString url = player.getAddress() + ":" + QString(player.getPort())
                + "/" + "sendPlayerInfo";
        QString resultString = postRequest(url, document);
        if (resultString=="1")
        {
            continue; // To the next player.
        }
        else {
            return 0;
        }
    }

    // 3. Return

    return 1;
}

int Client::sendForSig()
{
    // 1. Fetch the whole MoveChain and encode.
    MoveChain & mc = game->localMoveChain;
    QString moveChainString = mc.toJsonString();

    // 2. Send the whole MoveChain to the next player.
    IP & nextPlayer = game->players[(game->myIndex+1)%3];
    QString url = nextPlayer.getAddress() + ":" + QString(nextPlayer.getPort())
            + "/sendForSig";
    QJsonObject obj;
    obj.insert("moveChain", moveChainString);
    QJsonDocument document(obj);
    QString resultString = postRequest(url, document);

    // 3. Return
    if (resultString=="1")
    {
        return 1;
    }
    else {
        return 0;
    }

}

int Client::sendForSig(const MoveChain &mc, int playerIndex)
{
    // 1. Fetch the whole MoveChain and encode.
    QString moveChainString = mc.toJsonString();

    // 2. Send the whole MoveChain to the next player.
    IP & nextPlayer = game->players[playerIndex];
    QString url = nextPlayer.getAddress() + ":" + QString(nextPlayer.getPort())
            + "/sendForSig";
    QJsonObject obj;
    obj.insert("moveChain", moveChainString);
    QJsonDocument document(obj);
    QString resultString = postRequest(url, document);

    // 3. Return
    if (resultString=="1")
    {
        return 1;
    }
    else {
        return 0;
    }
}

int Client::broadcastNewMove()
{
    // 1. Fetch the whole MoveChain and enocde.
    MoveChain & mc = game->localMoveChain;
    QString moveChainString = mc.toJsonString();

    // 2. Send the whole MoveChain to the other players.
    for (int i=0; i<3; i++) {
        if (i != game->myIndex){
            IP & player = game->players[i];
            QString url = player.getAddress() + ":" + QString(player.getPort())
                    + "/boardcastNewMove";
            QJsonObject obj;
            obj.insert("moveChain", moveChainString);
            QJsonDocument document(obj);
            QString resultString = postRequest(url, document);
            if (resultString=="1")
            {
                continue;
            }
            else {
                return 0;
            }
        }
    }

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
    client.postRequest("127.0.0.1:8080", QJsonDocument());

}
