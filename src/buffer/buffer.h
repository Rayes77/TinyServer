/*
* @author:MutexCat
* @date  :2021/1/25
* @github:https://github.com/MutexCat
* @description:
*
*/

#ifndef TINYSERVER_BUFFER_H
#define TINYSERVER_BUFFER_H

#include <vector>
#include <atomic>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>

class buffer {
private:
    std::vector<char> m_buffer;
    std::atomic<size_t> readPos;
    std::atomic<size_t> writePos;

    decltype(auto) getWritePos();
    decltype(auto) bufferBegin();
    decltype(auto) writable();
    decltype(auto) readable();
    decltype(auto) writablePos();
public:
    size_t readFd(int fd);
    size_t writeFd(int fd);
};


#endif //TINYSERVER_BUFFER_H
