//
// Created by rayes on 2020/12/10.
//

#include "utils.h"

size_t rio_t::rio_read(std::vector<char> &usrbuf, size_t nbyte) {
    int nread = 0;
    int cnt = nbyte;
    while (buf.empty()){//refill the empty buf
        if ((nread = read(fd,buf.begin(),MAXLINE)) < 0){
            if (errno == EINTR){
                nread = 0;
            }else{
                return -1;
            }
        }else if (nread == 0){//EOF
            return 0;
        }else{
            bufptr = buf.begin();
            rio_cnt = nread;
        }
    }
    if (buf.size() < cnt){
        cnt = buf.size();
    }
    for (int i = 0; i < cnt; ++i) {
        usrbuf.push_back(*bufptr++);
    }
    rio_cnt -= cnt;
    return cnt;
}

size_t rio_t::rio_write(std::vector<char> &usrbuf) {
    int nleft = usrbuf.size();
    int nwritten = 0;
    while (nleft > 0){
        if (nwritten = write(fd,usrbuf.data(),nleft) <= 0){
            if (errno != EINTR)
                return -1;
            else
                nwritten = 0;
        }
        nleft -= nwritten;
        nwritten = 0;
    }
    return usrbuf.size();
}

size_t  rio_t::rio_readline(std::vector<char> &usrbuf,int maxlen) {
    std::vector<char> vec_temp;
    auto ptr = bufptr;
    int nread;

    for (int i = 0; i < maxlen; ++i) {
        if ((nread = rio_read(vec_temp,1)) == 1){
            //
        }
    }
    *vec_temp.end() = 0;
    std::copy(vec_temp.begin(),vec_temp.end(),usrbuf.begin());
    return nread;
}
