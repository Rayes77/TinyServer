/*
* @author:MutexCat
* @date  :2021/1/25
* @github:https://github.com/MutexCat
* @description:
*
*/


#include "buffer.h"

decltype(auto) buffer::bufferBegin() {
    return &*m_buffer.begin();
}

decltype(auto) buffer::writable() {
    return m_buffer.size() - writePos;
}

decltype(auto) buffer::readable() {
    return writePos - readPos;
}

decltype(auto) buffer::writablePos() {
    return bufferBegin() + writePos;
}

size_t buffer::readFd(int fd) {
    char buff[65535];
    iovec iv[2];
    size_t writableNum = writable();

    iv[0].iov_base =bufferBegin() + writePos;
    iv[0].iov_len = writableNum;
    iv[1].iov_base = buff;
    iv[1].iov_len = sizeof(buff);

    size_t len = readv(fd,iv,2);
    if (len < 0 ){
        //error handling
    }else if (len < writableNum){
        writePos += len;
    } else if (len > writableNum){
        size_t len2 = len-writableNum;
        m_buffer.resize(m_buffer.size() + len2 + 1);
        std::copy(buff,buff+len2,writablePos());
        writePos += len;
    }
    return len;
}

size_t buffer::writeFd(int fd) {
    size_t readNum = readable();
    int ret = write(fd,bufferBegin(),readNum);
    if (ret < 0){

    }
    readPos += ret;
    return ret;
}





