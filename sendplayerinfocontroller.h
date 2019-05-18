#ifndef SENDPLAYERINFOCONTROLLER_H
#define SENDPLAYERINFOCONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class SendPlayerInfoController : public HttpRequestHandler {
    Q_OBJECT
public:
    SendPlayerInfoController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SENDPLAYERINFOCONTROLLER_H
