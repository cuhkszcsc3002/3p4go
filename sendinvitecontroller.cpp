#include "sendinvitecontroller.h"

SendInviteController::SendInviteController(QObject* parent)
    : HttpRequestHandler(parent) {
    qDebug()<<"12";
}

void SendInviteController::service(HttpRequest &request, HttpResponse &response) {
    response.write("Hello World",true);
}
