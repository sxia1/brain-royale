#include "request.h"

request::request(char* re){
    /*
    char * type = new char[10];
    std::string test = std::string(req);
    int end = test.find(' ');
    printf("%i\n",end);
    std::string part = test.substr(0,end);
    printf("%s\n",part.c_str());
    */
    string req = string(re);
//    string  type;
//    string  target;
//    string  version;
//    string  rest;
    int end = req.find('\r');
    string line = req.substr(0,end);
 //   rest =  string(req.substr(end)); //everything besides first line
    int i = line.find(' ');
    type =  string(line.substr(0,i)); //set type (GET,POST,etc.)
//    const char* test = type.c_str();
//    printf("%s\n",*type);
    line = string(line.substr(i+1)); //
    i = line.find(' ');
    target =  string(line.substr(0,i)); //target route?
    version =  string(line.substr(i+1)); //last part of starting line
    upgrade = req.find("Upgrade: websocket") != string::npos;
}

string request::getType(){
    return type;
}

string request::getTarget(){
    return target;
}
string request::getVersion(){
    return version;
}

bool request::isUpgrade(){
    return upgrade;
}

/*
string* request::getRest(){
    return rest;
}

string request::to_string(){
    return *type;
}
*/


/*
request::~request(){
    delete type;
    delete target;
    delete version;
    delete rest;
}
*/