// Server side C/C++ program to demonstrate Socket programming
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <string>
#include <iostream>
#include <future>
#include "Router.h"
#include "static_file.h"

#define PORT std::stoi(getenv("PORT"))

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
        char buffer[1024] = {0};
        if ((new_socket = accept(this->server_fd, (struct sockaddr*) &this->address, (socklen_t*) &addrlen)) < 0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        valread = read(new_socket, buffer, 1024);
        std::cout << buffer << std::endl;
        char * response = this->router.respond(buffer);
        std::cout << "response found\n";
        send(new_socket, response, strlen(response), 0);
        printf("Hello message sent\n");
        close(new_socket);
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
