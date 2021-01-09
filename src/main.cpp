#include <vector>
#include <netinet/in.h>
#include <bits/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include "helper.h"
const int BUFSIZE = 512;


int main(int argc,char *argv[]) {
    helper help;
    std::cout<<helper::getListenedFd(argv[1]);
}
