/*
* @author:MutexCat
* @date  :2021/1/21
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "threadpool.h"

threadpool::threadpool(int threadNum) :m_maxThreadNum(threadNum)
                                      ,m_pool(std::make_shared<pool>()) {
    for (int i = 0; i < threadNum; ++i) {
        std::thread([pool_ = m_pool] {
            while (true) {
                std::unique_lock lock(pool_->m_mutex);
                if (!pool_->m_queue.empty()) {
                    auto task = pool_->m_queue.front();
                    pool_->m_queue.pop();
                    lock.unlock();
                    task();
                    lock.lock();
                }else if (pool_->isStop)break;
                 else {
                    pool_->cond.wait(lock);
                }
            }
        }).detach();
    }
}

template<typename F>
void threadpool::add(F &&task) {
    {
        std::lock_guard lock(m_pool->m_mutex);
        m_pool->m_queue.push(task);
    }
    m_pool->cond.notify_one();
}

threadpool::~threadpool() {
    {
        std::lock_guard guard(m_pool->m_mutex);
        m_pool->isStop = true;
    }
    m_pool->cond.notify_all();
}

