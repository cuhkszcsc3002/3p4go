#include "game.h"

HttpSessionStore* RequestMapper::sessionStore=0;

RequestMapper::RequestMapper(QObject* parent, Game* game)
    : HttpRequestHandler(parent) {
    // empty
    sendForSigController.game = game;
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());

    if (path=="/" || path=="/hello")
    {
        helloWorldController.service(request, response);
    }
    else if (path=="/list")
    {
        listDataController.service(request, response);
    }
    else if (path=="/login")
    {
        loginController.service(request, response);
    }
    else if (path=="/sendInvite")
    {
        sendInviteController.service(request,response);
    }
    else if (path=="/sendPlayerInfo")
    {
        sendPlayerInfoController.service(request,response);
    }
    else if (path=="/sendForSig")
    {
        sendForSigController.service(request,response);
    }
    else if (path=="/broadcastNewMove")
    {
        broadcastNewMoveController.service(request,response);
    }
    else
    {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.");
    }

    qDebug("RequestMapper: finished request");
}
