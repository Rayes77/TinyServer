#include <iostream>
#include <signal.h>
#include "Server.h"

int main(){
    std::cout<<"Starting service"<<std::endl;
    //signal(SIGSEGV,SIG_IGN);
    char *buf;
    const int MAXLINE = 1024;
    Server s;
    char *p = "8080";
    s.bind_and_listen(p);
    while (true){
        int connfd = s.accept();
        close(connfd);
        std::cout<<"a client has been closed!"<<std::endl;
    }
}
