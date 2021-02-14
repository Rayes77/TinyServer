/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "Acceptor.h"
#include "EventLoop.h"
#include "base/SocketOpts.h"


Acceptor::Acceptor(EventLoop *loop, const InetAddress &addr):
                   loop_(loop),
                   acceptSocket_(createNonblockingOrDie()),
                   acceptChannel_(loop,acceptSocket_.fd()),
                   isListening_(false){
    acceptSocket_.bindAddress(addr);
    acceptSocket_.setReuseAddr(true);
    acceptChannel_.setReadCallBack(std::bind(&Acceptor::handleRead,this));
}

void Acceptor::listen() {
    isListening_ = true;
    acceptSocket_.listen();
    acceptChannel_.enableReading();
}

void Acceptor::handleRead() {
    InetAddress addr(0);
    int fd = acceptSocket_.accept(&addr);
    if (fd >= 0){
        newConnCallBack(fd,addr);
    }else{
        close(fd);
    }
}
