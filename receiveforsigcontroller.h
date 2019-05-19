#ifndef SENDFORSIGCONTROLLER_H
#define SENDFORSIGCONTROLLER_H

#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

class Game;

using namespace stefanfrings;

/*
 * class: ReceiveForSigController
 * The ReceiveForSigController is used for receiveSignature from game and post it to
 * client. It is inheritanced from HttpRequestHandler to implementpost and get request.
 * -------------------------------------
 */

class ReceiveForSigController : public HttpRequestHandler
{
    Q_OBJECT

public:
    Game * game;
    ReceiveForSigController(Game* g, QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SENDFORSIGCONTROLLER_H
