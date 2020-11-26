#include <cassert>
#include <stdexcept>

#include <include/vserver.h>

namespace tcp_udp_server {

#if defined(_WIN32)
int VServer::_countServers = 0;
#endif

VServer::VServer()
{
#if defined(_WIN32)
    if (_countServers <= 0) {
        WSADATA wsaData;
        ::WSAStartup(MAKEWORD(2, 2), &wsaData);
    }

    _countServers++;
#endif
}

VServer::~VServer()
{
#if defined(_WIN32)
    _countServers--;
    if (_countServers <= 0) {
        ::WSACleanup();
    }
#endif
}

/**
 * @brief Close socket
 * @param sock - socket
 */
void VServer::close(int sock) const
{
    assert(sock != INVAL_SOCKET);
#if defined(_WIN32)
    ::closesocket(sock);
#endif

#if defined(__unix__)
    ::close(sock);
#endif
}

/**
 * @brief Binding cocket
 * @param sock - socket
 * @param local - socket local address
 */
void VServer::bind(int sock, struct sockaddr_in& local) const
{
    assert(sock != INVAL_SOCKET);
    const auto res = ::bind(sock, (struct sockaddr*)&local, sizeof(local));
    if (res < 0) {
        throw std::runtime_error(error_message::BIND);
    }
}
}