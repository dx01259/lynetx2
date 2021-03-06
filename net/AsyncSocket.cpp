//
// Created by DengXu on 2016/10/4.
//

#include "AsyncSocket.h"
#include "config.h"
#include <fcntl.h>
#include <assert.h>
#include <arpa/inet.h>

namespace lynetx {

    AsyncSocket::AsyncSocket():Socket()
    {

    }

    AsyncSocket::AsyncSocket(int family, int type, int protocol) : Socket(family, type, protocol)
    {
    }

    AsyncSocket::~AsyncSocket()
    {

    }

    int AsyncSocket::SetAsyncSocket()
    {
        int flags = fcntl(this->m_socketfd, F_GETFL, 0);
        if (-1 != flags)
        {
#ifdef __MAC_OS__
            flags |= O_NONBLOCK;
#elif __LINUX_OS__
            flags |= SOCK_NONBLOCK;
#endif
            flags = fcntl(this->m_socketfd, F_SETFL, flags);
            assert(-1 != flags);
            return this->m_socketfd;
        }
        return flags;
    }

    int AsyncSocket::InitAsyncSocket(const char *ip, bool isInaddrAny, const int port) throw(BaseException)
    {
        return  Socket::InitSocket(ip, isInaddrAny, port), SetAsyncSocket();
    }

    void AsyncSocket::GetSockaddrByAddress(const char *ip, const int port, struct sockaddr_in *address)
    {
        if (NULL != ip && NULL != address)
        {
            bzero(address, sizeof(struct sockaddr_in));
            address->sin_family = this->m_family;
            address->sin_port   = htons(port);
            inet_pton(this->m_family, ip, &address->sin_addr.s_addr);
        }
    }
}