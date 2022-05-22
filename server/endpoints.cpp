#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>
#include <websocketpp/error.hpp>
#include <websocketpp/extensions/permessage_deflate/disabled.hpp>
#include <cstring>
#include <string>
#include <iostream>
#include <future>
#include <functional>
#include "Router.h"
#include "static_file.h"
#include <vector>
#include "json.hpp"

typedef nlohmann::json json;

struct Player_Stats {
    int score; 
    int time_left;
    int puzzles_won;
    int incorrect_solutions;
    int total_attacks;
    int total_times_attacked;
    bool left_game;
};

void to_json(json& j, const Player_Stats& player_info){
    j["score"] = player_info.score;
    j["time_left"] = player_info.time_left;
    j["puzzles_won"] = player_info.puzzles_won;
    j["incorrect_solutions"] = player_info.incorrect_solutions;
    j["total_attacks"] = player_info.total_attacks;
    j["total_times_attacked"] = player_info.total_times_attacked;
    j["left_game"] = player_info.left_game;
};


class Lobby {
    public:
        static int lobby_id;
        int size; 
        std::vector<Player_Stats> player_list;
        bool is_private;
        int time_left; 
        int total_puzzles;
        // bool started = false;
        

        Lobby(const bool is_private, const std::vector<Player_Stats> & player_list){
            this->lobby_id++;
            this->is_private = is_private;
            this->player_list = player_list;
        }

        
        bool add_player(const Player_Stats & player){
            if(this->player_list.size() == 99){
                return false;
            }

            this->player_list.push_back(player);
            return true; 
        }

        void deactivate_player(const int player_id){
            this->player_list[player_id].left_game = true;
        }

        
        bool attack_player(const int attacker_id, const int reciever_id){
            this->player_list[attacker_id].total_attacks += 1;
            this->player_list[reciever_id].total_times_attacked += 1;

            return false;
        }


        json get_player_stats(const int player_id){
            Player_Stats player_info = this->player_list[player_id];

            json player = player_info;

            return player;
        }

        json get_player_stats(){
            json players = player_list; 
            return player_list;
        }


        void generate_new_puzzle(){
            1;
        }


        void skip_puzzle(){
            1;
        }

        void verify_puzzle_solution(){
            1;
        }
};