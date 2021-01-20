/*
* @author:MutexCat
* @date  :2021/1/19
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "epoller.h"

epoller::epoller(int timeout,int maxevent): timeOut(timeout), maxEvent(maxevent)
                                                    ,m_resultEvents(maxevent) {
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

int epoller::wait() {
    return epoll_wait(epollFd,m_resultEvents.data(),maxEvent,timeOut);
}

mEpollEvent epoller::getResultEvent(int index) {
    mEpollEvent events;
    events.m_fd = m_resultEvents[index].data.fd;
    events.m_event = m_resultEvents[index].events;
    return events;
}
