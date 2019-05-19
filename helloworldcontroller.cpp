#include "helloworldcontroller.h"
#include "game.h"
HelloworldController::HelloworldController(Game *g, QObject* parent)
    : HttpRequestHandler(parent)

{
    game = g;
}

void HelloworldController::service(HttpRequest &request, HttpResponse &response)
{
    response.write("Hello World");
}
