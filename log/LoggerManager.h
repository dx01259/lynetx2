//
// Created by DengXu on 2016/10/14.
//

#ifndef LYNETX_LOGGERMANAGER_H
#define LYNETX_LOGGERMANAGER_H

#include "Logger.h"

namespace lynetx{

    class LoggerManager
    {
    public:
        static LoggerManager *Instance()
        {
            static LoggerManager loggerManager;
            return &loggerManager;
        }

    public:
        inline Logger *GetSysLogger(){ return &this->m_SysLogger;}
        inline Logger *GetModuleLogger(){ return &this->m_ModuleLogger;}

    protected:
        Logger m_SysLogger;
        Logger m_ModuleLogger;
    private:
        LoggerManager():m_SysLogger(""),m_ModuleLogger(""){}
    };

}

#endif //LYNETX_LOGGERMANAGER_H
