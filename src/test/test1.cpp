/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/

#include "../EventLoop.h"
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

int main(){
    //test1();
    //test2();
}

