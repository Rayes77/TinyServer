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

Epoller::Epoller(EventLoop *loop) :
        loop_(loop),
        epfd_(epoll_create1(EPOLL_CLOEXEC)) {
}

void Epoller::addToEpoll(std::shared_ptr<Channel> channel) {

}

void Epoller::modifyEpoll(std::shared_ptr<Channel> channel) {

}

void Epoller::loop(std::vector<std::shared_ptr<Channel>> &activeChannel, int &savedError) {
    int num = epoll_wait(epfd_,
                         resultEvent_.data(),
                         resultEvent_.size(),
                         -1);
    if (num > 0) {
        auto beg = resultEvent_.begin();
        while (beg != resultEvent_.end()){
            auto fd = beg->data.fd;
            auto iter = channels_.find(fd);
            assert(iter != channels_.end());
            auto channel = iter->second;
            activeChannel.push_back(channel);
        }
    } else {
        savedError = errno;
    }
}

//update epoll's concern channel(add a new one or modify an exist one).
void Epoller::updateChannel(std::shared_ptr<Channel> channel) {
    auto isInEpoll = channel->isInEpoll();
    if (isInEpoll) {//add a new channel into epoll.
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




