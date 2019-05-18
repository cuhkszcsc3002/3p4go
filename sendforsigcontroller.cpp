#include "sendforsigcontroller.h"

SendForSigController::SendForSigController(QObject* parent)
    : HttpRequestHandler(parent) {
    // empty
}

void SendForSigController::service(HttpRequest &request, HttpResponse &response) {
    response.write("sendforsig",true);
}
