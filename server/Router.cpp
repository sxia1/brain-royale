#include "Router.h"
#include "request.h"
#include <string>
#include "static_file.h"

char* Router::respond(char* req){
    request r = request(req);
    std::string target = r.getTarget();
    if (target.compare("/")==0){
        const char *indexfile = readFiletoBuffer("index.html");
        char hello[strlen(indexfile)+128] = "HTTP/1.1 200 OK\r\n"
            "Connection: close\r\n"
            "Content-type: text/html\r\n"
            "\r\n";
        return strcat(hello, indexfile);
    }
    else if (target.compare("/index.css")==0){
        const char *cssfile = readFiletoBuffer("index.css");
        char css[strlen(cssfile)+128] = "HTTP/1.1 200 OK\r\n"
            "Connection: close\r\n"
            "Content-type: text/css\r\n"
            "\r\n";
        return strcat(css, cssfile);
    }

}