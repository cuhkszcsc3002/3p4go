#ifndef SENDPLAYERINFOCONTROLLER_H
#define SENDPLAYERINFOCONTROLLER_H

#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

class Game;


using namespace stefanfrings;

class SendPlayerInfoController : public HttpRequestHandler
{
    Q_OBJECT

public:
    Game * game;
    SendPlayerInfoController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SENDPLAYERINFOCONTROLLER_H
