#pragma once
#include <vector>
#include <future>
#include <websocketpp/server.hpp>
#include "Lobby.h"

class LobbyController{
private:
    std::vector<Lobby*> lobbies;
//    int maxSize;
    int numLobbies;
public:
    LobbyController();
    ~LobbyController();
    void debug();
    void createLobby();
    void on_open(websocketpp::connection_hdl&);
    void add(int id, websocketpp::connection_hdl&);
};
