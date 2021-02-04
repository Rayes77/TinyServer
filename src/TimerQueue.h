/*
* @author:MutexCat
* @date  :2021/2/4
* @github:https://github.com/MutexCat
* @description:
*
*/


#ifndef TINYSERVER_TIMERQUEUE_H
#define TINYSERVER_TIMERQUEUE_H
#include "Timer.h"
#include <set>
#include "Channel.h"
class EventLoop;
class TimerQueue {
    using TimerCallBack = std::function<void()>;
    using TimeStamp = std::chrono::high_resolution_clock::time_point;
public:
    TimerQueue(EventLoop* loop);
    ~TimerQueue();
    TimerId addTimer(const TimerCallBack,TimeStamp when,int interval);

    using Entry = std::pair<TimeStamp,Timer*>;
    using TimerList = std::set<Entry>;

    void handleRead();
    std::vector<Entry> getExpired(TimeStamp now);
    void reset(const std::vector<Entry> exxpired,TimeStamp now);

    bool insert(Timer* timer);

    EventLoop* loop_;
    const int timefd_;
    Channel timerFdChannel_;

    TimerList timers_;
};


#endif //TINYSERVER_TIMERQUEUE_H
