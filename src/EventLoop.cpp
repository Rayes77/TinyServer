/*
* @author:MutexCat
* @date  :2021/2/3
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "EventLoop.h"
#include "Poller.h"
thread_local EventLoop* loopInThisThread;

void EventLoop::abortNotInLoopThreed() {
    std::abort();
}

EventLoop::EventLoop():
            thisThreadId(std::this_thread::get_id()),
            looping_(false),
            quit_(false),
            poller_(std::make_unique<Poller>(this)){
    if (loopInThisThread){
        std::cerr<<"This thread already has a EventLoop.\n";
        std::abort();
    }else{
        loopInThisThread = this;
    }
}

EventLoop::~EventLoop() {
    assert(!looping_);
    loopInThisThread = NULL;
}

void EventLoop::loop() {
    assert(!looping_);
    assertInThread();
    looping_ = true;
    quit_ = false;
    while(!quit_){
        activeChannels_.clear();
        poller_->poll(1,activeChannels_);
        for(auto beg = activeChannels_.begin();
            beg != activeChannels_.end();beg++){
            (*beg)->handleEvent();
        }
    }
    looping_ = false;
}

EventLoop *EventLoop::getEventLoopOfCurrentThread() {
    return loopInThisThread;
}

void EventLoop::updateChannel(Channel *channel) {
    assert(channel->ownerLoop() == this);
    assertInThread();
    poller_->updateChannel(channel);
}
