//
// Created by DengXu on 2016/10/10.
//

#ifndef LYNETX_THREADPOOL_H
#define LYNETX_THREADPOOL_H

#include <pthread.h>
#include "TMap.h"
#include "ThreadFactory.h"

using namespace std;

namespace lynetx {

    class ThreadPool
    {
    public:
        /**
         * 初始化线程池，执行线程调用回调函数
         * @param corePoolSize 核心线程池大小，小于maxmunPoolSize的值
         * @param maxmunPoolSize 最大线程数
         * @param keepAliveTime 线程保存有效的等待时间
         * @param object 给线程传送的对象句柄，赋值给callFunc参数
         * @param callFunc 线程的回调函数
         * @return
         */
        ThreadPool(const int corePoolSize,
                   const int maxmunPoolSize,
                   unsigned long keepAliveTime,
                   void       *object,
                   pthread_func callFunc);

        virtual ~ThreadPool();

    protected:
        /**
         * 创建线程池，调用的函数，主要是用来监控所有线程的状态
         * 以及控制线程运行和垃圾的清理工作。
         * @param param 默认传输的是this指针
         * @return
         */
        static void *process(void *param);

        /**
         * 线程退出后，自动调用，释放资源
         * @param param 默认创送的是This指针
         */
        static void  clear(void *param);

    protected:
        TMap<pthread_t, boost::shared_ptr<ThreadObject> > m_ThreadPool;
        pthread_attr_t m_attr;
        short m_corePoolSize;
        short m_maxmunPoolSize;
    };
}

#endif //LYNETX_THREADPOOL_H
