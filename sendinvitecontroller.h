#ifndef SENDINVITECONTROLLER_H
#define SENDINVITECONTROLLER_H

#include "httprequesthandler.h"
#include <QJsonDocument>
#include <QJsonObject>

class Game;

using namespace stefanfrings;

class SendInviteController: public HttpRequestHandler
{
    Q_OBJECT
public:
    Game *game;
    SendInviteController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SENDINVITECONTROLLER_H
