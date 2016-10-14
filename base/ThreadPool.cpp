//
// Created by DengXu on 2016/10/10.
//

#include "ThreadPool.h"
#include "Timeout.h"

namespace lynetx {

    ThreadPool::ThreadPool(const int corePoolSize,
                           const int maxmunPoolSize,
                           unsigned long keepAliveTime,
                           void *object,
                           pthread_func callFunc)
    {
        this->m_corePoolSize = corePoolSize;
        this->m_maxmunPoolSize = maxmunPoolSize;
        for (int i = 0; i < corePoolSize; ++i)
        {
            boost::shared_ptr<ThreadObject> threadObject = ThreadFactory::Instance()->CreateThreadObject(
                    object, callFunc, keepAliveTime, WAITING, ThreadPool::process, this);
            this->m_ThreadPool.set(threadObject->id, threadObject);
        }
    }

    ThreadPool::~ThreadPool()
    { }

    void *ThreadPool::process(void *param)
    {
        ThreadPool *pool = (ThreadPool *)param;
        Timeout out(1000*60);//设置10秒超长时间
        out.Start();//开始计时
        cleanup_push_thread(ThreadPool::clear, pool);
        while (pool)
        {
            pthread_t id = pthread_self();
            boost::shared_ptr<ThreadObject> threadObject;
            if (0 != pool->m_ThreadPool.find(id, threadObject))
            {
                //添加此if判断是因为，线程在调用的时候，无法保证是主线程还是
                //子线程先运行，所以就无法保证线程池对象中已经保存子线程对象
                sleep(1);   //单位是秒
                if (out.IsTimeout()) break;
            }
            else
            {
                if (threadObject->callFunc)
                {
                    //以回调函数的形式，调用指定的函数。
                    threadObject->callFunc(threadObject->object);
                }
            }
        }
        cleanup_pop_thread(1);

        return 0;
    }

    void ThreadPool::clear(void *param)
    {
        ThreadPool *pool = (ThreadPool *)param;
        if (pool)
        {
            map<pthread_t, boost::shared_ptr<ThreadObject> >::iterator iter;
            pool->m_ThreadPool.remove(pthread_self());
        }
    }
}
