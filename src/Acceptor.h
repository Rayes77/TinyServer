/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/


#ifndef TINYSERVER_ACCEPTOR_H
#define TINYSERVER_ACCEPTOR_H
#include "Channel.h"
#include "base/InetAddr.h"
#include "base/Socket.h"

class EventLoop;
class Acceptor {
using connectionCallBack = std::function<void(int,const InetAddress&)>;
public:
    Acceptor(EventLoop* loop,const InetAddress& addr);
    void setNewConnCallBack(connectionCallBack cb){
        newConnCallBack = cb;
    }
    bool isListening(){return isListening_;}
    void listen();
private:
    //int listenfd;
    EventLoop* loop_;
    bool isListening_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    connectionCallBack newConnCallBack;
    void handleRead();

};


#endif //TINYSERVER_ACCEPTOR_H
