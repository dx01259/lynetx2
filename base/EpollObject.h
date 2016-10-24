//
// Created by DengXu on 2016/10/22.
// 此类是非多线程安全的
//

#ifndef LYNETX_EPOLLOBJECT_H
#define LYNETX_EPOLLOBJECT_H

#include <vector>
#include <sys/event.h>
#include "Timeout.h"
#include "config.h"
#include "define.h"
#include "MsgDeque.h"

#ifdef __LINUX_OS__
#include <sys/epoll.h>
#endif

using namespace std;

namespace lynetx {

    typedef struct EPOLL_EVENT
    {
#ifdef __MAC_OS__
        struct kevent           changelist;
        int                     nchanges;
        vector<struct kevent>   eventlist;
        int                     nevents;
        size_t                  maxNevents;
#elif __LINUX_OS__
        epoll_event     event;
        vector<epoll_event> vEvent;
        size_t          eventSize;
        size_t          maxNumbers;
        __sigset_t      siget;
#endif
    }EpollEvent;

    typedef struct EVENT_QUEUE
    {
        int events;
#ifdef __MAC_OS__
        vector<struct kevent> eventlist;
#elif __LINUX_OS__
        vector<struct epoll_event> eventlist;
#endif
    }EventQueue;

    class EpollObject
    {
    public:
        EpollObject();
        virtual ~EpollObject();

    public:
        /**
         * 创建事件监听文件描述符
         * @return 成功返回0，失败返回-1
         */
        int EpollCreate();

        /**
         * 设置EPOLL事件的超时等待时间
         * @param out 等待超时时间，0立刻返回，NULL一直等待
         */
        void SetEpollTimeout(const struct timespec *out);

        /**
         * 设置需要监听的文件描述符个数和能被监听的最大个数
         * @param nevents 需要被监听的文件描述符个数
         * @param maxNevents 能够被监听的文件描述符最大个数
         */
        void SetEventSize(const int nevents, const int maxNevents);

        /**
         * 将文件描述符添加，更新，删除等操作到监听文件描述符中
         * @param eopt 要进行到操作选项MAC系统包括EV_ADD，EV_DELETE，EV_ENABEL，EV_DISABLE，
         *             linux系统包括EPOLL_CTL_ADD，EPOLL_CTL_MOD，EPOLL_CTL_DEL
         * @param fd 需要被监听的文件描述符
         * @param events 表示事件的监听类型，Linux系统取值 EPOLLIN，EPOLLET等
         *               MAC系统取EVFILT_READ，EVFILT_WRITE等
         * @return 成功返回被监听的文件描述符，失败返回-1
         */
        int EpollCtl(const int eopt, const int fd, const int events);

        /**
         * 将文件描述符添加到监听文件描述符中
         * @param fd 需要被监听的文件描述符
         * @param events 表示事件的监听类型，Linux系统取值 EPOLLIN，EPOLLET等
         *               MAC系统取EVFILT_READ，EVFILT_WRITE等
         * @return 成功返回被监听的文件描述符，失败返回-1
         */
        int EpollAdd(const int fd, const int events);

        /**
         * 修改被监听的文件描述符的监听事件
         * @param fd 需要被监听的文件描述符
         * @param events 表示事件的监听类型，Linux系统取值 EPOLLIN，EPOLLET等
         *               MAC系统取EVFILT_READ，EVFILT_WRITE等
         * @return 成功返回被监听的文件描述符，失败返回-1
         */
        int EpollModify(const int fd, const int events);

        /**
         * 删除被监听的文件描述符
         * @param fd 需要被监听的文件描述符
         * @param events 表示事件的监听类型，Linux系统取值 EPOLLIN，EPOLLET等
         *               MAC系统取EVFILT_READ，EVFILT_WRITE等
         * @return 成功返回被监听的文件描述符，失败返回-1
         */
        int EpollDel(const int fd, const int events);

        /**
         * 等待监听事件是否有事件发生
         */
        void EpollWait();

    protected:
        virtual void *HanderEvent(void *parameter);
    protected:
        int         m_epollfd;
        int         m_timeout;
        struct timespec *m_pTimespec;
        EPOLL_EVENT m_epollEvent;
        MsgDeque<EventQueue> m_eventQueue;
    };
}
#endif //LYNETX_EPOLLOBJECT_H
