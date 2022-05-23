#pragma once
#include <unordered_map>
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>
#include "json.hpp"


typedef nlohmann::json json;
typedef websocketpp::server<websocketpp::config::core> server;

class iostream_server;

struct Player_Stats {
    int score = 0;
    int time_left = 0;
    int correct_solutions = 0;
    int incorrect_solutions = 0;
    int total_attacks = 0;
    int total_times_attacked = 0;
    bool left_game = false;
};


class Lobby{
private:
    std::unordered_map< int, websocketpp::connection_hdl > lobby;
    server *s;    
    std::unordered_map<int, Player_Stats> player_list;
    std::unordered_map<int, std::string> solutions;

    std::stringstream *output;
public:
    const int lobby_id = 1;
    // const static int lobby_id = 0;
    // std::vector<Player_Stats> player_list;
    int lobby_size = 0;
    bool started;
    bool is_private;
    int time_left; 
    int total_puzzles;

    Lobby();
    
    // Lobby(const bool is_private, const std::vector<Player_Stats> & player_list);
    void add(int, websocketpp::connection_hdl, server*);
    void start_lobby();
    
    bool add_player(const Player_Stats & player, int socketnum);
    void deactivate_player(const int player_id);
    bool attack_player(const int attacker_id, const int reciever_id);
    // json get_player_stats(const int player_id);
    // json get_player_stats();
    json generate_new_puzzle(int socketnum);
    void skip_puzzle();
    json verify_puzzle_solution(int socketnum, std::string solution);
    int size();

    void attack();
    void sendall(json message);
    
};
