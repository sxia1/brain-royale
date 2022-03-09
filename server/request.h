#pragma once
#include <string>

using std::string;

class request{
private:
    //no memory allocations yet, might need to do that
//    char* type;
//    char* target;
//    char* version;
//    char* rest;
    string type;
    string target;
    string version;
 //   string rest;
public:
    //request(char*);
    request(char*);
 //   ~request();
    //getters
    string getType();
    string getTarget();
    string getVersion();
   // char* getRest();
    char* to_string();
};
