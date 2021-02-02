/*
* @author:MutexCat
* @date  :2021/2/2
* @github:https://github.com/MutexCat
* @description:
*
*/

#include <iostream>
#include "Epoller.h"
#include "Channel.h"

int Epoller::wait(std::vector<Channel *> &activeChannel) {
    int num = epoll_wait(epollFd_, events_.data(), NULL, NULL);
    if (num > 0) {
        fillActiveChannels(num,activeChannel);
    } else if (num == 0) {
        //
    } else {
        std::cerr<<"epoll_wait return a negative value \n";

    }
    return num;
}

void Epoller::updateChannel(Channel *channel) {
    auto isInEpoll = channel->isInEpoll();
    int fd = channel->getFd();
    if (!isInEpoll) {//add a new one.
        channelMap_[fd] = channel;
        update(EPOLL_CTL_ADD, channel);
        channel->setIsInEpoll(true);
    } else {//modify n existing one.
        update(EPOLL_CTL_MOD, channel);
    }
}

void Epoller::update(int ctl, Channel *channel) {
    epoll_event event;
    auto fd = channel->getFd();
    event.events = channel->getEvent();
    event.data.ptr = channel;
    epoll_ctl(epollFd_, ctl, fd, &event);
}

void Epoller::fillActiveChannels(int num, std::vector<Channel *>& activeChannel) {
    auto beg = events_.begin();
    for(;beg != events_.end();beg++){

    }
}

