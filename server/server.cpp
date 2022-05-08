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
#include <websocketpp/extensions/permessage_deflate/disabled.hpp>
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

struct permessage_deflate_config {
    typedef websocketpp::config::core::request_type request_type;

    /// If the remote endpoint requests that we reset the compression
    /// context after each message should we honor the request?
    static const bool allow_disabling_context_takeover = true;

    /// If the remote endpoint requests that we reduce the size of the
    /// LZ77 sliding window size this is the lowest value that will be
    /// allowed. Values range from 8 to 15. A value of 8 means we will
    /// allow any possible window size. A value of 15 means do not allow
    /// negotiation of the window size (ie require the default).
    static const uint8_t minimum_outgoing_window_bits = 8;
};

typedef websocketpp::extensions::permessage_deflate::disabled <permessage_deflate_config> permessage_deflate_type;

void iostream_on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "Hi, this humble on_message function was called!!!" << std::endl;
    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        s->get_alog().write(websocketpp::log::alevel::app,
            "Text Message Received: "+msg->get_payload());
        std::cout << "TEXT!!!" << std::endl;
    } else {
        s->get_alog().write(websocketpp::log::alevel::app,
            "Binary Message Received: "+websocketpp::utility::to_hex(msg->get_payload()));
        std::cout << "BINARY!!!" << std::endl;
    }

    try {
        s->send(hdl, msg->get_payload(), msg->get_opcode());
        std::cout << "SENDING!!!" << std::endl;
    } catch (websocketpp::exception const & e) {
        s->get_alog().write(websocketpp::log::alevel::app,
            std::string("Echo Failed: ")+e.what());
        std::cout << "FAILURE!!!" << std::endl;
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

    else if(responseType == "joinLobby"){
        1;
    }

    else if(responseType == "completePuzzle"){
        1;
    }


    else if(responseType == "skipPuzzle"){
        1;
    }

    else if(responseType == "changeAttackStyle"){
        1;
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

   void handle_websocket_connection(char buffer[1024], int len) {
        // int len = strlen(buffer);
        int alreadyread = 0;
        while (alreadyread != len) {
            alreadyread += con->read_some(buffer, len - alreadyread);
            std::cout << "Total read: " << alreadyread << "/" << len << std::endl;
        }
   }
   //void async_handle_websocket_connection(char buffer[1024]){
   //    std::async(&iostream_server::handle_websocket_connection, buffer);
   //}
    
private:
    server s;
    std::ofstream log;
    server::connection_ptr con;
};


int GetBit(const char * data, unsigned int idx)
{
    unsigned int arIdx = idx / 8;
    unsigned int biIdx = idx % 8;
    return (data[arIdx] >> (7-biIdx)) & 1;
}

void ParseDataFrame(const char * packet)
{
    int FIN  = GetBit(packet, 0);
    int RSV1 = GetBit(packet, 1);
    int RSV2 = GetBit(packet, 2);
    int RSV3 = GetBit(packet, 3);
    unsigned char OPC = 0;
    {
        int opc0 = GetBit(packet, 4);
        int opc1 = GetBit(packet, 5);
        int opc2 = GetBit(packet, 6);
        int opc3 = GetBit(packet, 7);
        std::cout << opc0 << opc1 << opc2 << opc3 << std::endl;
        OPC |= (opc0 << 0);
        OPC |= (opc1 << 1);
        OPC |= (opc2 << 2);
        OPC |= (opc3 << 3);
    }
    unsigned int LEN = 0;
    {
        for(int i = 9; i < 16; i ++){
            int len = GetBit(packet, i);
            LEN |= (len << i-9);
        }
    }
    int MASK = GetBit(packet, 8);
    int MASK_KEY[32];
    if(MASK){
        for(int i = 16; i < 49; i ++){
            MASK_KEY[i-16] = GetBit(packet, i);
        }
    }
    std::cout << "DATA FRAME" << std::endl;
    std::cout << "FIN: " << FIN << std::endl;
    std::cout << "RSV: " << RSV1 << RSV2 << RSV3 << std::endl;
    std::cout << "OPCODE: " << OPC << MASK << std::endl;
    std::cout << "LENGTH: " << LEN << std::endl;
    std::cout << "MASK: " << MASK_KEY << std::endl;
    std::cout << "DATA FRAME END" << std::endl;
}

class http_server{
public:
    struct sockaddr_in address;
    int server_fd;
    int opt = 1;
    Router router = Router();
    std::stringstream wppoutput;
    iostream_server wppserver{&wppoutput};
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

    void handle_connection(){
        int new_socket, valread;
        int addrlen = sizeof(this->address);
        char buffer[1024] = {0};
        if ((new_socket = accept(this->server_fd, (struct sockaddr*) &this->address, (socklen_t*) &addrlen)) < 0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        valread = read(new_socket, buffer, 1024);
        //std::cout << &this->address << std::endl;
        //std::cout << buffer << std::endl;
        // check if request is websocket related
        // no then router.respond
        // yes then s.async_handle_websocket_connection()
        std::cout << buffer << std::endl;
        char * response = this->router.respond(buffer);
        if(response == nullptr){
            websocketfutures.push_back(std::async(&http_server::handle_websocket_connection, this, new_socket, buffer));
            // close(new_socket);
        }
        else{
            std::cout << "response found\n";
            // std::cout << response << std::endl;
            send(new_socket, response, strlen(response), 0);
            printf("Hello message sent\n");
            close(new_socket);
        }
    }
    void async_handle_connection(){
        while(1){
            std::cout << "HANDLING" << std::endl;
            std::async(&http_server::handle_connection, this);
        }
    }
    void handle_websocket_connection(int socketnum, char buffer[1024]){
        //std::cout << buffer << std::endl;
        const std::stringstream init;
        // std::stringstream output;
        // iostream_server s(&output);
        //std::cout << strlen(buffer) << std::endl;
        //ParseDataFrame(buffer);
        this->wppserver.handle_websocket_connection(buffer, strlen(buffer));
        const std::string tmp = this->wppoutput.str();
        //std::cout << tmp << std::endl;
        const char* cstr = tmp.c_str();
        this->wppoutput.str("");
        this->wppoutput.clear();
        this->wppoutput.copyfmt(init);
        memset(buffer, 0, 1024);
        send(socketnum, cstr, strlen(cstr), 0);
        
        char abuffer[1024];
        int valread;
        do {
            valread = read(socketnum, abuffer, 1024);
            if (valread <= 0) {continue;}
            ParseDataFrame(abuffer);
            this->wppserver.handle_websocket_connection(abuffer, valread);
            const std::string temp = this->wppoutput.str();
            const char* cstr = temp.c_str();
            std::cout << "WSPP RESPONSE: " << std::endl << cstr << std::endl;
            this->wppoutput.str("");
            this->wppoutput.clear();
            this->wppoutput.copyfmt(init);
            memset(abuffer, 0, 1024);
            send(socketnum, cstr, temp.length(), 0);
            std::cout << std::endl;
        }
        while(valread > 0);
    }
};

int main(int argc, char const *argv[]){
    http_server server;
    server.async_handle_connection();
    return 0;
}
