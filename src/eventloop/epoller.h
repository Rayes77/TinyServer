/*
* @author:MutexCat
* @date  :2021/1/19
* @github:https://github.com/MutexCat
* @description:
*
*/

#ifndef TINYSERVER_EPOLLER_H
#define TINYSERVER_EPOLLER_H
#include <vector>
#include <sys/epoll.h>

class epoller {
private:
    int epollFd;
    int maxEvent;
    int timeOut;

    std::vector<struct epoll_event> eventsResult;

public:
    epoller(int timeout = -1,int maxevent = 1024);
    int wait(int,u_int32_t);
    bool addFd(int,u_int32_t);
    bool modFd(int,u_int32_t);
    bool delFd(int);
};


#endif //TINYSERVER_EPOLLER_H
