#include "game.h"

//HttpSessionStore* RequestMapper::sessionStore=0;

RequestMapper::RequestMapper(QObject* parent, Game* game)

    : HttpRequestHandler(parent)
{
    this->game = game;
//    receiveForSigController.game = game;
//    receiveInviteController.game = game;
//    receiveNewMoveController.game = game;
//    receivePlayerInfoController.game = game;

}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {

    qDebug() << "Service Triggered.";
    QByteArray path=request.getPath();

    qDebug("RequestMapper: path=%s",path.data());


    if (path=="/")
    {
        HelloworldController(game).service(request,response);
    }
    else if (path=="/sendInvite")
    {
        ReceiveInviteController(game).service(request,response);
    }

    else if (path=="/sendPlayerInfo")
    {
        ReceivePlayerInfoController(game).service(request,response);
    }

    else if (path=="/sendForSig")
    {
        ReceiveForSigController(game).service(request,response);
    }

    else if (path=="/broadcastNewMove")
    {
        ReceiveNewMoveController(game).service(request,response);
    }

    else
    {
        response.setStatus(404,"Not found");

        response.write("The URL is wrong, no such document.");
    }

    qDebug("RequestMapper: finished request");
}
