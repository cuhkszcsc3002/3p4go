#include "game.h"

Client::Client()
{

}

IP Client::getLocalIP()
{
    qDebug() << "Getting Local IP. . .";
    QString ipAddress = getLocalIPAddress();
    IP local;
    local.setAddressFromString(ipAddress);
    QList<Key2> keys = RSA2::generateKey();
    local.setPublicKey(keys[0]);
    local.setPrivateKey(keys[1]);
    qDebug() << "Local IP:" << local;
    return local;
}

QString Client::getLocalIPAddress()
{
    qDebug() << "Getting Local IP Address . . .";
//    QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
//    QNetworkInterface eth;

    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
// //    qDebug() << info.addresses();
    QString localIPAddress = "";
    QList<QHostAddress> listAddress = QNetworkInterface::allAddresses();
    qDebug() << listAddress;
    for(int j = 0; j < listAddress.size(); j++){
      if(!listAddress.at(j).isNull()
          && listAddress.at(j).protocol() == QAbstractSocket::IPv4Protocol
          && listAddress.at(j) != QHostAddress::LocalHost
              && !listAddress.at(j).toString().startsWith("192.168")
          ){
              localIPAddress = listAddress.at(j).toString();
              qDebug() << "Local IP Address Received: "<< localIPAddress;
              return localIPAddress;
      }
    }
    qDebug() << "Get local IP address fail.";
//    return NULL;

//    foreach(QHostAddress address, info.addresses())

//    {
//         if(address.protocol() == QAbstractSocket::IPv4Protocol) {
//            qDebug() << "Loading Local IP:" <<address.toString();
//            return address.toString();
//         }
//    }
    return NULL;

}


void Client::init(Game * g)
{
    qDebug() << "Client init.";
    game = g;
}

QString Client::postRequest(QString url, QJsonDocument data)
{
    /*
     * A smart handler:
     * If http:// is lacked, add it automatically as default.
     */

    if ((!url.startsWith("http")) || (!url.startsWith("https")))
    {
        url = "http://" + url;
    }

    qDebug() << "Post Request Url:" << url;

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl qurl = QUrl(url);

    QByteArray dataArray = data.toJson(QJsonDocument::Compact);

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply * reply = manager->post(request, dataArray);

    QEventLoop eventLoop;
    qDebug() << "Post Request Start Loop";

//    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();


    qDebug() << "Post Request Finished";
    QByteArray replyData = reply->readAll();
    qDebug()<< "Post Request Reply: " << replyData;
//    delete manager;

    return replyData;
}


int Client::sendInvite(int playerIndex)
{
    // 1. Based on the IP, get the IP address.
    IP &ip = game->players[playerIndex];
//    qDebug() << ip;
    QString url = ip.getFullAddress() + "/sendInvite";

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
    qDebug() << "Send Player Info . . .";

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
        qDebug() << endl << "Full address: " << player.getFullAddress() << endl << player;
        QString url = player.getFullAddress()
                + "/" + "sendPlayerInfo";
        qDebug() << "Client.sendPlayerInfo: url: " << url << document;
        QString resultString = postRequest(url, document);
        if (resultString=="1")
        {
            qDebug() << "Send Player Info 1: Success";
            continue; // To the next player.
        }
        else {
            qDebug() << "Send Player Info 1: Fail";
            return 0;
        }
    }

    // 3. Return
    qDebug() << "Send Player Info Success.";
    return 1;
}

int Client::sendForSig()
{
    qDebug() << "Send For Sig . . .";
    // 1. Fetch the whole MoveChain and encode.
    MoveChain & mc = game->localMoveChain;
    QString moveChainString = mc.toJsonString();

    // 2. Send the whole MoveChain to the next player.
    IP & nextPlayer = game->players[(game->myIndex+1)%3];
    QString url = nextPlayer.getFullAddress()
            + "/sendForSig";
    QJsonObject obj;
    obj.insert("moveChain", moveChainString);
    QJsonDocument document(obj);
    QString resultString = postRequest(url, document);

    // 3. Return
    if (resultString=="1")
    {
        qDebug() << "Send For Sig Success.";
        return 1;
    }
    else {
        qDebug() << "Send For Sig Fail.";
        return 0;
    }

}

int Client::sendForSig(const MoveChain &mc, int playerIndex)
{
    qDebug() << "Send For Sig . . .";
    // 1. Fetch the whole MoveChain and encode.
    QString moveChainString = mc.toJsonString();

    // 2. Send the whole MoveChain to the next player.
    IP & nextPlayer = game->players[playerIndex];
    QString url = nextPlayer.getFullAddress()
            + "/sendForSig";
    QJsonObject obj;
    obj.insert("moveChain", moveChainString);
    QJsonDocument document(obj);
    QString resultString = postRequest(url, document);

    // 3. Return
    if (resultString=="1")
    {
        qDebug() << "Send For Sig Success.";
        return 1;
    }
    else {
        qDebug() << "Send For Sig Fail.";
        return 0;
    }
}

int Client::broadcastNewMove()
{
    qDebug() << "Broadcast New Move . . .";
    // 1. Fetch the whole MoveChain and enocde.
    MoveChain & mc = game->localMoveChain;
    QString moveChainString = mc.toJsonString();

    // 2. Send the whole MoveChain to the other players.
    for (int i=0; i<3; i++) {
        if (i != game->myIndex){
            IP & player = game->players[i];
            QString url = player.getFullAddress()
                    + "/broadcastNewMove";
            QJsonObject obj;
            obj.insert("moveChain", moveChainString);
            QJsonDocument document(obj);
            QString resultString = postRequest(url, document);
            if (resultString=="1")
            {
                qDebug() << "Broadcast New Move 1 Success.";
                continue;
            }
            else {
                qDebug() << "Broadcast New Move Fail.";
                return 0;
            }
        }
    }

    // 3. Return
    qDebug() << "Broadcast New Move Success.";
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
