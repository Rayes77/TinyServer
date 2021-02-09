/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "Channel.h"

Channel::Channel(EventLoop *loop,int fd)
                :loop_(loop),
                 fd_(fd){

}

Channel::~Channel() {

}

void Channel::handleEvent() {

}
