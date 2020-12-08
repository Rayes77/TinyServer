#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>

char *sock_ntop(const sockaddr_storage* sa,socklen_t len){
    char port[8];
    char addrtemp[128];

    switch (sa->ss_family) {
        case AF_INET:{
            sockaddr_in* addr = (sockaddr_in *)sa;
            if (inet_ntop(AF_INET,&addr->sin_addr,addrtemp,sizeof(addrtemp)) == NULL){
                return NULL;
            }
            if (ntohs(addr->sin_port) != 0){
                snprintf(port,sizeof(port),":%d",ntohs(addr->sin_port));
            }
            strcat(addrtemp,port);
            return addrtemp;
        }
        case AF_INET6:{
            sockaddr_in6* addr = (sockaddr_in6 *)sa;
            if (inet_ntop(AF_INET6,&addr->sin6_addr,addrtemp,sizeof(addrtemp)) == NULL){
                return NULL;
            }
            if (ntohs(addr->sin6_port) != 0){
                snprintf(port,sizeof(port),":%d",ntohs(addr->sin6_port));
            }
            strcat(addrtemp,port);
            return addrtemp;
        }
    }
}

size_t rio_readn(int fd,char *buf,size_t nbytes){
    size_t nleft = nbytes;
    int nread = 0;
    char *vptr = buf;

    while (nleft > 0){
        if ((nread = read(fd,vptr,nleft)) < 0){
            if (errno == EINTR)
                nread = 0;
            else
                return -1;
        }else if (nread = 0){
            break;
        }
        nleft -= nread;
        nread = 0;
    }

    return nbytes - nleft;
}

size_t rio_writen(int fd,char *buf,size_t nbytes){
    int nwritten = 0;
    size_t nleft = nbytes;
    char *vptr = buf;

    while (nleft > 0){
        if ((nwritten = write(fd,vptr,nleft)) < 0){
            if (errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        nwritten = 0;
    }

    return nbytes;
}

const int RIO_BUFSIZE = 8192;
using rio_t = struct {
    int fd;
    int rio_cnt;
    char *rio_bufptr;
    char rio_buf[RIO_BUFSIZE];
};

void rio_initb(rio_t *rio,int fd){
    rio->fd = fd;
    rio->rio_cnt = 0;
    rio->rio_bufptr = rio->rio_buf;
}

size_t rio_read(rio_t *rio,char *usrbuf,size_t nbytes){
    int cnt;
    while (rio->rio_cnt <= 0){//internal buf is empty,refill.
        if ((rio->rio_cnt = read(rio->fd,rio->rio_buf,RIO_BUFSIZE)) < 0){
            if (errno != EINTR)
                return -1;
        }else if (rio->rio_cnt == 0){
            return 0;
        }else
            rio->rio_bufptr = rio->rio_buf;
    }
    cnt = nbytes;
    if (rio->rio_cnt < nbytes){
        cnt = rio->rio_cnt;
    }
    memcpy(usrbuf,rio->rio_bufptr,cnt);
    rio->rio_bufptr += cnt;
    rio->rio_cnt -= cnt;
    return cnt;
}

size_t rio_readlineb(rio_t *rio,char *usrbuf,size_t maxlen){
    char c;
    size_t nread = 0,rc;
    char *ptr = usrbuf;

    for (int i = 0; i < maxlen; ++i) {
        if ((rc = rio_read(rio,&c,1)) == 1){
            *ptr++ = c;
            nread++;
            if (c == '\n'){
                return nread;
            }
        } else if (rc == 0){
            if (i == 0)
                return 0;
            else
                break;
        }else
            return -1;
    }

    *ptr = 0;
    return nread;
}

size_t rio_readnb(rio_t *rio,char *buf,size_t nbytes){
    int nread;
    int nleft = nbytes;
    char *vptr = buf;

    while (nleft > 0){
        if ((nread = rio_read(rio,buf,nleft)) < 0){
            return -1;
        }else if (nread == 0){
            break;
        }else {
            nleft -= nread;
            vptr += nread;
            nread = 0;
        }
    }
    return nbytes - nleft;
}

void Listen(int fd,int backlog){
    char *ptr;

    if ((ptr = getenv("LISTEN")) != NULL)
        backlog = atoi(ptr);
    listen(fd,backlog);
}
