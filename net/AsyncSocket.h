//
// Created by DengXu on 2016/10/4.
//

#ifndef LYNETX_ASYNCSOCKET_H
#define LYNETX_ASYNCSOCKET_H

#include "Socket.h"
#include <netinet/in.h>

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

    public:
        /**
         * 初始化对应的太接字，绑定IP和PORT，同时设置套接字为异步套接字
         * @param ip 套接字对应的IP地址信息，例如127.0.0.1
         * @param isInaddrAny 当isInaddrAny=true，表示IP填任何值都无效，否则设置对应的IP地址。
         * @param port 套接字对应的PORT端口，例如8000
         * @return 返回创建的socket对象
         */
        int InitAsyncSocket(const char *ip, bool isInaddrAny, const int port) throw(BaseException);

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

        void GetSockaddrByAddress(const char *ip, const int port, struct sockaddr_in *address);
    };
}

#endif //LYNETX_ASYNCSOCKET_H
