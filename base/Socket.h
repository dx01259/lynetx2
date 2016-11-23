//
// Created by DengXu on 2016/10/2.
//

#ifndef LYNETX_SOCKET_H
#define LYNETX_SOCKET_H

#include "BaseException.h"
#include "BServerPkg.h"
#include <sys/socket.h>

namespace lynetx {

    const int SOCK_MAX_CONN = 128;

    class Socket{

    public:
        /**
         * 函数结构体，用来初始化对应的套接字，默认的是创建SOCK_STREAM的AF_INET4的通信套接字
         * @return
         */
        Socket();

        /**
         * 指定对应的family,type,protocol创建对应的socket
         * @param family 协议族，例如AF_INET，AF_INET6，AF_LOCAL，AF_ROUTE，AF_KEY
         * @param type 套接字类型，SOCK_STREAM，SOCK_DGRAM，SOCK_SEQPACKET，SOCK_RAW
         * @param protocol 协议类型，IPPROTO_TCP，IPPROTO_UDP，IPPROTO_SCTP
         * @return
         */
        Socket(int family, int type, int protocol);

        virtual ~Socket();

        /**
         * 初始化对应的太接字，绑定IP和PORT
         * @param ip 套接字对应的IP地址信息，例如127.0.0.1
         * @param isInaddrAny 当isInaddrAny=true，表示IP填任何值都无效，否则设置对应的IP地址。
         * @param port 套接字对应的PORT端口，例如8000
         * @return 返回创建的socket对象
         */
        virtual int InitSocket(const char *ip, bool isInaddrAny, const int port) throw(BaseException);

        /**
         * 监听套接字，只是简单的封装了下listen函数
         * @param backlog 已经完成队列的最大个数
         * @return 成功返回0，失败返回-1
         */
        virtual int Listen(int backlog) throw(BaseException);

        /**
         * 连接服务器
         * @param sockaddr 服务器的地址信息
         * @param length 服务器的地址长度
         * @return
         */
        virtual int Connect(const struct sockaddr *sockaddr, socklen_t length) throw(BaseException);

        /**
         * 三次握手之后，从完成队列中获取建立链接的套接字
         * @param address 建立连接的套接字地址
         * @param length 建立连接的套接字地址的长度
         * @return 成功返回建立连接的套接字ID，失败返回-1
         */
        virtual int Accept(struct sockaddr *address, socklen_t *length) throw(BaseException);

        /**
         * 接收套接字发送过来的数据，包括任何其他协议类型的数据。例如TCP数据和UDP数据
         * @param bServerPkg 接收的数据包对象，保存数据体等相关信息。
         * @param flags 此参数可以通过man recv查看对应的介绍。
         * @return 成功返回接收的数据的长度，失败返回-1，并且设置了errno变量的值。
         */
        virtual ssize_t RecvPacket(BServerPkg *bServerPkg, int flags, struct sockaddr *address) throw(BaseException);

        /**
         * 发送套接字数据，包括发送的套接字对象和其他类型的数据，例如TCP数据和UDP数据
         * @param bServerPkg 需要发送的数据包对象，保存数据体等相关信息。
         * @param flags 此参数可以通过man send查看对应的介绍。
         * @return 成功返回发送的数据长度，失败返回-1，并且设置了errno变量的值。
         */
        virtual ssize_t SendPacket(const BServerPkg *bServerPkg, int flags, const struct sockaddr *address) throw(BaseException);

        /**
         * 关闭创建的套接字
         * @return 成功返回true，失败返回false，并且设置errno
         */
        virtual bool CloseSocket();

    protected:
        int m_socketfd;//套接字对象，用于发送数据
        int m_type;    //套接字的类型，例如SOCK_STREAM
        int m_family;  //套接字协议类型，例如AF_INET
        int m_protocol;//套接字协议类型，例如IPPROTO_TCP
    };
}

#endif //LYNETX_SOCKET_H
