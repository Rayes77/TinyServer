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
#include <mutex>
#include <assert.h>
#include <iostream>
#include <functional>
#include "base/nocopyable.h"


class Channel;
class Epoller;
class EventLoop : public nocopyable{
public:
    using ThreadID = std::thread::id;

    void quit();
    void loop();
    void wakeUp();
    void runInLoop(std::function<void()> cb);
    void updateChannel(Channel* channel);

    EventLoop();
    ~EventLoop();


    ThreadID thisThreadId_;
private:
    std::mutex mutex_;
    bool isLooping_;
    bool isDoingPendingFunction_;
    bool isQuite_;
    int savedError_;
    int wakeUpFd_;
    std::unique_ptr<Channel> wakeUpChannel_;
    std::vector<Channel*> resultChannel_;
    std::vector<std::function<void()>> pendingFunction_;
    std::unique_ptr<Epoller> epoller_;

    void handleRead();
    void doPendingFunction();
    void queueInLoop(std::function<void()> cb);

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
