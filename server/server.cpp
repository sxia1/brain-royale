// Server side C/C++ program to demonstrate Socket programming
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/core.hpp>
#include <websocketpp/error.hpp>
#include <cstring>
#include <string>
#include <iostream>
#include <future>
#include <functional>
#include "Router.h"
#include "static_file.h"
#include "json.hpp"

#define PORT std::stoi(getenv("PORT"))

//typedef websocketpp::server<websocketpp::config::asio> server;
typedef websocketpp::server<websocketpp::config::core> server;
//typedef websocketpp::config::asio::message_type::ptr message_ptr;
typedef websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> message_type;
typedef websocketpp::message_buffer::alloc::con_msg_manager<message_type> con_msg_man_type;
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

void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "Hi, this humble on_message function was called!!!" << std::endl;
    s->get_alog().write(websocketpp::log::alevel::app, "Received Reply: "+msg->get_payload());
    json message = json::parse(msg->get_payload());
    std::cout << message << std::endl;
    std::string responseType = message["type"];
    if (responseType == "connected") {
        json response = R"({
            "type" : "connect",
            "data" : null
        })"_json;
        s->send(hdl, response.dump(), msg->get_opcode());
    }
    // s->close(hdl,websocketpp::close::status::normal,"");
}

/*
std::error_code write_message(websocketpp::connection_hdl hdl, char const*buffer, size_t size) {
    std::cout << "Hi, this humble write_message function was called!!!" << std::endl;
    std::cout << buffer << std::endl;
    return websocketpp::error::make_error_code(websocketpp::error::value::general);
}
*/

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
        //s.set_write_handler(write_message);
        con = s.get_connection();
        con->start();
   }

   ~iostream_server(){
        log.close();
   }

   void handle_websocket_connection(char buffer[1024]) {
        //read initial buffer contents
        int len = strlen(buffer);
        con->read_all(buffer,len);
        //std::cout << con->get_shared() << std::endl;
        //message_type::ptr input = manager->get_message(websocketpp::frame::opcode::TEXT,1024);
        //std::cout << input->get_payload().c_str() << std::endl;
    }
    //void async_handle_websocket_connection(char buffer[1024]){
    //    std::async(&iostream_server::handle_websocket_connection, buffer);
    //}
    
private:
    server s;
    std::ofstream log;
    server::connection_ptr con;
    con_msg_man_type::ptr manager = websocketpp::lib::make_shared<con_msg_man_type>();
};
 
class http_server{
public:
    struct sockaddr_in address;
    int server_fd;
    int opt = 1;
    Router router = Router();
   
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
        std::cout << &this->address << std::endl;
        char buffer[1024] = {0};
        if ((new_socket = accept(this->server_fd, (struct sockaddr*) &this->address, (socklen_t*) &addrlen)) < 0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        std::cout << &this->address << std::endl;
        valread = read(new_socket, buffer, 1024);
        std::cout << buffer << std::endl;
        // check if request is websocket related
        // no then router.respond
        // yes then s.async_handle_websocket_connection()
        char * response = this->router.respond(buffer);
        if(response == nullptr){
            this->handle_websocket_connection(new_socket, buffer);
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
    void handle_websocket_connection(int socket, char buffer[1024]){
        std::stringstream output;
        iostream_server s(&output);
        
        s.handle_websocket_connection(buffer);
        const std::string tmp = output.str();
        std::cout << tmp << std::endl;
        const char* cstr = tmp.c_str();
        output.str(std::string());
        output.clear();
        send(socket, cstr, strlen(cstr), 0);
        
        char abuffer[1024];
        int valread = 0;
        while(valread = read(socket, abuffer, 1024) > 0){
          //int valread = read(socket, abuffer, 1024);
          //std::cout << "info: " << valread << std::endl;
          std::cout << abuffer << std::endl;
          s.handle_websocket_connection(abuffer);
          std::cout << std::endl;
          const std::string temp = output.str();
          std::cout << "WSPP RESPONSE: " << temp << std::endl;
          const char* cstr = temp.c_str();
          output.str(std::string());
          output.clear();
          send(socket, cstr, strlen(cstr), 0);
         }
    }
};

int main(int argc, char const *argv[]){
    http_server server;
    server.async_handle_connection();
    return 0;
}
