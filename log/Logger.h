//
// Created by DengXu on 2016/10/14.
//

#ifndef LYNETX_LOGGER_H
#define LYNETX_LOGGER_H

#include <stdio.h>
#include <string>

namespace lynetx {

    enum LOGGER_LEVEL{LOGGER_SYS, LOGGER_ERR, LOGGER_INFO, LOGGER_DEBUG};

    class Logger
    {
    public:
        Logger(const char *path);

    public:
        ssize_t Sys(const LOGGER_LEVEL level, const size_t length,
                    const char *fmt, ...);
        ssize_t Error(const LOGGER_LEVEL level, const size_t length,
                      const char *fmt, ...);
        ssize_t Info(const LOGGER_LEVEL level, const size_t length,
                     const char *fmt, ...);
        ssize_t Debug(const LOGGER_LEVEL level, const size_t length,
                      const char *fmt, ...);

    protected:
        ssize_t LogDoit(const LOGGER_LEVEL level, const size_t length,
                        const char *fmt, va_list arg);
        ssize_t LogPuts(const char *msg, const size_t length);
    private:
        std::string m_logPath;
    };
}
#endif //LYNETX_LOGGER_H
