/*
* @author:MutexCat
* @date  :2021/2/3
* @github:https://github.com/MutexCat
* @description:
*
*/

#ifndef TINYSERVER_POLLER_H
#define TINYSERVER_POLLER_H
#include <vector>
#include <map>

struct pollfd;
class Timestamp{};
class Channel;
class EventLoop;
class Poller {
using ChannelList = std::vector<Channel*>;
private:
    EventLoop* ownerLoop_;
    std::vector<struct pollfd> pollfds_;
    std::map<int,Channel*> channels_;

    void fillActiveChannels_(int numEvents,ChannelList& activeChannels)const;
public:

    Poller(EventLoop* loop):ownerLoop_(loop){};
    ~Poller(){}


    Timestamp poll(int timeousMS,ChannelList& activeChannels);

    void updateChannel(Channel* channel);

    void assertInLoopThread(){}
};


#endif //TINYSERVER_POLLER_H
