#ifndef SENDFORSIGCONTROLLER_H
#define SENDFORSIGCONTROLLER_H

#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

class Game;


using namespace stefanfrings;

class SendForSigController : public HttpRequestHandler
{
    Q_OBJECT

public:
    Game * game;
    SendForSigController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SENDFORSIGCONTROLLER_H
