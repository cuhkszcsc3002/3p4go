#include "helloworldcontroller.h"
#include "game.h"
HelloworldController::HelloworldController(QObject* parent)
    : HttpRequestHandler(parent)

{

}

void HelloworldController::service(HttpRequest &request, HttpResponse &response)
{
    response.write("Hello World");
}
