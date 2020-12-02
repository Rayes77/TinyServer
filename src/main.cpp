#include <iostream>
#include <netdb.h>
#include <sys/socket.h>

using SA = sockaddr;

int main(){
    int sock_fd;
    sock_fd = socket(AF_INET,SOCK_STREAM,0);

}
