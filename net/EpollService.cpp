//
// Created by DengXu on 2016/10/10.
//

#include "EpollService.h"
#include "LoggerManager.h"

namespace lynetx {

    EpollService::EpollService():
            m_isStarted(false)
    {
    }

    EpollService::EpollService(const AsyncSocket sock, const EpollEvent epollEvent):
            m_isStarted(false)
    {
        this->m_AsyncSocket = sock;
        this->m_EpollEvent  = epollEvent;
    }

    void EpollService::SetAsyncSocket(const AsyncSocket sock)
    {
        if(!this->m_isStarted){
            this->m_AsyncSocket = sock;
        } else {
            LoggerManager::Instance()->GetSysLogger()->Sys(
                    LOGGER_SYS, 120,"The EpollService object is running that can't set it.");
        }
    }

    bool EpollService::Start(const char *ip, const short port, pthread_func callFunc)
    {
        if (NULL != ip)
        {
            try {
                this->m_AsyncSocket.InitSocket(ip, true, port);

            }
            catch (BaseException baseException)
            {

            }
            catch (exception e)
            {

            }
        }

        return false;
    }

    bool EpollService::Stop()
    {
        return false;
    }

    void *EpollService::HanderEvent(void *parameter)
    {
        return EpollObject::HanderEvent(parameter);
    }
}