#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <functional>
#include <iostream>

#include "json.hpp"
#include "server_to_client.h"

bool joined_lobby(server* s, const websocketpp::connection_hdl & hdl, message_ptr & msg){
    // retuurn true when a user is sucessfuly connected to a lobby
    return false;
}

json get_new_puzzle(server* s, const websocketpp::connection_hdl & hdl, message_ptr & msg){
    json puzzle;
    // ask server for new puzzle here

    return puzzle;
}

bool solution_correct(server* s, const websocketpp::connection_hdl & hdl, message_ptr & msg){
    // tell serve the user got
    return false;
}


void game_over(server* s, const websocketpp::connection_hdl & hdl, message_ptr & msg){
    // tell server game is over
}

json player_preview(server* s, const websocketpp::connection_hdl & hdl, message_ptr & msg){
    json player_information;
    // get player information from the server
    return player_information;
}

void attack(server* s, const websocketpp::connection_hdl & hdl, message_ptr & msg){
    // call server attack function
}
