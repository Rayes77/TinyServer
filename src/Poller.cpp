/*
* @author:MutexCat
* @date  :2021/2/3
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "Poller.h"
#include <sys/poll.h>
#include "Channel.h"
#include <assert.h>
#include <iostream>

Timestamp Poller::poll(int timeousMS, Poller::ChannelList &activeChannels) {
    int numEvents = ::poll(pollfds_.data(), pollfds_.size(), timeousMS);
    Timestamp now;
    if (numEvents > 0) {
        fillActiveChannels_(numEvents, activeChannels);
    } else if (numEvents < 0) {
        std::cout << "none event happen\n";
    } else {
        std::cerr << "Poller::poll error\n";
    }
    return now;
}

void Poller::fillActiveChannels_(int numEvents, Poller::ChannelList &activeChannels) const {
    for (auto pfd = pollfds_.begin(); pfd != pollfds_.end() && numEvents > 0; pfd++) {
        if (pfd->revents > 0) {
            numEvents--;
            auto ch = channels_.find(pfd->fd);
            assert(ch != channels_.end());
            auto channel = ch->second;
            assert(channel->fd() == pfd->fd);
            channel->setRevent(pfd->revents);
            activeChannels.push_back(channel);
        }
    }
}

void Poller::updateChannel(Channel *channel) {
    assertInLoopThread();
    if (channel->index() < 0) {
        //add new one
        assert(channels_.find(channel->fd()) == channels_.end());
        struct pollfd pfd;
        pfd.fd = channel->fd();
        pfd.events = static_cast<short>(channel->events());
        pfd.revents = 0;
        pollfds_.push_back(pfd);
        int idx = static_cast<int>(pollfds_.size()) - 1;
        channel->setIndex(idx);
        channels_[pfd.fd] = channel;
    } else {
        //modify existing one
        assert(channels_.find(channel->fd()) != channels_.end());
        assert(channels_[channel->fd()] == channel);
        struct pollfd &pfd = pollfds_[channel->index()];
        pfd.events = channel->events();
        pfd.revents = 0;
    }
}
