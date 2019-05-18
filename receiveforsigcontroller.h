#ifndef SENDFORSIGCONTROLLER_H
#define SENDFORSIGCONTROLLER_H

#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

class Game;


using namespace stefanfrings;

class ReceiveForSigController : public HttpRequestHandler
{
    Q_OBJECT

public:
    Game * game;
    ReceiveForSigController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SENDFORSIGCONTROLLER_H
