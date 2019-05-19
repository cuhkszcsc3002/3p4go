#ifndef SENDPLAYERINFOCONTROLLER_H
#define SENDPLAYERINFOCONTROLLER_H

#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

class Game;


using namespace stefanfrings;

/*
 * class: ReceivePlayerInfoController
 * The ReceivePlayerInfoController is used for receive player information from client and post it to
 * game. It is inheritanced from HttpRequestHandler to implementpost and get request.
 * -------------------------------------
 */

class ReceivePlayerInfoController : public HttpRequestHandler
{
    Q_OBJECT

public:
    Game * game;
    ReceivePlayerInfoController(Game* g, QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SENDPLAYERINFOCONTROLLER_H
