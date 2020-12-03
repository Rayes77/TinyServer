#include "Server.h"

ssize_t Readline(int sockd, char *vptr, size_t maxlen) {
    ssize_t n, rc;
    char    c, *buffer;

    buffer = vptr;

    for ( n = 1; n < maxlen; n++ ) {

        if ( (rc = read(sockd, &c, 1)) == 1 ) {
            *buffer++ = c;
            if ( c == '\n' )
                break;
        }
        else if ( rc == 0 ) {
            if ( n == 1 )
                return 0;
            else
                break;
        }
        else {
            if ( errno == EINTR )
                continue;
            return -1;
        }
    }

    *buffer = 0;
    return n;
}

int Server::bind_and_listen(char *port) {
    std::cout<<"bind_and_listen start"<<std::endl;
    addrinfo *listp,*p;
    addrinfo hint;
    int optval = 1;

    memset(&hint,0,sizeof(addrinfo));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hint.ai_flags |= AI_NUMERICSERV;

    if ((getaddrinfo(NULL,port,&hint,&listp)) != NULL){
        fprintf(stderr,"get addr erro\nr");
        return -1;
    }

    for(p = listp;p != NULL;p = p->ai_next){
        if ((listenfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol) < 0)){
            //close(listenfd);
            continue;
        }
        /* Eliminates "Address already in use" error from bind */
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,    //line:netp:csapp:setsockopt
                   (const void *)&optval , sizeof(int));

        if ((bind(listenfd,p->ai_addr,p->ai_addrlen)) == 0){
            break;
        }
        close(listenfd);
    }

    if (!p){
        std::cout<<"p errpr"<<std::endl;
        return -1;
    }
    if (listen(listenfd,LISTNQ) < 0){
        std::cout<<"listen error";
        return -1;
    }
    std::cout<<"bind_and_listen start"<<std::endl;
    return listenfd;
}

int Server::accept() {
    char *buf;
    int connedfd = ::accept(listenfd,NULL,NULL);
    int n = Readline(connedfd,buf,1024);
    write(connedfd,buf,n);
    //close(connedfd);
    return connedfd;
}
