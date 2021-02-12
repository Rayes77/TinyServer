/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/
//


#include "EventLoopThread.h"
#include "EventLoop.h"

EventLoopThread::EventLoopThread() {

}
//TODO using lambda
EventLoop *EventLoopThread::startLoop() {
    std::thread thread(std::bind(&EventLoopThread::threadFunc,this));
    {
        std::unique_lock guard(mutex_);
        while (loop_ == NULL){
            cond_.wait(guard);
        }
    }
    return loop_;
}

void EventLoopThread::threadFunc() {
    EventLoop loop;
    {
        std::lock_guard guard(mutex_);
        loop_ = &loop;
        cond_.notify_one();
    }
    loop.loop();
}
