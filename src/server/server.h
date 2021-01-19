/*
* @author:MutexCat
* @date  :2021/1/19
* @github:https://github.com/MutexCat
* @description:
*
*/

/*
 * TODO:auto configure
 * TODO:
 */
#ifndef TINYSERVER_SERVER_H
#define TINYSERVER_SERVER_H
#include <memory>
#include <iostream>
#include "../eventloop/epoller.h"
class server {
private:
    std::shared_ptr<epoller> epoller;

    int listenFd;

    bool isStop = true;
public:
    server(int port);
    void start();
};


#endif //TINYSERVER_SERVER_H
