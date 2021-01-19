/*
* @author:MutexCat
* @date  :2021/1/19
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "server.h"

//read conf file.
server::server(int port) {

}

void server::start() {
    std::cout<<"Server Started!"<<std::endl;

    //event loop
    while (!isStop){
        int number = epoller->wait();
    }
}
