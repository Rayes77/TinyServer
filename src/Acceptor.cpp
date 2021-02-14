/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "Acceptor.h"
#include "base/SocketOpts.h"

void Acceptor::handleRead() {

}

Acceptor::Acceptor(EventLoop *loop, const InetAddress &addr):
                   loop_(loop),
                   acceptSocket_(createNonblockingOrDie()),
                   acceptChannel_(loop,acceptSocket_.fd()),
                   isListening_(false){
    acceptSocket_.bindAddress(addr);
    acceptSocket_.setReuseAddr(true);
    acceptChannel_.setReadCallBack(std::bind(&Acceptor::handleRead,this));
}
