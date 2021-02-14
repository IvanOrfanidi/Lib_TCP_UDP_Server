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
    virtual ~TCP_Server();

    /**
     * @brief Construct a new tcp server::tcp server object
     * @param addr - IP address
     * @param port port - TCP port
     */
    explicit TCP_Server(const char* addr, uint16_t port);

    /**
     * @brief Set IP address
     * @param addr - IP address
     */
    virtual void setAddress(const char* addr) override;

    /**
     * @brief Get the IP Address
     * @return std::string IP address
     */
    virtual std::string getAddress() const override;

    /**
     * @brief Set TCP port
     * @param port - TCP port
     */
    virtual void setPort(uint16_t port) override;

    /**
     * @brief Get the TCP Port
     * @return uint16_t TCP Port
     */
    virtual uint16_t getPort() const override;

    /** Listen socket */
    void listenSocket() const;

    /**
     * @brief Create socket
     * @param sock - socket number, output param
     */
    virtual int createSocket(int sock) const override;

    /** Start TCP server */
    virtual void start() override;

    /** Stop TCP server, socket close */
    virtual void stop() const override;

    /**
     * @brief Send data
     * @param data - data vector
     */
    virtual void sendData(const std::vector<char>& data) override;

    /**
     * @brief Receive data
     * @param data - data vector, output param
     * @param length - max data length
     */
    virtual void receiveData(std::vector<char>& data, const size_t length) override;

    /** Accept socket */
    void acceptSocket();

    /**
     * @brief Get socket
     * @return int socket
     */
    int getSocket() const override;

private:
    int _socket; //< socket number
    int _socketClient; //< socket number client
    struct sockaddr_in _local;
};

}