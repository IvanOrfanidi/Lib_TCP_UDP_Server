#pragma once

#include <string>
#include <vector>

#if defined(_WIN32)
#define _WINSOCK_DEPRECATED_NO_WARNINGS // disable warnings
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#if defined(__unix__)
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace tcp_udp_server {
namespace error_message {
    const std::string CREATE = "server socket not create";
    const std::string BIND = "server socket bind failed";
    const std::string LISTEN = "server socket listening failed";
    const std::string ACCEPT = "server socket accepting failed";
    const std::string SEND = "server socket sending data failed";
    const std::string RECEIVE = "server socket receve data failed";
}

class VServer {
public:
    static constexpr int INVAL_SOCKET = -1;

    VServer();
    virtual ~VServer();

    VServer(const VServer&) = delete;
    VServer& operator=(const VServer&) = delete;

    /**
     * @brief Set IP address
     * @param addr - IP address
     */
    virtual void setAddress(const char* addr) = 0;

    /**
     * @brief Set TCP port
     * @param port - TCP port
     */
    virtual void setPort(uint16_t port) = 0;

    /**
     * @brief Create cocket
     * @param sock - cocket number, output param
     */
    virtual int create(int sock) const = 0;

    /** Start TCP server */
    virtual void start() = 0;

    /** Stop server, socket close */
    virtual void stop() const = 0;

    /**
     * @brief Send data
     * @param data - data vector
     */
    virtual void send(const std::vector<char>& data) = 0;

    /**
     * @brief Receive data
     * @param data - data vector, output param
     * @param length - max data length
     */
    virtual void receive(std::vector<char>& data, const size_t length) = 0;

    /** Accept socket */
    virtual void accept() = 0;

    /**
     * @brief Get socket
     * @return int socket
     */
    virtual int getSocket() const = 0;

    /**
     * @brief Get socket client
     * @return int socket client
     */
    virtual int getSocketClient() const = 0;

protected:
    /**
     * @brief Close socket
     * @param sock - socket
     */
    void close(int sock) const;

    /**
     * @brief Binding cocket
     * @param sock - socket
     * @param local - socket local address
     */
    void bind(int sock, sockaddr_in& local) const;

#if defined(_WIN32)
    static int _countServers;
#endif
};
}