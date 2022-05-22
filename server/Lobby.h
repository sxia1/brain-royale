#pragma once
#include <unordered_map>
#include <websocketpp/server.hpp>

class Lobby{
private:
    std::unordered_map< int, websocketpp::connection_hdl* > lobby;
public:
    Lobby();
    void add(int, websocketpp::connection_hdl*);
    int size();
    void sendall();
};
