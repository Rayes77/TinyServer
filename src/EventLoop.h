/*
* @author:MutexCat
* @date  :2021/2/3
* @github:https://github.com/MutexCat
* @description:
*
*/


#ifndef TINYSERVER_EVENTLOOP_H
#define TINYSERVER_EVENTLOOP_H

#include <thread>
#include <atomic>
#include <iostream>
#include <memory>
#include <assert.h>
#include <mutex>
#include "Channel.h"
#include "TimerQueue.h"
class Poller;

using CallBack = std::function<void()>;

class EventLoop {
private:
    std::thread::id thisThreadId;
    std::atomic<bool> looping_;
    std::atomic<bool> quit_;
    std::unique_ptr<Poller> poller_;
    std::vector<Channel*> activeChannels_;
    TimerQueue* timerQueue_;
    void abortNotInLoopThreed();

    void handleRead();
    void doPendingFunctors();
    std::atomic<bool> callingPendingFunctors_;

    int wakeupFd_;
    //used to process the readable event that happened in wakeupFD_.
    std::unique_ptr<Channel> wakeupChannel_;

    std::mutex mutex_;
    std::vector<CallBack> pendingFunctors_;

public:
    EventLoop();
    ~EventLoop();
    void loop();
    void quit(){quit_ = true;}
    void updateChannel(Channel* channel);

    TimerId runAt(const TimeStamp& time,const TimerCallBack& cb){
        return timerQueue_->addTimer(cb,time,0.0);
    }
    TimerId runAfter(int delay,const TimerCallBack& cb){
        TimeStamp time;
        return runAt(time,cb);
    }

    TimerId runEvery(double interval,const TimerCallBack& cb){
        TimeStamp time;
        return runAt(time,cb);
    }

    static EventLoop* getEventLoopOfCurrentThread();

    void runInLoop(const CallBack& cb){
        if (isInLoopThread()){
            cb();
        }else{
            queueInLoop(cb);
        }
    }

    //calling in another thread.
    void queueInLoop(const CallBack& cb){
        {
            std::lock_guard guard(mutex_);
            pendingFunctors_.push_back(cb);
        }
        if (!isInLoopThread() || callingPendingFunctors_){
            wakeup();
        }
    }

    void wakeup();

    void doingPendingFunctors(){
        std::vector<CallBack> functors;
        callingPendingFunctors_ = true;
        {
            std::lock_guard guard(mutex_);
            functors.swap(pendingFunctors_);
        }
        for(auto beg = functors.begin();beg != functors.end();beg++){
            (*beg)();
        }
        callingPendingFunctors_ = false;
    }

    void exit(){
        quit_ = true;
        if (!isInLoopThread()){
            wakeup();
        }
    }

    void assertInThread(){
        if (!isInLoopThread()){
            abortNotInLoopThreed();
        }
    }
    bool isInLoopThread(){
        return thisThreadId == std::this_thread::get_id();
    }
};


#endif //TINYSERVER_EVENTLOOP_H
