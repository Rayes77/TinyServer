/*
* @author:MutexCat
* @date  :2021/2/14
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "SocketOpts.h"

int createNonblockingOrDie(){
    int sockfd = ::socket(AF_INET,SOCK_STREAM|SOCK_NONBLOCK|SOCK_CLOEXEC,0);
    if (sockfd < 0){
        std::cerr<<"createNonblockingOrDie error\n";
        std::abort();
    }
    return sockfd;
}

void bindOrDie(int fd,const struct sockaddr_in& addr){
    int ret = ::bind(fd,(struct sockaddr*)&addr,sizeof(addr));
    if (ret < 0){
        std::cerr<<"bindOrDie error\n";
        std::abort();
    }
}

void listenOrDie(int sockfd){
    int ret = ::listen(sockfd,4096);
    if (ret < 0){
        std::cerr<<"listen error\n";
        std::abort();
    }
}

int accept(int sockfd, struct sockaddr_in* addr)
{
    socklen_t addrlen = sizeof *addr;
    int connfd = ::accept4(sockfd, (struct sockaddr*)&addr,
                           &addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (connfd < 0)
    {
        int savedErrno = errno;

        switch (savedErrno)
        {
            case EAGAIN:
            case ECONNABORTED:
            case EINTR:
            case EPROTO: // ???
            case EPERM:
            case EMFILE: // per-process lmit of open file desctiptor ???
                // expected errors
                errno = savedErrno;
                break;
            case EBADF:
            case EFAULT:
            case EINVAL:
            case ENFILE:
            case ENOBUFS:
            case ENOMEM:
            case ENOTSOCK:
            case EOPNOTSUPP:
                // unexpected errors
                std::cerr<<"unexpected error of ::accept \n";
                break;
            default:
                std::cerr<<"unknown error of ::accept \n";
                break;
        }
    }
    return connfd;
}

int close(int sockfd)
{
    int ret = ::close(sockfd);
    if (ret < 0){
        std::cerr<<"close error \n";
        std::abort();
    }
}

void toHostPort(char* buf, size_t size,
                         const struct sockaddr_in& addr)
{
    char host[INET_ADDRSTRLEN] = "INVALID";
    ::inet_ntop(AF_INET, &addr.sin_addr, host, sizeof host);
    uint16_t port = networkToHost16(addr.sin_port);
    snprintf(buf, size, "%s:%u", host, port);
}

void fromHostPort(const char* ip, uint16_t port,
                           struct sockaddr_in* addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = hostToNetwork16(port);
    if (::inet_pton(AF_INET, ip, &addr->sin_addr) <= 0)
    {
        std::cerr<<"sockets::fromHostPort\n";
    }
}
