/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/

#ifndef TINYSERVER_CHANNEL_H
#define TINYSERVER_CHANNEL_H
#include <memory>
#include <sys/epoll.h>
#include <functional>
class EventLoop;

using CallBack = std::function<void()>;

class Channel {
public:
    Channel(EventLoop* loop,int fd);
    ~Channel();

    bool isInEpoll()const{return isInEpoll_;}
    int getEvent()const{return event_;}
    int getFd()const{return fd_;}
    void setRevent(int ev){event_ = ev;}
    void setInEpollState(bool tf){isInEpoll_ = tf;}
    void enableReading(){
        event_ |=EPOLLIN;
        //
    }


    void setReadCallBack(CallBack cb){readCallBack = cb;}
    void setWriteCallBack(CallBack cb){writeCallBack = cb;}
    void handleEvent();
private:
    int fd_;
    std::shared_ptr<EventLoop> loop_;
    int event_;
    int revent_;
    bool isInEpoll_;

    CallBack readCallBack;
    CallBack writeCallBack;

};


#endif //TINYSERVER_CHANNEL_H
