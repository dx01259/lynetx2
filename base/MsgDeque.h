//
// Created by DengXu on 2016/10/23.
//

#ifndef LYNETX_MSGDEQUE_H
#define LYNETX_MSGDEQUE_H

#include "Mutex.h"
#include "Timeout.h"
#include "BaseTime.h"
#include "config.h"
#include <semaphore.h>
#include <errno.h>
#include <deque>
#include <string>

using namespace std;

namespace lynetx {

    template<class V, class MUTEX=THREAD_MUTEX>
    class MsgDeque
    {
    public:
        MsgDeque(const size_t maxSize=50000):
                m_pNotEmpty(NULL),
                m_pNotFull(NULL)
        {
            m_bAbort  = false;
            m_bsNotep = false;
            m_bsNotfl = false;
            ResetInit(maxSize);
        }
        virtual ~MsgDeque()
        {
            AbortWait();
            SafeClose();
        }
    public:
        size_t ResetInit(size_t maxSize)
        {
            AUTO_GUARD(g, MUTEX, this->m_mutex);

            maxSize = maxSize>SEM_VALUE_MAX ? SEM_VALUE_MAX-1:maxSize;
            if(this->m_bAbort)
            {
                this->m_bAbort = false;
                SafeClose();
            }
            BaseTime baseTime;
            baseTime.SetCurrentTime();
            m_semNotEmptyName = baseTime.ToString()+"_NotEmpty";
            m_semNotFullName  = baseTime.ToString()+"_NotFull";

            m_pNotEmpty = sem_open(m_semNotEmptyName.c_str(), O_CREAT);
            m_pNotFull = sem_open(m_semNotFullName.c_str(), O_CREAT);

            return (m_pNotEmpty && m_pNotFull) ?
                   this->m_bsNotep=true,this->m_bsNotfl=true,
                   m_maxSize = maxSize : 0;
        }

        inline void SetMaxQueueSize(size_t maxSize)
        {
            AUTO_GUARD(g, MUTEX, this->m_mutex);

            maxSize = maxSize>SEM_VALUE_MAX ? SEM_VALUE_MAX-1:maxSize;
            m_maxSize = maxSize;
        }

        inline void SafeClose()
        {
            AUTO_GUARD(g, MUTEX, this->m_mutex);

            if(!this->m_bsNotep &&
               !this->m_bsNotfl)
            {
                sem_close(m_pNotEmpty);
                sem_close(m_pNotFull);
                sem_unlink(m_semNotEmptyName.c_str());
                sem_unlink(m_semNotFullName.c_str());
                m_bsNotep = false;
                m_bsNotfl = false;
            }
        }

        inline void AbortWait()
        {
            AUTO_GUARD(g, MUTEX, this->m_mutex);

            this->m_bAbort = true;
            sem_post(this->m_pNotEmpty);
            sem_post(this->m_pNotFull);
        }

        inline bool isFull(int offset=0)
        {
            return (m_deque.size()+offset) >= m_maxSize ? 1:0;
        }

        inline bool isEmpty()
        {
            return m_deque.empty();
        }

        inline bool isAbort()
        {
            return this->m_bAbort;
        }

        void Swap(MsgDeque &other)
        {
            AUTO_GUARD(g, MUTEX, this->m_mutex);

            m_deque.swap(other.m_deque);
        }

        bool Front(V &data, u_long out=0)
        {
            if(this->WaitforNotEmpty(out))
            {
                AUTO_GUARD(g, MUTEX, this->m_mutex);
                if(m_deque.size()>0)
                {
                    data = m_deque.front();
                    return true;
                }
                return false;
            }
            if(this->m_bAbort)
            {
                return false;
            }
            return false;
        }

        bool PopFront(V &data, u_long out=0)
        {
            if(!this->isAbort())
            {
                if(this->WaitforNotEmpty(out))
                {
                    AUTO_GUARD(g, MUTEX, this->m_mutex);
                    if(m_deque.size()>0)
                    {
                        data = m_deque.front();
                        m_deque.pop_front();
                        sem_post(this->m_pNotFull);
                        return true;
                    }
                    return false;
                }
            }
            else
            {
                AUTO_GUARD(g, MUTEX, this->m_mutex);
                if(!this->isEmpty())
                {
                    data = m_deque.front();
                    m_deque.pop_front();
                    return true;
                }
                return false;
            }
            return false;
        }

        bool PushFront(const V &data, u_long out=0)
        {
            if(!this->isAbort())
            {
                if(this->WaitforNotFull(out))
                {
                    AUTO_GUARD(g, MUTEX, this->m_mutex);
                    if(!this->isFull())
                    {
                        m_deque.push_front(data);
                        sem_post(this->m_pNotEmpty);
                        return true;
                    }
                }
            }
            return false;
        }

        bool Back(V &data, u_long out=0)
        {
            if(this->WaitforNotEmpty(out))
            {
                AUTO_GUARD(g, MUTEX, this->m_mutex);
                data = m_deque.back();
                return true;
            }
            if(this->m_bAbort)
            {
                return false;
            }
            return false;
        }

        bool PopBack(V &data, u_long out=0)
        {
            if(!this->isAbort())
            {
                if(this->WaitforNotEmpty(out))
                {
                    AUTO_GUARD(g, MUTEX, this->m_mutex);
                    data = m_deque.back();
                    m_deque.pop_back();
                    sem_post(this->m_pNotFull);
                    return true;
                }
            }
            else
            {
                AUTO_GUARD(g, MUTEX, this->m_mutex);
                if(!m_deque.empty())
                {
                    data = m_deque.back();
                    m_deque.pop_back();
                    return true;
                }
                return false;
            }
            return false;
        }

        bool PushBack(const V &data)
        {
            if(!this->isAbort())
            {
                AUTO_GUARD(g, MUTEX, this->m_mutex);
                if(!this->isFull())
                {
                    m_deque.push_back(data);
                    sem_post(this->m_pNotEmpty);
                    return true;
                }
            }
            return false;
        }

        bool Insert(typename std::deque<V>::const_iterator where, V *first, V *last)
        {
            if(!this->isAbort())
            {
                AUTO_GUARD(g, MUTEX, this->m_mutex);
                int offset = last-first;
                if(offset<0) offset=-offset;
                if(!this->isFull(offset))
                {
                    m_deque.insert(where, first, last);
                    sem_post(this->m_pNotEmpty);
                    return true;
                }
            }
            return false;
        }

        inline size_t Size()
        {
            //AUTO_GUARD(g, MUTEX, this->m_mutex);

            return m_deque.size();
        }

        void Clear()
        {
            //AUTO_GUARD(g, MUTEX, this->m_mutex);

            AbortWait();
            SafeClose();
            m_deque.clear();
        }

    protected:
        bool WaitforNotEmpty(u_long out = 0)
        {
            Timeout cnt;
            cnt.Init(out);
            while(!this->m_bAbort && this->m_bsNotep)
            {
                int ret = 0;
                u_long w = cnt.Timeleft();
                switch(out)
                {
                    case -1:
                        ret = sem_wait(this->m_pNotEmpty);
                        break;
                    default:
#ifdef __MAC_OS__
                        ret = sem_wait(this->m_pNotEmpty);
#elif __LINUX_OS__
                        struct timespec tim;
                        cnt.SetTimespecLeftNow(tim, w);
                        ret = sem_timedwait(this->m_pNotEmpty, &tim);
#endif
                        break;
                }
                if(0 == ret && !this->m_bAbort)
                {
                    return true;
                }
                else if(EINTR == errno)
                {
                    continue;
                }
                else{
                    return false;
                }
            }
            return false;
        }

        bool WaitforNotFull(u_long out = 0)
        {
            Timeout cnt;
            cnt.Init(out);
            while(!this->m_bAbort && this->m_bsNotfl)
            {
                int ret = 0;
                u_long w = cnt.Timeleft();
                switch(out)
                {
                    case -1:
                        ret = sem_wait(this->m_pNotEmpty);
                        break;
                    default:
#ifdef __MAC_OS__
                        ret = sem_wait(this->m_pNotEmpty);
#elif __LINUX_OS__
                    struct timespec tim;
                        cnt.SetTimespecLeftNow(tim, w);
                        ret = sem_timedwait(this->m_pNotEmpty, &tim);
#endif
                        break;
                }
                if(0 == ret && !this->m_bAbort)
                {
                    return true;
                }
                else if(EINTR == errno)
                {
                    continue;
                }
                else{
                    return false;
                }
            }
            return false;
        }

    private:
        string m_semNotEmptyName;
        string m_semNotFullName;
        bool m_bAbort;
        MUTEX m_mutex;
        deque<V>  m_deque;
        sem_t *m_pNotEmpty;
        sem_t *m_pNotFull;
        bool  m_bsNotep;
        bool  m_bsNotfl;
        size_t m_maxSize;
    };
}
#endif //LYNETX_MSGDEQUE_H
