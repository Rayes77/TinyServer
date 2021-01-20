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
#include <array>
#include <sys/epoll.h>

struct mEpollEvent{
    int m_fd;
    uint32_t m_event;
};

class epoller {
private:
    int epollFd;
    int maxEvent;
    int timeOut;

    //std::array<struct epoll_event,1024> m_resultEvents;
    std::vector<struct epoll_event> m_resultEvents;
public:
    epoller(int ,int );
    int wait();
    bool addFd(int ,u_int32_t );
    bool modFd(int ,u_int32_t );
    bool delFd(int );

    mEpollEvent getResultEvent(int );
};


#endif //TINYSERVER_EPOLLER_H
