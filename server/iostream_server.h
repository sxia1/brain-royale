#pragma once
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>
#include <fstream>
#include "LobbyController.h"

typedef websocketpp::server<websocketpp::config::core> server;

class LobbyController;

class iostream_server {
public:
    iostream_server(std::stringstream *output, int socketnum, LobbyController *lcontrol);

   ~iostream_server();

   void handle_websocket_connection(char buffer[1024], int len);
    
private:
    server s;
    std::ofstream log;
    server::connection_ptr con;
    websocketpp::connection_hdl hdl;
};
