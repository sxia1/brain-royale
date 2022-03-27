// Server side C/C++ program to demonstrate Socket programming
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <string>
#include <iostream>
#include "Router.h"
#include "static_file.h"

#define PORT std::stoi(getenv("PORT"))

int main(int argc, char const *argv[]){
    std::cout << "port: " << PORT << "\n";

    struct sockaddr_in address;
    int opt = 1;
    int server_fd;
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
     
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    std::cout << "port: " << PORT << "\n";
    Router router = Router();
    while(1){
        int new_socket, valread;
        int addrlen = sizeof(address);
        char buffer[1024] = {0};
          
        if ((new_socket = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        valread = read( new_socket , buffer, 1024);
        std::cout << buffer << std::endl;
        char * response = router.respond(buffer);
        std::cout << "response found\n";
        send(new_socket, response, strlen(response), 0);
        printf("Hello message sent\n");
        close(new_socket);
    }
    
}
