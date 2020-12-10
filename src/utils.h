//
// Created by rayes on 2020/12/10.
//

#ifndef TINYSERVER_UTILS_H
#define TINYSERVER_UTILS_H

#include <array>
#include <vector>
#include <unistd.h>
#include <errno.h>
#include <algorithm>
class rio_t{
public:
    static const int MAXLINE = 8196;

    rio_t(int fd_):fd(fd_){}
    rio_t(const rio_t&) = delete;
    rio_t& operator=(const rio_t&) = delete;

    int rio_cnt = 0;
    std::array<char,MAXLINE>::iterator bufptr = buf.begin();

    ~rio_t(){}
private:
    int fd;
    std::array<char,MAXLINE> buf;
public:
    //read from internal buf.
    //if the buf is empty then refill it.
    size_t rio_read(std::vector<char> &usrbuf,size_t nbyte);
    size_t rio_write(std::vector<char> &usrbuf);
    size_t rio_readline(std::vector<char> &usrbuf,int maxlen);
};

class utils {
public:

private:

};


#endif //TINYSERVER_UTILS_H
