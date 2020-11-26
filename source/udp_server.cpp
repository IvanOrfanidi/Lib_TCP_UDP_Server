#include <cassert>
#include <stdexcept>

#include <include/udp_server.h>

namespace tcp_udp_server {

/**
 * @brief Construct a new udp server::udp server object
 */
UDP_Server::UDP_Server()
    : _socket(INVAL_SOCKET)
    , _socketClient(INVAL_SOCKET)
{
    _local.sin_family = AF_INET;
}

/**
 * @brief Destroy the udp server::udp server object
 */
UDP_Server::~UDP_Server()
{
    UDP_Server::stop();
}

/**
 * @brief Construct a new udp server::udp server object
 * @param addr - IP address
 * @param port port - UDP port
 */
UDP_Server::UDP_Server(const char* addr, uint16_t port)
    : UDP_Server()
{
    assert(addr != nullptr);
    assert(port != 0);
    _local.sin_addr.s_addr = ::inet_addr(addr);
    _local.sin_port = ::htons(port);
}

/**
 * @brief Set IP address
 * @param addr - IP address
 */
void UDP_Server::setAddress(const char* addr)
{
    assert(addr != nullptr);
    _local.sin_addr.s_addr = ::inet_addr(addr);
}

/**
 * @brief Set UDP port
 * @param port - UDP port
 */
void UDP_Server::setPort(uint16_t port)
{
    assert(port != 0);
    _local.sin_port = ::htons(port);
}

/**
 * @brief Create cocket
 * @param sock - cocket number, output param
 */
int UDP_Server::create(int sock) const
{
    assert(sock != INVAL_SOCKET);
    sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        throw std::runtime_error(error_message::CREATE);
    }
    return sock;
}

/**
 * @brief Start server
 */
void UDP_Server::start()
{
    try {
        _socket = this->create(_socket);
    } catch (...) {
        throw std::current_exception();
    }

    try {
        VServer::bind(_socket, _local);
    } catch (...) {
        throw std::current_exception();
    }
}

/**
 * @brief Stop server, socket close
 */
void UDP_Server::stop() const
{
    ::shutdown(_socket, 1);
    close(_socket);
}

/**
 * @brief Send data
 * @param data - data vector
 */
void UDP_Server::send(const std::vector<char>& data)
{
    assert(_socketClient != INVAL_SOCKET);
    const auto res = ::sendto(_socketClient, data.data(), data.size(), 0, (struct sockaddr*)&_local, sizeof(struct sockaddr_in));
    if (res <= 0) {
        throw std::runtime_error(error_message::SEND);
    }
}

/**
 * @brief Receive data
 * @param data - data vector, output param
 * @param length - max data length
 */
void UDP_Server::receive(std::vector<char>& data, const size_t length)
{
    assert(_socketClient != INVAL_SOCKET);
    const int addrClientLen = sizeof(_local);
    const auto len = ::recvfrom(_socketClient, data.data(), length, 0, (struct sockaddr*)&_local, (socklen_t*)addrClientLen);
    if (len < 0) {
        throw std::runtime_error(error_message::RECEIVE);
    }
    data.resize(len);
}

/**
 * @brief Get socket
 * @return int socket
 */
int UDP_Server::getSocket() const
{
    return _socket;
}

/**
 * @brief Get socket client
 * @return int socket client
 */
int UDP_Server::getSocketClient() const
{
    return _socketClient;
}

}