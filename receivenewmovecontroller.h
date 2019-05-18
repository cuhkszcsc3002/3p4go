#ifndef BROADCASTNEWMOVE_H
#define BROADCASTNEWMOVE_H

#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

class Game;

using namespace stefanfrings;

/*
 * class: ReceiveNewMoveController
 * The ReceiveNewMoveController is used for receive new move from client and post it to
 * game. It is inheritanced from HttpRequestHandler to implementpost and get request.
 * -------------------------------------
 */

class ReceiveNewMoveController : public HttpRequestHandler {

    Q_OBJECT

public:

    Game *game;

    ReceiveNewMoveController(QObject* parent=0);

    void service(HttpRequest& request, HttpResponse& response);
};

#endif // HELLOWORLDCONTROLLER_H
