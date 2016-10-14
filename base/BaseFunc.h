//
// Created by DengXu on 2016/10/10.
//

#ifndef LYNETX_BASEFUNC_H
#define LYNETX_BASEFUNC_H

#include "BaseTime.h"
#include <sys/types.h>

namespace lynetx {

    class BaseFunc
    {
    public:
        /**
         * 判断BaseTime时间是不是有效的
         * @param time BaseTime时间对象
         * @return 有效返回true，否则返回false
         */
        static bool InvalidTime(const BaseTime &time);

        /**
         * 创建目录函数
         * @param pathname 需要创建的目录路径
         * @param mode 创建目录的权限，例如0777
         * @return 成功返回0，否则返回非零
         */
        static int mkdir_p(const char *pathname, mode_t mode);

        template <class T>
        static inline bool min(const T a, const T b)
        {
            return a<b ? true : false;
        }

        template <class T>
        static inline bool max(const T a, const T b)
        {
            return a > b ? true : false;
        }

    private:
        BaseFunc();
    };
}

#endif //LYNETX_BASEFUNC_H
