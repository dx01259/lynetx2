//
// Created by DengXu on 2016/10/10.
//

#ifndef LYNETX_BASETIME_H
#define LYNETX_BASETIME_H

#include <sys/time.h>
#include <string>

using namespace std;

namespace lynetx {

    class BaseTime
    {
    public:
        /**
         * 设置UTC时间
         * @param utc UTC时间参数
         * @return
         */
        BaseTime(time_t utc=0);

        /**
         * 根据年月日，时分秒，设置时间值
         * @param year 年 必须大于1900年
         * @param month 月
         * @param day 日
         * @param hour 时
         * @param minute 分
         * @param second 秒
         * @return
         */
        BaseTime(const int year, const int month, const int day,
            const int hour, const int minute, const int second);

        /**
         * 构造函数，实现赋值操作
         * @param other 被赋值的另一个对象
         * @return
         */
        BaseTime &operator=(const BaseTime &other)
        {
            if (&other != this)
            {
                this->m_time = other.m_time;
            }
            return *this;
        }

        /**
         * 拷贝构造函数
         * @param other
         * @return
         */
        BaseTime(const BaseTime &other)
        {
            this->operator=(other);
        }

        /**
         * 析构函数，释放资源
         */
        virtual ~BaseTime();

    public:
        /**
         * 等于运算符重载
         * @param other 被比较的对象
         * @return 等于被比较对象则返回true，否则返回false
         */
        bool operator == (const BaseTime &other);

        /**
         * 不等于运算符重载
         * @param other 被比较的对象
         * @return 不等于被比较对象则返回true，否则返回false
         */
        bool operator != (const BaseTime &other);

        /**
         * 大于等于运算符重载
         * @param other 被比较的对象
         * @return 大于等于被比较对象则返回true，否则返回false
         */
        bool operator >= (const BaseTime &other);

        /**
         * 小于等于运算符重载
         * @param other 被比较的对象
         * @return 小于等于被比较对象则返回true，否则返回false
         */
        bool operator <= (const BaseTime &other);

        /**
         * 大于运算符重载
         * @param other 被比较的对象
         * @return 大于被比较对象则返回true，否则返回false
         */
        bool operator >  (const BaseTime &other);

        /**
         * 小于运算符重载
         * @param other 被比较的对象
         * @return 小于被比较对象则返回true，否则返回false
         */
        bool operator <  (const BaseTime &other);

    public:
        /**
         * 获取UTC时间
         * @return 返回UTC时间
         */
        time_t GetUtcTime();

        /**
         * 获取时间
         * @return 返回时间对象
         */
        struct tm GetTime() const;

        /**
         * 设置时间为服务器当前时间
         */
        void SetCurrentTime();

        /**
         * 将时间对象字符串化
         * 按照年月日时分秒 "%04u-%02u-%02u %02u:%02u:%02"
         * @return 返回字符串化的值
         */
        string ToString();

        /**
         * 将时间对象字符串化
         * 按照年月日 "%04u-%02u-%02u"
         * @return 返回字符串化的值
         */
        string ToDayString();
    private:
        struct tm m_time;
    };
}
#endif //LYNETX_BASETIME_H
