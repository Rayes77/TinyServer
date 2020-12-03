#ifndef TINYSERVER_SERVER_H
#define TINYSERVER_SERVER_H
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

class Server{
public:
    Server()= default;
    int bind_and_listen(char *port);
    int accept();
    void echo();
private:
    int listenfd;
    const int LISTNQ = 1024;
};

#endif //TINYSERVER_SERVER_H
