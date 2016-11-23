//
// Created by DengXu on 02/11/2016.
//

#ifndef LYNETX_TCPCLIENT_H
#define LYNETX_TCPCLIENT_H

#include "AsyncSocket.h"

using namespace lynetx;

class TcpClient
{
public:
    TcpClient()
    {
        m_asyncSocket.InitAsyncSocket("127.0.0.1", false, 8000);
    }
    virtual ~TcpClient()
    {
        m_asyncSocket.CloseSocket();
    }

public:

    bool Connect(const char *ip, const int port)
    {
        struct sockaddr_in address;
        m_asyncSocket.GetSockaddrByAddress(ip, port, &address);
        m_asyncSocket.Connect((sockaddr *)&address, sizeof(address));
    }

protected:
    AsyncSocket m_asyncSocket;
};

#endif //LYNETX_TCPCLIENT_H
