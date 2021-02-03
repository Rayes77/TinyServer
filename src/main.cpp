/*
* @author:MutexCat
* @date  :2021/2/2
* @github:https://github.com/MutexCat
* @description:
*
*/
#include "EventLoop.h"

void test1Func(){
    std::cout<<"Thread id :"<<std::this_thread::get_id()<<" in test1\n";
    EventLoop loop;
    loop.loop();
}

void test1(){
    std::cout<<"Thread id :"<<std::this_thread::get_id()<<" in main\n";
    EventLoop loop;
    std::thread t(test1Func);
    loop.loop();
    t.join();
}


int main(){
    test1();
}