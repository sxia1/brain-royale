// Server side C/C++ program to demonstrate Socket programming
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>
#include <cstring>
#include <string>
#include <iostream>
#include <future>
#include <functional>
#include "Router.h"
#include "static_file.h"

#define PORT std::stoi(getenv("PORT"))

//typedef websocketpp::server<websocketpp::config::asio> server;
typedef websocketpp::server<websocketpp::config::core> server;
typedef websocketpp::config::asio::message_type::ptr message_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
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
    iostream_server() {
        // Set logging settings
        s.clear_access_channels(websocketpp::log::alevel::all);
        s.set_access_channels(websocketpp::log::alevel::connect);
        s.set_access_channels(websocketpp::log::alevel::disconnect);
        s.set_access_channels(websocketpp::log::alevel::app);
 
        log.open("output.log");
        s.get_alog().set_ostream(&log);
        s.get_elog().set_ostream(&log);
        s.register_ostream(&std::cout);
        s.set_message_handler(bind(&on_message,&s,::_1,::_2));
   }

   ~iostream_server(){
        log.close();
   }

   void handle_websocket_connection(char buffer[1024]) {
        server::connection_ptr con = s.get_connection();
        con->start();
        std::cout << "started connection" << std::endl;
        while(std::cin.get(buffer, 1024)) {
            std::cout << "hello" << std::endl;
            con->read_some(buffer,1);
        } 
        std::cout << "end of connection" << std::endl;
        con->eof();
    }
    //void async_handle_websocket_connection(char buffer[1024]){
    //    std::async(&iostream_server::handle_websocket_connection, buffer);
    //}
private:
    server s;
    std::ofstream log;
};
 
class http_server{
public:
    struct sockaddr_in address;
    int server_fd;
    int opt = 1;
    Router router = Router();
    iostream_server s;
    
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
    void handle_connection(){
        int new_socket, valread;
        int addrlen = sizeof(this->address);
        char buffer[1024] = {0};
        if ((new_socket = accept(this->server_fd, (struct sockaddr*) &this->address, (socklen_t*) &addrlen)) < 0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        valread = read(new_socket, buffer, 1024);
        std::cout << buffer << std::endl;
        // check if request is websocket related
        // no then router.respond
        // yes then s.async_handle_websocket_connection()
        char * response = this->router.respond(buffer);
        if(response == nullptr){
            //s.async_handle_websocket_connection(buffer);
            s.handle_websocket_connection(buffer);
        }
        else{
            std::cout << "response found\n";
            send(new_socket, response, strlen(response), 0);
            printf("Hello message sent\n");
            close(new_socket);
        }
    }
    void async_handle_connection(){
        while(1){
            std::async(&http_server::handle_connection, this);
        }
    }
};

int main(int argc, char const *argv[]){
    http_server server;
    server.async_handle_connection();
    return 0;
}
