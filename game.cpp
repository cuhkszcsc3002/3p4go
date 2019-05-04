#include "game.h"
#include "server.h"
#include "client.h"


Game::Game()
{
    Game::init();

    GUI = new GUI;
    GUI.init(this);

    server = new Server;
    server.init(this);

    client = new Client;
    client.init(this);

}

