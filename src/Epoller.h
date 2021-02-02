/*
* @author:MutexCat
* @date  :2021/2/2
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
class Epoller {
private:
    std::vector<struct epoll_event> fds_;
    std::map<int,Channel*> channelMap_;

public:
    int wait(std::vector<Channel*>&);

    void updateChannel(Channel*);
};


#endif //TINYSERVER_EPOLLER_H
