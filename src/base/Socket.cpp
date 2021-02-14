/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "Socket.h"

#include "InetAddr.h"
#include "SocketOpts.h"

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <strings.h>  // bzero


Socket::~Socket()
{
    ::close(sockfd_);
}

void Socket::bindAddress(const InetAddress& addr)
{
    ::bindOrDie(sockfd_, addr.getSockAddrInet());
}

void Socket::listen()
{
    ::listenOrDie(sockfd_);
}

int Socket::accept(InetAddress* peeraddr)
{
    struct sockaddr_in addr;
    bzero(&addr, sizeof addr);
    int connfd = ::accept(sockfd_, &addr);
    if (connfd >= 0)
    {
        peeraddr->setSockAddrInet(addr);
    }
    return connfd;
}

void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR,
                 &optval, sizeof optval);
    // FIXME CHECK
}
