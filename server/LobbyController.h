#pragma once
#include <vector>
#include <future>
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>
#include "Lobby.h"
#include "iostream_server.h"


typedef websocketpp::server<websocketpp::config::core> server;


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
    std::vector<Lobby*> getList();
    void add(int id , websocketpp::connection_hdl hdl, server *s,std::stringstream *output);
};
