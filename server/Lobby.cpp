#include "Lobby.h"
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>

#include "json.hpp"
#define MAX_SIZE 30

typedef websocketpp::server<websocketpp::config::core> server;

typedef nlohmann::json json;

Lobby::Lobby(){
    std::unordered_map< int, websocketpp::connection_hdl > lobby;
}
/*
Lobby::Lobby(const bool is_private, const std::vector<Player_Stats> & player_list){
    std::unordered_map< int, websocketpp::connection_hdl* > lobby;
    //this->lobby_id++;
    this->is_private = is_private;
    this->player_list = player_list;
}
*/
void Lobby::add(int id, websocketpp::connection_hdl hdl, server* s,std::stringstream *output){
    lobby[id] = hdl;
    this->s = s;
    this->output = output;
}
/*
bool Lobby::add_player(const Player_Stats & player){
    if(this->player_list.size() == 99){
        return false;
    }

    this->player_list.push_back(player);
    return true; 
}

void Lobby::deactivate_player(const int player_id){
    this->player_list[player_id].left_game = true;
}

bool Lobby::attack_player(const int attacker_id, const int reciever_id){
    this->player_list[attacker_id].total_attacks += 1;
    this->player_list[reciever_id].total_times_attacked += 1;

    return false;
}

json Lobby::get_player_stats(const int player_id){
    Player_Stats player_info = this->player_list[player_id];

    json player = player_info;

    return player;
}

json Lobby::get_player_stats(){
    json players = player_list; 
    return player_list;
}


void Lobby::generate_new_puzzle(){
    1;
}


void Lobby::skip_puzzle(){
    1;
}

void Lobby::verify_puzzle_solution(){
    1;
}

int Lobby::size(){
    return lobby.size();
}
*/
void Lobby::sendall(){
    json response = R"({
    "type" : "text",
    "data" : "hello!"
    })"_json;
    std::cout << "before sendall()\n";
    // std::cout << lobby.size() << std::endl;
// 
    for (auto i : lobby){
        std::cout << "socket id: " << i.first << "\n";
        (i.second);
        std::cout << "second worked\n";
        // std::cout << "opcode: " << websocketpp::frame::opcode::text << "\n";

        s->send(i.second, response.dump(), websocketpp::frame::opcode::text);

        // break;
    }
}
