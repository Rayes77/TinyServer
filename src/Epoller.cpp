/*
* @author:MutexCat
* @date  :2021/2/2
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "Epoller.h"
#include "Channel.h"
int Epoller::wait(std::vector<Channel *> &) {
    return 0;
}

void Epoller::updateChannel(Channel *channel) {
    int index =channel->getIndex();
    if (index < 0){

    }else{

    }
}
