#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"
#include "httpsessionstore.h"
#include "receiveforsigcontroller.h"
#include "receiveinvitecontroller.h"
#include "receiveplayerinfocontroller.h"
#include "receivenewmovecontroller.h"
#include "helloworldcontroller.h"
class Game;

using namespace stefanfrings;

/*
 * class: RequestMapper
 * The class set the mapper of the controller used in server. It is inheritanced
 * from HttpRequestHandler to post and get request.
 * -------------------------------------
 */

class RequestMapper : public HttpRequestHandler
{
    Q_OBJECT
public:
    RequestMapper(QObject* parent, Game * game);
    void service(HttpRequest& request, HttpResponse& response);
//    static HttpSessionStore* sessionStore;
private:
    Game * game;
    ReceiveForSigController *receiveForSigController;
    ReceiveInviteController *receiveInviteController;
    ReceivePlayerInfoController *receivePlayerInfoController;
    ReceiveNewMoveController *receiveNewMoveController;
    HelloworldController *helloworldController;

};

#endif // REQUESTMAPPER_H
