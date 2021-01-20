#include <iostream>
#include "server/server.h"

int main(){
    std::vector<std::string> words4(5, "Mo");

    server webSever(9999);
    webSever.start();
}