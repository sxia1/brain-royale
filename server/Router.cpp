#include "Router.h"
#include "request.h"
#include <string>
#include <iostream>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include "static_file.h"

#include <typeinfo>

namespace fs = boost::filesystem;

#define INDEX "../client/build/index.html"
#define CSSPATH "../client/build/static/css/"
#define JSPATH "../client/build/static/js/"

Router::Router(){
    //DEFAULT CASES JUST IN CASE
//    std::string CSS = "../client/build/static/css/main.26bfa704.css";
//    std::string JS = "../client/build/static/js/main.179a5f96.js";
    std::string CSS;
    std::string JS;
    fs::path p(CSSPATH);
    fs::directory_iterator end_itr; //used to detect end of directory iterator
    for (fs::directory_iterator itr(p); itr != end_itr; ++itr){
        fs::path filepath = itr->path().filename(); //get path from iterator
        std::string filename = filepath.string(); //convert to string for comparison
        if (filename.length() > 9){ //should always be true but just in case
            if (filename.substr(0,5).compare("main.")==0 && filename.substr(filename.length()-4).compare(".css")==0){
                CSS = CSSPATH + filename;
            }
        }
    }
    std::cout << "css filepath:" << CSS << "\n";

    fs::path p2(JSPATH);
    for (fs::directory_iterator itr(p2); itr != end_itr; ++itr){
        fs::path filepath = itr->path().filename(); //get path from iterator
        std::string filename = filepath.string(); //convert to string for comparison
        if (filename.length() > 8){ //should always be true but just in case
            if (filename.substr(0,5).compare("main.")==0 && filename.substr(filename.length()-3).compare(".js")==0){
                JS = JSPATH + filename;
            }
        }
    }
    std::cout << "js file path: " << JS << "\n";

    const char *indexfile = readFiletoBuffer(INDEX);
    const char *cssfile = readFiletoBuffer(CSS);
    const char *jsfile = readFiletoBuffer(JS);
    hello = new char[strlen(indexfile)+128];
    css = new char[strlen(cssfile)+128];
    js = new char[strlen(jsfile)+128];
    web = new char[1028];

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

    strcpy(web,"HTTP/1.1 101 Switching Protocols\r\n"
        "Upgrade: websocket\r\n"
        "Connection: upgrade\r\n"
        "Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=\r\n"
        "Server: Boost.Beast\r\n"
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
    delete web;
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
    int slash = target.find_last_of('/');
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
            if (r.isUpgrade() || (r.getType() != "GET" && r.getType() != "POST")){
                std::cout << "websocket\n";
                return nullptr;
            }
            std::cout << "homepage hello\n";
        return hello;
    }
    
}

