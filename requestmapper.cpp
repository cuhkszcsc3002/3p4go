#include "game.h"

HttpSessionStore* RequestMapper::sessionStore=0;

RequestMapper::RequestMapper(QObject* parent, Game* game)
    : HttpRequestHandler(parent) {
    // empty
    receiveForSigController.game = game;
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());


    if (path=="/sendInvite")
    {
        receiveInviteController.service(request,response);
    }
    else if (path=="/sendPlayerInfo")
    {
        receivePlayerInfoController.service(request,response);
    }
    else if (path=="/sendForSig")
    {
        receiveForSigController.service(request,response);
    }
    else if (path=="/broadcastNewMove")
    {
        receiveNewMoveController.service(request,response);
    }
    else
    {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.");
    }

    qDebug("RequestMapper: finished request");
}
