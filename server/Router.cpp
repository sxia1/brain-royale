#include "Router.h"
#include "request.h"
#include <string>
#include <iostream>
#include "static_file.h"

#define INDEX "../client/build/index.html"
#define CSS "../client/build/static/css/main.26bfa704.css"
#define JS "../client/build/static/js/main.179a5f96.js"

Router::Router(){
    const char *indexfile = readFiletoBuffer(INDEX);
    const char *cssfile = readFiletoBuffer(CSS);
    const char *jsfile = readFiletoBuffer(JS);
    hello = new char[strlen(indexfile)+128];
    css = new char[strlen(cssfile)+128];
    js = new char[strlen(jsfile)+128];

    strcpy(hello,"HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-type: text/html\r\n"
        "\r\n"
    );

    strcpy(css,"HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-type: text/css\r\n"
        "\r\n"
    );

    strcpy(js,"HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-type: application/javascript; charset=utf-8\r\n"
        "\r\n"
    );


    strcat(hello, indexfile);
    strcat(css, cssfile);
    strcat(js, jsfile);

}

Router::~Router(){
    delete hello;
    delete css;
    delete js;
}

char* Router::respond(char* req){
    request r = request(req);
    std::string target = r.getTarget();
    /*
    if (target.compare("/")==0){
        const char *indexfile = readFiletoBuffer(INDEX);
        char hello[strlen(indexfile)+128] = "HTTP/1.1 200 OK\r\n"
            "Connection: close\r\n"
            "Content-type: text/html\r\n"
            "\r\n";
        return strcat(hello, indexfile);
    }
    */
   
    printf("target: %s\n",target.c_str());
    if (target.compare("/static/css/main.26bfa704.css")==0){
/*        const char *cssfile = readFiletoBuffer(CSS);
        char css[strlen(cssfile)+128] = "HTTP/1.1 200 OK\r\n"
            "Connection: close\r\n"
            "Content-type: text/css\r\n"
            "\r\n";
            */
           std::cout << "css\n";
        return css;
    }
    else if (target.compare("/static/js/main.179a5f96.js")==0){
/*        const char *jsfile = readFiletoBuffer(JS);
        char js[strlen(jsfile)+128] = "HTTP/1.1 200 OK\r\n"
            "Connection: close\r\n"
            "Content-type: application/javascript; charset=utf-8\r\n"
            "\r\n";*/
           std::cout << "js\n";
        return js;
    }
    else {
/* 
        const char *indexfile = readFiletoBuffer(INDEX);
        char hello[strlen(indexfile)+128] = "HTTP/1.1 200 OK\r\n"
            "Connection: close\r\n"
            "Content-type: text/html\r\n"
            "\r\n";
*/ 
           std::cout << "hello\n";
        return hello;
    }
    
}
