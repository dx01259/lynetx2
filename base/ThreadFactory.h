//
// Created by DengXu on 2016/10/12.
//

#ifndef LYNETX_THREADFACTORY_H
#define LYNETX_THREADFACTORY_H

#include <pthread.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Timeout.h"

namespace lynetx {

    typedef void * (*pthread_func)(void *);//函数指针

    enum THREAD_STATUS{WAITING/*线程处于等待状态*/, RUNNING/*线程处于允许状态*/, STOPPED/*线程处于停止运行状态*/,
        HANGUP/*线程处于挂起状态*/, EXITED/*线程处于退出状态*/};

#ifdef pthread_cleanup_push_defer_np
#define cleanup_push_thread(clean_fun, arg) \
    pthread_cleanup_push_defer_np(clean_fun, arg)
#define cleanup_pop_thread pthread_cleanup_pop_restore_np
#else
#define cleanup_push_thread(clean_fun, arg)\
do{\
	if(clean_fun)\
	{\
		int oldtype, ret;\
		ret = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &oldtype);\
		if(0 == ret)\
		{\
			pthread_cleanup_push(clean_fun, arg)

#define cleanup_pop_thread(execute)\
			pthread_cleanup_pop(execute);\
			pthread_setcanceltype(oldtype, NULL);\
		}\
	}\
}while(0)
#endif

    /**
     * ThreadOjbect 线程结构体，主要是包含
     * 对象指针和需要的回调函数
     */
    typedef struct THREAD_OBJECT
    {
        pthread_t id;				//线程的ID
        void *object;				//传递给线程调用函数的句柄
        pthread_func callFunc;		//线程的回调函数
        THREAD_STATUS status;		//线程的运行状态
        Timeout keepAliveTime;		//线程可以空闲滞留的时间，单位为毫秒
    }ThreadObject;

    class ThreadFactory
    {
    private:
        ThreadFactory();
    public:
        static ThreadFactory *Instance()
        {
            static ThreadFactory factory;
            return &factory;
        }

        virtual ~ThreadFactory();

    public:
        /**
         * 创建线程对象
         * @param object
         * @param callFunc
         * @param status
         * @param pthreadFunc
         * @param param
         * @return
         */
        boost::shared_ptr<THREAD_OBJECT> CreateThreadObject(
                void *object, pthread_func callFunc, Timeout keepAliveTime,
                THREAD_STATUS status, pthread_func pthreadFunc, void *param);

		bool DestroyThreadObject(const ThreadObject *object, const useconds_t us);

    private:
        pthread_attr_t m_attr;
    };

}
#endif //LYNETX_THREADFACTORY_H
