#pragma once

class Router{
private:
    char* hello;
    char* css;
    char* js;
    char* web;
public:
    Router();
    ~Router();
    char* respond(char*);
};
