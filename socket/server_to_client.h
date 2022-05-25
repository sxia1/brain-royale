#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <functional>
#include <iostream>

#include "json.hpp"

bool joined_lobby(server* s, const websocketpp::connection_hdl & hdl, message_ptr  &msg);

json get_new_puzzzle(server *s, const websocketpp:connection_hdl & hdl, message_ptr & msg);

bool solution_correct(server *s, const websocketpp:connection_hdl & hdl, message_ptr & msg);

void game_over(server *s,  const websocketpp::connection_hdl & hdl, message_ptr & msg);

json player_preview(server *s, const websocketpp:connection_hdl & hdl, message_ptr & msg);

void attack(server *s, const websocketpp:connection_hdl & hdl, message_ptr & msg);