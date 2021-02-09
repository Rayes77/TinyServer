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
    void loop(std::vector<std::shared_ptr<Channel>>& activeChannel,int& error);

    void addToEpoll(std::shared_ptr<Channel> channel);
    void modifyEpoll(std::shared_ptr<Channel> channel);
    void updateChannel(std::shared_ptr<Channel> channel);
private:
    int epfd_;
    std::shared_ptr<EventLoop> loop_;

    std::map<int,std::shared_ptr<Channel>> channels_;
    std::vector<epoll_event> resultEvent_;

    Epoller(EventLoop* loop);
};


#endif //TINYSERVER_EPOLLER_H
