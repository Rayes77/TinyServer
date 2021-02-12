/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/

#include <sys/eventfd.h>
#include <unistd.h>
#include "EventLoop.h"
#include "Channel.h"
#include "Epoller.h"

thread_local EventLoop* loopInThisThread = nullptr;

static int createEventfd()
{
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0)
    {
        abort();
    }
    return evtfd;
}

void EventLoop::loop() {
    assertInLoopThread();
    isLooping_ = true;
    isQuite_ = false;
    //process looping

    while (!isQuite_){
        resultChannel_.clear();
        epoller_->loop(resultChannel_,savedError_);
        for(auto beg = resultChannel_.begin();
            beg != resultChannel_.end();beg++) {
            (*beg)->handleEvent();
        }
        //fixme There is little problem here.
        //suppose that we are doing pending function now
        //a call back function from pending functions calls queueInLoop     - 1
        //at the same time another thread calls quit,set isQuit_ flag to true,and calls wakeUp
        //after I/O thread has done doPendingFUnction,we enter next while iteration
        //now the state will be false,so pending function will not get chance to run.
        //these pending functions are added from previous doPendingFunction()
        //recall that we assume there is a call back function calls queueInLoop add another
        //call back function to pendingFunctions_.
        doPendingFunction();
    }

    isLooping_ = false;
}

void EventLoop::updateChannel(Channel* channel) {
    epoller_->updateChannel(channel);
}

EventLoop::EventLoop():thisThreadId_(std::this_thread::get_id()),
                       isLooping_(false),
                       epoller_(std::make_unique<Epoller>(this)),
                       wakeUpFd_(createEventfd()),//fixme
                       wakeUpChannel_(new Channel(this,wakeUpFd_)){
    if (loopInThisThread){
        std::abort();
    }else {
        loopInThisThread = this;
    }

    wakeUpChannel_->setReadCallBack(std::bind(&EventLoop::handleRead, this));
    wakeUpChannel_->enableReading();
}

EventLoop::~EventLoop() {
    loopInThisThread = nullptr;
}

void EventLoop::quit() {
    isQuite_ = true;
    if (!isInLoopThead()){
        wakeUp();
    }
}

//write to the event fd to wake up the channel that are waiting on epoll.
//So to handle the queue function.
void EventLoop::wakeUp() {
    uint64_t one = 1;
    ssize_t n = ::write(wakeUpFd_, &one, sizeof one);
    if (n != sizeof one)
    {
        std::abort();
    }
}

void EventLoop::handleRead() {
    uint64_t one = 1;
    ssize_t n = ::read(wakeUpFd_, &one, sizeof one);
    if (n != sizeof one)
    {
        std::abort();
    }
}

void EventLoop::runInLoop(std::function<void()> cb) {
    if (isInLoopThead()){
        cb();
    }else{
        queueInLoop(cb);
    }
}

void EventLoop::queueInLoop(std::function<void()> cb) {
    {
        std::lock_guard guard(mutex_);
        pendingFunction_.push_back(cb);
    }
    if (!isInLoopThead() || isDoingPendingFunction_){
        wakeUp();
    }
}

void EventLoop::doPendingFunction() {
    std::vector<std::function<void()>> functors_;
    isDoingPendingFunction_ = true;
    {
        std::lock_guard guard(mutex_);
        functors_.swap(pendingFunction_);
    }

    for(int i =0;i < functors_.size();i++){
        functors_[i]();
    }

    isDoingPendingFunction_ = false;
}

