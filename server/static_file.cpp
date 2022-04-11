#include "static_file.h"

char* readFiletoBuffer(std::string filename){
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    char *buffer = new char[size];
    file.read(buffer, size);
    file.close();
    return buffer;
}
