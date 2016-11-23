//
// Created by DengXu on 2016/10/10.
//

#ifndef LYNETX_EPOLLSERVICE_H
#define LYNETX_EPOLLSERVICE_H

#include <sys/types.h>
#include <sys/time.h>
#include "AsyncSocket.h"
#include "ThreadPool.h"
#include "EpollObject.h"

namespace lynetx {

    class EpollService :
            public EpollObject
    {
    public:
        EpollService();

        EpollService(const AsyncSocket sock);

        virtual ~EpollService();

    public:
        /**
         * 创建基于EPOLL的多线程网络服务器套接字
         * @param ip 指定服务器的IP地址
         * @param port 指定服务器的端口
         * @param corePoolSize 指定服务器核心线程数
         * @param maxmunPoolSize 指定服务器最大线程数
         * @param keepAliveTime 指定线程空闲保持的最大空闲时间
         * @return 成功返回true，否则返回false
         */
        bool Start(const char *ip, const short port, const int corePoolSize,
                   const int maxmunPoolSize,const Timeout keepAliveTime);

        /**
         * 停止系统服务器，回收系统资源
         * @return
         */
        bool Stop();

        /**
         * 当有数据到来时，接收数据
         * @param data 从网卡接收到的数据包
         * @param length 数据包的长度
         * @return 返回读取的数据包长短
         */
        size_t Receive(unsigned char *data, size_t length);

        /**
         * 发送数据包到网卡
         * @param data 需要发送的数据
         * @param length 需要发送的数据的长度
         * @return 成功发送的数据长度
         */
        size_t Send(const unsigned char *data, const size_t length);

    protected:
        static void *CallFunc(void *parameter);
        void *HandleEvent(void *parameter);
    private:
        bool        m_isStarted;
        AsyncSocket m_AsyncSocket;
        boost::shared_ptr<ThreadPoolHandle> m_pThreadPoolHandle;
    };
}


#endif //LYNETX_EPOLLSERVICE_H
