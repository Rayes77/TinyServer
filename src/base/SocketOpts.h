/*
* @author:MutexCat
* @date  :2021/2/14
* @github:https://github.com/MutexCat
* @description:
*
*/

#ifndef TINYSERVER_SOCKETOPTS_H
#define TINYSERVER_SOCKETOPTS_H
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <endian.h>
#include <cstdlib>

inline uint64_t hostToNetwork64(uint64_t host64)
{
    return htobe64(host64);
}

inline uint32_t hostToNetwork32(uint32_t host32)
{
    return htonl(host32);
}

inline uint16_t hostToNetwork16(uint16_t host16)
{
    return htons(host16);
}

inline uint64_t networkToHost64(uint64_t net64)
{
    return be64toh(net64);
}

inline uint32_t networkToHost32(uint32_t net32)
{
    return ntohl(net32);
}

inline uint16_t networkToHost16(uint16_t net16)
{
    return ntohs(net16);
}

int createNonblockingOrDie();
void bindOrDie(int fd,const struct sockaddr_in& addr);
void listenOrDie(int sockfd);
int  accept(int sockfd, struct sockaddr_in* addr);
int close(int sockfd);

void toHostPort(char* buf, size_t size,
                const struct sockaddr_in& addr);
void fromHostPort(const char* ip, uint16_t port,
                  struct sockaddr_in* addr);
#endif //TINYSERVER_SOCKETOPTS_H
