#pragma once

class Router{
private:
    char* hello;
    char* css;
    char* js;
public:
    Router();
    ~Router();
    char* respond(char*);
};
