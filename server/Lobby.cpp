#include "Lobby.h"
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>
#include <math.h>

#include "json.hpp"
#define MAX_SIZE 30

typedef websocketpp::server<websocketpp::config::core> server;

typedef nlohmann::json json;

Lobby::Lobby(){
    std::unordered_map< int, websocketpp::connection_hdl > lobby;
    this->is_private = false;
    this->lobby_size = 0;
}

void Lobby::add(int id, websocketpp::connection_hdl hdl, server* s){
    lobby[id] = hdl;
    this->s = s;
    this->output = output;
}

bool Lobby::add_player(const Player_Stats & player, int socketnum){
    if(this->player_list.size() == 99){
        return false;
    }
    this->player_list.insert(std::pair<int, Player_Stats>(socketnum, player));
    this->solutions.insert(std::pair<int, std::string>(socketnum, ""));
    this->lobby_size += 1;

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

json Lobby::generate_new_puzzle(int socketnum){
    std::vector<std::string> types = {"Word", "Color"};
    std::vector<std::string> colors = {"Red", "Orange", "Yellow", "Green", "Blue", "Purple"};
    std::vector<std::string> words = {"Red", "Orange", "Yellow", "Green", "Blue", "Purple"};
    std::vector<std::string> answers = {"left", "right"};
    std::cout << floor(rand() % types.size()) << std::endl;
    std::string type = types[floor(rand() % types.size())];
    int correct_rand = floor(rand() & types.size());

    std::string correct = answers[correct_rand % 2];
    std::string correct_color = colors[correct_rand];
    std::string correct_word = words[correct_rand];
    std::string left_color, right_color, left_word, right_word;

    std::string incorrect_color = colors[floor(rand() % colors.size())];
    std::string incorrect_word = words[floor(rand() % words.size())];

    while (type == "word" and incorrect_word == correct_word) {
        incorrect_word = words[floor(rand() % words.size())];
    }

    while (type == "color" and incorrect_color == correct_color){
        incorrect_color = colors[floor(rand() % colors.size())];
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
    }

    json response = {
        {"type", "generatePuzzle"},
        {"puzzle_information", {
            {"correct", correct},
            {"puzzle_type", type },
            {"correct_word", correct_word},
            {"left_word", left_word},
            {"left_color", left_color},
            {"right_word", right_word},
            {"right_color", right_color}
        }}
    };
    // json response;
    solutions[socketnum] = correct;
    return response;


}


void Lobby::skip_puzzle(){
    1;
}

json Lobby::verify_puzzle_solution(int socketnum, std::string user_solution){
    std::string solution = solutions[socketnum];

    if(user_solution == solution){
        player_list[socketnum].correct_solutions +=1;
        if(player_list[socketnum].correct_solutions%5 == 1){
            player_list[socketnum].attacks_left += 1;
        }
    }
    else{
        player_list[socketnum].incorrect_solutions += 1;
    }

    json response = {
        {"type", "verifyPuzzle"},
        {"correct", solution == user_solution}
    };

    return response;

}

int Lobby::size(){
    return lobby.size();
}

json Lobby::attack(int socketnum){
    if(player_list[socketnum].attacks_left == 0){
        json attacker_response = {
            {"type", "attack"},
            {"message", "no attacks left, solve more puzzles"}
        };
        
        return attacker_response;
    }

    player_list[socketnum].total_attacks += 1;

    json response = R"({
    "type" : "attack",
    "data" : "you've been attacked!"
    })"_json;
    
    auto it = std::next(lobby.begin(), rand() % lobby.size());
    auto i = (*it);
    player_list[i.first].total_times_attacked += 1;

    try {
        s->send(i.second, response.dump(), websocketpp::frame::opcode::text);
    }catch (...){
        std::cerr << "attack target not found\n";
    }

    json attacker_response = {
        {"type", "attack"},
        {"message", "attack successful"}
    };
    return attacker_response;
}

json Lobby::win(int socketnum){
    json winner_response = {
        {"type", "win"},
        {"winner", socketnum}
    };
    return winner_response;
}

void Lobby::sendall(json message){
    json response = R"({
    "type" : "text",
    "data" : "hello!"
    })"_json;

    for (auto i : lobby){
        s->send(i.second, response.dump(), websocketpp::frame::opcode::text);
    }
}
