#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"
#include "helloworldcontroller.h"
#include "listdatacontroller.h"
#include "logincontroller.h"
#include "httpsessionstore.h"
#include "sendforsigcontroller.h"
#include "sendinvitecontroller.h"
#include "sendplayerinfocontroller.h"
#include "broadcastnewmovecontroller.h"


using namespace stefanfrings;

    /*This Class is a mapper*/
class RequestMapper : public HttpRequestHandler
{
    Q_OBJECT
public:
    RequestMapper(QObject* parent, Game * game);
    void service(HttpRequest& request, HttpResponse& response);
    static HttpSessionStore* sessionStore;
private:
    HelloWorldController helloWorldController;
    ListDataController listDataController;
    LoginController loginController;
    SendForSigController sendForSigController;
    SendInviteController sendInviteController;
    SendPlayerInfoController sendPlayerInfoController;
    BroadcastNewMoveController broadcastNewMoveController;

};

#endif // REQUESTMAPPER_H
