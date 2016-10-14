//
// Created by DengXu on 2016/10/13.
//

#ifndef LYNETX_MUTEX_H
#define LYNETX_MUTEX_H

#include <pthread.h>

namespace lynetx{

    class Mutex
    {
    public:
        Mutex();
        virtual ~Mutex();

    public:
        int lock();
        int unlock();
        int trylock();
        bool islocked();

    private:
        bool volatile m_locked;
        pthread_mutex_t m_mutex;
    };

    template <class T>
    class AutoGuard
    {
    public:
        AutoGuard(T &mutex):
                m_mutex(mutex)
        {
            m_mutex.lock();
        }

        ~AutoGuard(void)
        {
            m_mutex.unlock();
        }

    protected:
        T &m_mutex;
    };

#ifndef THREAD_MUTEX
#define THREAD_MUTEX Mutex
#endif

//自动锁定义
//guard：CAutoGuard的局部变量名称
//mutex: 锁的类型
//mtx：   锁的对象
#ifndef AUTO_GUARD
#define AUTO_GUARD(guard, mutex, mtx)\
	AutoGuard<mutex> guard(mtx)
#endif
}

#endif //LYNETX_MUTEX_H
