// Server side C/C++ program to demonstrate Socket programming
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <string>
#include <iostream>
#define PORT 8080

const char hello[] = "HTTP/1.1 200 OK\r\n"
    "Connection: close\r\n"
    "Content-type: text/html\r\n"
    "\r\n"
    "<html>\r\n"
    "<head>\r\n"
    "<title>Hello, world!</title>\r\n"
    "</head>\r\n"
    "<body>\r\n"
    "<h1>Hello, world!</h1>\r\n"
    "</body>\r\n"
    "</html>\r\n\r\n";           

const char home[] = "HTTP/1.1 200 OK\r\n"
    "Connection: close\r\n"
    "Content-type: text/html\r\n"
    "\r\n"
    "<html>\r\n"
    "<head>\r\n"
    "<title>Hello, welcome home!</title>\r\n"
    "</head>\r\n"
    "<body>\r\n"
    "<h1>Hello, welcome home!</h1>\r\n"
    "</body>\r\n"
    "</html>\r\n\r\n";           

int main(int argc, char const *argv[]){
    int ctr = 0;
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
        ctr ++;
        std::cout << ctr << ": " << valread << std::endl;
        std::cout << buffer << std::endl;
        if(strstr(buffer, "home")){
            send(new_socket , home, strlen(hello) , 0 );
        }
        else{
            send(new_socket , hello , strlen(hello) , 0 );
        }
        printf("Hello message sent\n");
        close(new_socket);
    }
}
