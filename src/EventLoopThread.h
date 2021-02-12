/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/


#ifndef TINYSERVER_EVENTLOOPTHREAD_H
#define TINYSERVER_EVENTLOOPTHREAD_H
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

class EventLoop;
class EventLoopThread {
public:
    EventLoopThread();
    EventLoop* startLoop();
private:
    std::mutex mutex_;
    EventLoop* loop_;
    std::condition_variable cond_;
    void threadFunc();
};


#endif //TINYSERVER_EVENTLOOPTHREAD_H
