/*
* @author:MutexCat
* @date  :2021/2/4
* @github:https://github.com/MutexCat
* @description:
*
*/
//
// Created by rayes on 2021/2/4.
//

#ifndef TINYSERVER_TIMER_H
#define TINYSERVER_TIMER_H

#include <chrono>
#include <functional>

class TimerId{};
using Clock = std::chrono::high_resolution_clock;
using TimeStamp = Clock::time_point;
using TimerCallBack = std::function<void()>;
class Timer {

public:
    Timer(TimerCallBack cb, TimeStamp when, int interval)
            : callBack_(cb),
              expiration_(when),
              interval_(interval),
              repeat_(interval > 0.0)
    { }


    void run() const {
        callBack_();
    }



    void restart(){
            if (repeat_)
            {
                expiration_ = Clock::now() + std::chrono::milliseconds(interval_);
            }
            else
            {
                expiration_ = Clock::now() + std::chrono::milliseconds(-1);
            }
    }

    TimeStamp expiration() const  { return expiration_; }
    bool repeat() const { return repeat_; }
    //int64_t sequence() const { return sequence_; }

private:
    const TimerCallBack callBack_;
    TimeStamp expiration_;
    const int interval_;
    const bool repeat_;
    //const int64_t sequence_;


};


#endif //TINYSERVER_TIMER_H
