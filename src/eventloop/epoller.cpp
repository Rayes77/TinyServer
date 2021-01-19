/*
* @author:MutexCat
* @date  :2021/1/19
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "epoller.h"

epoller::epoller(int timeout,int maxevent): timeOut(timeout), maxEvent(maxevent) {
    epollFd = epoll_create(1024);
}

bool epoller::modFd(int fd,u_int32_t event) {
    if (fd < 0)return false;
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    return 0 == epoll_ctl(epollFd,EPOLL_CTL_MOD,fd,&ev);
}

bool epoller::addFd(int fd, u_int32_t event) {
    if (fd < 0)return false;
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    return 0 == epoll_ctl(epollFd,EPOLL_CTL_ADD,fd,&ev);
}

bool epoller::delFd(int fd) {
    if (fd < 0)return false;
    return 0 == epoll_ctl(epollFd,EPOLL_CTL_DEL,fd,NULL);
}

int epoller::wait(int, u_int32_t) {
    return epoll_wait(epollFd,&eventsResult[0],maxEvent,timeOut);
}
