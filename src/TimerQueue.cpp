/*
* @author:MutexCat
* @date  :2021/2/4
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "TimerQueue.h"
#include <assert.h>
using TimeStamp = std::chrono::high_resolution_clock::time_point;
using Entry = std::pair<TimeStamp,Timer*>;
std::vector<Entry> TimerQueue::getExpired(TimerQueue::TimeStamp now) {
    std::vector<Entry> expired;
    Entry sentry = std::make_pair(now,reinterpret_cast<Timer*>(UINTPTR_MAX));
    auto it = timers_.lower_bound(sentry);
    assert(it == timers_.end() || now < it->first);
    std::copy(timers_.begin(),it,std::back_inserter(expired));
    return expired;
}
