#pragma once
#include "LobbyController.h"
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>
#include <fstream>

typedef websocketpp::server<websocketpp::config::core> server;

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
