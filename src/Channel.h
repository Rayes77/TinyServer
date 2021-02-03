/*
* @author:MutexCat
* @date  :2021/2/3
* @github:https://github.com/MutexCat
* @description:
*
*/


#ifndef TINYSERVER_CHANNEL_H
#define TINYSERVER_CHANNEL_H

#include <functional>
class EventLoop;
class Channel {
using EventCallBack = std::function<void()>;
private:
    EventCallBack readCallBack;
    EventCallBack writeCallBack;
    EventCallBack errorCallBack;

    static const int kReadEvent;
    static const int kWriteEvent;
    static const int kNoneEvent;

    int fd_;
    int index_;
    int event_;
    int revent_;
    EventLoop* loop_;

    void update();
public:
    void setReadCallBack(EventCallBack cb){readCallBack = std::move(cb);}
    void setWriteCallBack(EventCallBack cb){writeCallBack = std::move(cb);}
    void setErrorCallBack(EventCallBack cb){errorCallBack = std::move(cb);}

    Channel(EventLoop* loop,int fd);
    ~Channel();

    void handleEvent();

    int index() const {return index_;}
    void setIndex(int idx){index_ = idx;}
    void setRevent(int rev){revent_ = rev;}

    EventLoop* ownerLoop(){return loop_;}

    void enableReading(){
        event_ |= kReadEvent;
        update();
    }
    /*
    void enableWriting(){
        event_ |= kReadEvent;
        update();
    }
    void disableWriting(){
        event_ |= kReadEvent;
        update();
    }
    void disableAll(){
        event_ |= kReadEvent;
        update();
    }*/
};


#endif //TINYSERVER_CHANNEL_H
