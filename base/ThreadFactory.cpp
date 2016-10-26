//
// Created by DengXu on 2016/10/12.
//

#include "ThreadFactory.h"
#include "define.h"

namespace lynetx {

    ThreadFactory::ThreadFactory()
    {
        check_zero(pthread_attr_init(&m_attr));
        check_zero(pthread_attr_setscope(&m_attr, PTHREAD_SCOPE_SYSTEM));
        check_zero(pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_DETACHED));
    }

    ThreadFactory::~ThreadFactory()
    {
        pthread_attr_destroy(&m_attr);
    }

    boost::shared_ptr<THREAD_OBJECT> ThreadFactory::CreateThreadObject(
            void *object, pthread_func callFunc, Timeout keepAliveTime,
            THREAD_STATUS status, pthread_func pthreadFunc, void *param)
    {
        boost::shared_ptr<ThreadObject> threadObject = boost::make_shared<ThreadObject>();
        threadObject->object   = object;
        threadObject->callFunc = callFunc;
        threadObject->status   = status;
        threadObject->keepAliveTime = keepAliveTime;
        pthread_create(&threadObject->id, &this->m_attr, pthreadFunc, param);

        return threadObject;
    }

    bool ThreadFactory::DestroyThreadObject(const ThreadObject *object, const useconds_t us)
    {
        if (object)
        {
            if(object->status != RUNNING)
            {
                pthread_cancel(object->id);
            } else {
                usleep(us);
                pthread_cancel(object->id);
            }
        }
        return false;
    }
}