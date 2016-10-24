//
// Created by DengXu on 2016/10/10.
//

#ifndef LYNETX_EPOLLSERVICE_H
#define LYNETX_EPOLLSERVICE_H

#include <sys/types.h>
#include <sys/time.h>
#include "AsyncSocket.h"
#include "ThreadFactory.h"
#include "EpollObject.h"

namespace lynetx {

    class EpollService :
            public EpollObject
    {
    public:
        EpollService();

        EpollService(const AsyncSocket sock, const EpollEvent epollEvent);

    public:
        void SetEpollEvent(const EpollEvent epollEvent);
        void SetAsyncSocket(const AsyncSocket sock);
        bool Start(const char *ip, const short port, pthread_func callFunc);
        bool Stop();

    protected:
        void *HanderEvent(void *parameter);
    private:
        bool        m_isStarted;
        AsyncSocket m_AsyncSocket;
        EpollEvent  m_EpollEvent;
    };
}


#endif //LYNETX_EPOLLSERVICE_H
