//
// Created by DengXu on 2016/10/14.
//

#include "Logger.h"
#include <limits.h>
#include <vector>

using namespace std;

namespace lynetx {

    Logger::Logger(const char *path)
    {
        ssize_t length = strlen(path);
        if (length > 0)
        {
            this->m_logPath.reserve(length + 1);
            memcpy(&this->m_logPath[0], path, length);
        }
    }

    ssize_t Logger::Sys(const LOGGER_LEVEL level, const size_t length, const char *fmt, ...)
    {
        ssize_t len = 0;
        va_list arg;
        va_start(arg, fmt);
        len = LogDoit(level, length, fmt, arg);
        va_end(arg);
        return len;
    }

    ssize_t Logger::Error(const LOGGER_LEVEL level, const size_t length, const char *fmt, ...)
    {
        ssize_t len = 0;
        va_list arg;
        va_start(arg, fmt);
        len = LogDoit(level, length, fmt, arg);
        va_end(arg);
        return len;
    }

    ssize_t Logger::Info(const LOGGER_LEVEL level, const size_t length, const char *fmt, ...)
    {
        ssize_t len = 0;
        va_list arg;
        va_start(arg, fmt);
        len = LogDoit(level, length, fmt, arg);
        va_end(arg);
        return len;
    }

    ssize_t Logger::Debug(const LOGGER_LEVEL level, const size_t length, const char *fmt, ...)
    {
        ssize_t len = 0;
        va_list arg;
        va_start(arg, fmt);
        len = LogDoit(level, length, fmt, arg);
        va_end(arg);
        return len;
    }

    ssize_t Logger::LogDoit(const LOGGER_LEVEL level, const size_t length, const char *fmt, va_list arg)
    {
        try {

            if (length < 2040)
            {
                char strTemp[PATH_MAX];
                bzero(strTemp, sizeof(strTemp));
                vsnprintf(strTemp, sizeof(strTemp), fmt, arg);
                return LogPuts(strTemp, strlen(strTemp));
            } else {
                vector<char> strTemp(length+1);
                bzero(&strTemp[0], length);
                vsnprintf(&strTemp[0], length, fmt, arg);
                return LogPuts(&strTemp[0], strlen(&strTemp[0]));
            }
        }catch (...){
            printf("the exception from write logger %d#%s", __LINE__, __FILE__);
        }

        return 0;
    }

    ssize_t Logger::LogPuts(const char *msg, const size_t length)
    {
        printf("%s\n", msg);//暂时写成这个
        return length;
    }

}