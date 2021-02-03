/*
* @author:MutexCat
* @date  :2021/2/3
* @github:https://github.com/MutexCat
* @description:
*
*/

#include <sys/poll.h>
#include "Channel.h"
#include "EventLoop.h"

const int Channel::kReadEvent = POLLIN;
const int Channel::kWriteEvent = POLLOUT;
const int Channel::kNoneEvent = 0;

void Channel::update() {
    //loop_->updateChannel(this);
}

Channel::Channel(EventLoop* loop,int fd):
         loop_(loop),
         fd_(fd),
         index_(-1),
         event_(0),
         revent_(0){

}

Channel::~Channel() {

}

void Channel::handleEvent() {
    if (revent_ & POLLNVAL){
        std::cerr<<"Channel::handle_event()POLLNVAL\n";
    }
    if (revent_ & (POLLERR | POLLNVAL)){
        if (errorCallBack)errorCallBack();
    }
    if (revent_ & POLLIN){
        if (readCallBack)readCallBack();
    }
    if (revent_ & POLLOUT){
        if (writeCallBack)writeCallBack();
    }
}
