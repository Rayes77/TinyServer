/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop *loop,int fd)
                :loop_(loop),
                 fd_(fd),
                 event_(0),
                 revent_(-1),
                 isInEpoll_(false){

}

Channel::~Channel() {

}

void Channel::handleEvent() {
    if (revent_ & EPOLLERR){
        if (errorCallBack)errorCallBack();
    }
    if (revent_ & EPOLLIN){
        if (readCallBack)readCallBack();
    }
    if (revent_ & EPOLLOUT){
        if (writeCallBack)writeCallBack();
    }
}

void Channel::update() {
    loop_->updateChannel(this);
}
