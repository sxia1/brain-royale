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
    int time_left;
    int puzzles_won = 0;
    int incorrect_solutions = 0;
    int total_attacks = 0;
    int total_times_attacked = 0;
    bool left_game = false;
};

// void to_json(json& j, const Player_Stats& player_info){
//     j["score"] = player_info.score;
//     j["time_left"] = player_info.time_left;
//     j["puzzles_won"] = player_info.puzzles_won;
//     j["incorrect_solutions"] = player_info.incorrect_solutions;
//     j["total_attacks"] = player_info.total_attacks;
//     j["total_times_attacked"] = player_info.total_times_attacked;
//     j["left_game"] = player_info.left_game;
// };

class Lobby{
private:
    std::unordered_map< int, websocketpp::connection_hdl > lobby;
    server *s;    
    std::unordered_map<int, Player_Stats> player_list;

    std::stringstream *output;
public:

    static int lobby_id;
    // std::vector<Player_Stats> player_list;
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
    void generate_new_puzzle();
    void verify_puzzle_solution();
    void skip_puzzle();
    int size();

    void sendall(json message);
    
};
