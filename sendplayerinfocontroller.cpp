#include "sendplayerinfocontroller.h"

SendPlayerInfoController::SendPlayerInfoController(QObject* parent)
    : HttpRequestHandler(parent) {
    qDebug()<<"tt";
}

void SendPlayerInfoController::service(HttpRequest &request, HttpResponse &response) {
    response.write("Hello World",true);
}
