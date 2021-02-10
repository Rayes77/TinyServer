/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/


#ifndef TINYSERVER_EVENTLOOP_H
#define TINYSERVER_EVENTLOOP_H

#include <memory>
#include <thread>
#include <vector>
#include <assert.h>
#include <iostream>
#include "base/nocopyable.h"


class Channel;
class Epoller;
class EventLoop : public nocopyable{
public:
    using ThreadID = std::thread::id;

    void quit();
    void loop();
    void updateChannel(Channel* channel);

    EventLoop();
    ~EventLoop();


    ThreadID thisThreadId_;
private:
    bool isLooping_;
    bool isQuite_;
    int savedError_;
    std::vector<Channel*> resultChannel_;
    std::unique_ptr<Epoller> epoller_;

    void assertInLoopThread() const {
        if (!isInLoopThead()){
            std::abort();
        }
    }

    bool isInLoopThead() const {
        return thisThreadId_ == std::this_thread::get_id();
    }

};


#endif //TINYSERVER_EVENTLOOP_H
