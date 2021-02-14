/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "../EventLoop.h"
#include "../Channel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include "../Acceptor.h"
EventLoop* g_loop = nullptr;

void test1_func(){
    std::cout<<"This thread id: "<<std::this_thread::get_id()<<std::endl;
    std::cerr<<"Loop in another will is abandon,so this will abort."<<std::endl;
    g_loop->loop();
}

void test1(){
    EventLoop loop;
    g_loop = &loop;
    std::thread t(test1_func);
    t.join();
}

void test2_func(){
    std::cout<<"This thread id: "<<std::this_thread::get_id()<<std::endl;
    EventLoop loop;
    loop.loop();
}

void test2(){
    std::cout<<"test2 thread id: "<<std::this_thread::get_id()<<std::endl;
    EventLoop loop;
    std::thread t(test2_func);
    loop.loop();
    t.join();
}


void timeout()
{
    printf("Timeout!\n");
    g_loop->quit();
}

void test3(){
    EventLoop loop;
    g_loop = &loop;

    int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    Channel channel(&loop, timerfd);
    channel.setReadCallBack(timeout);
    channel.enableReading();

    struct itimerspec howlong;
    bzero(&howlong, sizeof howlong);
    howlong.it_value.tv_sec = 5;
    ::timerfd_settime(timerfd, 0, &howlong, NULL);

    loop.loop();

    close(timerfd);
}

void run(){
    std::cout<<"thread id :"<<std::this_thread::get_id()<< " run is called "<<std::endl;
}

void thread_func_run(){
    std::cout<<"thread id :"<<std::this_thread::get_id()<<" is calling run"<<std::endl;
    g_loop->runInLoop(run);
}

void test4(){
    EventLoop loop;
    g_loop = &loop;
    std::thread thread(thread_func_run);
    loop.loop();
    thread.join();
}

void newConn(int fd,const InetAddress& addr){
    std::cout<<"accept a new connection.\n";
    write(fd,"Hello",6);
    close(fd);
}
void test5(){
    InetAddress addr(9999);
    EventLoop loop;
    Acceptor acceptor(&loop,addr);
    acceptor.setNewConnCallBack(newConn);
    acceptor.listen();

    loop.loop();
}

int main()
{
    test5();
}


