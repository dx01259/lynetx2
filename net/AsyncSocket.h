//
// Created by DengXu on 2016/10/4.
//

#ifndef LYNETX_ASYNCSOCKET_H
#define LYNETX_ASYNCSOCKET_H

#include "Socket.h"

namespace lynetx {

    /**
     * class AsyncSocket 类主要是异步类，用来进行socket通信
     */
    class AsyncSocket : public Socket
    {
    public:
        /**
         * 初始化异步套接字对象
         * @return
         */
        AsyncSocket();

        /**
         * 初始化异步套接字对象
         * @param family 协议族，例如AF_INET，AF_INET6，AF_LOCAL，AF_ROUTE，AF_KEY
         * @param type 套接字类型，SOCK_STREAM，SOCK_DGRAM，SOCK_SEQPACKET，SOCK_RAW
         * @param protocol 协议类型，IPPROTO_TCP，IPPROTO_UDP，IPPROTO_SCTP
         * @return
         */
        AsyncSocket(int family, int type, int protocol);

        virtual ~AsyncSocket();

        /**
         * 将套接字设置为异步的
         * @return 设置成功返回套接字FD，失败返回-1，并且设置errno参数
         */
        int SetAsyncSocket();

        /**
         * 获取套接字对象FD
         * @return 返回套接字对象FD
         */
        inline int GetAsyncSocket(){ return this->m_socketfd; }
    };
}

#endif //LYNETX_ASYNCSOCKET_H
