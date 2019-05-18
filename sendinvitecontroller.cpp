#include "sendinvitecontroller.h"

SendInviteController::SendInviteController(QObject* parent)
    : HttpRequestHandler(parent)
{
}

void SendInviteController::service(HttpRequest &request, HttpResponse &response) {
    response.write("sendinvite",true);
}
