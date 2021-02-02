/*
* @author:MutexCat
* @date  :2021/2/2
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop* ptr,int fd):
                 eventLoop_(ptr),
                 fd_(fd),
                 event_(-1),
                 revent_(-1),
                 index_(-1){//do something.

}

void Channel::handleEvent() {
    if (revent_ & EPOLLIN){
        if (readCallBack_)readCallBack_();
    }else if (revent_ & EPOLLOUT){
        if (writeCallBack_)writeCallBack_();
    }else if (revent_ & EPOLLRDHUP){
        if (closeCallBack_)closeCallBack_();
    }else{
        if (errorCallBack_)errorCallBack_();
    }
}

Channel::~Channel() {

}

void Channel::update() {
    eventLoop_->updateChannel(this);
}
