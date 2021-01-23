/*
* @author:MutexCat
* @date  :2021/1/21
* @github:https://github.com/MutexCat
* @description:
*
*/

#ifndef TINYSERVER_THREADPOOL_H
#define TINYSERVER_THREADPOOL_H

#include <mutex>
#include <queue>
#include <memory>
#include <thread>
#include <functional>
#include <condition_variable>

class threadpool {
private:
    struct pool {
        bool isStop;
        std::mutex m_mutex;
        std::condition_variable cond;
        std::queue<std::function<void()>> m_queue;
    };
    std::shared_ptr<pool> m_pool;

    int m_maxThreadNum;
public:
    explicit threadpool(int);
    ~threadpool();
    template<typename F>
    void add(F&&);
};


#endif //TINYSERVER_THREADPOOL_H
