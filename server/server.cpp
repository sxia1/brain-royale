// Server side C/C++ program to demonstrate Socket programming
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <string>
#include <iostream>

#include "static_file.h"

#define PORT 8080
#define INDEX "../client/build/index.html"
#define CSS "../client/build/static/css/main.26bfa704.css"
#define JS "../client/build/static/js/main.d4262ebc.js"

int main(int argc, char const *argv[]){
    const char *indexfile = readFiletoBuffer(INDEX);
    const char *cssfile = readFiletoBuffer(CSS);
    const char *jsfile = readFiletoBuffer(JS);

    char hello[strlen(indexfile)+128] = "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-type: text/html\r\n"
        "\r\n";

    char css[strlen(cssfile)+128] = "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-type: text/css\r\n"
        "\r\n";

    char js[strlen(jsfile)+128] = "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-type: application/javascript; charset=utf-8\r\n"
        "\r\n";

    strcat(hello, indexfile);
    strcat(css, cssfile);
    strcat(js, jsfile);

    std::cout << "DONE LOADING FILES" << std::endl;

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
        if(strstr(buffer, "css")) send(new_socket, css, strlen(css), 0);
        else if(strstr(buffer, "js")) send(new_socket, js, strlen(js), 0);
        else send(new_socket, hello, strlen(hello), 0 );
        printf("Hello message sent\n");
        close(new_socket);
    }
    delete indexfile;
    delete cssfile;
}
