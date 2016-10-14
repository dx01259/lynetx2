//
// Created by DengXu on 2016/10/13.
//

#include "Mutex.h"
#include "define.h"

namespace lynetx{

    Mutex::Mutex()
    {
        m_locked = false;
        check_zero(pthread_mutex_init(&m_mutex, NULL));
    }

    Mutex::~Mutex()
    {
        m_locked = false;
        pthread_mutex_destroy(&m_mutex);
    }

    int Mutex::lock()
    {
        m_locked = true;
        int ret = pthread_mutex_lock(&m_mutex);
        if(0 != ret)
            m_locked = false;
        return ret;
    }

    int Mutex::unlock()
    {
        int ret = 0;
        ret = pthread_mutex_unlock(&m_mutex);
        if(ret == 0)
            m_locked = false;
        return ret;
    }

    int Mutex::trylock()
    {
        int ret = 0;
        ret = pthread_mutex_trylock(&m_mutex);
        if(ret == 0)
            m_locked = true;
        return ret;
    }

    bool Mutex::islocked()
    {
        return this->m_locked;
    }
}