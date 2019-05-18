#include "broadcastnewmovecontroller.h"

BroadcastNewMoveController::BroadcastNewMoveController(QObject* parent)
    : HttpRequestHandler(parent) {
    // empty
}

void BroadcastNewMoveController::service(HttpRequest &request, HttpResponse &response) {
    response.write("broadcastmove",true);
}
