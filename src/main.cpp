#include <iostream>
#include <signal.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "Server.h"



int main(){
    int listenfd,connfd;
    socklen_t len;
    sockaddr_in serverAddr,clientAddr;
    char buf[1024];
    time_t ticks;

    listenfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&serverAddr,sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(13);

    bind(listenfd,(sockaddr *)&serverAddr,sizeof(serverAddr));
    listen(listenfd,1024);

    for(;;){
        len = sizeof(clientAddr);
        connfd = accept(listenfd,(sockaddr *)&clientAddr,&len);
        printf("connection from %s,port %d\n",
               inet_ntop(AF_INET,&clientAddr.sin_addr,buf,sizeof(buf)),
               ntohs(clientAddr.sin_port));
        ticks = time(NULL);
        snprintf(buf,sizeof(buf),".24s\r\n",ctime(&ticks));
        write(connfd,buf,sizeof(buf));
        close(connfd);
    }

}
