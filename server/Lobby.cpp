#include "Lobby.h"
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>

#include "json.hpp"
#define MAX_SIZE 30

typedef websocketpp::server<websocketpp::config::core> server;

typedef nlohmann::json json;

Lobby::Lobby(){
    std::unordered_map< int, websocketpp::connection_hdl > lobby;
    this->is_private = is_private;
    this->player_list = player_list;
}


Lobby::Lobby(const bool is_private, const std::vector<Player_Stats> & player_list){
    std::unordered_map< int, websocketpp::connection_hdl* > lobby;

    this->is_private = is_private;
    this->player_list = player_list;
}

void Lobby::add(int id, websocketpp::connection_hdl hdl, server* s,std::stringstream *output){
    lobby[id] = hdl;
    this->s = s;
    this->output = output;
}

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

/*
output json should be of form:
{
    correct: either "left" or "right" corresponding to correct side
    puzzle_type: either "word" or "color"
    correct_word: correct word value corresponding to answer
    left_word: word to be used on left
    left_color: color to be used on left
    right_word: word to be used on right
    right_color: color to be used on right
}

code below generates values random for json in javascript 
code just needs to be translated
*/
void Lobby::generate_new_puzzle(){
    let type = types[Math.floor(Math.random() * types.length)];
    let correct_rand = Math.floor(Math.random() * types.length);

        let correct = answers[correct_rand % 2];
        let correct_color = colors[correct_rand];
        let correct_word = words[correct_rand];
        let left_color, right_color, left_word, right_word;

        let incorrect_color = colors[Math.floor(Math.random()* colors.length)];
        let incorrect_word = words[Math.floor(Math.random() * words.length)];

        //note that 'incorrect' is a general misnomer as some matches can occur
        //we only want to ensure that if we ask to choose the correct word or color
        //that there is only one instance of the word or color in each respective case
        while (type == "word" && incorrect_word == correct_word) {
            incorrect_word = words[Math.floor(Math.random() * words.length)];
        }

        while (type == "color" && incorrect_color == correct_color) {
            incorrect_color = colors[Math.floor(Math.random()* colors.length)];
        }


        if (type == "word") {
            if (correct == "left") {
                left_word = correct_word;
                right_color = correct_color;
                right_word = incorrect_word;
                left_color = incorrect_color;
            }
            else {
                right_word = correct_word;
                left_color = correct_color;
                left_word = incorrect_word;
                right_color = incorrect_color;
            }
        }

        else {
            if (correct == "left") {
                left_color = correct_color;
                right_word = correct_word;
                right_color = incorrect_color;
                left_word  = incorrect_word;
            }

            else {
                right_color = correct_color;
                left_word = correct_word;
                left_color = incorrect_color;
                right_word = incorrect_word;
            }
;
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

void Lobby::sendall(){
    json response = R"({
    "type" : "text",
    "data" : "hello!"
    })"_json;

    std::vector<int> to_erase;

    for (auto i : lobby) {
        try {
            s->send(i.second, response.dump(), websocketpp::frame::opcode::text);
        } catch (...) {
            std::cout << "Deactivating player " << i.first << std::endl;
            to_erase.push_back(i.first);
        }
    }
    for (int i : to_erase) {
        lobby.erase(i);
    }
}
