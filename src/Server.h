#ifndef TINYSERVER_SERVER_H
#define TINYSERVER_SERVER_H

#include <netdb.h>
#include <sys/socket.h>
#include <memory>

class Server {
public:
    Server(char port_a):port(port_a){

    }
    void Start();
private:
    char port;
    int listenfd;
};


#endif //TINYSERVER_SERVER_H
