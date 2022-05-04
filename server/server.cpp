// Server side C/C++ program to demonstrate Socket programming
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>
#include <cstring>
#include <string>
#include <iostream>
#include <future>
#include <functional>
#include "Router.h"
#include "static_file.h"
#include "json.hpp"
#define PORT std::stoi(getenv("PORT"))

typedef websocketpp::server<websocketpp::config::core> server;
typedef server::message_ptr message_ptr;
typedef nlohmann::json json;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

void iostream_on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "Hi, this humble on_message function was called!!!" << std::endl;
    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        s->get_alog().write(websocketpp::log::alevel::app,
            "Text Message Received: "+msg->get_payload());
    } else {
        s->get_alog().write(websocketpp::log::alevel::app,
            "Binary Message Received: "+websocketpp::utility::to_hex(msg->get_payload()));
    }

    try {
        s->send(hdl, msg->get_payload(), msg->get_opcode());
    } catch (websocketpp::exception const & e) {
        s->get_alog().write(websocketpp::log::alevel::app,
            std::string("Echo Failed: ")+e.what());
    }
}

void on_close(server* s, websocketpp::connection_hdl) {
    std::cout << "Some connection closed" << std::endl;
}

class iostream_server {
public:
    iostream_server(std::stringstream *output) {
        // Set logging settings
        s.clear_access_channels(websocketpp::log::alevel::all);
        s.set_access_channels(websocketpp::log::elevel::all);
        s.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
 
        log.open("output.log");
        s.get_alog().set_ostream(&log);
        s.get_elog().set_ostream(&log);
        s.register_ostream(output);
        s.set_close_handler(std::bind(&on_close, &s, std::placeholders::_1));
        s.set_message_handler(std::bind(&iostream_on_message,&s,std::placeholders::_1,std::placeholders::_2));
        con = s.get_connection();
        con->start();
   }

   ~iostream_server(){
        log.close();
   }

   void handle_websocket_connection(char buffer[1024], int len) {
        int alreadyread = 0;
        while (alreadyread != len) {
            alreadyread += con->read_some(buffer, len - alreadyread);
            std::cout << "Total read: " << alreadyread << "/" << len << std::endl;
        }
   }
    
private:
    server s;
    std::ofstream log;
    server::connection_ptr con;
};

class http_server{
public:
    struct sockaddr_in address;
    int server_fd;
    int opt = 1;
    Router router = Router();
    //IMPLEMENT AS MAP<SOCKET: FUTURE> INSTEAD OF VECTOR
    std::vector<std::future<void>> websocketfutures;
   
    http_server(){
        // Creating socket file descriptor
        if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
         
        // Forcefully attaching socket to the port 8080
        if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &this->opt, sizeof(this->opt))){
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        this->address.sin_family = AF_INET;
        this->address.sin_addr.s_addr = INADDR_ANY;
        this->address.sin_port = htons( PORT );
        // Forcefully attaching socket to the port 8080
        if (bind(this->server_fd, (struct sockaddr *)&this->address, sizeof(this->address))<0){
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(this->server_fd, 3) < 0){
            perror("listen");
            exit(EXIT_FAILURE);
        }
    }

    void handle_connection(int new_socket){
        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, 1024);
        char * response = this->router.respond(buffer);
        if(response == nullptr){
            websocketfutures.push_back(std::async(&http_server::handle_websocket_connection, this, new_socket, buffer));
        }
        else{
            std::cout << "response found\n";
            send(new_socket, response, strlen(response), 0);
            close(new_socket);
        }
    }
    void async_handle_connection(){
        while(1){
            int new_socket;
            int addrlen = sizeof(this->address);
            if ((new_socket = accept(this->server_fd, (struct sockaddr*) &this->address, (socklen_t*) &addrlen)) < 0){
                perror("accept");
                exit(EXIT_FAILURE);
            }
            std::cout << "HANDLING" << std::endl;
            std::async(&http_server::handle_connection, this, new_socket);
        }
    }
    void handle_websocket_connection(int socketnum, char buffer[1024]){
        const std::stringstream init;
        std::stringstream wppoutput;
        iostream_server wppserver{&wppoutput};
        wppserver.handle_websocket_connection(buffer, strlen(buffer));
        const std::string tmp = wppoutput.str();
        const char* cstr = tmp.c_str();
        wppoutput.str("");
        wppoutput.clear();
        wppoutput.copyfmt(init);
        memset(buffer, 0, 1024);
        send(socketnum, cstr, strlen(cstr), 0);
        
        char abuffer[1024];
        int valread;
        do {
            valread = read(socketnum, abuffer, 1024);
            if (valread <= 0) {continue;}
            wppserver.handle_websocket_connection(abuffer, valread);
            const std::string temp = wppoutput.str();
            const char* cstr = temp.c_str();
            std::cout << "WSPP RESPONSE: " << std::endl << cstr << std::endl;
            wppoutput.str("");
            wppoutput.clear();
            wppoutput.copyfmt(init);
            memset(abuffer, 0, 1024);
            send(socketnum, cstr, temp.length(), 0);
            std::cout << std::endl;
        }
        while(valread > 0);
        //REMOVE FUTURE ASSOCIATED WITH SOCKETNUM WHEN CONNECTION CLOSED
    }
};

int main(int argc, char const *argv[]){
    http_server server;
    server.async_handle_connection();
    return 0;
}
