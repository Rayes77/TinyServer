/*
* @author:MutexCat
* @date  :2021/1/19
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "server.h"

bool server::getListenFd() {
    if (m_port > 65535 || m_port < 1024){
        return false;
    }
    int reuse = 1;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(m_port);

    if ((m_listenFd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        return false;
    }

    setsockopt(m_listenFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));

    if (bind(m_listenFd,(struct sockaddr*)&address,sizeof(address)) < 0){
        close(m_listenFd);
        return false;
    }

    if (listen(m_listenFd,1024) < 0){
        close(m_listenFd);
        return false;
    }
    return true;
}

// TODO:read conf file.
// TODO:init event pool.
server::server(int port_,int threadNum,int timeout ,int maxevent):m_port(port_)
                ,m_maxTimeout(timeout),m_maxEvent(maxevent),m_maxThreadNum(threadNum) {
    if (!getListenFd()){
        std::cout<<"getListenFd error"<<std::endl;
        std::terminate();
    }
    m_epoll = std::make_shared<epoller>(m_maxTimeout,m_maxEvent);
    m_threadPoll = std::make_shared<threadpool>(m_maxThreadNum);

}

void server::start() {
    std::cout<<"Server Started!"<<std::endl;

    //event loop
    while (!isStop){
        int number = m_epoll->wait();
        for (int i = 0; i < number; ++i) {
            auto retEvent = m_epoll->getResultEvent(i);
            if (retEvent.m_fd == m_listenFd && retEvent.m_event & EPOLLIN){
                //new connection
            }else if(retEvent.m_event && EPOLLIN){
                //read
            }else if(retEvent.m_event && EPOLLOUT){
                //write
            }else if (retEvent.m_event & (EPOLLHUP | EPOLLERR | EPOLLRDHUP) ){
                //close
            }else{
                //default
            }
        }
    }
}
