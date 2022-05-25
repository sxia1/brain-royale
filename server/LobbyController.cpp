#include "LobbyController.h"
#include "Lobby.h"

#include <iostream>


typedef websocketpp::server<websocketpp::config::core> server;

//#include "server.cpp"

//#define MAX_SIZE 30;


LobbyController::LobbyController(){
//    maxSize = MAX_SIZE;
    numLobbies = 0;
    createLobby();
}

LobbyController::~LobbyController(){
    for (int i = 0; i < lobbies.size(); ++i){
        delete lobbies[i];
    }
}

void debug(){
    std::cout << "lcontrol debug\n";
}

void LobbyController::createLobby(){
    lobbies.push_back(new Lobby);
    numLobbies++;
}

std::vector<Lobby*> LobbyController::getList(){
    return lobbies;
}

void LobbyController::add(int id, websocketpp::connection_hdl hdl, server *s,std::stringstream *output){
    std::cerr << "in add\n";
    lobbies[0]->add(id, hdl, s);
    std::cerr << "out add\n";
    return;
}