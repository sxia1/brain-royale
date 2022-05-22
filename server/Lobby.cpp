#include "Lobby.h"
#include <websocketpp/server.hpp>

#define MAX_SIZE 30

Lobby::Lobby(){
    std::unordered_map< int, websocketpp::connection_hdl* > lobby;
}

void Lobby::add(int id, websocketpp::connection_hdl* hdl){
    lobby[id] = hdl;
    send(id, "added", 5, 0);
}

int Lobby::size(){
    return lobby.size();
}

void sendall();