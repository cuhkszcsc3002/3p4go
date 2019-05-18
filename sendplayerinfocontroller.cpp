#include "sendplayerinfocontroller.h"

SendPlayerInfoController::SendPlayerInfoController(QObject* parent)
    : HttpRequestHandler(parent)
{

}

void SendPlayerInfoController::service(HttpRequest &request, HttpResponse &response) {\
    qDebug()<<&response<<"1uihuu";
    response.write("sendplayerinfo",true);
}
