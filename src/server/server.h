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
#include <unistd.h>
#include <arpa/inet.h>
#include "../eventloop/epoller.h"
class server {
private:
    std::shared_ptr<epoller> m_epoll;

    int m_listenFd;         //listen fd
    int m_port;             //port
    int m_maxTimeout;       //timeout
    int m_maxThreadNum;     //max thread num
    int m_maxEvent;         //max event num

    bool isStop = true;

    //internal utils
    bool getListenFd();
public:
    server(int port_,int timeout = -1,int maxevent = 1024);
    void start();
};


#endif //TINYSERVER_SERVER_H
