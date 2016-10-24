//
// Created by DengXu on 2016/10/2.
//

#include "Socket.h"
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <assert.h>
#include <limits.h>

namespace lynetx {

    Socket::Socket()
    {
        this->m_family   = AF_INET;
        this->m_type     = SOCK_STREAM;
        this->m_protocol = IPPROTO_TCP;
    }

    Socket::Socket(int family, int type, int protocol)
    {
        this->m_family = family;
        this->m_type = type;
        this->m_protocol = protocol;
    }

    int Socket::InitSocket(const char *ip, bool isInaddrAny, const int port) throw(BaseException)
    {
        int sockfd = socket(this->m_family, this->m_type, this->m_protocol);
        if (-1 == sockfd){
            throw BaseException(strerror(errno));
        }
        this->m_socketfd = sockfd;
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = this->m_family;
        addr.sin_port   = htons(port);
        if (isInaddrAny)
        {
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
        } else{
            assert(inet_pton(this->m_family, ip, &addr.sin_addr.s_addr) != -1);
        }

        socklen_t socklen = sizeof(sockaddr);

        if (-1 == bind(this->m_socketfd, (struct sockaddr *)&addr, socklen)) {
            throw BaseException(strerror(errno));
        }
        return this->m_socketfd;
    }

    int Socket::Listen(int backlog)
    {
        int ret = listen(this->m_socketfd, backlog);
        if(-1 == ret){
            throw BaseException(strerror(errno));
        }
        return 0;
    }

    int Socket::Accept(struct sockaddr *address, socklen_t *length)
    {
        int sockfd = accept(this->m_socketfd, address, length);
        if (-1 == sockfd){
            throw BaseException(strerror(errno));
        }
        return sockfd;
    }

    ssize_t Socket::RecvPacket(BServerPkg *bServerPkg, int flags,
                               struct sockaddr *address) throw(BaseException)
    {
        ssize_t recvlen = 0;
        if (NULL != bServerPkg)
        {
            switch (this->m_type)
            {
                case SOCK_DGRAM:
                    {
                        socklen_t socklen = sizeof(sockaddr);
                        recvlen = recvfrom(this->m_socketfd, bServerPkg->GetPackageData(),
                                           bServerPkg->GetPackageLength(), flags, address, &socklen);
                    }
                    break;
                case SOCK_STREAM:
                    {
                        recvlen = recv(this->m_socketfd, bServerPkg->GetPackageData(),
                                       bServerPkg->GetPackageLength(), flags);
                    }
                    break;
                default:
                    break;
            }
            if ( -1 == recvlen && errno != EAGAIN && errno != EWOULDBLOCK && errno != EISDIR && errno != ECONNABORTED)
            {
                throw BaseException(strerror(errno));
            }
        }
        return recvlen;
    }

    ssize_t Socket::SendPacket(const BServerPkg *bServerPkg, int flags,
                               const struct sockaddr *address) throw(BaseException)
    {
        ssize_t sendlen = 0;
        if (NULL != bServerPkg)
        {
            switch (this->m_type)
            {
                case SOCK_DGRAM:
                    {
                        socklen_t socklen = sizeof(sockaddr);
                        sendlen = sendto(this->m_socketfd, bServerPkg->GetPackageData(),
                                         bServerPkg->GetPackageLength(), flags, address, sendlen);
                    }
                    break;
                case SOCK_STREAM:
                    {
                        sendlen = send(this->m_socketfd, bServerPkg->GetPackageData(),
                                       bServerPkg->GetPackageLength(), flags);
                    }
                    break;
                default:
                    break;
            }
            if ( -1 == sendlen && errno != EAGAIN && errno != EWOULDBLOCK && errno != EISDIR && errno != ECONNABORTED)
            {
                throw BaseException(strerror(errno));
            }
        }
        return sendlen;
    }

    bool Socket::CloseSocket()
    {
        if (this->m_socketfd >=0 && close(this->m_socketfd)>0)
        {
            return true;
        }

        return false;
    }
}