/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/

#ifndef TINYSERVER_EPOLLER_H
#define TINYSERVER_EPOLLER_H
#include <sys/epoll.h>
#include <memory>
#include <vector>
#include <map>

class Channel;
class EventLoop;

class Epoller {
public:
    void loop(std::vector<Channel*> &activeChannel,int& error);

    void updateChannel(Channel* channel);

    Epoller(EventLoop* loop);

private:
    int epfd_;
    EventLoop* loop_;

    std::map<int,Channel*> channels_;
    std::vector<epoll_event> resultEvent_;

};


#endif //TINYSERVER_EPOLLER_H
