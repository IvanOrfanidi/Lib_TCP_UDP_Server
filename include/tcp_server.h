#pragma once

#include <vector>

#if defined(__unix__)
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include "vserver.h"

namespace tcp_udp_server {

class TCP_Server : public VServer {
public:
    TCP_Server();
    ~TCP_Server();

    /**
     * @brief Construct a new tcp server::tcp server object
     * @param addr - IP address
     * @param port port - TCP port
     */
    TCP_Server(const char* addr, uint16_t port);

    /**
     * @brief Set IP address
     * @param addr - IP address
     */
    virtual void setAddress(const char* addr) override;

    /**
     * @brief Set TCP port
     * @param port - TCP port
     */
    virtual void setPort(uint16_t port) override;

    /** Listen socket */
    void listen() const;

    /**
     * @brief Create cocket
     * @param sock - cocket number, output param
     */
    virtual int create(int sock) const override;

    /** Start TCP server */
    virtual void start() override;

    /** Stop server, socket close */
    virtual void stop() const override;

    /**
     * @brief Send data
     * @param data - data vector
     */
    virtual void send(const std::vector<char>& data) override;

    /**
     * @brief Receive data
     * @param data - data vector, output param
     * @param length - max data length
     */
    virtual void receive(std::vector<char>& data, const size_t length) override;

    /** Accept socket */
    virtual void accept() override;

    /**
     * @brief Get socket
     * @return int socket
     */
    int getSocket() const override;

    /**
     * @brief Get socket client
     * @return int socket client
     */
    int getSocketClient() const override;

private:
    int _socket; //< socket number
    int _socketClient; //< socket number client
    struct sockaddr_in _local;
};
}