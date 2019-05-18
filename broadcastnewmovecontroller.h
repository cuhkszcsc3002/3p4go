#ifndef BROADCASTNEWMOVE_H
#define BROADCASTNEWMOVE_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class BroadcastNewMoveController : public HttpRequestHandler {
    Q_OBJECT

public:
    BroadcastNewMoveController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // HELLOWORLDCONTROLLER_H
