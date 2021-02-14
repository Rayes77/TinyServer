/*
* @author:MutexCat
* @date  :2021/2/14
* @github:https://github.com/MutexCat
* @description:
*
*/


#ifndef TINYSERVER_INETADDR_H
#define TINYSERVER_INETADDR_H

#include <cstdint>
#include <string>
#include <netinet/in.h>
/**
 * Coped from muduo.
 **/
class InetAddress {
public:
    /// Constructs an endpoint with given port number.
    /// Mostly used in TcpServer listening.
    explicit InetAddress(uint16_t port);

    /// Constructs an endpoint with given ip and port.
    /// @c ip should be "1.2.3.4"
    InetAddress(const std::string &ip, uint16_t port);

    /// Constructs an endpoint with given struct @c sockaddr_in
    /// Mostly used when accepting new connections
    InetAddress(const struct sockaddr_in &addr)
            : addr_(addr) {}

    std::string toHostPort() const;

    // default copy/assignment are Okay

    const struct sockaddr_in &getSockAddrInet() const { return addr_; }

    void setSockAddrInet(const struct sockaddr_in &addr) { addr_ = addr; }

private:
    struct sockaddr_in addr_;
};


#endif //TINYSERVER_INETADDR_H
