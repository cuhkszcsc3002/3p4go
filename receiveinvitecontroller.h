#ifndef SENDINVITECONTROLLER_H
#define SENDINVITECONTROLLER_H

#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

class Game;

using namespace stefanfrings;

/*
 * class: ReceiveInviteController
 * The ReceiveInviteController is used for receiveInvite from client and post it to
 * game. It is inheritanced from HttpRequestHandler to implementpost and get request.
 * -------------------------------------
 */

class ReceiveInviteController: public HttpRequestHandler
{

    Q_OBJECT

public:

    Game *game;

    ReceiveInviteController(QObject* parent=0);

    void service(HttpRequest& request, HttpResponse& response);

};

#endif // SENDINVITECONTROLLER_H
