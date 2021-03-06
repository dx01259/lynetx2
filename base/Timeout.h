//
// Created by DengXu on 2016/10/12.
//

#ifndef LYNETX_TIMEOUT_H
#define LYNETX_TIMEOUT_H

#include <sys/time.h>

namespace lynetx {

    //秒，毫秒，微秒，纳秒，皮秒
    class Timeout
    {
    public:
        /**
         * 设置超时时间，单位是毫秒
         * @param to 多长时间之后超时
         * @return
         */
        Timeout(const unsigned long to=0);
        virtual ~Timeout();

    public:
        /**
         * 设置超时时间，单位是毫秒
         * @param out 毫秒数
         */
        void Init(const unsigned long out);

        /**
         * 重新初始化超时对象
         */
        void Reset();

        /**
         * 开始启动超时计时器
         * @return
         */
        unsigned long Start();

        /**
         * 设置超时的毫秒数
         * @param out
         */
        void SetTimeout(const unsigned long out);

        /**
         * 判断是否超时
         * @return 如果超时返回true，否则返回false
         */
        bool IsTimeout() const;

        /**
         * 计算还启动定时器之后，流失的时间
         * @return 返回流失的时间值
         */
        unsigned long Elapse() const;

        /**
         * 计算剩余多少时间，就会超时
         * @return 返回剩余的时间值
         */
        unsigned long Timeleft();

        /**
         * 获取本地此时此刻的服务器的UTC时间
         * @return 返回UTC时间
         */
        unsigned long TimeGetTime() const;

        /**
         * 将spec参数的时间值，累加minisec毫秒数
         * @param spec 需要变更的时间
         * @param minisec 需要累加的时间值，单位是毫秒
         * @return 成功返回true，否则返回false
         */
        static bool SetTimespecLeftNow(struct timespec &spec, const unsigned long &millisecond);

        /**
         * 返回当前时间对象
         * @return 获取当前时间，返回timespec对象
         */
        struct timespec *GetLocalTimespec();

    protected:
        bool  m_started;
        unsigned long m_startTime;
        unsigned long m_timeout;
        struct timespec m_spec;
    };
}
#endif //LYNETX_TIMEOUT_H
