/*
* @author:MutexCat
* @date  :2021/2/2
* @github:https://github.com/MutexCat
* @description:
*
*/


#ifndef TINYSERVER_CHANNEL_H
#define TINYSERVER_CHANNEL_H

#include <sys/epoll.h>
#include <functional>
#include <memory>

class EventLoop;

class Channel {
using callback = std::function<void()>;
private:
    callback readCallBack_;
    callback writeCallBack_;
    callback closeCallBack_;
    callback errorCallBack_;

    int fd_;
    bool isInEpoll_;
    int event_;
    int revent_;
    EventLoop* eventLoop_;

    void update();

public:
    Channel(EventLoop* ptr,int fd);

    ~Channel();

    void handleEvent();
    void setRevent(int rev){revent_ = rev;}
    bool isInEpoll(){return isInEpoll_;}
    int getEvent(){return event_;}
    int getFd(){return fd_;}

    void setReadCallBack(callback cb) {
        readCallBack_ = cb;
    }
    void setWriteCallBack(callback cb) {
        writeCallBack_ = cb;
    }
    void setCloseCallBack(callback cb) {
        closeCallBack_ = cb;
    }
    void setIsInEpoll(bool b){isInEpoll_ = b;}
    void enableReading() {
        event_ |= EPOLLIN;
        update();
    }
};


#endif //TINYSERVER_CHANNEL_H
