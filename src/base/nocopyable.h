/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/


#ifndef TINYSERVER_NOCOPYABLE_H
#define TINYSERVER_NOCOPYABLE_H


class nocopyable {
public:
    nocopyable() = default;
    ~nocopyable() = default;
    nocopyable(const nocopyable&) = delete;
    nocopyable& operator =(const nocopyable&) = delete;
private:
};


#endif //TINYSERVER_NOCOPYABLE_H
