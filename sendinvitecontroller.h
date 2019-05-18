#ifndef SENDINVITECONTROLLER_H
#define SENDINVITECONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class SendInviteController: public HttpRequestHandler
{
    Q_OBJECT
public:
    SendInviteController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SENDINVITECONTROLLER_H
