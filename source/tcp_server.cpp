#include <cassert>
#include <stdexcept>

#include <include/tcp_server.h>

namespace tcp_udp_server {

/**
 * @brief Construct a new tcp server::tcp server object
 */
TCP_Server::TCP_Server()
    : _socket(INVAL_SOCKET)
    , _socketClient(INVAL_SOCKET)
{
    _local.sin_family = AF_INET;
}

/**
 * @brief Construct a new tcp server::tcp server object
 * @param addr - IP address
 * @param port port - TCP port
 */
TCP_Server::TCP_Server(const char* addr, uint16_t port)
    : TCP_Server()
{
    assert(addr != nullptr);
    assert(port != 0);
    _local.sin_addr.s_addr = inet_addr(addr);
    _local.sin_port = htons(port);
}

/**
 * @brief Destroy the tcp server::tcp server object
 */
TCP_Server::~TCP_Server()
{
    TCP_Server::stop();
}

/**
 * @brief Set IP address
 * @param addr - IP address
 */
void TCP_Server::setAddress(const char* addr)
{
    assert(addr != nullptr);
    _local.sin_addr.s_addr = inet_addr(addr);
}

/**
 * @brief Get the IP Address
 * @return std::string IP address
 */
std::string TCP_Server::getAddress() const
{
    return inet_ntoa(_local.sin_addr);
}

/**
 * @brief Set TCP port
 * @param port - TCP port
 */
void TCP_Server::setPort(uint16_t port)
{
    assert(port != 0);
    _local.sin_port = htons(port);
}

/**
 * @brief Get TCP port
 * @return port - TCP port
 */
uint16_t TCP_Server::getPort() const
{
    return ntohs(_local.sin_port);
}

/**
 * @brief Listen socket
 */
void TCP_Server::listenSocket() const
{
    assert(_socket != INVAL_SOCKET);
    constexpr int QUEUE_LENGTH = 5;
    const auto res = listen(_socket, QUEUE_LENGTH);
    if (res < 0) {
        throw std::runtime_error(error_message::LISTEN);
    }
}

/**
 * @brief Create socket
 * @param sock - socket number, output param
 */
int TCP_Server::createSocket(int sock) const
{
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        throw std::runtime_error(error_message::CREATE);
    }
    return sock;
}

/**
 * @brief Start server
 */
void TCP_Server::start()
{
    try {
        _socket = createSocket(_socket);
    } catch (...) {
        throw std::current_exception();
    }

    try {
        VServer::bindSocket(_socket, _local);
    } catch (...) {
        throw std::current_exception();
    }

    try {
        listenSocket();
    } catch (...) {
        throw std::current_exception();
    }
}

/**
 * @brief Stop server, socket close
 */
void TCP_Server::stop() const
{
    shutdown(_socket, 1);
    closeSocket(_socket);
}

/**
 * @brief Send data
 * @param data - data vector
 */
void TCP_Server::sendData(const std::vector<char>& data)
{
    assert(_socketClient != INVAL_SOCKET);
    const auto res = sendto(_socketClient, data.data(), data.size(), 0, (struct sockaddr*)&_local, sizeof(struct sockaddr_in));
    if (res < 1) {
        throw std::runtime_error(error_message::SEND);
    }
}

/**
 * @brief Receive data
 * @param data - data vector, output param
 * @param length - max data length
 */
void TCP_Server::receiveData(std::vector<char>& data, const size_t length)
{
    assert(_socketClient != INVAL_SOCKET);
    while (true) {
        const auto len = recv(_socketClient, data.data(), length, 0);
        if (len < 0) {
            if (errno == EINTR) {
                continue;
            }
            break;
        } else if (0 == len) {
            break;
        } else {
            data.resize(len);
            return;
        }
    }

    throw std::runtime_error(error_message::RECEIVE);
}

/**
 * @brief Accept socket
 */
void TCP_Server::acceptSocket()
{
    // Get client socket descriptor
    assert(_socket != INVAL_SOCKET);
    _socketClient = accept(_socket, NULL, NULL);
    if (_socketClient < 0) {
        throw std::runtime_error(error_message::ACCEPT);
    }
}

/**
 * @brief Get socket
 * @return int socket
 */
int TCP_Server::getSocket() const
{
    return _socket;
}

}
