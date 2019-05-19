#ifndef HELLOWORLDCONTROLLER_H
#define HELLOWORLDCONTROLLER_H

#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

class Game;

using namespace stefanfrings;

/*
 * class: HelloworldController
 * The ReceiveForSigController is a initialized page for server
 * to test.
 * -------------------------------------
 */

class HelloworldController: public HttpRequestHandler
{
    Q_OBJECT

public:
    Game * game;
    HelloworldController(Game * g, QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // HELLOWORLDCONTROLLER_H
