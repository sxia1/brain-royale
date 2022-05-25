#include "iostream_server.h"
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>
#include <iostream>
//#include "json.hpp"
#include "LobbyController.h"

typedef websocketpp::server<websocketpp::config::core> server;
typedef server::message_ptr message_ptr;
typedef nlohmann::json json;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;


void iostream_on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg, LobbyController* lcontrol) {
    std::cout << "Hi, this humble on_message function was called!!!" << std::endl;
    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        s->get_alog().write(websocketpp::log::alevel::app,
            "Text Message Received: "+msg->get_payload());
    } else {
        s->get_alog().write(websocketpp::log::alevel::app,
            "Binary Message Received: "+websocketpp::utility::to_hex(msg->get_payload()));
    }
    std::cout << "new message received\n";
    try {
        s->send(hdl, msg->get_payload(), msg->get_opcode());
    } catch (websocketpp::exception const & e) {
        s->get_alog().write(websocketpp::log::alevel::app,
            std::string("Echo Failed: ")+e.what());
        std::cout << "FAILURE!!!" << std::endl;
    }

    json message = json::parse(msg->get_payload());
    std::cout << message << std::endl;

    if (!message.contains("type")) {return;}
    std::string responseType = message["type"];

    if (responseType == "connected") {
        json response = R"({
            "type" : "connect",
            "data" : null
        })"_json;
<<<<<<< HEAD
        std::cout << "message optcode is" << msg->get_opcode() << "\n";
        s->send(hdl, response.dump(), msg->get_opcode());
=======
        std::cout << "message opcode is " << msg->get_opcode() << "\n";
        lcontrol->getList()[0]->sendall();
>>>>>>> parent of ea14246 (Merge pull request #7 from sxia1/ghaz-endpoints)
    }
    
   else if(responseType == "joinLobby"){
        // if(lobbies.size() == 0){
        //     std::vector<Player_Stats> players = {};
        //     Lobby current = Lobby(false, players);
        //     lobbies.push_back(current);

        //     json response;
        //     response["lobby_id"] = 1;

        //     s->send(hdl, response.dump(), websocketpp::frame::opcode::text);

        // }
        1;
   }
<<<<<<< HEAD

    else if(responseType == "attack"){
       std::vector<Lobby *> lobbies = lcontrol->getList();
        int lobby_number = message["lobby_id"];
        bool found = false;

        for(Lobby* lobby: lobbies){
            if(lobby->lobby_id == lobby_number){
                json response = lobby->attack(socketnum);
                s->send(hdl, response.dump(), msg->get_opcode());
                found = true;
                break;
            }
        }
   }

=======
/*
      
        // Lobby()
        // if(message.contains("data")){
            // if(!typeid(message["data"]).name() == 'i'){
            //     1;
            // }
            // std::string data = message["data"];
        // }
    }
*/

    else if(responseType == "completePuzzle"){
        1;
    }
    else if(responseType == "skipPuzzle"){
        1;
    }
    else if(responseType == "changeAttackStyle"){
        1;
    }
    else if (responseType == "attack"){
        lcontrol->getList()[0]->attack();
    }
>>>>>>> parent of ea14246 (Merge pull request #7 from sxia1/ghaz-endpoints)
}

void on_open(server* s, websocketpp::connection_hdl hdl, int socketnum, LobbyController* lcontrol,std::stringstream *output){
    std::cout << "in open\n";
 //   lcontrol.debug();
    lcontrol->add(socketnum, hdl, s, output);
    
}

void on_close(server* s, websocketpp::connection_hdl) {
    std::cout << "Some connection closed" << std::endl;
}



iostream_server::iostream_server(std::stringstream *output, int socketnum, LobbyController *lcontrol) {
        // Set logging settings
        std::cout << "in iostream constructor\n";
        s.clear_access_channels(websocketpp::log::alevel::all);
        s.set_access_channels(websocketpp::log::elevel::all);
        s.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
 
        log.open("output.log");
        s.get_alog().set_ostream(&log);
        s.get_elog().set_ostream(&log);
        s.register_ostream(output);
        std::cout << "before open\n";
        s.set_open_handler(std::bind(&on_open, &s, std::placeholders::_1, socketnum, lcontrol, output));
        std::cout << "after open\n";
        s.set_close_handler(std::bind(&on_close, &s, std::placeholders::_1));
        s.set_message_handler(std::bind(&iostream_on_message,&s,std::placeholders::_1,std::placeholders::_2,lcontrol));
        con = s.get_connection();
        con->start();
}

iostream_server::~iostream_server(){
        log.close();
}

void iostream_server::handle_websocket_connection(char buffer[1024], int len) {
        int alreadyread = 0;
        while (alreadyread != len) {
            alreadyread += con->read_some(buffer, len - alreadyread);
            std::cout << "Total read: " << alreadyread << "/" << len << std::endl;
        }
}


