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
#include "iostream_server.h"
#include "Router.h"
#include "LobbyController.h"
#include "static_file.h"
//#include "endpoints.cpp"
#include "json.hpp"
#define PORT std::stoi(getenv("PORT"))

typedef websocketpp::server<websocketpp::config::core> server;
typedef server::message_ptr message_ptr;
typedef nlohmann::json json;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

std::vector<Lobby> lobbies;

class http_server{
public:
    struct sockaddr_in address;
    int server_fd;
    int opt = 1;
    Router router = Router();
    LobbyController lcontrol = LobbyController();
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
        std::cout << "websocket conn\n";
        const std::stringstream init;
        std::stringstream wppoutput;
        std::cout << "before iostream\n";
        iostream_server wppserver{&wppoutput, socketnum, &lcontrol};
        std::cout << "breakpoint iostream done\n"; //===============================================================
        wppserver.handle_websocket_connection(buffer, strlen(buffer));
        const std::string tmp = wppoutput.str();
        const char* cstr = tmp.c_str();
        std::cout << "tmp: " << tmp << "\n";
        wppoutput.str("");
        wppoutput.clear();
        wppoutput.copyfmt(init);
        memset(buffer, 0, 1024);
        send(socketnum, cstr, tmp.length(), 0);
        
        char abuffer[1024];
        int valread;
        do {
            valread = read(socketnum, abuffer, 1024);
            if (valread <= 0) {continue;}
            wppserver.handle_websocket_connection(abuffer, valread);
            const std::string temp = wppoutput.str();
            const char* cstr = temp.c_str();
            std::cout << "WSPP RESPONSE: " << std::endl << cstr << std::endl;
            memset(abuffer, 0, 1024);
            send(socketnum, cstr, temp.length(), 0);
            wppoutput.str("");
            wppoutput.clear();
            wppoutput.copyfmt(init);
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