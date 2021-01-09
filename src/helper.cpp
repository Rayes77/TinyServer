//
// Created by rayes on 2021/1/9.
//

#include "helper.h"

int helper::getListenedFd(char *port) {
    int listenfd,optval = 1;
    struct addrinfo hints,*result,*list;

    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_flags |= AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;
    int rc;
    if ((rc = getaddrinfo(NULL,port,&hints,&result)) != 0){
        std::cout<<"---ERROR: ";
        std::cout<<gai_strerror(rc)<<std::endl;
    }
    char buf[INET_ADDRSTRLEN];
    std::cout<<"start for loop"<<std::endl;
    for(list = result;list;list = list->ai_next){
        if ((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
            continue;
        }
        inet_ntop(AF_INET,list->ai_addr,buf,INET_ADDRSTRLEN);
        std::cout<<buf<<std::endl;
        /*
        if ((connect(listenfd,list->ai_addr,list->ai_addrlen)) != -1){
            break;
        }
        */
        setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval ));

        if (bind(listenfd,list->ai_addr,list->ai_addrlen) != -1){
            std::cout<<"bind success"<<std::endl;
            break;
        }
        close(listenfd);
    }

    freeaddrinfo(result);
    if (!list){
        std::cout<<"list is empty\n";
        return -1;
    }

    if (listen(listenfd,1024) < 0){
        close(listenfd);
        return -1;
    }
    std::cout<<std::endl;
    return listenfd;
}