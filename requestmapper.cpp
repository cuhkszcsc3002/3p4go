#include "game.h"

//HttpSessionStore* RequestMapper::sessionStore=0;

RequestMapper::RequestMapper(QObject* parent, Game* game)

    : HttpRequestHandler(parent)
{
    this->game = game;
    helloworldController = new HelloworldController(game);
    receiveForSigController = new ReceiveForSigController(game);
    receiveInviteController = new ReceiveInviteController(game);
    receiveNewMoveController = new ReceiveNewMoveController(game);
    receivePlayerInfoController = new ReceivePlayerInfoController(game);

}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {

    qDebug() << "Service Triggered.";
    QByteArray path=request.getPath();

    qDebug("RequestMapper: path=%s",path.data());


    if (path=="/")
    {
        helloworldController->service(request,response);
    }
    else if (path=="/sendInvite")
    {
        qDebug() << "Match Path: /sendInvite";
        receiveInviteController->service(request,response);
    }

    else if (path=="/sendPlayerInfo")
    {
        receivePlayerInfoController->service(request,response);
    }

    else if (path=="/sendForSig")
    {
        receiveForSigController->service(request,response);
    }

    else if (path=="/broadcastNewMove")
    {
        receiveNewMoveController->service(request,response);
    }

    else
    {
        response.setStatus(404,"Not found");

        response.write("The URL is wrong, no such document.", true);
    }

    qDebug("RequestMapper: finished request");
}
