/*
* @author:MutexCat
* @date  :2021/2/2
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "EventLoop.h"

EventLoop::EventLoop() {

}

EventLoop::~EventLoop() {

}

void EventLoop::loop() {

    int num = epoller_->wait(activeChannels_);
    for (int i = 0; i < num; ++i) {
        activeChannels_[i]->handleEvent();
    }

}

void EventLoop::updateChannel(Channel *channel) {
    epoller_->updateChannel(channel);
}
