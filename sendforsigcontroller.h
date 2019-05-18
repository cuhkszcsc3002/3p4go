#ifndef SENDFORSIGCONTROLLER_H
#define SENDFORSIGCONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class SendForSigController : public HttpRequestHandler {
    Q_OBJECT

public:
    SendForSigController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SENDFORSIGCONTROLLER_H
