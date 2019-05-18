#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"
#include "httpsessionstore.h"
#include "receiveforsigcontroller.h"
#include "receiveinvitecontroller.h"
#include "receiveplayerinfocontroller.h"
#include "receivenewmovecontroller.h"


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
    ReceiveForSigController receiveForSigController;
    ReceiveInviteController receiveInviteController;
    ReceivePlayerInfoController receivePlayerInfoController;
    ReceiveNewMoveController receiveNewMoveController;

};

#endif // REQUESTMAPPER_H
