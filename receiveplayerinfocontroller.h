#ifndef SENDPLAYERINFOCONTROLLER_H
#define SENDPLAYERINFOCONTROLLER_H

#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

class Game;


using namespace stefanfrings;

class ReceivePlayerInfoController : public HttpRequestHandler
{
    Q_OBJECT

public:
    Game * game;
    ReceivePlayerInfoController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SENDPLAYERINFOCONTROLLER_H
