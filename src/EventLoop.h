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
#include <assert.h>
#include "Channel.h"

class EventLoop {
private:
    std::thread::id thisThreadId;
    std::atomic<bool> looping_;
    std::atomic<bool> quit_;

    void abortNotInLoopThreed();
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void updateChannel(Channel* channel);

    static EventLoop* getEventLoopOfCurrentThread();


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
