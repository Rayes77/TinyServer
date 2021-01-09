#ifndef TINYSERVER_HELPER_H
#define TINYSERVER_HELPER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
class helper {
public:
    static int getListenedFd(char *port);
private:
};


#endif //TINYSERVER_HELPER_H
