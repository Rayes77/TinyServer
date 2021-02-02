/*
* @author:MutexCat
* @date  :2021/2/2
* @github:https://github.com/MutexCat
* @description:
*
*/
#ifndef TINYSERVER_EVENTLOOP_H
#define TINYSERVER_EVENTLOOP_H

#include <memory>
#include "Channel.h"
#include "Epoller.h"
class EventLoop {
private:
    std::unique_ptr<Epoller> epoller_;
    std::vector<Channel*> activeChannels_;
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void updateChannel(Channel* channel);
};


#endif //TINYSERVER_EVENTLOOP_H
