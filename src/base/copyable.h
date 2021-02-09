/*
* @author:MutexCat
* @date  :2021/2/9
* @github:https://github.com/MutexCat
* @description:
*
*/


#ifndef TINYSERVER_COPYABLE_H
#define TINYSERVER_COPYABLE_H

class copyable {
public:
    copyable() = default;
    ~copyable() = default;
    copyable(const copyable&) = default;
    copyable& operator =(const copyable&) = default;
private:
};

#endif //TINYSERVER_COPYABLE_H
