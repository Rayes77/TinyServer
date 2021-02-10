/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "Epoller.h"
#include "Channel.h"
#include <assert.h>
#include <iostream>

Epoller::Epoller(EventLoop* loop) :
        loop_(loop),
        epfd_(epoll_create1(EPOLL_CLOEXEC)),
        resultEvent_(16){
}


void Epoller::loop(std::vector<Channel*> &activeChannel, int &savedError) {
    int num = epoll_wait(epfd_,
                         resultEvent_.data(),
                         resultEvent_.size(),
                         -1);
    if (num > 0) {
        for(auto beg = resultEvent_.begin();beg != resultEvent_.end() && num != 0;beg++){
            --num;
            auto fd = beg->data.fd;
            auto event = beg->events;
            auto iter = channels_.find(fd);
            auto channel = iter->second;
            activeChannel.push_back(channel);
            beg++;
        }
    } else {
        savedError = errno;
    }
}

//update epoll's concern channel(add a new one or modify an exist one).
void Epoller::updateChannel(Channel* channel) {
    auto isInEpoll = channel->isInEpoll();
    if (!isInEpoll) {//add a new channel into epoll.
        int fd = channel->getFd();
        channels_[fd] = channel;
        struct epoll_event event;
        event.events = channel->getEvent();
        event.data.fd = fd;
        epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &event);
        channel->setInEpollState(true);
    } else {//modify exist one.
        int fd = channel->getFd();
        channels_[fd] = channel;
        struct epoll_event event;
        event.events = channel->getEvent();
        event.data.fd = fd;
        epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &event);
    }
}




