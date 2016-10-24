//
// Created by DengXu on 2016/10/22.
//

#include <stdio.h>
#include <cstring>
#include <errno.h>
#include <sys/event.h>
#include "EpollObject.h"

using namespace std;

namespace lynetx {

    EpollObject::EpollObject():
            m_epollfd(0),
            m_timeout(-1),
            m_pTimespec(NULL)
    {
        memset(&m_epollEvent, 0, sizeof(EPOLL_EVENT));
        m_epollEvent.eventlist.reserve(1);
        m_epollEvent.nevents = 1;
        m_eventQueue.Clear();
    }

    EpollObject::~EpollObject()
    {
        m_eventQueue.SafeClose();
        m_epollfd = 0;
        m_epollEvent.eventlist.clear();
        delete_memory(m_pTimespec);
    }

    int EpollObject::EpollCreate()
    {
#ifdef __MAC_OS__
        this->m_epollfd = kqueue();
        if (-1 == m_epollfd){
            printf("call function of kqueue is error because of %s", strerror(errno));
            return -1;
        }
#elif __LINUX_OS__
        this->m_epollfd = epoll_create1(EPOLL_CLOEXEC);
        if (-1 == m_epollfd){
            printf("call function of epoll_create1 is error because of %s", strerror(errno));
            return -1;
        }
#endif
        return 0;
    }

    void EpollObject::SetEpollTimeout(const struct timespec *out)
    {
        if (NULL != out)
        {
            if (NULL == m_pTimespec)
                m_pTimespec = new struct timespec();
            m_pTimespec->tv_sec = out->tv_sec;
            m_pTimespec->tv_nsec = out->tv_nsec;
            m_timeout = m_pTimespec->tv_sec*1000+m_pTimespec->tv_nsec/1000;
        }
    }

    void EpollObject::SetEventSize(const int nevents, const int maxNevents)
    {
#ifdef __MAC_OS__
        m_epollEvent.eventlist.resize(nevents);
        m_epollEvent.nevents = nevents;
        m_epollEvent.maxNevents = maxNevents;
#elif __LINUX_OS__
        m_epollEvent.vEvent.resize(nevents);
        m_epollEvent.eventSize = nevents;
        m_epollEvent.maxNumbers = maxNevents;
#endif
    }

    int EpollObject::EpollCtl(const int eopt, const int fd, const int events)
    {
        int ret = -1;
        if (m_epollfd > 0)
        {
#ifdef __MAC_OS__
            struct kevent change;
            EV_SET(&change, fd, events, eopt, 0, 0, NULL);
            ret = kevent(m_epollfd, &change, events, NULL, 0, m_pTimespec);
            if(ret <= 0)
            {
                printf("call function of kevent is error because of %s", strerror(errno));
            }
#elif __LINUX_OS__
            m_epollEvent.event.events = events;
            m_epollEvent.event.data.fd = fd;

            ret  = epoll_ctl(m_epollfd, eopt, fd, &m_epollEvent.event);
            if(ret <= 0)
            {
                printf("call function of epoll_ctl is error because of %s", strerror(errno));
            }
            return fd;
#endif
        }
        return ret;
    }

    int EpollObject::EpollAdd(const int fd, const int events)
    {
#ifdef __MAC_OS__
        return EpollCtl(EV_ADD, fd, events);
#elif __LINUX_OS__
        return EpollCtl(EPOLL_CTL_ADD, fd, events);
#endif
    }

    int EpollObject::EpollModify(const int fd, const int events)
    {
#ifdef __MAC_OS__
        return EpollCtl(EV_ADD, fd, events);
#elif __LINUX_OS__
        return EpollCtl(EPOLL_CTL_MOD, fd, events);
#endif
    }

    int EpollObject::EpollDel(const int fd, const int events)
    {
#ifdef __MAC_OS__
        return EpollCtl(EV_DELETE, fd, events);
#elif __LINUX_OS__
        return EpollCtl(EPOLL_CTL_DEL, fd, events);
#endif
    }

    void EpollObject::EpollWait()
    {
#ifdef __MAC_OS__
        int ret = kevent(m_epollfd, NULL, 0, &m_epollEvent.eventlist[0],
                         m_epollEvent.nevents, m_pTimespec);
        if ( -1 != ret )
        {
            EventQueue eventQueue;
            eventQueue.events    = m_epollEvent.nevents;
            eventQueue.eventlist = m_epollEvent.eventlist;
            m_eventQueue.PushBack(eventQueue);
        } else {
            printf("call function of kevent is error because of %s", strerror(errno));
        }
#elif __LINUX_OS__
        int fdsize = epoll_pwait(m_epollfd, &m_epollEvent.vEvent[0],
                        m_epollEvent.eventSize, m_timeout);
        if ( -1 != fdsize )
        {
            EventQueue eventQueue;
            eventQueue.events    = m_epollEvent.vEvent;
            eventQueue.eventlist = m_epollEvent.eventSize;
            m_eventQueue.PushBack(eventQueue);
        } else {
            printf("call function of epoll_pwait is error because of %s", strerror(errno));
        }
#endif
    }
}